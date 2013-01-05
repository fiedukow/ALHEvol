#pragma once

#include <evol/Chromosome.hpp>

using namespace evol

class PointValue : public Chromosome
{
    public:
    virtual ChromosomePtr crossWith(ChromosomePtr toCross ) const;
    virtual void mutate();
  
    private:
    double value;
};

#endif
