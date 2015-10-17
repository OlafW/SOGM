//
//  midiEvent.h
//  scheduler
//
//  Created by Olaf Wisselink on 13-06-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#ifndef __scheduler__midiEvent__
#define __scheduler__midiEvent__

#include <iostream>
#include "event.h"
#include "scheduler.h"

//Forward declarations
class MidiNote;

class noteOff;
typedef noteOff* noteOffPtr;


//Midi NoteOn class
class MidiNote : public Event {
public:
    MidiNote(double time, int channel, int key, int vel, double duration);
    void doIt();
    double getDuration();
    
private:
    int channel;
    int key;
    int vel;
    double duration;
};


//Midi NoteOff class
class noteOff : public Event {
public:
    noteOff(double time, int channel, int key, int vel, double duration);
    void doIt();
    
private:
    int channel;
    int key;
    int vel;
    double duration;
};

#endif /* defined(__scheduler__midiEvent__) */
