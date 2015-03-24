// Header file for linear_data_generator.cpp

#ifndef _LINEAR_DATA_GEN_INCLUDED
#define _LINEAR_DATA_GEN_INCLUDED

#include "defaults.h"
#include "errors.h"
#include <cstdlib>
#include <iostream>
#include <vector>

typedef std::vector<float> flt_vtr;

void generate_coefficients(flt_vtr&, int);
void generate_hyperplane(flt_vtr&, int);
void linear_data_generator(flt_vtr&,flt_vtr&,flt_vtr&);


#endif
