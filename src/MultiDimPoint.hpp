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
  
  void setPosition(std::vector<double> pos);

  double getFunctionValue() const;

  virtual void print() const;

  private:
  int dimensionsCount;
  const MultiDimGauss& ff;
};

