/********************************************************************
*       (c) Copyright 2005, Hogeschool voor de Kunsten Utrecht
*                       Hilversum, the Netherlands
*********************************************************************
*
* File name     : thread_struct.cpp
* System name   : pthreads programming course
* 
* Version       : $Revision: 1.1.1.1 $
*
*
* Description   : Passing arguments to threads
*
*
* Author        : Marc_G
* E-mail        : marcg@dinkum.nl
*
********************************************************************/

/************
   $Log: thread_struct.cpp,v $
   Revision 1.1.1.1  2005/04/04 09:39:23  marcg
   Imported using TkCVS

************/

using namespace std;

#include <iostream>
#include <cstdlib>
#include <unistd.h>	// usleep
#include <fcntl.h>	// threads
#include <pthread.h>


typedef struct thread_data
{
  int step;
  int endtime;
};



void *first(void *arg)
{
int time;
thread_data *localtd=(thread_data *)arg;
int step = localtd->step;
int endtime = localtd->endtime;

  for(time=0; time<endtime; time+=step){
    cout << "First thread: " << time << endl;
    usleep(step);
  }
  cout << "First thread ends\n";
  pthread_exit((void *)0);
} // do_first()



void *second(void *arg)
{
int time;
thread_data *localtd=(thread_data *)arg;
int step = localtd->step;
int endtime = localtd->endtime;

  for(time=0; time<endtime; time+=step){
    cout << "\tSecond thread: " << time << endl;
    usleep(step);
  }
  cout << "Second thread ends\n";
  pthread_exit((void *)0);
} // do_first()



int main(int argc, char **argv)
{
pthread_t thr;
thread_data thread1_data,thread2_data;

  // Initialise data for the threads
  thread1_data.step=1000000;
  thread2_data.step=3000000;
  thread1_data.endtime=15000000;
  thread2_data.endtime=20000000;

  // Create two threads and pass the structs as arguments
  if(pthread_create(&thr,NULL,first,(void *)(&thread1_data)) ||
     pthread_create(&thr,NULL,second,(void *)(&thread2_data)) )
  {
    cout << argv[0] << " cannot make thread\n";
    exit(1);
  }

  /*
   * At this point the main thread can perform its actions or end
   */
  cout << "** Main thread ends **\n";
  pthread_exit((void *)0);

} // main()

