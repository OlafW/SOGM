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
    if(res > 1.0) { //zaagtand maken als test
      res = -1.0;
    }
    return res;
}

double audioObj::out(long t) {
    if (t <= lastTime) {    //Check of de berekening voor tijdstip t al is gedaan
        return lastValue;
    }
    lastValue = process(t);
    lastTime = t;
    return lastValue;
}

bool audioObj::connectA(audioObjPtr aPtr) {
    if (numA >= sizeA) {    //Is aantal pointers groter of gelijk aan arraysize: resize
        int newSize;
        audioObjPtr *temp;
        
        newSize = 2 * sizeA;
        if (newSize < 1) {
           newSize = 1;
        }
        temp = new audioObjPtr[newSize];    //Nieuwe array van audioObjPtr's
        for (int j=0; j<numA; j++) {    //Kopieren naar deze nieuwe
            temp[j] = inA[j];
        }
        if (inA) delete[] inA;  //Verwijder de oude array
        inA = temp; //inA wijst nu naar de nieuwe array
        sizeA = newSize;   //Arraygrootte is nieuwe grootte
        cout << newSize << endl;
    }
    inA[numA] = aPtr;
    numA ++;    //Aantal pointers in de array += 1
    
    return true;
}

bool audioObj::connectB(audioObjPtr bPtr) {
    if (numA >= sizeB) {    //Is aantal pointers groter dan arraysize: resize
        int newSize;
        audioObjPtr *temp;
        
        newSize = 2 * sizeB;
        if (newSize < 1) {
            newSize = 1;
        }
        temp = new audioObjPtr[newSize];    //Nieuwe array van audioObjPtr's
        for (int j=0; j<numB; j++) {    //Kopieren naar deze nieuwe
            temp[j] = inB[j];
        }
        if (inB) delete[] inB;  //Verwijder de oude array
        inA = temp; //inA wijst nu naar de nieuwe array
        sizeA = newSize;    //Arraygrootte is nieuwe grootte
    }
    inA[numB] = bPtr;   //Insert nieuw audioObject in de array
    numA ++;    //Arraygrootte is nieuwe grootte
    
    return true;
}
