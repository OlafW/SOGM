#include "node.h"

int main() {

	NoteEvent note1("e", 4);
	NoteEvent note2("fis", 15);
	NoteEvent note3("a", 2);
	NoteEvent note4("des", 9);

	Node node(&note1);
	node.insert(&note2);
	node.insert(&note3);
	node.insert(&note4);

	node.print();


	return 0;
}
