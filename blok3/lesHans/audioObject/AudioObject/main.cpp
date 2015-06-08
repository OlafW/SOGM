//
//  main.cpp
//  AudioObject
//
//  Created by Olaf Wisselink on 30-04-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#include <iostream>
#include "audioObj.h"

using namespace std;

int main(int argc, const char * argv[])
{
    audioObj A;
    
    for (int i=0; i<5; i++) {
        audioObjPtr x;
        A.connectA(x);
    }
    
    WaveTable sinus;
    sinus.init();
    
    double* data = new double[SIZE*2];
    float rate = 0.5;
    
    for (unsigned long i=0; i<SIZE; i++) {
        data[i] = sinus.linearInterp(i*rate);
    }

    return 0;
}

