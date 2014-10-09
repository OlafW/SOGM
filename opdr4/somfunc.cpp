#include <iostream>

using namespace std;


void som(int array[], int length) {
	int x;
	for(int i = 0; i < length; i++) {
		x += array[i];	
	}
	cout << "Totaal: " << x << endl;
}


int main(int argc, char *argv[]) {	
	int length = argc -1;
	int var_array[length];
	if(argc == 1) {
		cout << "Geef een aantal getallen om op te tellen" << endl;
	}
	else {
	for (int i = 0; i < length; i++) {
		var_array[i] = atoi(argv[i+1]);
	}
	som(var_array, length);
	return 0;
	}
}
