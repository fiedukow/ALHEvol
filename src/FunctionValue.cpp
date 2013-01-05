#include "FunctionValue.hpp"
#include "MultiDimPoint.hpp"

#include <gsl/gsl_vector.h>
#include <iostream>

using namespace evol;

FunctionValue::FunctionValue(double value, const MultiDimGauss& ff)
  : value(value),
    fitnessFunction(ff)
{}

bool FunctionValue::operator>(const FitnessFunction& toCompare) const
{
  return (this->value > dynamic_cast<const FunctionValue&>(toCompare).value);
}

bool FunctionValue::operator==(const FitnessFunction& toCompare) const
{
  return (this->value == dynamic_cast<const FunctionValue&>(toCompare).value);
}

void FunctionValue::calculate(const Subject& toCalculate)
{
  const MultiDimPoint& subject = dynamic_cast<const MultiDimPoint&>(toCalculate);
  gsl_vector* dimValues = gsl_vector_alloc(subject.getDimensionsCount());
  for(int i = 0; i < subject.getDimensionsCount(); ++i)
    gsl_vector_set(dimValues, i, subject.getDimensionValue(i));
  
  value = fitnessFunction.getValueForVector(dimValues);
  gsl_vector_free(dimValues);
}

std::unique_ptr<FitnessFunction> FunctionValue::clone() const
{
  return std::unique_ptr<FitnessFunction>(new FunctionValue(*this));
}

double FunctionValue::getValue() const
{
  return value;
}

void FunctionValue::print() const
{
  std::cout << "Wartosc funkcji: " << value << std::endl;
}
