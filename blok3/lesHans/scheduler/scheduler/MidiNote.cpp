//
//  MIDInote
//  scheduler
//
//  Created by Olaf Wisselink on 08-06-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#include "MidiNote.h"

MidiNote::MidiNote(double time, int channel, int key, int vel, double duration) : Event(time) {
    this->channel = channel;
    this->key = key;
    this->vel = vel;
    this->duration = duration;
}

MidiNote::~MidiNote() {
    
}

void MidiNote::doIt() {
    cout << "MIDIEvent Note On key: "<< key << endl;;
}