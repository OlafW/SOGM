//
//  wavetable.h
//  WaveTable
//
//  Created by Olaf Wisselink on 21-05-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#ifndef __WaveTable__wavetable__
#define __WaveTable__wavetable__

#include <iostream>
#include "math.h"
using namespace std;

#define SIZE 4096

class WaveTable {
public:
    WaveTable();
    WaveTable(long size);
    ~WaveTable();
    void init();
    void linearInterp(unsigned lookup);
    
private:
    double* data;   //data of wavetable
    long size;  //size of wavetable
    int sampleRate;
};

#endif /* defined(__WaveTable__wavetable__) */
