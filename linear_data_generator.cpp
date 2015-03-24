/* Generates linearly separable data with a single output dimension

Dependencies:
    Defaults

Prerequisites:
    random number generator must be seeded
    requires a Dataset subclass capable of storing information about a hyperplane
*/
#include "linear_data_generator.h"

// generates coefficients for linear_data_generator
// weights will store the generated coefficients
// could also be called "generate hyperplane"
// weights should be an array of size in_size-1
void generate_coefficients(flt_vtr& weights, int in_size){

    size_error(weights.size(), in_size, -1, "generate_coefficients");
    int i;
    float temp;

    /* we assume that the last variable has coefficient -1
    to give the generation process a clear geometric interpretation */
    for(i=0; i<in_size-1; i++){
        temp = rand();
        temp = temp/RAND_MAX;
        temp = temp*(MAX_SLOPE - MIN_SLOPE) + MIN_SLOPE;
        weights[i] = temp;
    }
}

// so here it is
inline void generate_hyperplane(flt_vtr& weights, int in_size){
    generate_coefficients(weights, in_size);
}

// a function of dp_generator type
void linear_data_generator(flt_vtr& inputs, flt_vtr& outputs, flt_vtr& weights){
if (outputs.size() != 1) {
    std::cout << "linear_data_generator only supports a single output dimension.";
    exit(EXIT_FAILURE);
}
else {
    size_error(inputs.size(), weights.size(), 1, "linear_data_generator()");
    int i;
    float temp;
    float sum = 0;

    // generate and store inputs
    for (i=0; i<inputs.size(); i++){
        temp = rand();
        temp = temp/RAND_MAX;
        temp = temp*XRANGE;
        inputs[i] = temp;
    }

    // weighted-sum the inputs except the last one
    for (i=0; i<inputs.size() - 1; i++){
        sum = sum + (inputs[i] * weights[i]);
    }

    // point is group 1 (output = 1) if it lies above the hyperplane determined by the weights
    // otherwise (output = -1)
    if (inputs[inputs.size()-1] >= sum){
        outputs[0] = 1;
    } else {
        outputs[0] = -1;
    }
}
}
