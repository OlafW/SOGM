//
//  wavetable.cpp
//  WaveTable
//
//  Created by Olaf Wisselink on 21-05-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#include "wavetable.h"


WaveTable::WaveTable() {
    size = SIZE+1;
    data = new double[size];
}

WaveTable::~WaveTable() {
    if (data) delete data;
}

WaveTable::WaveTable(long size) {
    this->size = size+1;
    data = new double[size];
}

void WaveTable::init() {
    
    for (unsigned i=0; i<size; i++) {    //1 period of sinus
        data[i] = sin(i * 2*M_PI / size);
        //cout << data[i] << endl;
    }
}

void WaveTable::linearInterp(unsigned lookup) {
    double interp = lookup/size;
    lookup = floor(lookup % size);

    data[lookup] =  data[lookup] * (1-interp) +  data[lookup+1] * interp;   //linear interpolation
}