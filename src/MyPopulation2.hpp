#pragma once
#include <evol/Population.hpp>

using namespace evol;

class MyPopulation2 : public Population
{
public:
  MyPopulation2(const FitnessFunction &goal_,
               const SubjectPtr prototype_,
               unsigned int populationSize_,
               double mutationChance_,
               double crossFactor_ );
  
  int getTotalChancesNumber();
  int winnerIndex(int winnerChance);

  std::vector<double> averagePoint() const;
  double fromAverageDistance(SubjectPtr subj) const;
  double averageFromAverageDistance() const;

protected:
  virtual void selectSubjects();
};
