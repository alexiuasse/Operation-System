#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main ()
{
  
  pid_t meuPID;
  pid_t paiPID;
  
  
  meuPID = getpid();
  paiPID = getppid();
  for (;;)
  {
    printf ("PID = %i\nPPID = %i\n",meuPID,paiPID);
  }
  
  return 0;
  
}