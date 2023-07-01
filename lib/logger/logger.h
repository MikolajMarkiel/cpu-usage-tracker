#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __clang__
#pragma clang diagnostic ignored "-Wformat-nonliteral"
// https://stackoverflow.com/questions/36120717/correcting-format-string-is-not-a-string-literal-warning
#endif //__clang__

#include <semaphore.h>
#include <pthread.h>

int my_log(char const* format, ...);
int log_init(pthread_mutex_t *log_mutex,  sem_t * full, sem_t* empty, const char *filename);
int flush_message(void);
int shutdown_logger(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: LOGGER_H */
