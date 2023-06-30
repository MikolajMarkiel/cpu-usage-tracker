#include "cpu_printer.h"
#include "logger.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("hello main\n");

  // // logger
  // log_init("log.txt");
  // my_log("log message from main %s", "test");
  // shutdown_logger();

  // // cpu_reader
  // cpu_raw_data_t* cpu;
  // cpu = create_cpu_raw_data(1);
  // get_raw_data(cpu);
  // delete_raw_data(cpu);
  return EXIT_SUCCESS;
}
