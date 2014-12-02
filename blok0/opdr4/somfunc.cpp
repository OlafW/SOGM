#include <iostream>
#include <stdlib.h>

using namespace std;


int som(int array[], int length) {
	int x;
	for(int i = 0; i < length; i++) {
		x += array[i];
	}
	return x;
}


int main(int argc, char *argv[]) {
	int var_length = argc -1;
	int var_array[var_length];
	if(argc == 1) {
		cout << "Geef een aantal getallen om op te tellen" << endl;
	}
	else {
	for (int i = 0; i < var_length; i++) {
		var_array[i] = atoi(argv[i+1]);
	}

	int totaal = som(var_array, var_length);
	cout << "Totaal: " << totaal << endl;
	
	return 0;
	}
}
