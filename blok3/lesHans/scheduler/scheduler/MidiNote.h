//
//  MidiNote.h
//  scheduler
//
//  Created by Olaf Wisselink on 08-06-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#ifndef __scheduler__MidiNote__
#define __scheduler__MidiNote__

#include <iostream>
#include "event.h"
#include "noteOff.h"

class MidiNote : public Event {
public:
    MidiNote(double time, int channel, int key, int vel, double duration);
    ~MidiNote();
    void doIt();
    
private:
    int channel;
    int key;
    int vel;
    double duration;   
};

#endif /* defined(__scheduler__midiEvent__) */
