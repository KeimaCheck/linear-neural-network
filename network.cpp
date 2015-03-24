/* Implementation of a base network class with a single layer and
equipped for online learning.

Dependencies:
    Run/Dataset (Note: network.h includes Dataset/point)
    Neuron (NOTE: network.h includes neuron.h)

Any class extending Network should extend Run/Dataset/point
and Neuron as necessary.
*/

#include "neuron.h"
#include "dataset.h"
#include "datapoint.h"
#include "network.h"

Network::Network(){}

Network::Network(int no_of_inputs, int no_of_nodes, wa_function activation_function, wu_rule update_rule){
    weights_seeded = 0;
    set_size(no_of_inputs, no_of_nodes);
    prime_neurons(activation_function, update_rule);
    seed_weights();
}

// accessor methods
void Network::set_size(int no_of_inputs, int no_of_nodes){
    // set the ize parameters
    input_dimension = no_of_inputs;
    network_size = no_of_nodes;

    // create an array of null-initialized neurons
    neurons = Neuron_vtr(network_size);

    // create i/o vectors
    input_vector = flt_vtr(input_dimension);
    output_vector = flt_vtr(network_size);
}

void Network::prime_neurons(wa_function activation_function, wu_rule update_rule){
    int i;

    /* loop over the neurons, calling their accessor methods to set their
    sizes, vectors, IDs, and functions
    */
    for(i=0; i<network_size; i++){
        neurons[i].initialize(i, input_dimension, input_vector, this);
        neurons[i].set_functions(activation_function, update_rule);
    }
}

void Network::fix_input_vector(flt_vtr inputs){
size_error(input_vector.size(), inputs.size(), "Network::fix_input_vector()");
    int i;

    for(i=0; i< input_dimension; i++){
        input_vector[i] = inputs[i];
    }
}

// preparatory methods

void Network::seed_weights(){
if ( not weights_seeded){
    int i;

    for(i=0; i<network_size; i++){
        neurons[i].seed_weights();
    }
    weights_seeded = 1;
}
}
// execution and online training

void Network::run(Datapoint instance, RunDatapoint& output){
    int i;

    // updating the Network's input vector will update the Neurons' correspondingly
    fix_input_vector(instance.input_vector);

    // update all the outputs
    for (i=0; i<network_size; i++){
        neurons[i].activate();
    }

    // store the output
    output = RunDatapoint(instance, output_vector);


}

void Network::run(Dataset sample, RunDataset& output){
    output = RunDataset(sample, this);
}

// TODO: clean this up
void Network::train(Datapoint training_instance, RunDatapoint& output){
    int i;
    flt_vtr errors(network_size, 0);

    fix_input_vector(training_instance.input_vector);

    for (i=0; i<network_size; i++){
        neurons[i].activate();
    }

    output = RunDatapoint(training_instance, output_vector);

    output.error_vector(errors);

    for (i=0; i<network_size; i++){
        // TODO: write this method
        neurons[i].update(errors[i]);
    }

}

void Network::train(Dataset training_sample, RunDataset& output){
    output = RunDataset(training_sample, this, 1);
}

void Network::save(std::string filename){
    save(filename, "");
}

void Network::save(std::string filename, std::string comment){
    std::ofstream save_location(filename);
    save_location << "~net\n" << input_dimension << "\n" << network_size << "\n" << comment << "\nnet~";

    int i;
    for (i=0; i<network_size; i++){
        save_location << "\n\n";
        neurons[i].save(save_location);
    }

    save_location.close();
}
