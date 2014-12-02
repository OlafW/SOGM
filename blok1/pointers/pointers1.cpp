#include <iostream>

using namespace std;


int main()
{
  unsigned short year = 2014;
  unsigned short* yearpointer;
  unsigned short* anotheryearpointer;

  yearpointer = &year;
  cout << "Inhoud van variable year: " << year << endl;
  cout << "Inhoud yearpointer: " << yearpointer << endl;
  cout << "Inhoud waar yearpointer naar wijst: " << *yearpointer << endl;
  cout << "Inhoud van variable year veranderen via yearpointer" << endl;
  *yearpointer = 2015;
  cout << "Inhoud van variable year: " << year << endl;

  cout << "\n";

  anotheryearpointer = yearpointer;
  cout << "Inhoud van anotheryearpointer: " << anotheryearpointer << endl;
  cout << "Inhoud van waar anotheryearpointer naar wijst: " << *anotheryearpointer << endl;
  cout << "Inhoud van year (via yearpointer) veranderen via anotheryearpointer" << endl;
  *anotheryearpointer = 2016;
  cout << "Inhoud van de variabele year: " << year << endl;
  cout << "Inhoud van waar de pointer yearpointer naar wijst: " << *yearpointer << endl;

  return 0;
}
