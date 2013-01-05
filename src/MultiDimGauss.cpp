#include "MultiDimGauss.hpp"
#include <gsl_addons/rmv.h>
#include <cassert>

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
  for(std::vector<MyGaussDescription>::iterator i = hills.begin();
      i != hills.end();
      ++i)
  {
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
  for(std::vector<gsl_matrix*>::const_iterator i = covarianceMatrixes.begin();
      i != covarianceMatrixes.end();
      ++i)
  {
    gsl_matrix_free(*i);
  }
  
  for(std::vector<gsl_vector*>::const_iterator i = expectedValues.begin();
      i != expectedValues.end();
      ++i)
  {
    gsl_vector_free(*i);
  }
}

double MultiDimGauss::getValueForVector(gsl_vector* point) const
{
  assert(point->size == covarianceMatrixes.size());
  double result = 0.0;

  for(unsigned int i = 0; i < covarianceMatrixes.size(); ++i)
  {
    result += dmvnorm(point->size, point, expectedValues[i], covarianceMatrixes[i])
              * heightFactors[i];
  }

  return result;
}

