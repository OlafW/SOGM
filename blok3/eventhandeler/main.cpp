#include "Event.h"

using namespace std;

int main() {

	Event event1(10);
	Event event2(30);
	Event event3(20);

	event1.insert(&event3);
	event3.insert(&event2);

	event1.show();
	cout << endl;
	event2.show();
	cout << endl;
	event3.show();

	return 0;
}
