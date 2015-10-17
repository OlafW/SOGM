#include <iostream>
using namespace std;

enum {ARG_NAME=0, ARG_TIMES, NUM_ARGS};

int factorial(int n) {
	if (n <= 1) {
		return 1;
	}
	else {
		return n* factorial(n-1);
	}
}


int main(int numargs, char** argc) {

	if (numargs == NUM_ARGS) {
		int n = atoi(argc[ARG_TIMES]);
		cout << factorial(n) << endl;
	}
	
	return 0;
}
