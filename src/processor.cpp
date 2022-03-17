#include "processor.h"
#include "linux_parser.h"

// Done: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::vector<std::string> cpu_util = LinuxParser::CpuUtilization();
  const long int usertime = std::stol(cpu_util[0]),
                 nicetime = std::stol(cpu_util[1]),
                 systemtime = std::stol(cpu_util[2]),
                 idletime = std::stol(cpu_util[3]),
                 iowait = std::stol(cpu_util[4]),
                 irq = std::stol(cpu_util[5]),
                 softirq = std::stol(cpu_util[6]),
                 steal = std::stol(cpu_util[7]);
  const float IDLE = idletime + iowait,
              NONE_IDLE = usertime + nicetime + systemtime + irq + softirq + steal,
              TOTAL = IDLE + NONE_IDLE;
  if (prev_user == -1 || prev_nice == -1 || prev_system == -1 || prev_idle == -1 ||
      prev_iowait == -1 || prev_irq == -1 || prev_softirq == -1 || prev_steal == -1) {
    prev_user = usertime;
    prev_nice = nicetime;
    prev_system = systemtime;
    prev_idle = idletime;
    prev_iowait = iowait;
    prev_irq = irq;
    prev_softirq = softirq;
    prev_steal = steal;
    return (TOTAL == 0.0) ? 0.0 : ((TOTAL - IDLE) / TOTAL);
  } else {
    const long int PREV_IDLE = prev_idle + prev_iowait,
                   PREV_NONE_IDLE = prev_user + prev_nice + prev_system +
                                    prev_irq + prev_softirq + prev_steal,
                   PREV_TOTAL = PREV_IDLE + PREV_NONE_IDLE;
    const float TOTAL_DIF = TOTAL - PREV_TOTAL,
                IDLE_DIF = IDLE - PREV_IDLE;
    prev_user = usertime;
    prev_nice = nicetime;
    prev_system = systemtime;
    prev_idle = idletime;
    prev_iowait = iowait;
    prev_irq = irq;
    prev_softirq = softirq;
    prev_steal = steal;
    return (TOTAL_DIF == 0.0) ? 0.0 : ((TOTAL_DIF - IDLE_DIF) / TOTAL_DIF);
  }
}