#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "logger.h"

int main() {
  log_init("log.txt");
  printf("hello main\n");
  my_log("log message from main %s", "test");
  shutdown_logger();
  return EXIT_SUCCESS;
}

