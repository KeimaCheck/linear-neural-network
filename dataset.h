// Header file for dataset.cpp

#ifndef _DATASET_INCLUDED
#define _DATASET_INCLUDED

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "datapoint.h"

#ifndef _NETWORK_INCLUDED
class Network;
#endif

typedef std::vector<Datapoint> Datapoint_vtr;
typedef std::vector<RunDatapoint> RunDatapoint_vtr;

class Dataset{
/* TODO:
    needs options for parameters in generator function
*/
protected:

    int input_dimension;
    int output_dimension;

    // accessor methods invoked by subclasses only
    void set_size(int,int);
    void generate_empty_set(int);
    void generate_set(int, dp_generator);
    void generate_set(int, dp_generator, flt_vtr);
public:
    // null-initialized Dataset
    Dataset();
    // size-initialized Dataset
    Dataset(int,int,int);
    // fully initialized Dataset
    Dataset(int,int,int, dp_generator);
    // fully initialized Dataset, generator takes params
    Dataset(int,int,int, dp_generator, flt_vtr);


    Datapoint_vtr population;

    int population_size();

    // prints the Dataset to the screen
    void print();

    friend class RunDataset;
};

class RunDataset: public Dataset{
private:

public:
    /* construct a RunDataset by running a Network on each Datapoint
    of a given Dataset */
    RunDataset();
    RunDataset(Dataset, Network*);
    RunDataset(Dataset, Network*, int);
    RunDatapoint_vtr population;

    void error_report();
    void error_report(std::string);

    float mean_sum_squared_error();

    int population_size();
    void print();

};


#endif
