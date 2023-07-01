#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

static sem_t full, empty;
static pthread_mutex_t log_mutex;
static pthread_t t1;

static int status = 0;

static void *logger() {
  while (!status) {
    sem_wait(&full);
    assert(flush_message() == status);
    sem_post(&empty);
  }
  return NULL;
}

int main() {
  assert(log_init(&log_mutex, &full, &empty, "test_log.txt") == 0);
  pthread_create(&t1, NULL, logger, NULL);
  for (int i = 0; i < 200; i++) {
    assert(my_log("test %u", i) == 0);
  }
  sleep(1);
  status = 1;
  sem_post(&full);
  pthread_join(t1, NULL);
  assert(shutdown_logger() == 0);
  assert(log_init(&log_mutex, &full, &empty, "test_log.txt") == 0);
  assert(shutdown_logger() == 0);
  return EXIT_SUCCESS;
}
