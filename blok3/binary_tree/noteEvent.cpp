#include "noteEvent.h"


NoteEvent::NoteEvent(string note, int timeStamp) {
	this->note = note;
	this->timeStamp = timeStamp;
}

bool NoteEvent::operator> (NoteEvent event) {
	return this->getTime() > event.getTime();
}

bool NoteEvent::operator< (NoteEvent event) {
	return this->getTime() < event.getTime();
}

int NoteEvent::getTime() {
	return this->timeStamp;
}

void NoteEvent::print() {
	cout << "Note value: " << note;
	cout << " Timestamp: " << timeStamp;
}
