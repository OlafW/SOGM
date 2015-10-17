
#include "song.h"

void Song::setTitle(string newTitle)
{
  title = newTitle;
}

int Song::setYear(unsigned short newYear)
{
  if (newYear < 1900) return -1;
  year = newYear;
  return 0;
}

string Song::getTitle()
{
  return title;
}

unsigned short Song::getYear()
{
  return year;
}
