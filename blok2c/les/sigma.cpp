#include <iostream>
#include <stdlib.h>


using namespace std;


int iterate2(int begin, int eind) {

  int n = 0;

  for (int i = begin; i<= eind; i++) {

    n += i -1;
  }
  return n;
}


int iterate3(int begin, int eind) {

  int n = 1;

  for (int i = begin; i< eind; i++) {

    n *= 10 -i;
  }
  return n;
}


float iterate4(int begin, int eind) {

  float n = 1;

  for (int i = begin; i<= eind; i++) {

    n *= (i * 0.5);
  }
  return n;
}



int main() {

  cout << iterate4(1, 5) << endl;

  return 0;
}
