#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main ()
{
  
  int pipe_fd[2];
  pid_t pid;
  
  /* cria pipe e testa erro */
  if ( pipe ( pipe_fd ) == -1 )
  {
    printf ("\nError ao usar pipe!");
    exit (1);
  }
  
  pid = fork();
  
  if ( pid == -1 )
  {
    printf ("\nError ao usar fork!");
    exit (1);
  }
  
  if ( pid == 0 )
  {
    /* fecha descritor de escrita */
    close ( pipe_fd [1] );
    FILE *fd_leitura;
    fd_leitura = fdopen ( pipe_fd [0], "r" );
    FILE *fd_file;
    
    char buffer [1024];
    
    fd_file = fopen ( "saida.txt", "w" );
    
    while ( !feof(fd_leitura) && !ferror(fd_leitura) 
      && fgets (buffer, sizeof(buffer), fd_leitura) )
    {
      
      if ( strcmp (  buffer, "sair" ) == 0 )
      {
	fclose (fd_file);
	fclose (fd_leitura);
	exit (0);
      } else {
	fprintf ( fd_file, "%s", buffer );
	fflush ( fd_file );
      }
    }
    
  } else {
    /* fecha descritor de leitura */
    close ( pipe_fd [0] );
    FILE *fd_escrita;
    fd_escrita = fdopen ( pipe_fd [1], "w" );
    
    int flag = 1;
    char msg [1024];
    
    printf ("Digite merdas aqui!:\t");
    
    /* linder way */
    while ( strcmp ( msg, "sair\n" ) != 0 )
    {
      fgets ( msg, sizeof(msg), stdin );
      fprintf ( fd_escrita, "%s", msg );
      fflush ( fd_escrita );
    }
    /* japa way */
//     while ( flag )
//     {
//       __fpurge (stdin);
//       scanf ("%[^\n]s",msg);
//       if ( strcmp ( msg, "sair") == 0 )
// 	flag = 0;
//       fprintf ( fd_escrita, "%s\n", msg );
//       fflush ( fd_escrita );
//     }
    
    fclose (fd_escrita);
    wait ();
  }
  
  return 0;
}