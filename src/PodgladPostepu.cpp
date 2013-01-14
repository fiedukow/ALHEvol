#include "PodgladPostepu.hpp"
#include "MyPopulation.hpp"
#include <evol/EvolFunctions.hpp>
#include <evol/Subject.hpp>
#include "MultiDimPoint.hpp"
#include "FunctionValue.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <cstdio>

PodgladPostepu::PodgladPostepu() : populationCounter(0)
{}

void PodgladPostepu::update( evol::Population& population )
{
    MultiDimPoint* best = evol::EvolFunctions::ptr_cast<SubjectPtr, MultiDimPoint>(
            population.getSubjects().at( population.getBestId() )
    );

    ++populationCounter;


    double current = best->getFunctionValue();
    if( !bestFValue || current > bestFValue )
    {
        bestFValue = current;
        std::cout << "Poprawil sie wynik najlepszego osobnika."<< std::endl;
        std::cout << "Obecny wynik (pokolenie nr. " << populationCounter << ") to: " << std::endl;
        best->print();
    }
/*    {
    std::stringstream ss;
    ss << "presentation/data/" << "subjects_" <<  populationCounter << ".dat";
    saveSubjectsSnapshot(ss.str(), population);
    }
    
    {
    std::stringstream ss;
    ss << "./presentation/genGenerationPng " << populationCounter << "";
    system(ss.str().c_str());
    }*/

    const MyPopulation& myPop = dynamic_cast<const MyPopulation&>(population);
    std::vector<double> avg = myPop.averagePoint();
    std::cout << "Jestem obok ";
    for(double i : avg)
      std::cout << i << " ";
    std::cout << std::endl;

    if(populationCounter >= 490)
    {
      std::cout << std::endl << "Pokolenie nr. "<< populationCounter << std::endl;

      const MyPopulation& myPop = dynamic_cast<const MyPopulation&>(population);
      std::vector<double> avg = myPop.averagePoint();
      std::cout << "Srodek masy: ";
      int cnt = 0;
      for(double i : avg)
        std::cout << i << ((cnt++ > 0) ? ", " : ";");
      std::cout << std::endl;
      FunctionValue fv = dynamic_cast<const FunctionValue&>(myPop.getGoal());
      MultiDimPoint p(avg.size(), fv.getGauss(), 0.0);    
      p.setPosition(avg);    
      lastResult[populationCounter-490] = p.getFunctionValue();

      if(populationCounter == 500)
      {
        population.stopLoop();
        double avg = 0;
        for(int i = 0; i < 10; ++i)
        {
          avg += lastResult[i];
        }
        avg/=10;
        std::cout << "R: " << myPop.getMVariance() << " " << avg << std::endl;  
      }
    }
}

void PodgladPostepu::saveSubjectsSnapshot(const std::string& fileName,
                                          evol::Population& population)
{
  std::fstream output;
  output.open(fileName, std::fstream::out);  
  assert(output.good());
  std::vector<evol::SubjectPtr>& subjects = population.getSubjects();
  for(auto& i : subjects)
  {
    MultiDimPoint* curr = evol::EvolFunctions::ptr_cast<SubjectPtr, MultiDimPoint>(i);
    int dims = curr->getDimensionsCount();
    for(int j = 0; j < dims; ++j)
    {
      output << curr->getDimensionValue(j) << ((j < dims - 1) ? " " : "");
    }
    output << std::endl;
  }

  output.close();
}
