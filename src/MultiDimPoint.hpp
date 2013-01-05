#pragma once

#include <vector>

#include <evol/EvolException.hpp>
#include <evol/Subject.hpp>

#include "PointValue.hpp"

using namespace evol;

class MultiDimPoint : public Subject
{
  public:
  MultiDimPoint(int dimensionsCount); 

  virtual void setInitialValue();
  virtual SubjectPtr clone() const;

  virtual void print() const;

  private:
  int dimensionsCount;
  std::vector<PointValue> points;
/*std::list<double> covarianceFactors;
  std::list<double> heightFactors;
  std::list<std::list<double>> expectedValues;*/
};

