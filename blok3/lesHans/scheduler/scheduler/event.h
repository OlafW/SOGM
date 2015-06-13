#ifndef EVENT_H
#define EVENT_H

#include <iostream>
using namespace std;

class Event;    //Forward declarations
typedef Event* EventPtr;

class Scheduler;
typedef Scheduler* SchedulerPtr;

class Event {   //Element in double linked list
friend class Scheduler;     //Friend of Event, Event can access Scheduler's elements

public:
	Event(double time); //Constructor with timeStamp
	~Event();
    EventPtr prepend(EventPtr ev);
	EventPtr append(EventPtr ev);
	void show();
	void showTiming();
	virtual void doIt();    //Overrided by inheriting class

	bool operator >= (Event x); //Operator overloading
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
