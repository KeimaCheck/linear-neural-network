// Default defines for the neural network library

#ifndef _DEFAULTS_INCLUDED
#define _DEFAULTS_INCLUDED

// floating point parameters for activation functions
#define MAX_SIGNAL 1.0
#define MIN_SIGNAL -1.0

/* higher values correspond to faster, likely less accurate learning,
lower values to slower, possibly more accurate learning*/
#define LEARNING_RATE .7

// constants for data generation
#define YRANGE 20
#define XRANGE 20
#define MAX_SLOPE 1.25
#define MIN_SLOPE .75

// starting weight parameters
#define MAX_INIT_WEIGHT 1


// includes
#include <vector>

/* typedefs */
typedef std::vector<float> flt_vtr;

// activation function
typedef float (*wa_function)(flt_vtr*, flt_vtr);
// weight update rule
// takes an error and an input
typedef float (*wu_rule)(float, float);


#endif
