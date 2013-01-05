#pragma once

#include <gsl_addons/rmv.h>
#include <evol/Population.hpp>
#include "MultiDimGauss.hpp"

using namespace evol;

class FunctionValue : public FitnessFunction
{
public:
  FunctionValue(double value, const MultiDimGauss& ff);
  
  virtual bool operator>(const FitnessFunction& toCompare) const;
  virtual bool operator==(const FitnessFunction& toCompare) const;
  virtual void calculate(const Subject& toCalculate);
  virtual std::unique_ptr< FitnessFunction > clone() const;

  double getValue() const;

  virtual void print() const;
  
private: 
  double value;
  const MultiDimGauss& fitnessFunction;
};

