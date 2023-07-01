#ifndef WATCHDOG_H
#define WATCHDOG_H

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __clang__
#pragma clang diagnostic ignored "-Wpadded"
// https://stackoverflow.com/questions/20184259/what-does-the-padding-class-tester-with-4-bytes-warning-mean
  
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
// https://github.com/llvm/llvm-project/issues/53438
#endif //__clang__


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
int wd_check_all(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: WATCHDOG_H */
