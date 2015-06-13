//
//  noteOff.cpp
//  scheduler
//
//  Created by Olaf Wisselink on 12-06-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#include "noteOFF.h"

noteOff::noteOff(double time, int channel, int key, int vel, double duration) : Event(time) {
    this->channel = channel;
    this->key = key;
    this->vel = vel;
    this->duration = duration;
}

void noteOff::doIt() {
    cout << "MIDIEvent Note Off key: " << key << endl;
}
