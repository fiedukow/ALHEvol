#include <iostream>
#include <vector>
#include <evol/Evol.hpp>
#include "FunctionValue.hpp"
#include "MultiDimGauss.hpp"
#include "PointValue.hpp"
#include "MultiDimPoint.hpp"

int main(int /*argc*/, char** /*argv*/)
{
  std::vector<MyGaussDescription> mgds;
  double g1ex[] = {0, 0};
  mgds.push_back(MyGaussDescription(1.0, 1.0, 2, g1ex));
  double g2ex[] = {0, 2};
  mgds.push_back(MyGaussDescription(0.6, 0.2, 2, g2ex));
  
  MultiDimGauss gauss(mgds);
  FunctionValue goal(200, gauss); 
  evol::SubjectPtr prototype((evol::Subject*) new MultiDimPoint(2, gauss));
  evol::Population pop((FitnessFunction&) goal, prototype, 1000, 0.2, 2.0);

  pop.start()->print();
  return 0;
}
