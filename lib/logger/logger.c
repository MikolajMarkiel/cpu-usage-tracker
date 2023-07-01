#include "logger.h"
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define LOG_BUFFER 20

static FILE *logfile;
static const char *f_name;
static char *log_buf[LOG_BUFFER];

static sem_t *log_full_sem;
static sem_t *log_empty_sem;
static pthread_mutex_t *log_buf_mutex;

static int write_to_file(char *msg, const char *mode) {
  if (f_name == NULL) {
    fprintf(stderr, "log error: wrong file name\n");
    return 1;
  }
  if ((logfile = fopen(f_name, mode)) == NULL) {
    fprintf(stderr, "log error: opening log file\n");
    return 2;
  }
  fprintf(logfile, "%s\n", msg);
  fclose(logfile);
  return 0;
}

int flush_message(void) {
  static int buf_offset = 0;
  if (log_buf[buf_offset] == NULL) {
    buf_offset = (buf_offset + 1) % LOG_BUFFER;
    return 1;
  }
  write_to_file(log_buf[buf_offset], "a");
  free(log_buf[buf_offset]);
  log_buf[buf_offset] = NULL;
  buf_offset = (buf_offset + 1) % LOG_BUFFER;
  return 0;
}

int shutdown_logger(void) {
  pthread_mutex_destroy(log_buf_mutex);
  sem_destroy(log_full_sem);
  sem_destroy(log_empty_sem);
  return 0;
}

int log_init(pthread_mutex_t *log_mutex, sem_t *full, sem_t *empty,
             const char *filename) {
  if (log_mutex == NULL || full == NULL || empty == NULL || filename == NULL) {
    return 1;
  }
  f_name = filename;
  log_buf_mutex = log_mutex;
  log_full_sem = full;
  log_empty_sem = empty;
  if (pthread_mutex_init(log_buf_mutex, NULL)) {
    return 2;
  }
  if (sem_init(log_full_sem, 0, 0)) {
    return 3;
  }
  if (sem_init(log_empty_sem, 0, LOG_BUFFER)) {
    return 4;
  }
  return 0;
}

int my_log(char const *format, ...) {
  static int buf_offset = 0;
  va_list args_1, args_2;
  char *buf;
  size_t len;
  if (f_name == NULL) {
    return 1;
  }
  va_start(args_1, format);
  len = (size_t)vsnprintf(NULL, 0, format, args_1);
  va_end(args_1);
  if (len == 0) {
    fprintf(stderr, "log error: empty message\n");
    return 2;
  }
  buf = (char *)malloc((len + 1) * sizeof(char *));
  va_start(args_2, format);
  vsprintf(buf, format, args_2);
  va_end(args_2);

  sem_wait(log_empty_sem);
  pthread_mutex_lock(log_buf_mutex);
  if (log_buf[buf_offset] != NULL) {
    free(buf);
    fprintf(stderr, "log error: dropped message\n");
    sem_post(log_empty_sem);
    return 3;
  }
  log_buf[buf_offset] = buf;
  buf_offset = (buf_offset + 1) % LOG_BUFFER;
  pthread_mutex_unlock(log_buf_mutex);
  sem_post(log_full_sem);
  return 0;
}
