/* Linear and step-linear activation functions for neural network nodes

Dependencies:
    defaults.h
*/

#include "linear_activation.h"

/* returns the output for a neuron having a step-linear activation
having been fed the given inputs and having the given weights */
float step_linear_activation(flt_vtr* inputs, flt_vtr weights){
    float input = 0;
    int i;

    flt_vtr inputs_t = *inputs;

size_error(inputs_t.size(), weights.size(), "step_linear_activation()");

    for (i=0; i<inputs_t.size(); i++){
        input = inputs_t[i]*weights[i] + input;
    }

    if (input > 0){
        return MAX_SIGNAL;
    } else {
        return MIN_SIGNAL;
    }
}

/* returns the delta for a given weight given the input for that weight,
as well as the output and desired output for the current neuron */
float step_linear_update(float input, float error){
    float delta = LEARNING_RATE * (error) * input;
    return delta;
}
