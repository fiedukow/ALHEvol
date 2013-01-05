#include "PointValue.hpp"
#include <evol/EvolFunctions.hpp>
#include <iostream>

PointValue::PointValue()
  : value((EvolFunctions::random()-0.5)*10) //-5 to 5
{
}

PointValue::PointValue(double value)
  : value(value)
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
  return PointValuePtr(new PointValue(childValue));
}

void PointValue::mutate()
{
  double factor = EvolFunctions::gaussRandom(0, 0.33);
  value += value * factor;
}

double PointValue::getValue() const
{
  return value;
}
