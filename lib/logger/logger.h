#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __clang__
#pragma clang diagnostic ignored "-Wformat-nonliteral"
// https://stackoverflow.com/questions/36120717/correcting-format-string-is-not-a-string-literal-warning
#endif //__clang__

int my_log(char const* format, ...);
int log_init(const char *filename);
int shutdown_logger(void);
// void test_logger(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: LOGGER_H */
