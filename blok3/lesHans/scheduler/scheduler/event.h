#ifndef EVENT_H
#define EVENT_H

#include <iostream>
using namespace std;

class Event;
typedef Event* EventPtr;

class Scheduler;
typedef Scheduler* SchedulerPtr;

class Event {   //Element in double linked list
friend class Scheduler;

public:
	Event(double time);
	~Event();
	EventPtr insert(EventPtr ev);
	void show();
	void showTiming();
	virtual void doIt();

	EventPtr prevEventPtr();
	EventPtr nextEventPtr();
	bool GEthan(Event x);
	bool operator >= (Event x);
	bool operator < (Event x);

protected:
	double time; //timeStamp of event

private:
	static long number;
	long ID; //ID = number
	SchedulerPtr myScheduler;	//Scheduler for this event
	EventPtr prev; //Pointer to previous in queue
	EventPtr next; //Pointer to next in queue
};

#endif
