#include "PodgladPostepu.hpp"
#include <evol/EvolFunctions.hpp>
#include <evol/Subject.hpp>
#include "MultiDimPoint.hpp"

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
        std::cout << std::endl;
    }
    else if( populationCounter%100 == 0 )
    {
        std::cout << "Pokolenie nr. "<< populationCounter << std::endl << std::endl; 
    }
    {
    std::stringstream ss;
    ss << "presentation/data/" << "subjects_" <<  populationCounter << ".dat";
    saveSubjectsSnapshot(ss.str(), population);
    }
    
    {
    std::stringstream ss;
    ss << "./presentation/genGenerationPng " << populationCounter << "";
    system(ss.str().c_str());
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
