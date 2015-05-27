#include "Event.h"

long Event::number = 0;

Event::Event(double time) {
	ID = number++;
	this->time = time;
	next = NULL;
	prev = NULL;
}

Event::~Event() {
	if (next) {
		 next->prev = prev;	//Delete this, next->prev is this->prev
	}
	else {
		cout << "Last in queue?" << endl;
	}
	if (prev) {
		 prev->next = next; //Delete this, prev->next is this->next
	}
	else {
		cout << "First in queue?" << endl;
	}
	if (prev != NULL) {
		cout << "Execution of non first event" << endl;
	}
}

EventPtr Event::insert(EventPtr ev) {
	ev->next = next;	//Next of new event becomes this next
	if (next) {
		next->prev = ev;	//Prev of next becomes new ev
	}
	next = ev;	//This next becomes new ev
	ev->prev = this; //Prev of new ev becomes this
	return ev;
}

void Event::show() {
	cout << "Own ID: " << this->ID << endl;
	cout << "Own time :" << time << endl;

	if (prev) {
		cout << "ID of previous: " << prev->ID << endl;
	}
	if (next) {
		cout << "ID of next: " << next->ID << endl;
	}
}

void Event::showTiming() {
	cout << "At time:    " << time << " \t ID:      " << ID << endl;
	if(prev) {
		 cout << "Prev at time: " << prev->time << " \t prev ID: " << prev->ID << endl;
	}
	else {
		cout << "No prev, prev: NULL" << endl;
	}
	if(next) {
		cout << "Next at time: " << next->time << " \t next ID: " << next->ID << endl;
	}
	else {
		cout << "No next, next: NULL" << endl;
	}
}

void Event::doIt() {
	cout << "Event::doit() " << endl;
	show();
}

EventPtr Event::prevEventPtr() {
	return prev;
}

EventPtr Event::nextEventPtr() {
	return next;
}

bool Event::GEthan(Event x) {	//a.GEthan(x) means a.(>=)(x)
	return (time >= x.time);
}

bool Event::operator >= (Event x) {	// a >= x; means a.(>=)(x)
	return (time >= x.time);
}

bool Event::operator < (Event x) {	// a < x; means a.(<)(x)
	return (time < x.time);
}
