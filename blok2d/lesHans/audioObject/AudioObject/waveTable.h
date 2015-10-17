//
//  waveTable.h
//  WaveTable
//
//  Created by Olaf Wisselink on 21-05-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#ifndef __WaveTable__waveTable__
#define __WaveTable__waveTable__

#include <iostream>
#include "math.h"
using namespace std;

#define SIZE 4096   //Buffersize

class WaveTable {
public:
    WaveTable();
    WaveTable(long size);
    ~WaveTable();
    void init();
    double linearInterp(double lookup);
    
private:
    double* data;   //Data of wavetable
    long size;  //Size of wavetable
    int sampleRate;
};

#endif /* defined(__WaveTable__wavetable__) */
