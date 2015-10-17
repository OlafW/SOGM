#include <iostream>
#include <stdlib.h>

using namespace std;


int max_array(int array[], int length) {
	int max =0;

	for (int index=0; index < length; index++) {
		if(array[index] >= max) {
			max = array[index];
		}
	}
	return max;
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

	int result = max_array(var_array, var_length);
	cout << "Maximum: " << result << endl;
	return 0;
	}
}
