#ifndef EVENT_H
#define EVENT_H

#include <iostream>
using namespace std;

class Event;
typedef Event* EventPtr;

class Event {
public:
	Event(long timeStamp);
	EventPtr insert(EventPtr inserted);
	EventPtr prevEventPtr();
	EventPtr nextEventPtr();
	void show();

	virtual void doIt();
	bool GEthan(Event x);
	bool operator >= (Event x);
	bool operator < (Event x);

private:
	static long index;
	long ID; //welke het is in de lijst
	double timeStamp; //timeStamp
	EventPtr prev; //pointer naar de vorige in de lijst
	EventPtr next; //pointer naar de volgende in de lijst
};

#endif
