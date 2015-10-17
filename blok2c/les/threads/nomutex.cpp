/********************************************************************
*       (c) Copyright 2005, Hogeschool voor de Kunsten Utrecht
*                       Hilversum, the Netherlands
*********************************************************************
*
* File name     : nomutex.cpp
* System name   : pthreads programming course
* 
* Version       : $Revision: 1.1.1.1 $
*
*
* Description   : Unprotected shared resources
*
*
* Author        : Marc_G
* E-mail        : marcg@dinkum.nl
*
********************************************************************/

/************
   $Log: nomutex.cpp,v $
   Revision 1.1.1.1  2005/04/04 09:39:23  marcg
   Imported using TkCVS

************/

using namespace std;

#include <iostream>
#include <cstdlib>
#include <unistd.h>	// usleep
#include <fcntl.h>	// threads
#include <pthread.h>


static long balance=1000;


typedef struct thread_data
{
  long increment;
  long busytime; // time it takes to complete task
};



void *threadfunction(void *arg)
{
thread_data *localtd=(thread_data *)arg;
long oldbalance;

cout << "start\n";
  oldbalance=balance;
  usleep(localtd->busytime);
  balance=oldbalance+localtd->increment;
cout << "end\n";
  pthread_exit(NULL);
} // do_first()



int main(int argc, char **argv)
{
pthread_t thr1,thr2,thr3; // now we need a thread variable for each thread
thread_data thread1_data,thread2_data,thread3_data;
pthread_attr_t thread_attr; // for detaching threads
void *status;

  // Initialise data for the threads
  thread1_data.increment=10;
  thread2_data.increment=10;
  thread3_data.increment=10;
  thread1_data.busytime=100000;
  thread2_data.busytime=1250000;
  thread3_data.busytime=500000;

  // Create a thread attribute variable to be used in thread creation
  pthread_attr_init(&thread_attr);
  pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_JOINABLE);

  // Create threads with a small delay in-between
  if(pthread_create(&thr1,&thread_attr,threadfunction,(void *)(&thread1_data))){
    cout << argv[0] << ": cannot make thread 1\n";
  }
  usleep(500000);
  if(pthread_create(&thr2,&thread_attr,threadfunction,(void *)(&thread2_data))){
    cout << argv[0] << ": cannot make thread 2\n";
  }
  usleep(100000);
  if(pthread_create(&thr3,&thread_attr,threadfunction,(void *)(&thread3_data))){
    cout << argv[0] << ": cannot make thread 3\n";
  }
  
  // Free attribute variable
  pthread_attr_destroy(&thread_attr);

  // Join (collapse) the threads
  if(pthread_join(thr1, &status) ||
     pthread_join(thr2, &status) ||
     pthread_join(thr3, &status) )
  {
    cout << argv[0] << ": thread join failed\n";
    exit(1);
  }

  cout << "Resulting balance: " << balance << endl;
  pthread_exit(NULL);

} // main()

