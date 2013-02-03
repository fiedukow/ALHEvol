#include "Options.hpp"
#include <fstream>
#include <gsl/gsl_vector.h>
#include <cassert>

Options* Options::I = NULL;

Options::Options(const char* fileName)
{
  I = this;
  std::fstream in;
  in.open(fileName, std::fstream::in);
  assert(in.good());
  
  in >> runStopThread_;
  in >> goalValue_;
  in >> dims_;
  in >> hillsCount_;
  in >> sumOrMax_;
  in >> maxGenerations_;
  in >> smoothResultGenerations_;
  in >> populationSize_;
  in >> mutationFactor_;
  in >> crossFactor_;
  in >> mutationVariance_;
  
  std::vector<MyGaussDescription> mgds;
  double heightC, covC;
  double *middleC = new double[dims_];
  
  for(int i = 0; i < hillsCount_; ++i)
  {
    in >> heightC >> covC;
    for(int j = 0; j < dims_; ++j)
      in >> middleC[j];
    
    MyGaussDescription currentHill(covC, heightC, dims_, middleC);
    std::vector<MyGaussDescription> ctmp;
    ctmp.push_back(currentHill);
    mgds.push_back(currentHill);
    hills_.push_back(MultiDimGauss(ctmp));
  }
  delete[] middleC;

  ff_ = new MultiDimGauss(mgds);

  in.close();
}

Options::~Options()
{
  delete ff_;
}

double Options::mutationVariance() const
{
  return mutationVariance_;
}

double Options::mutationFactor() const
{
  return mutationFactor_;
}

double Options::crossFactor() const
{
  return crossFactor_;
}

double Options::goalValue() const
{
  return goalValue_;
}

int Options::maxGeneration() const
{
  return maxGenerations_;
}

int Options::smoothGenerations() const
{
  return smoothResultGenerations_;
}

int Options::populationSize() const
{
  return populationSize_;
}

int Options::dims() const
{
  return dims_;
}

int Options::hillsCount() const
{
  return hillsCount_;
}

bool Options::stopThread() const
{
  return runStopThread_;
}

MultiDimGauss Options::getFF() const
{
  return *ff_;
}


