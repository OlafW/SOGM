#include "art.h"

ART::ART(unsigned long N, double vigilance, unsigned long groups) {
    this->N = N;
    this->vigilance = vigilance;
    this->groups = groups;
    
    field = new Neuron*[FIELDSIZE];
    neuronCount = 0;
    c = 0.5;
    
    group = new int[groups];
    groupFalseNeg = new int[groups];
    groupFalsePos = new int[groups];
    groupHasNeuron = new bool[groups];
    for (int i=0; i<groups; i++) {
        group[i] = i;
        groupFalseNeg[i] = 0;
        groupFalsePos[i] = 0;
        groupHasNeuron[i] = false;
    }
    falseNeg = 0;
    falsePos = 0;
}

ART::~ART() {
    delete[] field;
}

long ART::evaluate(double* x, unsigned long groupID) {
    if (neuronCount <= 0) {
        addNeuron(x, groupID);  //If groupcount=0, add a new group
        evaluate(x, groupID);
    }
    else {
        double* y = new double[neuronCount]; //Outputs of all the neurons

        for (unsigned long i=0; i<neuronCount; ++i) {
            y[i] = field[i]->evaluate(x);   //Compute the output of every neuron
        }

        unsigned long max_i = 0;    //Find the highest output
        for (unsigned long i=0; i<neuronCount; ++i) {
            if (y[i] > y[max_i]) {
                max_i = i;
            }
        }
        double max_val = y[max_i];
        delete[] y;
        
        if (max_val > vigilance) { //Check if highest output > vigilance
            field[max_i]->won();
            
            return max_i;
        }
        else {
            addNeuron(x, groupID);  //If output<vigilance, add a new group
            return neuronCount -1;
        }
        return -1;
    }
    return 0;
}

void ART::train(double* x) {    
    for (int i=0; i<groups; i++) {
        unsigned long groupCount = neuronCount;
        unsigned long matchID = evaluate(x, group[i]);
        
        if (neuronCount > groupCount) {
            if (groupHasNeuron[group[i]]) {
                groupFalseNeg[group[i]]++;
                falseNeg++;
            }
            else groupHasNeuron[group[i]] = true;
        }
        if (getGroupIDof(matchID) != group[i]) {
            groupFalsePos[group[i]]++;
            falsePos++;
        }
    }
}

void ART::getTrainInfo() {
    cout << "Number of groups: " << neuronCount << endl;
    cout << "Total false negatives: " << falseNeg << endl;
    cout << "Total false positives: " << falsePos << endl;
}

void ART::addNeuron(double* x, unsigned long groupID) {
    field[neuronCount] = new Neuron(x, N, c, groupID);
    neuronCount++;
}

unsigned long ART::getGroupIDof(unsigned long i) {
    return field[i]->getGroupID();
}


