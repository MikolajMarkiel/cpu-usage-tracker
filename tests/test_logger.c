#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"

int main() {
  // TODO - change tests for new version of logger
  // assert(write_to_file("test", "a") == 1);
  assert(log_init("test_log.txt") == 0);
  // assert(write_to_file("test", "a") == 0);
  for (int i = 0; i < 200; i++) {
    assert(my_log("test %u", i) == 0);
  }
  assert(shutdown_logger() == 0);
  assert(log_init("test_log.txt") == 0);
  return EXIT_SUCCESS;
}
