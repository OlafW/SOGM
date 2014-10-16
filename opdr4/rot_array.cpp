#include <iostream>
#include <stdlib.h>

using namespace std;


void rot_array(int *array, int length) {
	int rotN = 1; //aantal rotaties
	int temp[length];

	for (int i = 0; i < length; i++) {
		temp[(i + length - (rotN % length)) % length] = array[i];
	}
	for (int i = 0; i < length; i++) {
			array[i] = temp[i];
	}
	cout << "array " << rotN << " keer geroteerd: ";
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
	for (int i = 0; i < var_length; i++) {
		cout << var_array[i] << " ";
	}
	cout << endl;
	return 0;
	}
}
