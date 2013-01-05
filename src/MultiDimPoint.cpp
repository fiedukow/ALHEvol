#include "MultiDimPoint.hpp"
#include <evol/Chromosome.hpp>

#include <iostream>

MultiDimPoint::MultiDimPoint(int dimensionsCount)
  : dimensionsCount(dimensionsCount)
{
  points.reserve(dimensionsCount);
}

void MultiDimPoint::setInitialValue()
{
  clearChromosomes();
  for(int i = 0; i < dimensionsCount; ++i)
    addChromosome(ChromosomePtr(new PointValue()));
}

SubjectPtr MultiDimPoint::clone() const
{
  SubjectPtr newMultiDimPoint(new MultiDimPoint(dimensionsCount));
  for(int i = 0; i < dimensionsCount; ++i)
    newMultiDimPoint->addChromosome(ChromosomePtr(new PointValue(points[i].getValue())));

  return newMultiDimPoint;
}

int MultiDimPoint::getDimensionsCount() const
{
  return dimensionsCount;
}

double MultiDimPoint::getDimensionValue(int dim) const
{
  return points[dim].getValue();
}

void MultiDimPoint::print() const
{
  std::cout << "Punkt: ";
  for(int i = 0; i < dimensionsCount; ++i)
    std::cout << points[i].getValue() << ((i != dimensionsCount-1) ? ", " : ";");
  std::cout << std::endl;
}
