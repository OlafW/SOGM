#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "event.h"

class Scheduler {	//Friend of Event, Event can acces Scheduler's elements

public:
	Scheduler( double (*fp)() );    //Constructor needs clock function
	~Scheduler();
	bool postForward(EventPtr here, EventPtr aNew);
	bool postBackward(EventPtr here, EventPtr aNew);

	long pending();
	void showInfo(bool val);
	void show();
	EventPtr post(EventPtr toPost);
	EventPtr post(Event &aNew);
	long p();

	double localTime();
	double maxTime();
	double Tstart();
	double Tend();
	double Tlast();
	EventPtr Start();
	EventPtr End();
	EventPtr Last();
	void setLocalTime(double val);
	double advance(double delta);
	void flush();

	double secondsClock();

private:
	EventPtr start;	//Pointer to first element in queue
	EventPtr end;	//Pointer to last element in queue
	EventPtr last;	//Pointer to last inserted element in queue
	double tStart;	//Timestamp of first element
	double tEnd;	//Timestamp of last element
	double tLast;	//Timestamp of last inserted element
	double _localTime;	//Time of this Scheduler
	long total;	//Total of events in queue
	double (*clock)();	//Funtion pointer to a clock funtion
	bool showInfoFlag;
};

#endif
