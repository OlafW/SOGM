#include "scheduler.h"


Scheduler::Scheduler( double (*fp)() ) {

}

Scheduler::~Scheduler() {

}

bool Scheduler::postForward(EventPtr here, EventPtr aNew) {

}

bool Scheduler::postBackward(EventPtr here, EventPtr aNew) {

}

bool Scheduler::post(EventPtr aNew) {

}

long Scheduler::pending() {

	return total;
}

void Scheduler::show() {

}

double Scheduler::localTime() {

	return _localTime;
}

double Scheduler::maxTime() {

	return tEnd;
}

double Scheduler::Start() {
	return tStart;
}

double Scheduler::End() {
	return tEnd;
}

double Scheduler::Last() {
	return tLast;
}

void Scheduler::setLocalTime(double val) {
	_localTime = val;
}

double Scheduler::advance(double delta) {

}

void Scheduler::flush() {

}

double Scheduler::sampleClock() {
	static double val = 0.0;
	double res = val;val +=0.001;
	return res;
}
