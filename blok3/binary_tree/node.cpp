#include "node.h"

Node::Node(NoteEvent* event) {
	contents = event;
	left = NULL;
	right = NULL;
	counter = 1;
}

void Node::insert(NoteEvent* newEvent) {
	if (*newEvent > *contents) {
		if (right) {
			right->insert(newEvent);
		}
		else {
			right = new Node(newEvent);
		}
	}
	else if (*newEvent < *contents) {
		if (left) {
			left->insert(newEvent);
		}
		else {
			left = new Node(newEvent);
		}
	}
	else counter ++;
}

void Node::print() {
	if (left) {
		left->print();
	}
	contents->print();
	cout << " Counter: " << counter << endl;
	if (right) {
		right->print();
	}
}
