// Header file for network.cpp

#include "defaults.h"
#include "errors.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifndef _NETWORK_INCLUDED
#define _NETWORK_INCLUDED

#ifndef _NEURON_INCLUDED
class Neuron;
#endif

#ifndef _DATAPOINT_INCLUDED
class Datapoint;
class RunDatapoint;
#endif

#ifndef _DATASET_INCLUDED
class Dataset;
class RunDataset;
#endif

typedef std::vector<Neuron> Neuron_vtr;

class Network {
private:
    // in the base network class, the network size and output dimension coincide
    int network_size;
    int input_dimension;

    // hard array of neurons
    Neuron_vtr neurons;

    flt_vtr input_vector;
    flt_vtr output_vector;


    // boolean controls
    int weights_seeded;
    // int loaded;

protected:
    // accessor methods
    void set_size(int, int);
    void prime_neurons(wa_function, wu_rule);
    void fix_input_vector(flt_vtr);

public:
    Network  ();
    Network (int, int, wa_function, wu_rule);

    // preparation
    void seed_weights();

    // execution and online learning
    /* TODO: this is messy as all get out because lazy
    */
    void run(Datapoint, RunDatapoint&);
    void run(Dataset, RunDataset&);
    void train(Datapoint, RunDatapoint&);
    void train(Dataset, RunDataset&);


    void save(std::string);
    void save(std::string, std::string);

    friend class Neuron;
};

#endif
