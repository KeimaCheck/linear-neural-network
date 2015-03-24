// test routines
#include "datapoint.h"
#include "dataset.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

// generate a (1,1) datapoint, manually fill its input vectors with zeroes, print it
int _simple_datapoint_test(){

    Datapoint d = Datapoint(1,1);
    d.input_vector[0] = 0;
    d.output_vector[0] = 0;

    d.print(1);

    return 0;
}

#include "linear_data_generator.h"

// confirms that linear_data_generator.cpp is working correctly
int _linear_generator_test(){
    srand(time(NULL));
    int in_size = 2;
    int out_size = 1;
    flt_vtr weights(in_size -1);
    generate_coefficients(weights, in_size);


    Datapoint d = Datapoint(in_size, out_size, linear_data_generator, weights);

    d.print(1);

    cout << (d.input_vector[1] - d.input_vector[0]*weights[0]);

    return 0;
}
