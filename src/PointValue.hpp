#pragma once

#include <evol/Chromosome.hpp>
#include <memory>

using namespace evol;

class PointValue;
typedef std::shared_ptr<PointValue> PointValuePtr;

class PointValue : public Chromosome
{
public:
    PointValue(double mVariance, int i);
    PointValue(double mVariance, double value);
    virtual ChromosomePtr crossWith(ChromosomePtr toCross ) const;
    virtual void mutate();

    double getValue() const;
    void setValue(double);

    static const double maxRange;
  
private:
    static double ensureValueInRange(double v);

    double value;
    const double mVariance_;
};

