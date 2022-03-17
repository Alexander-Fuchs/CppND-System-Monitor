#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using std::stol;


Process::Process(int pid) {
  pid_ = pid;
}

// Done: Return this process's ID
int Process::Pid() const {
  return pid_;
}

// Done: Return this process's CPU utilization
float Process::CpuUtilization() const {
  return (float)LinuxParser::ActiveJiffies(Pid()) /
         (float)(LinuxParser::UpTime() - LinuxParser::UpTime(Pid()));
}

// Done: Return the command that generated this process
string Process::Command() const {
  return LinuxParser::Command(Pid());
}

// Done: Return this process's memory utilization
string Process::Ram() const {
  return LinuxParser::Ram(Pid());
}

// Done: Return the user (name) that generated this process
string Process::User() const {
  return LinuxParser::User(Pid());
}

// Done: Return the age of this process (in seconds)
long int Process::UpTime() const {
  return LinuxParser::UpTime() - LinuxParser::UpTime(Pid());
}

// Done: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
  return stol(Ram()) < stol(a.Ram());
}