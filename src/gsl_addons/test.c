/***************************************************************************************
 *  A testing program for multivariate distributions
 *  Using GSL -> www.gnu.org/software/gsl
 *  Copyright (C) 2006  Ralph dos Santos Silva
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  AUTHOR 
 *     Ralph dos Santos Silva,  address@hidden
 *     March, 2006       
 ***************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <math.h>
/* GSL - GNU Scientific Library  */
/* #define GSL_CHECK_RANGE_OFF   */
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_cdf.h>
/* ----------------------------- */
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
/* ----------------------------- */
#include "rmv.h"

#define RANGE 30
#define A 0.4

int main(){
double result;
gsl_vector *x = gsl_vector_calloc(2),
           *mean = gsl_vector_calloc(2),
           *mean1 = gsl_vector_calloc(2);
gsl_matrix *m = gsl_matrix_alloc(2,2),
           *m1 = gsl_matrix_alloc(2,2);

gsl_matrix_set(m,0,0, 1.0);
gsl_matrix_set(m,0,1, 0.0);
gsl_matrix_set(m,1,0, 0.0);
gsl_matrix_set(m,1,1, 1.0);

gsl_matrix_set(m1,0,0, A);
gsl_matrix_set(m1,0,1, 0.0);
gsl_matrix_set(m1,1,0, 0.0);
gsl_matrix_set(m1,1,1, A);

gsl_vector_set(mean,0,0);
gsl_vector_set(mean,1,0);

gsl_vector_set(mean1,0, 3);
gsl_vector_set(mean1,1, 0);

for(int i = -RANGE; i <= 2*RANGE; ++i)
{
  for(int j = -RANGE; j <= RANGE; ++j)
  {
    double cx = ((double)i)*0.1;
    double cy = ((double)j)*0.1;
    gsl_vector_set(x,0,cx);
    gsl_vector_set(x,1,cy);

    result = dmvnorm(2,x,mean,m) + dmvnorm(2,x,mean1,m1);
    fprintf(stdout,"%.3f %.3f %.3f\n", cx, cy, result);
  }
  fprintf(stdout,"\n");
}

return 0;
}


