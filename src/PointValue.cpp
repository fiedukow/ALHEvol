#include "PointValue.hpp"
#include <evol/EvolFunctions.hpp>
#include <iostream>

const double PointValue::maxRange = 3;

PointValue::PointValue(double mVariance)
  : value(-3/*(EvolFunctions::random()-0.1*maxRange)*10*/), //-5 to 5
    mVariance_(mVariance)
{
}

PointValue::PointValue(double mVariance, double value)
  : value(value),
    mVariance_(mVariance)
{
}

ChromosomePtr PointValue::crossWith(ChromosomePtr toCross) const
{
  /** child has value = weighted average of parents 
      with random weight **/
  PointValue* toCrossPV 
      = EvolFunctions::ptr_cast<ChromosomePtr, PointValue>(toCross);
  double randomFactor = 0.5 + EvolFunctions::gaussRandom(0, 0.15);
  double childValue = this->value*(randomFactor);
  childValue += toCrossPV->value*(1 - randomFactor);
  childValue = ensureValueInRange(childValue);
  return PointValuePtr(new PointValue(mVariance_, childValue));
}

void PointValue::mutate()
{
  double factor = EvolFunctions::gaussRandom(0, mVariance_);
  value += factor;
  value = ensureValueInRange(value);
}

double PointValue::getValue() const
{
  return value;
}

void PointValue::setValue(double val)
{
  value = val;
}

double PointValue::ensureValueInRange(double v)
{
/*  if(v <= maxRange && v >= -maxRange)
    return v;
  return (EvolFunctions::random()-0.1*maxRange)*10;*/
  return v;
}
