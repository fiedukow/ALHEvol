#pragma once
#include <boost/optional.hpp>

#include <evol/Observer.hpp>
#include <evol/Population.hpp>

#include <string>

#define MAX_GENERATION 250
#define LAST_AVG 10

class PodgladPostepu : public evol::NewGenerationObserver
{
public:
    PodgladPostepu();
    void update( evol::Population& population );

private:

    void saveSubjectsSnapshot(const std::string& fileName,
                              evol::Population& population);

    boost::optional<double> bestFValue;
    unsigned int populationCounter;
    double lastResult[10];
}; 

