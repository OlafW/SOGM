#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <lo/lo.h>


int imagehandler(const char *path,const char *types,
          lo_arg **argv,int argc,void *data,void *user_data)
{
char* messagetype;
long timestamp;
int framesize;
int pitch;

  printf("path: %s\n",path);
  messagetype = (char*)argv[0];
  timestamp = argv[1]->h;
  framesize=argv[2]->i;
  pitch=argv[3]->i;
  printf("imagehandler: %s %ld %d %d\n",messagetype,timestamp,framesize,pitch);

  return 0;
} // imagehandler()



int soundhandler(const char *path,const char *types,
          lo_arg **argv,int argc,void *data,void *user_data)
{
char* messagetype;
long timestamp;
int framesize;
int pitch;

  printf("path: %s\n",path);
  messagetype = (char*)argv[0];
  timestamp = argv[1]->h;
  framesize=argv[2]->i;
  pitch=argv[3]->i;
  printf("soundhandler: %s %ld %d %d\n",messagetype,timestamp,framesize,pitch);

  return 0;
} // soundhandler()


void errorhandler(int num, const char* msg, const char* where)
{
  printf("Error %d, %s - %s\n",num,msg,where);
  exit(1);
} // errorhandler()


int main()
{
int done = 0;
const char* serverport="7770";

  lo_server_thread server = lo_server_thread_new(serverport,errorhandler);
  lo_server_thread_add_method(server,"/sound","shii",soundhandler,NULL);
  lo_server_thread_add_method(server,"/image","shii",imagehandler,NULL);
  if(lo_server_thread_start(server) < 0)
  {
    printf("Server failed to start\n");
    exit(1);
  }

  printf("Listening on port %s\n",serverport);

  while (!done) 
  {
    usleep(1000);
  }

  return 0;
} // main()

