#include <iostream>

using namespace std;



int byValue(int varVal) {
  varVal = 2;

  return varVal;
}


int* byPointer(int* varPointer) {
  *varPointer = 2;

  return varPointer;
}



int main()
{
  int baseVal = 1;
  int* valPointer = &baseVal;

  cout << "Default waarde variabele: " << baseVal << endl;
  cout << "Waarde van byValue functie: " << byValue(baseVal) << endl;
  cout << "Waarde van variable na byValue functie: " << baseVal << endl;
  cout << "De waarde van de variable is niet veranderd" << "\n" << endl;

  cout << "Waarde van byPointer functie: " << *byPointer(valPointer) << endl;
  cout << "Waarde van variable na byPointer functie: " << baseVal << endl;
  cout << "De variable is nu wel veranderd" << "\n" << endl;

  baseVal = 3;
  cout << "Verander de waarde van de variabele: " << baseVal << endl;
  cout << "Waarde van byPointer functie na veranderen van variable: " << *valPointer << endl;
  cout << "Nu is de waarde van de pointer veranderd" << endl;

  return 0;
}
