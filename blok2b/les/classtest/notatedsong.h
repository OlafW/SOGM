#include "song.h"

#include <string>
#include <iostream>


class NotatedSong : public Song {

public:
  void set_sheet(Notation sheet);
  void display();

private:
  Notation sheet;

};
