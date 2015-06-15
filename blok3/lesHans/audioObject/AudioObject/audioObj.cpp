//
//  audioObj.cpp
//  AudioObject
//
//  Created by Olaf Wisselink on 30-04-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#include "audioObj.h"

audioObj::audioObj() {
    inA = inB = nullptr;
    numA = numB = 0;
    lastTime = 0;
    lastValue = 0;
    sizeA = sizeB = 0;
}

double audioObj::process(long t) {
    static double res = 0;
    res += 0.1;
    if(res > 1.0) { //Sawtooth for testing
      res = -1.0;
    }
    return res;
}

double audioObj::out(long t) {
    if (t <= lastTime) {    //Check if already calculated for time t
        return lastValue;
    }
    lastValue = process(t);
    lastTime = t;
    return lastValue;
}

bool audioObj::connectA(audioObjPtr aPtr) { //Insert a new audioObject in inA
    if (numA >= sizeA) {    //If number of pointers is greater than arraysize: resize the array
        int newSize;
        audioObjPtr *temp;
        
        newSize = 2 * sizeA;
        if (newSize < 1) {
           newSize = 1;
        }
        temp = new audioObjPtr[newSize];    //New array of audioObjPtr's
        for (int j=0; j<numA; j++) {    //Copy old array to new one
            temp[j] = inA[j];
        }
        if (inA) delete[] inA;  //Delete old array
        inA = temp; //inA now points to the new array
        sizeA = newSize;    //Size is now the new size
        cout << "New size: " << newSize << endl;
    }
    inA[numA] = aPtr; //Insert the new audioObject
    numA ++;    //Number of pointers += 1
    
    return true;
}

bool audioObj::connectB(audioObjPtr bPtr) { //Insert a new audioObj in inB
    if (numB >= sizeB) {    //If number of pointers is greater than arraysize: resize the array
        int newSize;
        audioObjPtr *temp;
        
        newSize = 2 * sizeB;
        if (newSize < 1) {
            newSize = 1;
        }
        temp = new audioObjPtr[newSize];    //New array of audioObjPtr's
        for (int j=0; j<numB; j++) {    //Copy old array to new one
            temp[j] = inB[j];
        }
        if (inB) delete[] inB;  //Delete old array
        inB = temp; //inB now points to the new array
        sizeB = newSize;    //Size is now the new size
    }
    inB[numB] = bPtr;   //Insert the new audioObject
    numB ++;    //Number of pointers += 1
    
    return true;
}
