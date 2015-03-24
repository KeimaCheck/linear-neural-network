// Header file for datagen.cpp

#ifndef _DATAGEN_INCLUDED
#define _DATAGEN_INCLUDED

#ifndef _DATAPOINT_INCLUDED
class Datapoint;
#endif

#ifndef _DATASET_INCLUDED
class Dataset;
#endif

/* PRECONDITIONS:
T must be a class with members
    int input_dimension
    int output_dimension
    void input_vector(vector<float>&)
    void output_vector(vector<float>&)

and the first two arguments to the constructor of DatapointGenerator
must correspond to the sizes input_dimension and output_dimension.

POSTCONDITION:
    target will be initialized from the T argument
*/
template<class T>
class DatapointGenerator {
    Datapoint target;

public:
    DatapointGenerator();
    DatapointGenerator(int,int, T);

};

/*
T must additionally have a
    void reload()
method.

target will be an initialized Dataset

*/
template<class T>
class DatasetGenerator {
    Dataset target;

public:
    DatasetGenerator();
    DatasetGenerator(int,int,int, T);
};

#endif // _DATAGEN_INCLUDED
