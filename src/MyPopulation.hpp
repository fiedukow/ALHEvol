#pragma once
#include <evol/Population.hpp>

using namespace evol;

class MyPopulation : public Population
{
public:
  MyPopulation(const FitnessFunction &goal_,
               const SubjectPtr prototype_,
               unsigned int populationSize_,
               double mutationChance_,
               double crossFactor_ );
  
  int getTotalChancesNumber();
  int winnerIndex(int winnerChance);

protected:
  virtual void selectSubjects();
};
