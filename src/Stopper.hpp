#pragma once
#include <evol/Population.hpp>

class Stopper
{
public:
  Stopper(evol::Population& pop);
  void operator()();

private:
  evol::Population& pop;
};
