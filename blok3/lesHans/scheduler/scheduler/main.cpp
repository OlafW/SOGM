#include "event.h"
#include "scheduler.h"

using namespace std;

double sampleClock() {
	static double val = 0.0;
	double res = val;val +=0.001;
	return res;
}


int main() {
    
    Scheduler scheduler(sampleClock);
    EventPtr ev;

    scheduler.show();
    for (int i=0; i<5; i++) {
        ev = new Event(1.0*i);
        scheduler.post(ev);
        ev->showTiming();
    }
    scheduler.show();
    
	return 0;
}
