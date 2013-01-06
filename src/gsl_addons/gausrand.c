#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int main()
{
  gsl_rng* randomNumberGenerator;
  const gsl_rng_type* generatorType;
  gsl_rng_env_setup();

  generatorType = gsl_rng_default;
  randomNumberGenerator = gsl_rng_alloc (generatorType);
  gsl_rng_set(randomNumberGenerator, time(NULL));

  for(int i = 0; i < 10; ++i)
    printf("%f\n", gsl_ran_gaussian(randomNumberGenerator, 0.33));

  gsl_rng_free(randomNumberGenerator);
}
