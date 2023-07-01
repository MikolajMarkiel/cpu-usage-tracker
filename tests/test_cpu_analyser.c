#include "cpu_analyser.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "logger.h"


#define LOG_FILENAME "log_test.txt"

static cpu_data_array_t arr;

int main() {
  log_init(LOG_FILENAME);
  assert(cpu_analyser_init(NULL) == 1);
  assert(cpu_analyser_init(&arr) == 0);
  for (int j = 0; j < 2; j++) {
    sleep(1);
    for (int i = 0; i < arr.quantity; i++) {
      assert(arr.cpu[i] != NULL);
      assert(arr.cpu[i]->raw_curr != NULL);
      assert(arr.cpu[i]->raw_prev != NULL);
      get_raw_data(arr.cpu[i]->raw_curr);
      analyze_data(arr.cpu[i]);
      printf("cpu%d:%3u%% | ", i, arr.cpu[i]->usage);
      assert(memcmp(arr.cpu[i]->raw_curr, arr.cpu[i]->raw_prev,
                    sizeof(cpu_raw_data_t)) == 0);
    }
    fflush(stdout);
    printf("\r");
  }
  printf("\n");
  delete_cpu_data_array(&arr);
  return EXIT_SUCCESS;
}
