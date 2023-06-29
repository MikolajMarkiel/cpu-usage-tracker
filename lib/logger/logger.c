#include <pthread.h>
#include <semaphore.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define LOG_BUFFER 20

enum logger_status { log_exit, log_run };

enum logger_status status = log_exit;

FILE *logfile;
const char *f_name;
char *log_buf[LOG_BUFFER];

pthread_t logger_thread;

sem_t log_full_sem;
sem_t log_empty_sem;

pthread_mutex_t log_buf_mutex;

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

static void *logger(void *arg) {
  static int buf_offset = 0;
  while (1) { 
    sem_wait(&log_full_sem);
    if (status == log_exit) {
      break;
    }
    if (log_buf[buf_offset] != NULL) {
      write_to_file(log_buf[buf_offset], "a");
      free(log_buf[buf_offset]);
      log_buf[buf_offset] = NULL;
    } else {
      fprintf(stderr, "log error: trying to insert null message\n");
    }
    sem_post(&log_empty_sem);
    buf_offset = (buf_offset + 1) % LOG_BUFFER;
  }
  return NULL;
}

int shutdown_logger(void) {
  status = log_exit;
  sem_post(&log_full_sem);
  pthread_join(logger_thread, NULL); 
  pthread_mutex_destroy(&log_buf_mutex);
  sem_destroy(&log_full_sem);
  sem_destroy(&log_empty_sem);
  return 0;
}

int log_init(const char *filename) {
  f_name = filename;
  status = log_run;
  if (pthread_mutex_init(&log_buf_mutex, NULL)) {
    return 1;
  }
  if (sem_init(&log_full_sem, 0, 0)) {
    return 2;
  }
  if (sem_init(&log_empty_sem, 0, LOG_BUFFER)) {
    return 3;
  }
  if (pthread_create(&logger_thread, NULL, &logger, NULL)) {
    return 4;
  }
  return 0;
}

int my_log(const char *format, ...) {
  static int buf_offset = 0;
  va_list args_1, args_2;
  char *buf;
  int len;

  va_start(args_1, format);
  len = vsnprintf(NULL, 0, format, args_1);
  va_end(args_1);
  if (len == 0) {
    fprintf(stderr, "log error: empty message\n");
    return 1;
  }
  buf = (char *)malloc((len + 1) * sizeof(char *));
  va_start(args_2, format);
  vsprintf(buf, format, args_2);
  va_end(args_2);

  sem_wait(&log_empty_sem);
  pthread_mutex_lock(&log_buf_mutex);
  if (log_buf[buf_offset] != NULL) {
    free(buf);
    fprintf(stderr, "log error: dropped message\n");
    sem_post(&log_empty_sem);
    return 1;
  }
  log_buf[buf_offset] = buf;
  buf_offset = (buf_offset + 1) % LOG_BUFFER;
  pthread_mutex_unlock(&log_buf_mutex);
  sem_post(&log_full_sem);
  return 0;
}
