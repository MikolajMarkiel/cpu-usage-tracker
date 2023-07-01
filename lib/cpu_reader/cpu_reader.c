#include "cpu_reader.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int skip_lines(FILE *fp, int num) {
  char ch;
  do {
    ch = (char)getc(fp);
    num = (ch == '\n') ? (num - 1) : num;
    if (ch == EOF) {
      my_log("skip lines error: end of file");
      return 1;
    }
  } while (num);
  return 0;
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
  if (buf == NULL) {
    my_log("get raw data error: null buffer");
    return 1;
  }
  if (buf->id < 0) {
    my_log("get raw data error: wrong id");
    return 2;
  }
  FILE *fp = fopen("/proc/stat", "r");
  if (fp == NULL) {
    my_log("get raw data error: unable to open /proc/stat");
    err = 3;
  } else {
    if (skip_lines(fp, buf->id + 1) == 1) {
      err = 4;
    } else {
      fscanf(fp, "%s ", cpu_num);
      if (cmp_cpu_id(cpu_num, buf->id) != 0) {
        my_log("get raw data error: cpus id not equal");
        err = 5;
      } else {
        fscanf(fp, "%u %u %u %u %u %u %u", &(buf->user), &(buf->nice),
               &(buf->system), &(buf->idle), &(buf->iowait), &(buf->irq),
               &(buf->softirq));
      }
    }
  }
  fclose(fp);
  return err;
}

int delete_raw_data(cpu_raw_data_t *buf) {
  if (buf == NULL) {
    my_log("delete raw data error: null buffer");
    return 1;
  }
  free(buf);
  buf = NULL;
  return 0;
}
