#include "processor.h"

// TODO: Return the aggregate CPU utilization
double Processor::Utilization() { 
  std::vector<std::string> JiffiesList = LinuxParser::CpuUtilization();
  
  for (size_t i{0}; i<JiffiesList.size();i++){
    if (i!=LinuxParser::kGuest_ and i!=LinuxParser::kGuestNice_){
    	TotalJiffies += std::stof(JiffiesList[i]);
    }
    if (i==LinuxParser::kIdle_ or i==LinuxParser::kIOwait_){
    	IdleJiffies += std::stof(JiffiesList[i]);
    }
  }
  UtilJiffies = TotalJiffies - IdleJiffies;
  
  bool CurrUtil = true;
  if (CurrUtil){
    usage = (UtilJiffies-UtilJiffiesPrev)/(TotalJiffies-TotalJiffiesPrev);
    TotalJiffiesPrev = TotalJiffies;
    UtilJiffiesPrev = UtilJiffies;
  }
  else{
    usage = UtilJiffies/TotalJiffies;
  }
  
  return usage;}