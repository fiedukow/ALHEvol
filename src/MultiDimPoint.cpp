#include "MultiDimPoint.hpp"
#include "FunctionValue.hpp"
#include <evol/Chromosome.hpp>
#include <evol/EvolFunctions.hpp>

#include <cassert>
#include <iostream>

MultiDimPoint::MultiDimPoint(int dimensionsCount, const MultiDimGauss& ff, double mVariance)
  : dimensionsCount(dimensionsCount),
    ff(ff),
    mVariance_(mVariance)
{
  setInitialValue();
}

void MultiDimPoint::setInitialValue()
{
  clearChromosomes();
  for(int i = 0; i < dimensionsCount; ++i)
    addChromosome(ChromosomePtr(new PointValue(mVariance_, i)));
}

SubjectPtr MultiDimPoint::clone() const
{
  SubjectPtr newMultiDimPoint(new MultiDimPoint(dimensionsCount, ff, mVariance_));
  for(int i = 0; i < dimensionsCount; ++i)
  {
    newMultiDimPoint->addChromosome(
      ChromosomePtr(
        new PointValue(
          mVariance_,
          getDimensionValue(i)
        )
      )
    );
  }

  return newMultiDimPoint;
}

int MultiDimPoint::getDimensionsCount() const
{
  return dimensionsCount;
}

double MultiDimPoint::getDimensionValue(int dim) const
{
  return EvolFunctions::ptr_cast<ChromosomePtr, PointValue>(getChromosome(dim))->getValue();
}

void MultiDimPoint::setPosition(std::vector<double> pos)
{
  assert((int)pos.size() == getDimensionsCount());
  for(int i = 0; i < (int)pos.size(); ++i)
    EvolFunctions::ptr_cast<ChromosomePtr, PointValue>(getChromosome(i))->setValue(pos[i]);
}

double MultiDimPoint::getFunctionValue() const
{
  FunctionValue fv(0, ff);
  fv.calculate(*this);
  return fv.getValue();
}

double MultiDimPoint::getMVariance() const
{
  return mVariance_;
}

void MultiDimPoint::print() const
{
  std::cout << "Punkt: ";
  for(int i = 0; i < dimensionsCount; ++i)
    std::cout << getDimensionValue(i) << ((i != dimensionsCount-1) ? ", " : ";");
  std::cout << std::endl;
  std::cout << "Wynik: " << getFunctionValue() << std::endl;
}


