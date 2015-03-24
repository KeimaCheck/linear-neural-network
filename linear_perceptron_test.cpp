/* Instantiates, trains, and tests a neural network with
a single output dimension, two input dimensions, a
linearly seperable dataset, and a step-linear activation
Dependencies:
    Network
    Run/Dataset
    linear_activation

*/
#define INDIM 2
#define OUTDIM 1
#define NSIZE 100

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "defaults.h"
#include "linear_activation.h"
#include "linear_data_generator.h"
#include "datapoint.h"
#include "dataset.h"
#include "neuron.h"
#include "network.h"

using namespace std;

int main(){

    srand(time(NULL));

    flt_vtr weights(INDIM - 1);
    generate_coefficients(weights, INDIM);

    Network n = Network(INDIM,OUTDIM,step_linear_activation,step_linear_update);
    Dataset d_test = Dataset(NSIZE, INDIM, OUTDIM, linear_data_generator, weights);
    Dataset d_train = Dataset(NSIZE, INDIM, OUTDIM, linear_data_generator, weights);

    //d_test.population.size();

    RunDataset r_test;
    RunDataset r_train;

    n.run(d_test, r_test);
    r_test.error_report("outdiddy.txt");
    n.train(d_train, r_train);
    n.run(d_test, r_test);
    r_test.error_report("outdiddy2.txt");

    //std::cout << "Made it this far.";

    return 0;

}
