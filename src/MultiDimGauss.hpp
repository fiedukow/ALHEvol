#pragma once
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <vector>
#include <string>

struct MyGaussDescription
{
  MyGaussDescription(double covarianceFactor,
                     double heightFactor,
                     int nDim,
                     double expectedValues[]);

  std::vector<double> expectedValues;
  int nDim;
  double covarianceFactor;
  double heightFactor;
};

class MultiDimGauss
{
public:
  MultiDimGauss(std::vector<MyGaussDescription> hills);
  ~MultiDimGauss();

  double getValueForVector(gsl_vector* point) const;
  void saveAsGridData(const std::string& targetFile,
                      double range,
                      double res) const;

private:
  std::vector<gsl_matrix*> covarianceMatrixes;
  std::vector<gsl_vector*> expectedValues;
  std::vector<double> heightFactors;
};
