/*
 * Alex Matos Iuasse
 * Universidade Federal de Mato Grosso
 * Calcular PI
 */

#include <stdio.h>
#include <stdlib.h>
/* Biblioteca da thread */
#include <pthread.h>

void *pi_thread ( void *arg );
/* numero total de interações */
int ni;
/* numero de threads */
int nt;
/* pi global */
double pi = 0.0;
/* flag para controlar a espera ocupada */
pthread_mutex_t *flag_mutex;

int main ( int argc, char **argv )
{
	/* numero de interações de calculcar pi */
	ni = atoi ( argv[1] );
	/* numero de threads */
	nt = atoi ( argv[2] );
	
	pthread_t *thread_ids = (pthread_t*) malloc (nt*sizeof(pthread_t));
	/* inicializa o mutex */
	flag_mutex = (pthread_mutex_t*) malloc (sizeof(pthread_mutex_t));
	pthread_mutex_init ( flag_mutex, NULL );
	/* cria trheads */
	int i;
	int	*thread_number = (int*) malloc (nt*sizeof(int));
	for ( i = 0; i < nt; i ++ )
	{
		thread_number[i] = i;
		pthread_create ( &thread_ids[i], NULL, pi_thread, &thread_number[i] );
	}
	/* main espera termino das threads */
	for ( i = 0; i < nt; i ++ )
		pthread_join ( thread_ids[i], NULL );
	free ( thread_ids );
	pthread_mutex_destroy ( flag_mutex );
	printf ( "PI: %lf\n", pi );
	
	return 0;
}

void *pi_thread ( void *arg )
{
	/* numero da thread */
	int id = *((int*)arg);
	/* numero de interações por thread */
	int n_iter = ni / nt;
	/* inicio do laço de uma thread */
	int t_inicio = id * n_iter;
	/* fim do laço */
	int t_fim = t_inicio + n_iter;
	
	int i;
	double soma = 0.0;
	double lol = 1.0;
	for ( i = t_inicio; i < t_fim; i ++ )
	{
		soma += lol * ( 1.0 / (2.0*i + 1.0) );
		lol *= -1.0;
	}
	soma *= 4.0;
	/* Região critica */
	pthread_mutex_lock ( flag_mutex );
	pi += soma;
	/* saida da regia critica */
	pthread_mutex_unlock ( flag_mutex );
	return 0;
}