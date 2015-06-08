//
//  audioObj.h
//  AudioObject
//
//  Created by Olaf Wisselink on 30-04-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#ifndef __AudioObject__audioObj__
#define __AudioObject__audioObj__

#include <iostream>
#define BUFFERSIZE 128
using namespace std;

class audioObj; //Forward declaration
typedef audioObj* audioObjPtr;

class audioObj {
public:
    audioObj();
    virtual double process(long t);
    double out(long t);
    bool connectA(audioObjPtr aPtr);    //Insert new audioObject
    bool connectB(audioObjPtr bPtr);    //Insert new audioObject
    
protected:
    audioObjPtr *inA, *inB; //Array of inputs of audio object (is **) So far 2 inputs
    int numA, numB; //Number of pointers(inputs) of inA and inB
    int sizeA, sizeB; //Size of array inA en inB
    double outBuffer[BUFFERSIZE];
    long lastTime;  //Last time calculated
    double lastValue;   //Last value calculated
};

#endif /* defined(__AudioObject__audioObj__) */
