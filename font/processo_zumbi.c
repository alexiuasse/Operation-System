#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main ()
{
  
  pid_t pid;
  
  pid = fork();
  
  if ( pid == 0 )
  {
    sleep (10);
    printf ("Oi eu sou o Goku!\n");
    exit (0);
  } else {
    for (;;);
  }
  
  return 0;
}