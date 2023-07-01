#include <stdio.h>
#include <stdlib.h>
#include "watchdog.h"
#include "logger.h"

wd_test_t *first;

int wd_test_init(wd_test_t* test, char* msg){
  if (test == NULL){
    return 1;
  }
  static wd_test_t *prev = NULL;
 if(prev == NULL){
   first = test;
 } else {
   prev->next = test;
 } 
 test->prev = prev;
 test->next = NULL;
 test->val = 0;
 test->message = msg;
 prev = test;
 return 0;
}

int wd_feed(wd_test_t* test){
  if (test == NULL){
    return 1;
  }
  test->val = 0;
  return 0;
}

int wd_check_test(wd_test_t *test){
  if (test == NULL){
    return 1;
  }
  if(test->val == 1){
    my_log("watchdog error: %s", test->message);
    printf("\nwatchdog error: %s\n", test->message);
    return 2;
  }
  test->val = 1;
  return 0;
}

int wd_check_all(){
  int err = 0;
  wd_test_t *c_test = first;
  while(c_test != NULL){
    if(wd_check_test(c_test)){
      err = 1;
    }
    c_test = c_test->next;
  }
  return err;
}

