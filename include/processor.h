#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();
 private:
  long int prev_user{-1};
  long int prev_nice{-1};
  long int prev_system{-1};
  long int prev_idle{-1};
  long int prev_iowait{-1};
  long int prev_irq{-1};
  long int prev_softirq{-1};
  long int prev_steal{-1};
};

#endif