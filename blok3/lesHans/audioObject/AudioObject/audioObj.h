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
    bool connectA(audioObjPtr aPtr);    //Insert nieuw audioObject
    bool connectB(audioObjPtr bPtr);
    
protected:
    audioObjPtr *inA, *inB; //Array van inputs van audio object (is **) Tot nu toe 2 inputs
    int numA, numB; //Aantal pointers(inputs) in inA en inB
    int sizeA, sizeB; //Grootte van de array inA en inB
    double outBuffer[BUFFERSIZE];
    long lastTime;  //Laatste keer uitgerekend
    double lastValue;   //Laatste waarde uitgerekend
};

#endif /* defined(__AudioObject__audioObj__) */
