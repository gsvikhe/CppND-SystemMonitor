#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include "linux_parser.h"
#include <string>
#include <vector>
class Processor {
 public:
  double Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  float TotalJiffies{0.0}, TotalJiffiesPrev{0.0}, IdleJiffies{0.0}, UtilJiffies{0.0}, UtilJiffiesPrev{0.0}, usage{0.0};
};
#endif