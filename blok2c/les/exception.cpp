#include <iostream>

using namespace std;


char word[5];


char read_one_char(void)
{
char c;

  cin >> c;
  if(c == 'e') throw 5; // throw int
  if(c == 'q') throw 3.2f; // throw float
  return c;
} // read_one_char()


void read_word()
{
  for(int i=0; i<4; i++){
    try{
      word[i] = read_one_char();
    } // try
    catch (float err) {
      cout << "Exception " << err << " handled in read_word() " << endl;
    } // catch
    /*
      // uncomment this code to handle int execeptions here instead of in main()
      catch (int err) {
      cout << "Exception " << err << " handled in read_word() " << endl;
    } // catch
    */
  } // for

  word[4]=0; // terminate string with \0
} // read_word()


int main()
{

  try {
    read_word();
    cout << word << endl;
  } // try
  catch (int err) {
    cout << "Exception " << err << " handled in main() " << endl;
  } // catch

} // main()

