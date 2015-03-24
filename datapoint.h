// Header file for datapoint.cpp

#ifndef _DATAPOINT_INCLUDED
#define _DATAPOINT_INCLUDED

#include <cstdlib>
#include <iostream>
#include <vector>
#include "defaults.h"

/* pointer to a function with no return, taking two arrays
 of floats, two ints sizing the given arrays, and a final
 array of floats passing additional parameters */
typedef void (*dp_generator)(flt_vtr&, flt_vtr&, flt_vtr&);

class Datapoint{
protected:


public:
    // creates a null-initialized Datapoint
    Datapoint ();

    /* creates a Datapoint with sizes intialized but vectors null'd */
    Datapoint (int, int);

    /* creates a Datapoint initialized by call back to a "generator function" */
    Datapoint (int, int, dp_generator);

    // Same as the above but generator function can take params
    Datapoint (int, int, dp_generator, flt_vtr);

    // Finally, pass the vectors directly;
    Datapoint (flt_vtr, flt_vtr);

    /* Need to find a way to protect these */
    flt_vtr input_vector;
    flt_vtr output_vector;

    int input_dimension();
    int output_dimension();

    // accessor methods
    void generate_empty_point(int, int);
    void generate_point(int, int, dp_generator);
    // Same as the above but generator function can take params
    void generate_point (int, int, dp_generator, flt_vtr);

    // prints the datapoint to the screen
    void print(int);

    friend class RunDatapoint;
};

class RunDatapoint: public Datapoint {
private:
    flt_vtr observation_vector;
public:
    RunDatapoint ();

    /* Construct a RunDatapoint by pairing a Datapoint with a
    vector of size with the Datapoint's output vector */
    RunDatapoint (Datapoint, flt_vtr);

    void error_vector(flt_vtr&);
    float sum_squared_error();

    void print();

};

#endif
