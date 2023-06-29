#include "cpu_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void next_line(FILE *fp)
{
    char ch;
    do ch = getc(fp);
    while(ch != '\n' || ch == EOF);
    return;
}

cpu_raw_data_t* create_cpu_raw_data(int id){
  // TODO
  return NULL;
}

int get_raw_data(cpu_raw_data_t* buf){
  // TODO
  return 0;
}

int delete_raw_data(cpu_raw_data_t* buf){
  // TODO
  return 0;
}

int main(){
  // TODO
  return EXIT_SUCCESS;
}
