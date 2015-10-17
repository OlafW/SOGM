#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "event.h"

//Global Clock functions
double sampleClock();
double secondsClock();

class Scheduler {	
public:
	Scheduler( double (*fp)() );    //Constructor gets clock function (function pointer)
	~Scheduler();

	void show();
	EventPtr post(EventPtr toPost);
	EventPtr post(Event &aNew);
	long run();
	void flush();

private:
	EventPtr start;	//Pointer to first element in queue
	EventPtr end;	//Pointer to last element in queue
	EventPtr last;	//Pointer to last inserted element in queue
	double tStart;	//Timestamp of first element
	double tEnd;	//Timestamp of last element
	double tLast;	//Timestamp of last inserted element
	double localTime;	//Time of this Scheduler
	long total;	//Total of events in queue
	double (*clock)();	//Function pointer to a clock funtion
};

#endif
