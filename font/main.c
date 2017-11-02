#include "soma.h"
#include "areacirc.h"
#include <stdlib.h>
#include <stdio.h>

int main ( int argc, char **argv )
{
  /* 
   * argc contador de programa
   * argv strings de parametros
   */
  
  int a = atoi ( argv[1] );
  int b = atoi ( argv[2] );
  float r = atof ( argv[3] );
  
  int s = soma ( a, b );
  float area = areacirc ( r );
  
  printf ( "Soma: %i", s );
  printf ( "\nArea: %f\n", area );
  
  return 0;
}