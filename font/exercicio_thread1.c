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
int flag = 0;

int main ( int argc, char **argv )
{
	/* numero de interações de calculcar pi */
	ni = atoi ( argv[1] );
	/* numero de threads */
	nt = atoi ( argv[2] );
	
	pthread_t *thread_ids = (pthread_t*) malloc (nt*sizeof(pthread_t));
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
	while ( id != flag );
	pi += soma;
	/* saida da regia critica */
	flag = (flag+1)%nt;
	return 0;
}

/* Calculo de pi sem paralelizar */
// int main ( int argc, char **argv )
// {
// 	int i, n = atoi ( argv[1] );
// 	double lol = 1.0, pi = 0.0;
// 	for ( i = 0; i < n; i ++ )
// 	{
// 		pi += lol * ( 1.0/((2*i)+1) );
// 		lol *= -1.0;
// 	}
// 	
// 	printf ( "Pi: %lf\n", 4.0*pi );
// 	
// 	return 0;
// }