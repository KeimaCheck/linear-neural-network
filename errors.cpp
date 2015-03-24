// tests to catch and report unexpected behavior
// outside of main(), these should be the only routines
// allowed to terminate a program

#include "errors.h"



void size_error(int a, int b, std::string callback){
    // Requires a == b (i.e. a - b ==0)

    if (a-b == 0){}
    else {
        std::cerr << "Size mismatch in function " << callback << ".\nRequires parameters equal.";
        exit(EXIT_FAILURE);
    }

}

void size_error(int a, int b, int difference, std::string callback){
    // Requires a == b + difference (i.e. a-b == difference)

    if (a-b == difference){}
    else {
        std::cerr << "Size mismatch in function " << callback << ".\nRequires parameters differ by " << difference << ".";
        exit(EXIT_FAILURE);
    }
}
