/*
 * Alex Matos Iuasse
 * Universidade Federal de Mato Grosso
 */

#include <stdio.h>
#include <stdlib.h>
/* Biblioteca da thread */
#include <pthread.h>

void *hello ( void *num );

int main ( int argc, char **argv )
{
	/* pegando o argumento de quantidade de threads e casting */
	int n_thread = atoi ( argv[1] );
	pthread_t *thread_ids;
	/* alocar memoria para os ids da thread */
	thread_ids = ( pthread_t* ) malloc ( n_thread * sizeof ( pthread_t) );
	/* criação de thread */
	int i;
	for ( i = 0; i < n_thread; i ++ )
		/* chamada de sistema que cria thread */
		pthread_create ( &thread_ids[i], NULL, hello, &i );
	printf ( "\nThread Principal !" );
	/* esperar as threads */
	for ( i = 0; i < n_thread; i ++ )
		pthread_join ( thread_ids[i], NULL );
	/* liberando memoria */
	free ( thread_ids );
	/* bye */
	return 0;
}

/* codigo da thread */
void *hello ( void *num )
{
	/* casting */
	int n = *((int*)num);
	int i;
	for ( ;; )
		printf ( "\nHello From Thread %i", n );
}