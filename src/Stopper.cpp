#include "Stopper.hpp"
#include <iostream>

Stopper::Stopper(evol::Population& pop)
  : pop(pop)
{}

void Stopper::operator()()
{
  std::string s;
  do
  {
  std::cin >> s;
  } while(s != "stop");
  pop.stopLoop();
}

