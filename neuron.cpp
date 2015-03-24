/* A simple neuron class for implementing neural nets.
This could also have been called "Perceptron," although
that term has a different use in this library.

Dependencies:
    Forward declarations of Network class

Prerequisites:
    An activation function (this is presumably linear or step-linear)

*/



#include "network.h"
#include "neuron.h"

Neuron::Neuron(){}

// accessor methods
void Neuron::initialize(int id, int input_size, flt_vtr& inputs, Network* home){
size_error(input_size, inputs.size(), "Neuron::initialize(...)");

    id_no = id;
    input_dimension = input_size;
    input_vector = &inputs;
    weights = flt_vtr(input_dimension);
    weights_seeded = 0;
    network = home;
}



void Neuron::set_functions(wa_function activation, wu_rule update){
    activation_function = activation;
    update_rule = update;
}

// preparatory methods
void Neuron::seed_weights(){
if (not weights_seeded){

    int i;
    float temp;
    for (i=0; i<input_dimension; i++){
        temp = rand();
        temp = (temp / RAND_MAX);
        temp = MAX_INIT_WEIGHT * temp;
        weights[i] = temp;

    }

    weights_seeded = 1;
}
else { std::cout << "Cannot reseed weights of Neuron " << id_no;}
}

// execution and training

void Neuron::activate(){
    float output = (*activation_function)(input_vector, weights);

    network->output_vector[id_no] = output;
}

void Neuron::update(float error){
    int i;

    for (i=0; i<input_dimension; i++){
        weights[i] = weights[i] + (*update_rule)(input_vector->at(i), error);
    }
}

// administrative

void Neuron::save(std::ofstream& save_location_stream){
    save_location_stream << "~~neu\n" << id_no << "\n";

    int i;
    for (i=0; i<input_dimension; i++){
        save_location_stream << weights[i] << " ";

    }

    save_location_stream << "\nneu~~";
}
