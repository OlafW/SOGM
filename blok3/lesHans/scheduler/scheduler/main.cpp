#include "event.h"
#include "scheduler.h"
#include "midiEvent.h"

using namespace std;

int main() {
    
    srand(unsigned(time(NULL)));
    
    Scheduler scheduler(secondsClock);
    EventPtr ev;
    
    for (int i=0; i<3; i++) {
        double time;
        time = (rand()%100);
        time /= 10;
        ev = new MidiNote(time,1,rand()%128,127,2.0);   //Insert some MIDI events
        scheduler.post(ev);
        ev->showTiming();
    }
    scheduler.show();
    
    while(scheduler.run() > 0); //Run the scheduler until queue is empty
    
    return 0;
}
