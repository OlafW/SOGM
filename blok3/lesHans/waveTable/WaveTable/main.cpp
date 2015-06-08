//
//  main.cpp
//  WaveTable
//
//  Created by Olaf Wisselink on 21-05-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#include <iostream>
#include "wavetable.h"

int main(int argc, const char * argv[])
{
    WaveTable sinus;
    sinus.init();
    
    double* data = new double[SIZE*2];
    float rate = 0.5;
    
    for (unsigned long i=0; i<SIZE; i++) {
        data[i] = sinus.linearInterp(i*rate);
    }
    
    return 0;
}

