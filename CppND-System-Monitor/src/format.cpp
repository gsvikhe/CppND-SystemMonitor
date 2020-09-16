#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  std::string hours = "";
  std::string minutes = "";
  std::string sec = "";
  
  hours = std::to_string(seconds / 3600);  
  minutes = std::to_string((seconds % 3600)/60);
  sec = std::to_string(seconds % 60);
  
  if(hours.length() == 1) {hours = "0" + hours;} 
  if(minutes.length() == 1) {minutes = "0" + minutes;}
  if(sec.length() == 1) {sec = "0" + sec;}
  
  return(hours + ":" + minutes + ":" + sec);
    
  return string(); }