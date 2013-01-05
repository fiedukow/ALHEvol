#pragma once
#include <boost/optional.hpp>

#include <evol/Observer.hpp>
#include <evol/Population.hpp>

class PodgladPostepu : public evol::NewGenerationObserver
{
    public:
    PodgladPostepu();
    void update( evol::Population& population );

    private:
    boost::optional<double> bestFValue;
    unsigned int populationCounter;
}; 

