#include <iostream>
#include <string.h>
using namespace std;


void point1()
{
  long year = 2014;
  long* yearpointer = &year; //adres van variable year;

  cout << "year: " << year << endl;
  cout << "inhoud yearpointer: " << *yearpointer << endl; //inhoud van variable year;

  *yearpointer = 2001;
  cout << "year: " << year << endl;
  cout << "inhoud yearpointer: " << *yearpointer << endl;
}



#define NROFYEARS 4

void arraypoint()
{
  short *years;
  years = new short[NROFYEARS] {2000,2010,2014,2015};

  short* yearpointer;
  yearpointer = years; //pointer = array

  for (int i = 0; i <NROFYEARS; i++) {
    cout << *yearpointer << endl;
    yearpointer++; //pointer wijst naar het volgende element in de array, pointer verandert
    cout << *(years+i) << endl; //pointer wijst naar het volgende element in de array, pointer verandert niet
    cout << years[i] << endl; //geeft gewoon op normale manier een element uit de array
  }
delete[] years;
}



void stringpoint()
{
  char* title = "New Song";
  cout << title << endl;

  char *stringpointer = title;
  for (int i = 0; i<= strlen(title); i++) {
    cout << (int) *stringpointer << endl;
    stringpointer++;
  }
}



int main()
{
  
  stringpoint();

  return 0;
}
