#include "cpu_analyser.h"
#include "cpu_printer.h"
#include "cpu_reader.h"
#include "logger.h"
#include "watchdog.h"
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LOG_FILENAME "log.txt"

static pthread_t t[4];
static sem_t sem_reader, sem_analyse, sem_print;
static cpu_data_array_t cpu_arr;

static wd_test_t wd_reader;
static wd_test_t wd_analyzer;
static wd_test_t wd_printer;

static enum {
  run,
  term,
} process_state;

static void shutdown_app() {
  process_state = term;
  sem_post(&sem_print);
  sem_post(&sem_analyse);
  sem_post(&sem_reader);
  return;
}

static void handle_sigterm() {
  printf("\nterminating...\n");
  fflush(stdout);
  shutdown_app();
}

static void *reader() {
  while (1) {
    wd_feed(&wd_reader);
    sem_wait(&sem_reader);
    if (process_state == term) {
      break;
    }
    for (int i = 0; i < cpu_arr.quantity; i++) {
      get_raw_data(cpu_arr.cpu[i]->raw_curr);
      sem_post(&sem_analyse);
    }
  }
  pthread_exit(0);
}

static void *analyser() {
  while (1) {
    for (int cnt = 0; cnt < cpu_arr.quantity; cnt++) {
      wd_feed(&wd_analyzer);
      sem_wait(&sem_analyse);
      if (process_state == term) {
        break;
      }
      analyze_data(cpu_arr.cpu[cnt]);
    }
    if (process_state == term) {
      break;
    }
    sem_post(&sem_print);
  }
  pthread_exit(0);
}

static void *printer() {
  while (1) {
    wd_feed(&wd_printer);
    sleep(1);
    sem_post(&sem_reader);
    sem_wait(&sem_print);
    if (process_state == term) {
      break;
    }
    print_cpu_data(&cpu_arr);
  }
  pthread_exit(0);
}

static void *watchdog() {
  static int err;
  while (1) {
    sleep(2);
    err = wd_check_all();
    if (err) {
      my_log("ERROR: watchdog reset");
      printf("ERROR: watchdog reset\n");
      shutdown_app();
    }
    if (process_state == term) {
      break;
    }
  }
  pthread_exit(0);
}

int main() {
  signal(SIGTERM, &handle_sigterm);
  log_init(LOG_FILENAME);

  wd_test_init(&wd_reader, "reader");
  wd_test_init(&wd_analyzer, "analyzer");
  wd_test_init(&wd_printer, "printer");

  if (cpu_analyser_init(&cpu_arr)) {
    return 1;
  }

  if (sem_init(&sem_reader, 0, 0) ||  //
      sem_init(&sem_analyse, 0, 0) || //
      sem_init(&sem_print, 0, 0)) {
    return 2;
  }

  if (pthread_create(&t[0], NULL, reader, NULL) ||
      pthread_create(&t[1], NULL, analyser, NULL) ||
      pthread_create(&t[2], NULL, printer, NULL) ||
      pthread_create(&t[3], NULL, watchdog, NULL)) {
    return 3;
  }

  for (size_t i = 0; i < sizeof(t) / sizeof(pthread_t); i++) {
    if (pthread_join(t[i], NULL)) {
      return 4;
    }
  }

  sem_destroy(&sem_reader);
  sem_destroy(&sem_analyse);
  sem_destroy(&sem_print);

  delete_cpu_data_array(&cpu_arr);

  shutdown_logger();

  printf("end of program\n");

  return EXIT_SUCCESS;
}
