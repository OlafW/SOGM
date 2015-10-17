#include <iostream>

#include "neuron.h"
#include "art.h"


int main() {
    const int N = 10;
    double vigilance = 0.01;
    double input[N];
    int groups = 5;
    
    srand (unsigned(time(NULL)));
    for (int i=0; i<N; i++) {
        input[i] = rand() % 10;
    }
    
    ART art(N, vigilance, groups);
    art.train(input);
    art.getTrainInfo();
    
    return 0;
}

