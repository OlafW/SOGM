#ifndef _SONG_H_
#define _SONG_H_

#include <string>
using namespace std;

typedef string Notation;


class Song {

public:
      void setTitle(string newTitle);
      int setYear(unsigned short newYear);
      string getTitle();
      unsigned short getYear();

private:
    string title;
    unsigned short year;

}; // Song{}


#endif
