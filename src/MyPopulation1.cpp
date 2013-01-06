#include "MyPopulation.hpp"
#include <cmath>
#include <algorithm>
#include <evol/EvolFunctions.hpp>
#include <iostream>

MyPopulation::MyPopulation(const FitnessFunction &goal_,
                           const SubjectPtr prototype_,
                           unsigned int populationSize_,
                           double mutationChance_,
                           double crossFactor_ )
  : Population(goal_,
               prototype_,
               populationSize_,
               mutationChance_,
               crossFactor_)
{
}

int MyPopulation::getTotalChancesNumber()
{
  int result = subjects.size()+1;
  result*=subjects.size();
  result/=2;
  return result;
}

int MyPopulation::winnerIndex(int winnerChance)
{
  int wi = ceil(1.0/2.0*(sqrt(8*((double)winnerChance)+1)-1));
  wi = (populationSize+populationSize*crossFactor) - wi;
  return wi;
}

void MyPopulation::selectSubjects()
{
  notifySelection();

  for( SubjectPtr sub : subjects )
  {
      std::shared_ptr<FitnessFunction> wynik = goal.clone();
      wynik->calculate(*sub);
  }

  SubjectComparator comparator(goal);
  std::sort(this->subjects.begin(), this->subjects.end(), comparator);
  
  std::vector<SubjectPtr> selected;
  selected.push_back(subjects[0]);

  for(unsigned int i = 0; i < populationSize-1; ++i)
  {
    double winner;
    do
    {
      winner = EvolFunctions::gaussRandom(0, (1+populationSize)*crossFactor*3);  
      winner = EvolFunctions::abs(winner);
    } while(winner >= populationSize);
    int winId = (int)winner;
    selected.push_back(subjects[winId]);  
  }
  
  selected.swap(subjects);
}
