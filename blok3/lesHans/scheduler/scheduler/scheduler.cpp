#include "scheduler.h"
#include <ctime>

Scheduler::Scheduler(double (*fp)()) {
	clock = fp;
	start = end = last = NULL;
	tStart = tEnd = tLast = 0.0;
	total = 0;
	showInfoFlag = false;
}

Scheduler::~Scheduler() {
	cout << " In Scheduler::~Scheduler()" << endl;
	flush();
	cout << " Scheduler is destructed" << endl;
}

void Scheduler::show() {
	if(!showInfoFlag) return;
	if(start) {
			cout << "\nScheduler has now:" << endl;
			EventPtr ev = start;
			while(ev) {
				ev->show();
				ev = ev->next;
			}
			cout << "\nEnd of this queue " << endl;
			cout << endl;
	}
}

EventPtr Scheduler::post(EventPtr toPost) {
	EventPtr res = NULL;
	double t1, t2, t3;
	toPost->myScheduler = this; //Scheduler of toPost event is this one

	if (toPost->time <tStart && toPost->time < _localTime) {    //Event has to run immediately
		cout << "Immediate doit()" << endl;
		toPost->doIt();
        tStart = toPost->time;
		delete toPost;
		return NULL;
	}
    if (toPost->time <tStart && toPost->time > _localTime) {    //Event has to run immediately but local time < event time: put event in queue
        if (start) {
            EventPtr temp = start;
            start = toPost; toPost->next = temp;
            temp->prev = start;
            tStart = toPost->time;
            tLast = tStart;
            last = toPost;
            total++;
        }
        return start;
    }

	t1 = toPost->time - tStart;	//Distance from first element
	t2 = toPost->time - tLast;	//Distance from last inserted element
	t3 = toPost->time - tEnd;	//Distance from last element in queue

	if(t1 <0) t1 = -t1;	//Absolute values
	if(t2 <0) t2 = -t2;
	if(t3 <0) t3 = -t3;

	if (total <=0) {	//CASE 1: Queue is empty
		start = end = last = toPost;	//Posted event is all there is
		tStart = tLast = tEnd = toPost->time;
		total ++;
		if(showInfoFlag) {
			cout << "Inserted in empty queue" << endl;
			show();
		}
		return start;
	}
	//CASE 2: Queue has 1 element or more
	if (toPost->time < start->time) {	//Insert before first element
			EventPtr temp = start;
			start = toPost; toPost->next = temp;
			temp->prev = start;
			tStart = toPost->time;
			tLast = tStart;
			last = toPost;
			total++;
			if (showInfoFlag) cout << "Inserted as first element" << endl;
			if (showInfoFlag) show();
			return start;
	}
	if (toPost->time >= tEnd) {	//Insert after last element
		end->append(toPost);
		last = end = toPost;
		tLast = tEnd = toPost->time;
		total++;
		if (showInfoFlag) cout << "Inserted as last element" << endl;
		if (showInfoFlag) show();
		return end;
	}
	if (t1 <= t2) {	//toPost time closest to start, search forwards from there
		res = start;
		while (res->next && res->next->time < toPost->time) res = res->next;	//searching
		if (res) {
			res->append(toPost);
			last = toPost;
			tLast = toPost->time;
			total++;
			if(showInfoFlag) cout << "Inserted searching from the end" << endl;
			if(showInfoFlag) show();
			return res;
		}
	}
	if (t3 <= t2) { //toPost time closest to end, search backwards from there
		res = end;
		while(res->prev && res->time > toPost->time) res = res->prev;
		res->append(toPost);
		tLast = toPost->time;
		last = toPost;
		total ++;
		if(showInfoFlag)cout << "Inserted searching from the end" << endl;
		if(showInfoFlag) show();
		return res;
	}
	res = last;
	if (toPost->time >= res->time) {    //toPost closest to last inserted, searching forward from there
		while(res->next && toPost->time > res->next->time)	res = res->next;
		res->append(toPost);
		tLast = toPost->time;
		last = toPost;
		total++;
		if(showInfoFlag)cout << "Inserted searching forward from the last inserted element" << endl;
		if(showInfoFlag) show();
		return res;
	}
	if (toPost->time <= res->time) {//toPost closest to last inserted, searching backward from there
		while (res->prev && toPost->time < res->time)	res = res->prev;
		res->append(toPost);
		tLast = toPost->time;
		last = toPost;
		total++;
		if(showInfoFlag)cout << "Inserted searching backward from the last inserted element" << endl;
		if(showInfoFlag) show();
		return res;
	}
	cout << "Error: Event not inserted ! " << endl;
	cout << "t1: " << t1 << " \t t2: " << t2 << " \t t3: " << t3 << endl;
	return NULL;

}

EventPtr Scheduler::post(Event &aNew) {
	EventPtr temp = &aNew;
	EventPtr ev = post(temp);
	show();
	return ev;
}

long Scheduler::run() { //Run the scheduler
	EventPtr temp;
    double t = clock();
    while (start && start->time <= t) { //Check if event has to run
        temp = start;
        cout << "\nat: " << t << " ";
        temp->doIt();
        start = start->next;
        delete temp;
        total --;
    }
	return total;
}

void Scheduler::flush() {
    cout << " Flushing Event queue" << endl;
    EventPtr temp;
    while(start){
        cout << "Deleting queue of: " << total << " elements" << endl;
        temp = start->next;
        delete start;
        start = temp;
        total --;
    }
}

//Global clock funtions
double sampleClock() {
	static double val = 0.0;
	double res = val;val +=0.001;
	return res;
}

double secondsClock(){
    static bool first = true;
    double t = clock();
    static double offset;
    static double systemticks = CLOCKS_PER_SEC;
    static double lastT = 0.0;
    if(first){
        offset = t/systemticks;
        first = false;
        cout << "secondsClock initialised, offset: " <<  offset << endl;
        cout << "systemticks: " << systemticks << endl;
    }
    t = t/systemticks;
    t -= offset;
    static int cntr  = 0;
    if(t == long(t) || t - lastT >= 0.1){
        lastT = t;
        if(cntr <= 0) cout << "t: " << t;
        cout << "."; cout.flush();
        cntr ++;
        if(cntr >= 10){
            cout << endl;
            cntr = 0;
        }
    }
    return t;
}