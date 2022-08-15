#ifndef CHANGEMAKER_CHANGEMAKER_H
#define CHANGEMAKER_CHANGEMAKER_H

#include <string>
#include "Stack.h"
using namespace std;

class ChangeMaker { //////only two things?
private:
    // coin counts
    int quarterCount;
    int dimeCount;
    int nickelCount;
    int pennyCount;

    // coins desired
    int quartersDesired;
    int dimesDesired;
    int nickelsDesired;
    int penniesDesired;

    // stacks
    Stack stackOfCoins;

    // file names
    string inputFileName;
    string outputFileName;

public:
    ~ChangeMaker(); // destructor
    ChangeMaker(); // creates change maker object
    void readCoins(); // reads coins from input file
    void getChange(); // enacts change plan from checkChange
    bool checkChange(int desiredChange); // creates changePlan
};


#endif //CHANGEMAKER_CHANGEMAKER_H