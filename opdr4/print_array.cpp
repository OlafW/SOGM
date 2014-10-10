#include <iostream>
#include <stdlib.h> 

using namespace std;


void print_array(int array[], int length) {
	for(int index=0; index < length; index++) {
		cout << index+1 << ": " << array[index] << endl;
	}
}

int main(int argc, char *argv[]) {
	int var_length = argc -1;
	int var_array[var_length];
	if(argc == 1) {
		cout << "Geef een array" << endl;
	}
	
	else {
	for(int i = 0; i < var_length; i++) {
		var_array[i] = atoi(argv[i+1]);
	}
	
	print_array(var_array, var_length);
	return 0;
	}
}