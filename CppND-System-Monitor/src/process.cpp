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


Process::Process(int pid) : pid_(pid){CpuUtil = Process::CpuUtilization();}
// TODO: Return this process's ID
int Process::Pid() { return pid_; }
int Process::GetPid() const {
    int TempPid = pid_;
    return TempPid;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  float ProcessCpuUtil = 0.0;
  long upTime = LinuxParser::UpTime();

  std::string line, key, value;
  const int TempPid = GetPid();
  std::string TempString = std::to_string(TempPid);
  std::ifstream filestream(LinuxParser::kProcDirectory + TempString +
                           LinuxParser::kStatFilename);

  int uTimeClkTks = 0;
  int sTimeClkTks = 0;
  int cuTimeClkTks = 0;
  int csTimeClkTks = 0;
  float startTimeClkTks = 0.0;

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), '(', '_');
      std::replace(line.begin(), line.end(), ')', '_');
      std::replace(line.begin(), line.end(), '-', '_');
      std::istringstream linestream(line);
      std::istream_iterator<std::string> beg(linestream), end;
      std::vector<std::string> vec(beg, end);
      uTimeClkTks = std::stoi(vec[13]);
      sTimeClkTks = std::stoi(vec[14]);
      cuTimeClkTks = std::stoi(vec[15]);
      csTimeClkTks = std::stoi(vec[16]);
      startTimeClkTks = std::stof(vec[21]);

      float TotalTime =
          (float)(uTimeClkTks + sTimeClkTks + cuTimeClkTks + csTimeClkTks);
      float seconds = upTime - startTimeClkTks / sysconf(_SC_CLK_TCK);
      ProcessCpuUtil = (TotalTime / sysconf(_SC_CLK_TCK)) / seconds;
    }
  }

  return ProcessCpuUtil;
  }

// TODO: Return the command that generated this process
string Process::Command() { 
  
  
  if(LinuxParser::Command(Pid()).length()>50){
    LinuxParser::Command(Pid()) = LinuxParser::Command(Pid()).substr(0,49);
    return LinuxParser::Command(Pid());               
  };
  return LinuxParser::Command(Pid());
}

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const{ 
  return CpuUtil > a.CpuUtil; }