#include <stdio.h>
#include <lo/lo.h>

int main()
{
lo_address target;

  target = lo_address_new("127.0.0.1","7770");

  // message: source type timestamp framesize [item]*
  lo_send(target,"/sound","siii","pitch",765432,1,42);
  lo_send(target,"/sound","siii","pitch",765442,1,43);
  lo_send(target,"/image","siii","blob",765477,1,2000);
  lo_send(target,"/sound","siii","pitch",765480,1,44);
  lo_send(target,"/sound","siii","pitch",765481,1,42);
  lo_send(target,"/sound","siii","pitch",765482,1,43);
  // next message has a different typespec
  lo_send(target,"/sound","sisi","pitch",765482,"blabla",43);
  lo_send(target,"/sound","siii","pitch",765483,1,45);
  lo_send(target,"/image","siii","centre",765485,1,798);
} // main()

