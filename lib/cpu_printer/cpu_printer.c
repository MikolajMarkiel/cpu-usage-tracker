#include "cpu_analyser.h"
#include <stdio.h>
#include <stdlib.h>

int print_cpu_data(cpu_data_array_t *arr) {
  if(arr == NULL){
    return 1;
  }
  for (int i = 0; i < arr->quantity; i++) {
    printf("cpu%d:%3d%% | ", i, arr->cpu[i]->usage);
  }
  fflush(stdout);
  printf("\r");
  return 0;
}
