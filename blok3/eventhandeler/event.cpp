#include "Event.h"

long Event::index = 0;

Event::Event(long timeStamp) {
	ID = index++;
	this->timeStamp = timeStamp;
	next = NULL;
	prev = NULL;
}

EventPtr Event::insert(EventPtr inserted) {
	EventPtr temp = next;	//tijdelijk opslaan adres van pointer naar volgende in de lijst
	next = inserted;	//pointer naar volgende wordt nu inserted
	inserted->prev = this; //pointer naar vorige van inserterd wordt huidige object
	inserted->next = temp; //pointer naar volgende van inserted wordt de oude volgende

	if (temp) {	//check of er wel een volgende is
		temp->prev = inserted;	//pointer naar vorige van de volgende (inserted)
	}
	return inserted;
}

EventPtr Event::prevEventPtr() {
	return prev;
}

EventPtr Event::nextEventPtr() {
	return next;
}

void Event::show() {
	cout << "Own ID: " << this->ID << endl;	//eigen ID
	cout << "Own timeStamp :" << timeStamp << endl;	//eigen timeStamp

	if (prev) {	//check of er een vorige is
		cout << "ID of previous: " << prev->ID << endl;	//ID van vorige
	}
	if (next) {	//check of er een volgende is
		cout << "ID of next: " << next->ID << endl;	//ID van volgende
	}
}

void Event::doIt() {
	cout << "Event::doIt()" << endl;
	show();
}

bool Event::GEthan(Event x) {	//a.GEthan(x) betekent a.(>=)(x)
	return (timeStamp >= x.timeStamp);
}

bool Event::operator >= (Event x) {	// a >= x; betekent a.(>=)(x)
	return (timeStamp >= x.timeStamp);
}

bool Event::operator < (Event x) {	// a < x; betekent a.(<)(x)
	return (timeStamp < x.timeStamp);
}
