#include "cpu_analyser.h"
#include "cpu_printer.h"
#include "cpu_reader.h"
#include "logger.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LOG_FILENAME "log.txt"

static pthread_t t[3];
static sem_t sem_get_data, sem_analyse, sem_print;
static cpu_data_array_t cpu_arr;

static void *reader() {
  while (1) {
    sem_wait(&sem_get_data);
    for (int i = 0; i < cpu_arr.quantity; i++) {
      get_raw_data(cpu_arr.cpu[i]->raw_curr);
      sem_post(&sem_analyse);
    }
  }
  return NULL;
}

static void *analyser() {
  while(1){
    for (int cnt = 0; cnt < cpu_arr.quantity; cnt++) {
      sem_wait(&sem_analyse);
      analyze_data(cpu_arr.cpu[cnt]);
    }
    sem_post(&sem_print);
  }
    return NULL;
}

static void *printer() {
  while(1){
    sleep(1);
    sem_post(&sem_get_data);
    sem_wait(&sem_print);
    print_cpu_data(&cpu_arr);
  }
  return NULL;

}

int main() {
  log_init(LOG_FILENAME);
  if (cpu_analyser_init(&cpu_arr)) {
    return 1;
  }
  if (sem_init(&sem_get_data, 0, 0) || //
      sem_init(&sem_analyse, 0, 0) ||  //
      sem_init(&sem_print, 0, 0)) {
    return 2;
  }

  if (pthread_create(&t[0], NULL, reader, NULL) ||
      pthread_create(&t[1], NULL, analyser, NULL) ||
      pthread_create(&t[2], NULL, printer, NULL)) {
    return 3;
  }

  if (pthread_join(t[0], NULL) || //
      pthread_join(t[1], NULL) || //
      pthread_join(t[2], NULL)) {
    return 4;
  }
  sem_destroy(&sem_get_data);
  sem_destroy(&sem_analyse);
  sem_destroy(&sem_print);

  delete_cpu_data_array(&cpu_arr);
  shutdown_logger();

  return EXIT_SUCCESS;
}
