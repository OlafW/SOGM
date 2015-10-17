
#ifndef __NeuralNet__neuron__
#define __NeuralNet__neuron__

#include <iostream>
using std::cout;
using std::endl;

class Neuron;

class Neuron {
    
public:
    Neuron(double* x, unsigned long N, double c, unsigned long groupID);
    ~Neuron();
    double evaluate(double* x);
    void updateWeights();
    void won();
    unsigned long getGroupID();
    
private:
    unsigned long N;        //Input vector size
    double c;               //Learning constant
    unsigned long groupID;  //group ID of neuron
    double* weights;        //Weights for every input
    double y;               //Output value
    double* lastX;          //Last input vector
};

#endif
