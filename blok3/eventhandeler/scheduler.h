#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "event.h"

class Scheduler {

public:
	Scheduler( double (*fp)() );
	~Scheduler();
	bool postForward(EventPtr here, EventPtr aNew);
	bool postBackward(EventPtr here, EventPtr aNew);
	bool post(EventPtr aNew);

	long pending();

	void show();
	double localTime();
	double maxTime();
	double Start();
	double End();
	double Last();
	void setLocalTime(double val);
	double advance(double delta);
	void flush();

	double sampleClock();

private:
	EventPtr start;
	EventPtr end;
	EventPtr last;
	double tStart;
	double tEnd;
	double tLast;
	double _localTime;
	long total;
	double (*clock)();
};

#endif
