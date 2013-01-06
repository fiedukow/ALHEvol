#include "MyPopulation2.hpp"
#include "MultiDimPoint.hpp"
#include <cmath>
#include <algorithm>
#include <evol/EvolFunctions.hpp>
#include <iostream>

MyPopulation2::MyPopulation2(const FitnessFunction &goal_,
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

int MyPopulation2::getTotalChancesNumber()
{
  int result = subjects.size()+1;
  result*=subjects.size();
  result/=2;
  return result;
}

int MyPopulation2::winnerIndex(int winnerChance)
{
  int wi = ceil(1.0/2.0*(sqrt(8*((double)winnerChance)+1)-1));
  wi = (populationSize+populationSize*crossFactor) - wi;
  return wi;
}

std::vector<double> MyPopulation2::averagePoint() const 
{
  std::vector<double> result;
  if(subjects.size() == 0)
    return result;

  int nDim = EvolFunctions::ptr_cast<SubjectPtr, MultiDimPoint>(subjects[0])->getDimensionsCount();
  for(int i = 0; i < nDim; ++i)
    result.push_back(0);

  int cnt = 0;
  for( SubjectPtr sub : subjects )
  {
    MultiDimPoint* curr = EvolFunctions::ptr_cast<SubjectPtr, MultiDimPoint>(sub);
    for(int i = 0; i < nDim; ++i)
    {                
      result[i] *= cnt;
      result[i] += curr->getDimensionValue(i);
      result[i] /= ++cnt;
    }
  }
  return result;
}

double MyPopulation2::fromAverageDistance(SubjectPtr subj) const
{
  MultiDimPoint* point = EvolFunctions::ptr_cast<SubjectPtr, MultiDimPoint>(subj);
  std::vector<double> avgs = averagePoint();
  double result = 0;
  for(unsigned int i = 0; i < avgs.size(); ++i)
    result += EvolFunctions::abs(avgs[i]-point->getDimensionValue(i));

  return result;
}

double MyPopulation2::averageFromAverageDistance() const
{
  double result = 0.0;
  for( SubjectPtr sub : subjects )
  {
    result += fromAverageDistance(sub);
  }

  return result/subjects.size();
}

void MyPopulation2::selectSubjects()
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
  double avgFAD = averageFromAverageDistance();

  selected.push_back(subjects[getBestId()]);
  for(unsigned int i = 0; i < populationSize-1; ++i)
  {
    int winner = EvolFunctions::random(1, getTotalChancesNumber());
    int winId = winnerIndex(winner);
    double facf = fromAverageDistance(subjects[winId]);
    facf -= avgFAD;
    facf = EvolFunctions::abs(facf);
    facf /= 2.0;
//    facf *= facf;
    if(EvolFunctions::random() > facf)
      --i;
    else
      selected.push_back(subjects[winId]); 
  }
   
  selected.swap(subjects);
}
