#include "MultiDimPoint.hpp"
#include "FunctionValue.hpp"
#include <evol/Chromosome.hpp>
#include <evol/EvolFunctions.hpp>

#include <iostream>

MultiDimPoint::MultiDimPoint(int dimensionsCount, const MultiDimGauss& ff)
  : dimensionsCount(dimensionsCount),
    ff(ff)
{
  setInitialValue();
}

void MultiDimPoint::setInitialValue()
{
  clearChromosomes();
  for(int i = 0; i < dimensionsCount; ++i)
    addChromosome(ChromosomePtr(new PointValue()));
}

SubjectPtr MultiDimPoint::clone() const
{
  SubjectPtr newMultiDimPoint(new MultiDimPoint(dimensionsCount, ff));
  for(int i = 0; i < dimensionsCount; ++i)
  {
    newMultiDimPoint->addChromosome(
      ChromosomePtr(
        new PointValue(
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

double MultiDimPoint::getFunctionValue() const
{
  FunctionValue fv(0, ff);
  fv.calculate(*this);
  return fv.getValue();
}

void MultiDimPoint::print() const
{
  std::cout << "Punkt: ";
  for(int i = 0; i < dimensionsCount; ++i)
    std::cout << getDimensionValue(i) << ((i != dimensionsCount-1) ? ", " : ";");
  std::cout << std::endl;
  std::cout << "Wynik: " << getFunctionValue() << std::endl;
}
