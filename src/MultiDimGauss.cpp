#include "MultiDimGauss.hpp"
#include <gsl_addons/rmv.h>
#include <cassert>
#include <fstream>
#include <iostream>

MyGaussDescription::MyGaussDescription(double covarianceFactor,
                                       double heightFactor,
                                       int nDim,
                                       double exVal[])
  : nDim(nDim),
    covarianceFactor(covarianceFactor),
    heightFactor(heightFactor)
{
  for(int i = 0; i < nDim; ++i)
    expectedValues.push_back(exVal[i]);
}

MultiDimGauss::MultiDimGauss(std::vector<MyGaussDescription> hills)
{
  int dimensions;
  for(std::vector<MyGaussDescription>::iterator i = hills.begin();
      i != hills.end();
      ++i)
  {
    assert(i == hills.begin() || dimensions == i->nDim);
    dimensions = i->nDim;

    gsl_matrix* cov = gsl_matrix_calloc(i->nDim, i->nDim);
    gsl_vector* ex  = gsl_vector_alloc(i->nDim);
    for(int j = 0; j < i->nDim; ++j)
    {
      gsl_matrix_set(cov, j, j, i->covarianceFactor);
      gsl_vector_set(ex, j, i->expectedValues[j]);
    } 

    covarianceMatrixes.push_back(cov);
    expectedValues.push_back(ex); 
    heightFactors.push_back(i->heightFactor);
  } 
}

MultiDimGauss::~MultiDimGauss()
{
  //FIXME - memory leak here
}

double MultiDimGauss::getValueForVector(gsl_vector* point) const
{
  assert(covarianceMatrixes.size() == 0 ||
         expectedValues[0]->size == point->size);
  double result = 0.0;

  for(unsigned int i = 0; i < covarianceMatrixes.size(); ++i)
  {
    result += dmvnorm(point->size, point, expectedValues[i], covarianceMatrixes[i])
              * heightFactors[i];
  }

  return result;
}

void MultiDimGauss::saveAsGridData(const std::string& targetFile,
                                   double range,
                                   double res) const
{
  if(!(expectedValues.size() > 0 && expectedValues[0]->size == 2))
    return; //grid are only saved for 2D gauss

  std::fstream output;
  output.open(targetFile, std::fstream::out);
  assert(output.good());
  int samples = range/res + 1;
  samples *= 2;
  gsl_vector* v = gsl_vector_alloc(2);

  for(int i = 0; i < samples; ++i)
  {
    for(int j = 0; j < samples; ++j)
    {
      double cx = -range+i*res;
      double cy = -range+j*res;
      gsl_vector_set(v, 0, cx);
      gsl_vector_set(v, 1, cy);
      double value = getValueForVector(v);
      output << cx << " " << cy << " " << value << std::endl;
    }
    output << std::endl;
  }
  output.close();
  gsl_vector_free(v);
}

