//
//  midiEvent.cpp
//  scheduler
//
//  Created by Olaf Wisselink on 13-06-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#include "midiEvent.h"

//Midi NoteOn class
MidiNote::MidiNote(double time, int channel, int key, int vel, double duration) : Event(time) {
    this->channel = channel;
    this->key = key;
    this->vel = vel;
    this->duration = duration;
}

void MidiNote::doIt() {
    cout << "MIDIEvent NoteOn, Key: "<< key << " Velocity: " << vel << " Duration: " << duration << endl;
    
    noteOffPtr ev = new noteOff(time+duration,channel,key,vel,duration);   //Note on event triggers a note off event
    myScheduler->post(ev);
}

double MidiNote::getDuration() {
    return duration;
}


//Midi NoteOff class
noteOff::noteOff(double time, int channel, int key, int vel, double duration) : Event(time) {
    this->channel = channel;
    this->key = key;
    this->vel = vel;
    this->duration = duration;
}

void noteOff::doIt() {
    cout << "MIDIEvent NoteOff, Key: "<< key << " Velocity: " << vel << " Duration: " << duration << endl;
}
