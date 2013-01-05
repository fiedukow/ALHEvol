#include "PodgladPostepu.hpp"
#include <evol/EvolFunctions.hpp>
#include <evol/Subject.hpp>
#include "MultiDimPoint.hpp"

#include <iostream>

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
}
