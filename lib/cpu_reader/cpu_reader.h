#ifndef CPU_READER_H
#define CPU_READER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  int id;
  unsigned long user;
  unsigned long nice;
  unsigned long system;
  unsigned long idle;
  unsigned long iowait;
  unsigned long irq;
  unsigned long softirq;
} cpu_raw_data_t;

cpu_raw_data_t* create_cpu_raw_data(int id);
int get_raw_data(cpu_raw_data_t* buf);
int delete_raw_data(cpu_raw_data_t* buf);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: CPU_READER_H */
