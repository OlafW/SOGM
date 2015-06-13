#include "Event.h"

long Event::number = 0;


Event::Event(double time) {
	ID = number++;
	this->time = time;
	next = prev = NULL;
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

EventPtr Event::prepend(EventPtr ev) {
	ev->next = this;	//Next of new event becomes this
    ev->prev = this->prev;  //Prev of new event becomes previous of this event
	if (prev) {
		prev->next = ev;	//Next of prev becomes new event
	}
	prev = ev;	//This prev becomes new event
	ev->next = this; //Next of new event becomes this
	return ev;
}

EventPtr Event::append(EventPtr ev) {
	ev->next = next;	//Next of new event becomes this next
	if (next) {
		next->prev = ev;	//Prev of next becomes new event
	}
	next = ev;	//This next becomes new event
	ev->prev = this; //Prev of new event becomes this
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

bool Event::operator >= (Event x) {	// a >= x; means a.(>=)(x)
	return (time >= x.time);
}

bool Event::operator < (Event x) {	// a < x; means a.(<)(x)
	return (time < x.time);
}
