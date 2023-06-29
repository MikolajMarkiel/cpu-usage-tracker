#include "cpu_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void skip_lines(FILE *fp, int num) {
  char ch;
  do {
    ch = getc(fp);
    num = (ch == '\n') ? (num - 1) : num;
  } while ((num) && (ch != EOF));
  return;
}

static int cmp_cpu_id(char *str, int id) {
  char cpu_id[6];
  sprintf(cpu_id, "cpu%d", id);
  return (strcmp(str, cpu_id) & 1); 
}

cpu_raw_data_t *create_cpu_raw_data(int id) {
  cpu_raw_data_t *buf = (cpu_raw_data_t *)malloc(sizeof(cpu_raw_data_t));
  buf->id = id;
  return buf;
}

int get_raw_data(cpu_raw_data_t *buf) {
  int err = 0;
  char cpu_num[6];
  FILE *fp = fopen("/proc/stat", "r");
  skip_lines(fp, buf->id + 1);
  fscanf(fp, "%s ", cpu_num);
  if (cmp_cpu_id(cpu_num, buf->id) == 0) {
    fscanf(fp, "%u %u %u %u %u %u %u", &(buf->user), &(buf->nice),
           &(buf->system), &(buf->idle), &(buf->iowait), &(buf->irq),
           &(buf->softirq));
  } else {
    err = 1;
  }
  fclose(fp);
  return err;
}

void delete_raw_data(cpu_raw_data_t *buf) {
  free(buf);
  buf = NULL;
  return;
}
