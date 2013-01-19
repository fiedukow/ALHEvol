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

#define DIMS 2

int main(int argc, char** argv)
{
  std::vector<MyGaussDescription> mgds;
  double g1ex[] = {-1.5, -1.5 };
  mgds.push_back(MyGaussDescription(1.0, 1.2, DIMS, g1ex));
  double g2ex[] = {-0.5, 0.5 };
  mgds.push_back(MyGaussDescription(0.2, 1.1, DIMS, g2ex));
  double g3ex[] = {1.5, 1.5};
  mgds.push_back(MyGaussDescription(0.2, 3.5, DIMS, g3ex));

  double mVariance = 0.33;
  if(argc > 1)
  {
    std::cout << atof(argv[1]) << std::endl;
    mVariance = atof(argv[1]);
  }

  MultiDimGauss gauss(mgds);
  gsl_vector* v = gsl_vector_alloc(DIMS);
  gsl_vector_set(v, 0, -1.5);
  gsl_vector_set(v, 1, -1.5);
  std::cout << "F(-1.5, -1.5) = " << gauss.getValueForVector(v) << std::endl;
  gsl_vector_set(v, 0, -0.5);
  gsl_vector_set(v, 1, 0.5);
  std::cout << "F(-0.5, 0.5) = " << gauss.getValueForVector(v) << std::endl;
  gsl_vector_set(v, 0, 1.5);
  gsl_vector_set(v, 1, 1.5);
  std::cout << "F(1.5, 1.5) = " << gauss.getValueForVector(v) << std::endl;
/*
  std::cout << "Generating gauss.dat - grid data file for gnuplot with"
            << " fitness function values..." << std::endl;
  gauss.saveAsGridData("presentation/data/gauss.dat", 3, 0.05);
  std::cout << "Grid data file generated." << std::endl << std::endl;
*/

  FunctionValue goal(2200.87747, gauss); 
  evol::SubjectPtr prototype((evol::Subject*) new MultiDimPoint(DIMS, gauss, mVariance));
  MyPopulation pop((FitnessFunction&) goal, prototype, 400, 0.5, 2.0);
  pop.registerObserver( NObserverPtr( new PodgladPostepu() ) );

  Stopper stopper(pop);
/*  boost::thread stThread(stopper);
  pop.start()->print();*/
  pop.start();
  return 0;
}
