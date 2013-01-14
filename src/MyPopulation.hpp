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
  
  std::vector<double> averagePoint() const;
  int getTotalChancesNumber();
  int winnerIndex(int winnerChance);
  void sortSubjects();
  
  const FitnessFunction& getGoal() const;

protected:
  virtual void selectSubjects();
  virtual void crossoverSubjects();
};
