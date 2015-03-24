/* Implements simple containers for Run/Datapoints and
automated generation of datasets.

Dependencies:
    Datapoint
    Network

Any class extending Network may need a corresponding extension
of Dataset, which may require a corresponding extension of
Datapoint
*/


#include "network.h"
#include "dataset.h"

using namespace std;

// Dataset

// accessor methods
void Dataset::set_size(int in, int out){
    input_dimension = in;
    output_dimension = out;
}

void Dataset::generate_empty_set(int pop){
    // Note: sets the return value of population_size()
    population = Datapoint_vtr(pop);

    // size-initialize the Datapoints
    int i;
    for (i=0; i<population_size(); i++){
        population[i].generate_empty_point(input_dimension, output_dimension);
    }
}

void Dataset::generate_set(int pop, dp_generator generator){
    population = Datapoint_vtr(pop, Datapoint());

    int i;
    for (i=0; i<population_size(); i++){
        population[i].generate_point(input_dimension, output_dimension, generator);
    }
}

void Dataset::generate_set(int pop, dp_generator generator, flt_vtr params){
    population = Datapoint_vtr(pop, Datapoint());

    int i;
    for (i=0; i<population_size(); i++){
        population[i].generate_point(input_dimension, output_dimension, generator, params);
    }
}

// null-initialized Dataset
Dataset::Dataset(){
    set_size(0,0);

    population = Datapoint_vtr();
}

// size-initialized Dataset
Dataset::Dataset(int pop, int in, int out){
    set_size(in,out);

    generate_empty_set(pop);
}

// fully-initialized Dataset
Dataset::Dataset(int pop, int in, int out, dp_generator generator){
    set_size(in,out);

    generate_set(pop, generator);
}

// same as above with parameters
Dataset::Dataset(int pop, int in, int out, dp_generator generator, flt_vtr params){
    set_size(in,out);

    generate_set(pop, generator, params);
}

int Dataset::population_size(){
    return population.size();
}

int RunDataset::population_size(){
    return population.size();
}

void Dataset::print(){
    int i;

    cout << "(" << input_dimension << "," << output_dimension << ")" << "\n\n";

    for(i=0; i<population_size(); i++){
        population[i].print(0);
    }
}

// RunDataset

RunDataset::RunDataset(){
}

RunDataset::RunDataset(Dataset sample, Network* runner){
    /* run the Network on each Datapoint of sample, saving the
    output RunDatapoint in the RunDataset under construction.
    */

    set_size(sample.input_dimension, sample.output_dimension);
    int a = sample.population_size();

    // return value of this.population_size() set
    population = RunDatapoint_vtr(a, RunDatapoint());


    int i;
    for(i=0; i<population_size(); i++){
        runner->run(sample.population[i], population[i]);
    }

}

RunDataset::RunDataset(Dataset training_sample, Network* runner, int train){
    /* same as the above, only runs the online training algorithm
    instead of the straight run algorithm
    */
    set_size(training_sample.input_dimension, training_sample.output_dimension);

    int a = training_sample.population_size();
    population = RunDatapoint_vtr(a, RunDatapoint());



    int i;
    for(i=0; i<population_size(); i++){
        runner->train(training_sample.population[i], population[i]);
    }


}

void RunDataset::error_report(){
    int i, j;
    flt_vtr err_v(output_dimension,0);
    for(i=0; i<population_size(); i++){
        population[i].error_vector(err_v);
        for (j =0; j<output_dimension; j++){
            std::cout << err_v[j] << " ";
        }
        std::cout<< "\n";
    }
    std::cout<<"\n";
}

void RunDataset::error_report(std::string filename){
    std::ofstream report_location(filename);

    int i, j;
    flt_vtr err_v(output_dimension, 0);
    for (i=0; i<population_size(); i++) {
        population[i].error_vector(err_v);
        for (j=0; j<output_dimension; j++){
            report_location << err_v[j] << " ";
        }
        report_location << "\n";
    }
    report_location << "\n";
}

void RunDataset::print(){
    int i;

    cout << "(" << input_dimension << "," << output_dimension << ")" << "\n\n";

    for(i=0; i<population_size(); i++){
        population[i].print();
    }
}
