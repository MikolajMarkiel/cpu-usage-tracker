#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

int my_log(const char *format, ...);
int log_init(const char *filename);
int shutdown_logger(void);
void test_logger(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: LOGGER_H */
