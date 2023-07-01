#include "cpu_analyser.h"
#include "cpu_reader.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>

static unsigned int get_total(cpu_raw_data_t *buf) {
  return buf->user + buf->nice + buf->system + buf->idle + buf->iowait +
         buf->irq + buf->softirq;
}

static unsigned int get_idle(cpu_raw_data_t *buf) {
  return buf->idle + buf->iowait;
}

static int count_cpu(int *buf) {
  if (buf == NULL) {
    my_log("count cpu error: null buffer");
    return 1;
  }
  *buf = get_nprocs();
  return 0;
}

static cpu_data_t *create_cpu_data(int id) {
  cpu_data_t *buf = (cpu_data_t *)malloc(sizeof(cpu_data_t));
  buf->raw_curr = create_cpu_raw_data(id);
  buf->raw_prev = create_cpu_raw_data(id);
  return buf;
}

static int delete_cpu_data(cpu_data_t *cpu) {
  if (cpu == NULL) {
    my_log("delete cpu error: null buffer");
    return 1;
  }
  if (cpu->raw_curr != NULL) {
    delete_raw_data(cpu->raw_curr);
  }
  if (cpu->raw_prev != NULL) {
    delete_raw_data(cpu->raw_prev);
  }
  free(cpu);
  cpu = NULL;
  return 0;
}

int cpu_analyser_init(cpu_data_array_t *arr) {
  int err;
  if (arr == NULL) {
    my_log("cpu analyser init error: null array");
    return 1;
  }
  if (count_cpu(&(arr->quantity)) != 0) {
    return 2;
  }
  if (arr->quantity < 1) {
    my_log("cpu analyser init error: quantity = 0");
    return 3;
  }
  arr->cpu =
      (cpu_data_t **)malloc((size_t)arr->quantity * sizeof(cpu_data_t *));
  for (int i = 0; i < arr->quantity; i++) {
    arr->cpu[i] = create_cpu_data(i);
  }
  for (int i = 0; i < arr->quantity; i++) {
    err = get_raw_data(arr->cpu[i]->raw_prev);
    if (err) {
      my_log("cpu analyser error: get raw data of cpu%d", i);
      return err + 3;
    }
  }
  return 0;
}

int delete_cpu_data_array(cpu_data_array_t *arr) {
  int err = 0;
  for (int i = 0; i < arr->quantity; i++) {
    if (delete_cpu_data(arr->cpu[i])) {
      err++;
      my_log("delete cpu error: cpu%d", i);
    }
  }
  free(arr->cpu);
  return err; // num of failed deleted cpu_data
}

int analyze_data(cpu_data_t *cpu) {
  if (cpu->raw_curr == NULL) {
    my_log("analyze data error: null raw current buffer");
    return 1;
  }
  if (cpu->raw_prev == NULL) {
    my_log("analyze data error: null raw prev buffer");
    return 2;
  }
  unsigned int idle_curr = get_idle(cpu->raw_curr);
  unsigned int total_curr = get_total(cpu->raw_curr);
  unsigned int idle_prev = get_idle(cpu->raw_prev);
  unsigned int total_prev = get_total(cpu->raw_prev);
  unsigned int idle_d = idle_curr - idle_prev;
  unsigned int total_d = total_curr - total_prev;
  memcpy(cpu->raw_prev, cpu->raw_curr, sizeof(cpu_raw_data_t));
  if (total_d == 0) {
    my_log("analyze data error: divide by zero");
    return 3;
  }
  cpu->usage = (100 * (total_d - idle_d)) / total_d;
  return 0;
}
