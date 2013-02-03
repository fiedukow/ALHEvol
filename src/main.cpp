#include <iostream>
#include <vector>
#include <boost/thread/thread.hpp>

#include <gsl/gsl_vector.h>

#include "PodgladPostepu.hpp"
#include <evol/Evol.hpp>
#include "FunctionValue.hpp"
#include "MultiDimGauss.hpp"
#include "PointValue.hpp"
#include "MultiDimPoint.hpp"
#include "Stopper.hpp"
#include "MyPopulation.hpp"
#include "MyPopulation2.hpp"
#include "Options.hpp"

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    std::cout << "Podaj nazwe pliku z danymi proby jako argument" << std::endl;
    return 1;
  }
   
  Options opt(argv[1]);  
  double mVariance = opt.mutationVariance();
  double mutationFactor = opt.mutationFactor();
  double crossFactor = opt.crossFactor();
  double goalValue = opt.goalValue();
  int popSize = opt.populationSize();
  int dims = opt.dims();
  bool runStopThread = opt.stopThread();
  MultiDimGauss gauss = opt.getFF();

  if(dims == 2)
  {
    std::cout << "Generating gauss.dat - grid data file for gnuplot with"
              << " fitness function values..." << std::endl;
    gauss.saveAsGridData("presentation/data/gauss.dat", 3, 0.05);
    std::cout << "Grid data file generated." << std::endl << std::endl;
  }
  else
  {
    std::cout << "Grid data generating skiped becouse dims != 2 (dims = " 
              << dims << ")." << std::endl;
  }

  FunctionValue goal(goalValue, gauss); 
  evol::SubjectPtr prototype((evol::Subject*) new MultiDimPoint(dims, gauss, mVariance));
  MyPopulation pop((FitnessFunction&) goal, prototype, popSize, mutationFactor, crossFactor);
  pop.registerObserver( NObserverPtr( new PodgladPostepu() ) );

  if(runStopThread)
  {
    Stopper stopper(pop);
    boost::thread stThread(stopper);
    std::cout << "Type 'stop' in console to stop evaluation after current generation" << std::endl;
  }

  pop.start();
  return 0;
}
