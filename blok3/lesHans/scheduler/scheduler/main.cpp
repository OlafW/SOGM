#include "event.h"
#include "scheduler.h"
#include "MidiNote.h"
#include "noteOff.h"

using namespace std;

int main() {
    
    Scheduler scheduler(secondsClock);
    EventPtr ev;
    
    for (int i=0; i<5; i++) {
        double time = 5*i;
        ev = new MidiNote(time,1,rand()%128,127,100);
        scheduler.post(ev);
        ev->showTiming();
    }
    
    while(scheduler.run() > 0);
    
    return 0;
}
