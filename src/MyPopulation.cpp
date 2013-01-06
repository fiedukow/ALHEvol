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
  wi = (subjects.size()) - wi;
  return wi;
}

void MyPopulation::sortSubjects()
{
  for( SubjectPtr sub : subjects )
  {
    std::shared_ptr<FitnessFunction> wynik = goal.clone();
    wynik->calculate(*sub);
  }

  SubjectComparator comparator(goal);
  std::sort(this->subjects.begin(), this->subjects.end(), comparator);
}

void MyPopulation::crossoverSubjects()
{
  notifyCrossover();
  if(populationSize == 1) return;
  sortSubjects();

  for(int i = 0; i < populationSize*crossFactor; ++i)
  {
    int winner = EvolFunctions::random(1, getTotalChancesNumber());
    int winId[2] = {-1, -1};
    winId[0] = winnerIndex(winner);
    do
    {
      winner = EvolFunctions::random(1, getTotalChancesNumber());
      winId[1] = winnerIndex(winner);
    } while(winId[0] == winId[1]);
    addSubject(subjects[winId[0]]->crossWith(subjects[winId[1]]));  
  }
}

void MyPopulation::selectSubjects()
{
  notifySelection();
  sortSubjects();
  
  std::vector<SubjectPtr> selected;
  selected.push_back(subjects[0]);

  for(unsigned int i = 0; i < populationSize-1; ++i)
  {
    int winner = EvolFunctions::random(1, getTotalChancesNumber());
    selected.push_back(subjects[winnerIndex(winner)]);  
  }
  
  selected.swap(subjects);
}
