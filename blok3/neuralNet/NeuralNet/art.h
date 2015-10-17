
#ifndef __NeuralNet__art__
#define __NeuralNet__art__

#include "neuron.h"
#include "math.h"
#include <time.h>

#define VECSIZE 256 //Input vector size
#define FIELDSIZE 2048 //Number of neurons in network

class ART { //Adaptive Resonance Theory

public:
    ART(unsigned long N, double vigilance, unsigned long groups);
    ~ART();
    long evaluate(double* x, unsigned long groupID);
    void train(double* x);
    void getTrainInfo();
    
    unsigned long getGroupIDof(unsigned long i);
    void addNeuron(double* x, unsigned long groupID);

private:
    unsigned long N;            //Input vector size
    double vigilance;           //Threshold
    unsigned long groups;        //Maximum amount of desired groups
    Neuron** field;             //Pointer to all neurons in network
    double c;                   //Learning constant
    unsigned long neuronCount;  //Neuron count = groupcount
    
    //Training variables
    int* group;
    bool* groupHasNeuron;
    int* groupFalseNeg;
    int* groupFalsePos;
    int falseNeg;
    int falsePos;
};

#endif
