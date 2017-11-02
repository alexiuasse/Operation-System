#include "quadrado.h"
#include "fatorial.h"
#include <stdio.h>

int main ( int argc, char **argv ) 
{
	long int fats = fat ( 4 );
	float quad = sqr ( 2.0 );
	printf ( "fatorial de 4 = %ld , quadrado = %f \n",fats,quad );
	return 0;
}
