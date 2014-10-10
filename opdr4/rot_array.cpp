#include <iostream>
#include <stdlib.h>

using namespace std;


void rot_array(int array[], int length) {
	int rotN = 1; //aantal rotaties

	cout << "Geroteerde array: ";
	for(int i = rotN; i < length; i++) {
		cout << array[i] << " ";
	}
	for (int i = 0; i < rotN; i++ ) {
		cout << array[i] << " ";
	}
	cout << endl;
}


int main(int argc, char *argv[]) {
	int var_length = argc-1;
	int var_array[var_length];

	if(argc == 1) {
		cout << "Geef een array" << endl;
	}
	else {
		for(int i = 0; i < var_length; i++) {
			var_array[i] = atoi(argv[i+1]);
		}
	rot_array(var_array, var_length);
	return 0;
	}
}
