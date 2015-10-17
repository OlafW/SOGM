#include <iostream>
#include "playablesong.h"
#include "notatedsong.h"



int main(int argc, char ** argv)
{
  Song song1;
  song1.setTitle("Never gonna give you up");

  PlayableSong song2;
  song2.setTitle("Gurlz just wanna ave fun");
  song2.setYear(1983);
  song2.set_url("home/olaf/gurlz.mp3");
  song2.play();

  NotatedSong song3;
  song3.setTitle("Olaf");
  song3.setYear(1993);
  song3.set_sheet("home/olaf/olaf.pdf");
  song3.display();


  return 0;
}
