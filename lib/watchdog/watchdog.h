#ifndef WATCHDOG_H
#define WATCHDOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"

  typedef struct wd_test{
    struct wd_test* prev;
    struct wd_test* next;
    bool val;
    char* message;
  } wd_test_t;

int wd_test_init(wd_test_t* test, char* msg);
int wd_feed(wd_test_t* test);
int wd_check_test(wd_test_t *test);
int wd_check_all();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: WATCHDOG_H */
