#include "song.h"

#include <string>
#include <iostream>


class PlayableSong : public Song {

public:
  void set_url(string url);
  void play();

private:
  string url;

};
