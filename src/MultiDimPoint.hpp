#pragma once

#include <evol/EvolException.hpp>
#include <evol/Subject.hpp>

using namespace evol;

class MultiDimPoint : public Subject
{
    public:
    virtual SubjectPtr crossWith(SubjectPtr &subject) const throw (SubjectCrossException);
    virtual void mutate();

    virtual void setInitialValue();
    virtual SubjectPtr clone() const;

    virtual void print() const;
};

