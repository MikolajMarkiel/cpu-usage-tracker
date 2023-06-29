#ifndef CPU_ANALYSER_H
#define CPU_ANALYSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cpu_reader.h"

typedef struct {
  cpu_raw_data_t **raw;
  int usage;
} cpu_data;

typedef struct {
  cpu_data *cpu;
  int quantity;
} cpu_data_array;

cpu_data_array *create_cpu_data_array();
int count_cpu(int *buf);
int analyze_data(cpu_data *cpu);
int delete_cpu_data_array(cpu_data *cpu);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: CPU_ANALYSER_H */
