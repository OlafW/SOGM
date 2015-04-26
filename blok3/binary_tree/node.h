#ifndef _NODE_H
#define _NODE_H

#include "NoteEvent.h"
#include <iostream>

using namespace std;

class Node {

public:
	Node(NoteEvent* event);
	void insert(NoteEvent* event);
	void print();

private:
	NoteEvent* contents;
	Node* left;
	Node* right;
	long counter;
};

#endif
