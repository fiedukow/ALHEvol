#include "MyPopulation.hpp"
#include "MultiDimPoint.hpp"
#include <cmath>
#include <algorithm>
#include <evol/EvolFunctions.hpp>
#include <iostream>

/*1 means +1 chance per position, 0.1 means +10 chances per position*/
#define CHANCES_FACTOR 1.0

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
  result/=2*CHANCES_FACTOR;
  return result;
}

std::vector<double> MyPopulation::averagePoint() const
{
  std::vector<double> result;
  if(subjects.size() == 0)
    return result;

  int nDim = EvolFunctions::ptr_cast<SubjectPtr, MultiDimPoint>(subjects[0])->getDimensionsCount();
  for(int i = 0; i < nDim; ++i)
    result.push_back(0);

  for( SubjectPtr sub : subjects )
  {
    MultiDimPoint* curr = EvolFunctions::ptr_cast<SubjectPtr, MultiDimPoint>(sub);
    for(int i = 0; i < nDim; ++i)
      result[i] += curr->getDimensionValue(i);
  }

  for(int i = 0; i < nDim; ++i)
    result[i] /= subjects.size();

  return result;
}


int MyPopulation::winnerIndex(int winnerChance)
{
  int wi = ceil(1.0/2.0*(sqrt(CHANCES_FACTOR*8.0*((double)winnerChance)+1)-1));
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

const FitnessFunction& MyPopulation::getGoal() const
{
  return goal;
}

double MyPopulation::getMVariance() const
{
  return EvolFunctions::ptr_cast<SubjectPtr, MultiDimPoint>(subjects[1])->getMVariance();
}
