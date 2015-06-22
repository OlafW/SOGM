//
//  waveTable.cpp
//  WaveTable
//
//  Created by Olaf Wisselink on 21-05-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#include "waveTable.h"


WaveTable::WaveTable() {
    size = SIZE+1;  //Size +1 because you want to interpolate the last value of the buffer
    data = new double[size];
    
    if (!data) {
        size = 0;
        cout << "Error allocating memory" << endl;
    }
}

WaveTable::~WaveTable() {
    if (data) delete data;
}

WaveTable::WaveTable(long size) {
    this->size = size+1;
    data = new double[size];
    
    if (!data) {
        size = 0;
        cout << "Error allocating memory" << endl;
    }
}

void WaveTable::init() {
    for (unsigned i=0; i<size; i++) {    //1 period of sine function
        data[i] = sin(i * 2*M_PI / size);
    }
}

double WaveTable::linearInterp(double lookup) {
    int index = int(lookup); //Truncated value of lookup
    double interp = lookup - index;  //Percentage
    double val = 0;
    
    val =  data[index] * (1-interp) +  data[index+1] * interp;   //linear interpolation
    
    return val;
}