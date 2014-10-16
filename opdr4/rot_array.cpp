#include <iostream>
#include <stdlib.h>

using namespace std;


void rot_array(int *array, int length, int rotN) {
	int temp[length];

	for (int i = 0; i < length; i++) {
		temp[(i + length - (rotN % length)) % length] = array[i];
	}
	for (int i = 0; i < length; i++) {
			array[i] = temp[i];
	}
}


int main(int argc, char *argv[]) {
	int var_length = argc-1;
	int var_array[var_length];
	int var_rot;
	if(argc == 1) {
		cout << "Geef een array" << endl;
	}
	else {
		  for(int i = 0; i < var_length; i++) {
			var_array[i] = atoi(argv[i+1]);
		}

	cout << "Geef het aantal rotaties: ";
	cin >> var_rot;
	rot_array(var_array, var_length, var_rot);
	for (int i = 0; i < var_length; i++) {
		cout << var_array[i] << " ";
	}
	cout << endl;
	return 0;
	}
}
