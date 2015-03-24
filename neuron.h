// Header file for neuron.cpp

// weighted activation function
// takes inputs and weights

#include "defaults.h"
#include "errors.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

#ifndef _NETWORK_INCLUDED
class Network;
#endif // _NETWORK_INCLUDED

class Neuron {
protected:
    /* unique identifier of this Neuron---must correspond
    to the array index of this Neuron in its Network's array
    of Neurons, as well as the array index where this Neuron's
    output is stored in the output vector
    */
    int id_no;
    Network* network;

    int input_dimension;
    flt_vtr weights;

    // this should point to the input vector of the network
    flt_vtr *input_vector;

    wa_function activation_function;
    wu_rule update_rule;

    // boolean controls
    int weights_seeded;

protected:
    // accessor methods
    void initialize(int, int, flt_vtr&, Network*);
    void set_functions(wa_function, wu_rule);

public:
    // TODO: There should be a constructor that doesn't suck
    Neuron();

    void seed_weights();

    void activate();
    void update(float);

    void save(std::ofstream&);

    friend class Network;
};
