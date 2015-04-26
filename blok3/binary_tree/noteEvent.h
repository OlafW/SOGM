#ifndef _NOTE_EVENT_H
#define _NOTE_EVENT_H

#include <iostream>
using namespace std;

class NoteEvent {

public:
	NoteEvent(string note, int timeStamp);
	bool operator> (NoteEvent event);
	bool operator< (NoteEvent event);
	int getTime();
	void print();

private:
	string note;
	int timeStamp;
};

#endif
