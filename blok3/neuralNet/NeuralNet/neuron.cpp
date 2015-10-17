#include "neuron.h"

Neuron::Neuron(double* x, unsigned long N, double c, unsigned long groupID) {
    this->N = N;
    this->c = c;
    this->groupID = groupID;
    y = 0;

    weights = new double[N];
    for (unsigned long n=0; n<N; ++n) {
        weights[n] = x[n];
    }
}

Neuron::~Neuron() {

    delete[] weights;
}

double Neuron::evaluate(double* x) {
    y = 0;

    for (unsigned long n=0; n<N; ++n) {
        y+= x[n] * weights[n];  //Output is the sum of all inputs times their weights (In product)
    }
    lastX = x;  //Last input vector is current input vector
    return y;
}

void Neuron::updateWeights() {
    double error = 0;

    for (unsigned long n=0; n<N; ++n) {
        error = lastX[n] - weights[n]; //Error is difference between last input val - current val
        weights[n] += c * error;    //Adjust the weights according to error and learning constant
    }
}

void Neuron::won() {
    
    updateWeights();
}

unsigned long Neuron::getGroupID() {
    
    return groupID;
}
