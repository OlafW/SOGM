//
//  noteOff.h
//  scheduler
//
//  Created by Olaf Wisselink on 12-06-15.
//  Copyright (c) 2015 olaf. All rights reserved.
//

#ifndef __scheduler__noteOff__
#define __scheduler__noteOff__

#include <iostream>
#include "event.h"

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

#endif /* defined(__scheduler__noteOFF__) */
