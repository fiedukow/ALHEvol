#pragma once
#ifndef OPTIONS_H
#define OPTIONS_H
#include <vector>
#include "MultiDimGauss.hpp"

class Options
{
public:
  Options(const char* fileName);
  ~Options();
  double mutationVariance() const;
  double mutationFactor() const;
  double crossFactor() const;
  double goalValue() const;
  int maxGeneration() const;
  int smoothGenerations() const;
  int populationSize() const;
  int dims() const;
  int hillsCount() const;
  bool stopThread() const;
  MultiDimGauss getFF() const;

  double secondHillFirstCoord() const;
  
  static Options* I;

private:
  int dims_;
  double mutationVariance_;
  double mutationFactor_;
  double crossFactor_;
  double goalValue_;
  int populationSize_;
  int hillsCount_;
  std::vector<MultiDimGauss> hills_;
  MultiDimGauss* ff_;
  int maxGenerations_;
  int smoothResultGenerations_;
  double secondHillFirstCoord_;
  
  bool sumOrMax_;
  bool runStopThread_;
};

#endif
