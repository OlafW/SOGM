#include <iostream>

using namespace std;


void print_array(int array[], int length) {
	for(int index=0; index < length; index++) {
		cout << index+1 << ": " << array[index] << endl;
	}

}

int main(int argc, char *argv[]) {
	int var_array[argc - 1];
	int length = argc -1;
	if(argc == 1) {
		cout << "Geef een array" << endl;
	}
	
	else {
	for(int i = 0; i < length; i++) {
		var_array[i] = atoi(argv[i+1]);
	}
	
	print_array(var_array, length);
	return 0;
	}
}