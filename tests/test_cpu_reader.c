#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "cpu_reader.h"

int main(void)
{
  cpu_raw_data_t* cpu;
  cpu = create_cpu_raw_data(-1);
  assert(get_raw_data(NULL) == 1);
  assert(get_raw_data(cpu) == 2);
  cpu->id = 1000;
  assert(get_raw_data(cpu) == 4);
  cpu->id = 0;
  assert(get_raw_data(cpu) == 0);
  assert (delete_raw_data(cpu) == 0);
  assert (delete_raw_data(NULL) == 1);
  return EXIT_SUCCESS;
}
