#include <iostream>
#include <vector>
#include <boost/thread/thread.hpp>

#include "PodgladPostepu.hpp"
#include <evol/Evol.hpp>
#include "FunctionValue.hpp"
#include "MultiDimGauss.hpp"
#include "PointValue.hpp"
#include "MultiDimPoint.hpp"
#include "Stopper.hpp"
#include "MyPopulation.hpp"

int main(int /*argc*/, char** /*argv*/)
{
  std::vector<MyGaussDescription> mgds;
  double g1ex[] = {1, 1};
  mgds.push_back(MyGaussDescription(1.2, 1.2, 2, g1ex));
  double g2ex[] = {-1, -1};
  mgds.push_back(MyGaussDescription(1.2, 1.1, 2, g2ex));
  
  MultiDimGauss gauss(mgds);

  std::cout << "Generating gauss.dat - grid data file for gnuplot with"
            << " fitness function values..." << std::endl;
  gauss.saveAsGridData("presentation/data/gauss.dat", 3, 0.05);
  std::cout << "Grid data file generated." << std::endl << std::endl;

  FunctionValue goal(20.1945, gauss); 
  evol::SubjectPtr prototype((evol::Subject*) new MultiDimPoint(2, gauss));
  MyPopulation pop((FitnessFunction&) goal, prototype, 2500, 0.4, 2.0);
  pop.registerObserver( NObserverPtr( new PodgladPostepu() ) );

  Stopper stopper(pop);
  boost::thread stThread(stopper);
  pop.start()->print();
  return 0;
}
