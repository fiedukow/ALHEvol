#pragma once

#include <evol/Chromosome.hpp>
#include <memory>

using namespace evol;

class PointValue;
typedef std::shared_ptr<PointValue> PointValuePtr;

class PointValue : public Chromosome
{
    public:
    PointValue();
    PointValue(double value);
    virtual ChromosomePtr crossWith(ChromosomePtr toCross ) const;
    virtual void mutate();
  
    private:
    double value;
};

