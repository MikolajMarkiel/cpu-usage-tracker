#include "cpu_analyser.h"
#include "cpu_printer.h"
#include "cpu_reader.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static cpu_data_array_t arr;

int main() {
  assert(print_cpu_data(NULL) == 1);
  cpu_analyser_init(&arr);
  for (int j = 0; j < 2; j++) {
    sleep(1);
    for (int i = 0; i < arr.quantity; i++) {
      get_raw_data(arr.cpu[i]->raw_curr);
      analyze_data(arr.cpu[i]);
    }
    assert(print_cpu_data(&arr) == 0);
  }
  printf("\n");
  delete_cpu_data_array(&arr);
  return EXIT_SUCCESS;
}
