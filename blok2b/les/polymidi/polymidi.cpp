#include "midi_event.h"


int main()
{
  MidiEvent* eventqueue[10];

  eventqueue[0] = new MidiNoteEvent(60);
  eventqueue[1] = new MidiNoteEvent(58);
  eventqueue[2] = new MidiEvent;
  eventqueue[3] = new MidiNoteEvent(64);
  eventqueue[4] = new MidiNoteEvent;
  eventqueue[5] = new MidiEvent;
  eventqueue[6] = new MidiEvent;
  eventqueue[7] = new MidiNoteEvent(61);
  eventqueue[8] = new MidiNoteEvent(67);
  eventqueue[9] = new MidiNoteEvent(68);

    for (int i = 0; i < 10; i++) {
    eventqueue[i] -> set_timestamp(i+100);
  }


  for (int i = 0; i<10; i++) {
    eventqueue[i] -> play();
  }

  return 0;
}
