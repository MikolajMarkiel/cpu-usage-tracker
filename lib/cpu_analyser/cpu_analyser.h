#ifndef CPU_ANALYSER_H
#define CPU_ANALYSER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __clang__
#pragma clang diagnostic ignored "-Wpadded"
// https://stackoverflow.com/questions/20184259/what-does-the-padding-class-tester-with-4-bytes-warning-mean
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
// https://github.com/llvm/llvm-project/issues/53438
#endif //__clang__

#include "cpu_reader.h"

typedef struct {
  cpu_raw_data_t *raw_curr;
  cpu_raw_data_t *raw_prev;
  unsigned int usage;
} cpu_data_t;

typedef struct {
  cpu_data_t **cpu;
  int quantity;
} cpu_data_array_t;

int analyze_data(cpu_data_t *cpu);
int delete_cpu_data_array(cpu_data_array_t *cpu);
int cpu_analyser_init(cpu_data_array_t *arr);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: CPU_ANALYSER_H */
