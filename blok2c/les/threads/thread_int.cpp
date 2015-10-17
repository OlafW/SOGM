/********************************************************************
*       (c) Copyright 2005, Hogeschool voor de Kunsten Utrecht
*                       Hilversum, the Netherlands
*********************************************************************
*
* File name     : thread_int.cpp
* System name   : pthreads programming course
* 
* Version       : $Revision: 1.1.1.1 $
*
*
* Description   : Passing one argument to a thread
*
*
* Author        : Marc_G
* E-mail        : marcg@dinkum.nl
*
********************************************************************/

/************
   $Log: thread_int.cpp,v $
   Revision 1.1.1.1  2005/04/04 09:39:23  marcg
   Imported using TkCVS

************/

using namespace std;

#include <iostream>
#include <cstdlib>
#include <unistd.h>	// usleep
#include <fcntl.h>	// threads
#include <pthread.h>


#define ENDTIME_1	15000000 // usecs, thread ends when reaching this
#define ENDTIME_2	20000000 // usecs, thread ends when reaching this


void *first(void *arg)
{
int time;
int *stepaddr=(int *)(arg); // typecast from void* to int*
int step = *stepaddr; // get the contents

  for(time=0; time<ENDTIME_1; time+=step){
    cout << "First thread: " << time << endl;
    usleep(step);
  }
  cout << "First thread ends\n";
  pthread_exit((void *)0);
} // do_first()



void *second(void *arg)
{
int time;
int *stepaddr=(int *)(arg); // typecast from void* to int*
int step = *stepaddr; // get the contents

  for(time=0; time<ENDTIME_2; time+=step){
    cout << "\tSecond thread: " << time << endl;
    usleep(step);
  }
  cout << "Second thread ends\n";
  pthread_exit((void *)0);
} // do_first()



int main(int argc, char **argv)
{
pthread_t thr;
int step1=1000000,
    step2=3000000;

  // Create two threads and pass the variables step1 and step2 as arguments
  if(pthread_create(&thr,NULL,first,(void *)(&step1)) ||
     pthread_create(&thr,NULL,second,(void *)(&step2)) )
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

