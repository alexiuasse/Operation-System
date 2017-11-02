/*
 * Alex Matos Iuasse
 * Untrversidade Federal de Mato Grosso
 * Calcular Integral
 */

#include <stdio.h>
#include <stdlib.h>
/* Biblioteca da thread */
#include <pthread.h>

void *area_thread ( void *arg );
double integral ( double h );

/* numero total de interações */
double ntr;
/* numero de threads */
double nt;
/* area global */
double area = 0.0;
/* limite superior */
double ls = 4.0;
/*limite inferior */
double li = 0.0;
/* flag para controlar a espera ocupada */
pthread_mutex_t *flag_mutex;

int main ( int argc, char **argv )
{
	/* numero de trapezios */
	ntr = atoi ( argv[1] );
	/* numero de threads */
	nt = atoi ( argv[2] );
	/* limite superior */
// 	ls = atoi ( argv[3] );
// 	/*limite inferior */
// 	li = atoi ( argv[4] );
	
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
		pthread_create ( &thread_ids[i], NULL, area_thread, &thread_number[i] );
	}
	/* main espera termino das threads */
	for ( i = 0; i < nt; i ++ )
		pthread_join ( thread_ids[i], NULL );
	free ( thread_ids );
	pthread_mutex_destroy ( flag_mutex );
	printf ( "Area/Integral aproximada: %lf\n", area );
	
	return 0;
}

void *area_thread ( void *arg )
{
	/* base maior global */
	double bma;
	/* base menor global */
	double bme;
	/* altura global */
	double h = (ls - li) / ntr;
	/* numero da thread */
	int id = *((int*)arg);
	/* fim do laço */
	double t_fim = ntr / nt;
	/* inicio do laço de uma thread */
	double t_inicio = li + (id * t_fim * h);
	
	/* */
	double aux = t_inicio;
	int i;
	double soma = 0.0;
	for ( i = 0; i < t_fim; i ++ )
	{
		bma = integral (aux);
		bme = integral (aux + h);
		soma += ( (bma+bme)*h ) / 2;
		aux += h;
	}
	/* Região critica */
	pthread_mutex_lock ( flag_mutex );
	area += soma;	
	/* saida da regia critica */
	pthread_mutex_unlock ( flag_mutex );
	
}

double integral ( double h )
{
	return h*h;
}