#pragma once

#include <vector>

#include <evol/EvolException.hpp>
#include <evol/Subject.hpp>

#include "PointValue.hpp"
#include "MultiDimGauss.hpp"

using namespace evol;

class MultiDimPoint : public Subject
{
  public:
  MultiDimPoint(int dimensionsCount, const MultiDimGauss& ff); 

  virtual void setInitialValue();
  virtual SubjectPtr clone() const;

  int getDimensionsCount() const;
  double getDimensionValue(int dim) const;

  double getFunctionValue() const;

  virtual void print() const;

  private:
  int dimensionsCount;
  std::vector<PointValue> points;
  const MultiDimGauss& ff;
};

