// #include "cpu_analyser.h"
#include "cpu_printer.h"
#include <logger.h>
#include <stdio.h>
#include <stdlib.h>

int print_cpu_data(cpu_data_array_t *arr) {
  if (arr == NULL) {
    my_log("print cpu data error: null buffer");
    return 1;
  }
  for (int i = 0; i < arr->quantity; i++) {
    printf("cpu%d:%3u%% | ", i, arr->cpu[i]->usage);
  }
  fflush(stdout);
  printf("\r");
  return 0;
}
