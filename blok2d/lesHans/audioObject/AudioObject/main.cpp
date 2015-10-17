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
    
    for (int i=0; i<5; i++) {   //Connect some audioObjPtr's for testing
        audioObjPtr x;
        A.connectA(x);
    }
    
    WaveTable sinus;
    sinus.init();
    
    double data[SIZE*2];
    float rate = 0.5;
    
    for (unsigned long i=0; i<SIZE; i++) {
        data[i] = sinus.linearInterp(i*rate);   //Fill wavetable with interpolated sine function (half the rate)
    }

    return 0;
}

