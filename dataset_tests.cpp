// testing routines for dataset.cpp

#include "dataset.h"
#include "defaults.h"
#include "linear_data_generator.h"
#include <iostream>

using namespace std;


// loads up datapoints' arrays with zeroes
void bogus_data_generator(float* inputs, float* outputs, int in_size, int out_size, float* params){
    int i;

    for (i=0; i<in_size; i++){
        inputs[i] = 0;
    }
    for (i=0; i<out_size; i++){
        outputs[i] = 0;
    }
}

int _linear_dataset_test(){
    int in_size = 2;
    int out_size = 1;

    flt_vtr weights(in_size - 1);

    generate_coefficients(weights, in_size);

    Dataset d = Dataset(100, 2,1, linear_data_generator, weights);

    d.print();

    return 0;
}
