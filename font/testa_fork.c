#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main ( )
{
    printf ("\n Processo Pai Em Execução\n");
    
    pid_t pid;
    pid = fork();
    
    if ( pid == -1 )
    {
      printf ("\nErro durante a execução de fork\n");
      exit (1);
    } else {
      if ( pid == 0 ) //processo filho
      {
	  execlp ( "/bin/cd", "teste", NULL );
      } else { //processo pai
	wait ( NULL ); //esperar processo filho terminar
	exit ( 0 );
      }
    }
}
