/* Implements a simple container for input/output pairs of data

Dependencies:
    None
    cstdlib
    iostream

Any class extending Dataset may need a corresponding extension of
Datapoint

TODO:
    fix spaghetti-like properties
*/

#include "datapoint.h"


// Datapoint

// accessor methods to get size
int Datapoint::input_dimension(){
    return input_vector.size();
}

int Datapoint::output_dimension(){
    return output_vector.size();
}

// accessor method to partially generate the datapoint
void Datapoint::generate_empty_point(int in, int out){
    input_vector = flt_vtr(in);
    output_vector = flt_vtr(out);
}

// accessor method to generate the datapoint
void Datapoint::generate_point(int in, int out, dp_generator generator){
     generate_empty_point(in, out);
     flt_vtr null_vec;
     // only used when the generator doesn't require params
     (*generator)(input_vector, output_vector, null_vec);
}

void Datapoint::generate_point(int in, int out, dp_generator generator, flt_vtr params){
    generate_empty_point(in, out);
    (*generator)(input_vector,output_vector, params);
}

// Null-initialized Datapoint
Datapoint::Datapoint(){
    generate_empty_point(0,0);
}

// Size-initialized Datapoint with null vectors
Datapoint::Datapoint(int in, int out){
    generate_empty_point(in, out);
}

// Fully-initialized Datapoint
Datapoint::Datapoint(int in, int out, dp_generator generator){
    generate_point(in,out,generator);
}

Datapoint::Datapoint(int in, int out, dp_generator generator, flt_vtr params){
    generate_point(in,out,generator, params);
}

Datapoint::Datapoint(flt_vtr inputs, flt_vtr outputs){}

void Datapoint::print(int print_size){
    int i;

    if (print_size) {
        // print the size as an ordered pair
        std::cout << "(" << input_dimension() << "," << output_dimension() << ")" << "\n";
    }
    // print the first input entry, no comma
    std::cout << input_vector[0];

    // print a comma then the next entry, repeat
    for(i=1; i<input_dimension(); i++){
        std::cout << ", " << input_vector[i];
    }
    std::cout << "\n";

    std::cout << output_vector[0];
    for (i=1; i<output_dimension(); i++){
        std::cout << ", " << output_vector[i];
    }

    std::cout << "\n\n";
}

// RunDatapoint

RunDatapoint::RunDatapoint(){}

RunDatapoint::RunDatapoint(Datapoint instance, flt_vtr observations){
    int i;

    // initialize
    generate_empty_point(instance.input_dimension(), instance.output_dimension());
    observation_vector = flt_vtr(output_dimension());

    // TODO: clean up
    for(i=0; i<input_dimension(); i++){
        input_vector[i] = instance.input_vector[i];
    }
    for(i=0; i<output_dimension(); i++){
        output_vector[i] = instance.output_vector[i];
        observation_vector[i] = observations[i];
    }


}

void RunDatapoint::error_vector(flt_vtr& storage){
    int i;

    for(i=0; i<output_dimension(); i++){
        storage[i] = output_vector[i] - observation_vector[i];
    }

}

void RunDatapoint::print(){
    int i;

    // print the first input entry, no comma
    std::cout << input_vector[0];

    // print a comma then the next entry, repeat
    for(i=1; i<input_dimension(); i++){
        std::cout << ", " << input_vector[i];
    }
    std::cout << "\n";

    std::cout << output_vector[0];
    for (i=1; i<output_dimension(); i++){
        std::cout << ", " << output_vector[i];
    }

    std::cout << "\n";

    std::cout << observation_vector[0];
    for (i=1; i<output_dimension(); i++){
        std::cout << ", " << observation_vector[i];
    }

    std::cout << "\n\n";
}
