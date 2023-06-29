#ifndef LOGGER_H
#define LOGGER_H


int my_log(const char *format, ...);

int log_init(const char *filename);
int shutdown_logger(void);

void test_logger(void);
#endif /* end of include guard: LOGGER_H */
