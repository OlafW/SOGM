#include <iostream>

using namespace std;


void process(long* sample)
{
  *sample += 2;
}


int main()
{
  long sample = 42;


  cout << "Sample: " << sample << endl;
  process(&sample);
  cout << "Sample: " << sample << endl;

  return 0;
}
