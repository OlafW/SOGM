#include <iostream>

using namespace std;


class MidiEvent
{
public:
  MidiEvent() { timestamp=0; }
  void set_timestamp(long ts) { timestamp = ts; }
  long get_timestamp() { return timestamp; }
  virtual void play() { cout << "It is now " << (int)timestamp << endl; }
  //virtual void play() = 0; "= 0, laat de compiler geen objecten van baseclass MidiEvent maken"

private:
  long timestamp;
};


class MidiNoteEvent : public MidiEvent
{
public:
  MidiNoteEvent(){};
  MidiNoteEvent(unsigned char p){notenumber=p;};
  void setPitch(unsigned char p) {notenumber=p;}
  void play() { MidiEvent::play();
                cout << " Now playing note " << (int)notenumber << endl; }

private:
  bool on_off;
  unsigned char notenumber;
};
