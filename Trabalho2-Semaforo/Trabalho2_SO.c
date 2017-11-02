/*
 * Alex Matos Iuasse
 * Untrversidade Federal de Mato Grosso
 * Semaforo
 */

#include <stdio.h>
#include <stdlib.h>
/* Biblioteca da thread */
#include <pthread.h>
/* Biblioteca do semaforo */
#include <semaphore.h>
/* Biblioteca sleep */
#include <unistd.h>

void *produtor (void *arg );
void *consumidor (void *arg );
void consumir ();
void produzir();

sem_t *full; //Quantidade de elementos no buffer
sem_t *empty; //Quantidade de posições disponíveis no buffer
sem_t *mutex; //Semaforo Binario
/* Posição de entrada */
int in = 0;
/* Posição de saida */
int out = 0;
/* Numero de consumidores */
int n_consumidor = 0;
/* Numero de produtores */
int n_produtor = 0;
/* Numero de elementos no vetor */
int n_vetor = 0;
/* Vetor com os elementos a serem consumidos/produzidos */
int *vetor_elementos;
/* Quantidade de elementos no buffer(vetor) */
int contador = 0;

int main ( int argc, char **argv )
{
    /* numero de consumidores */
    n_consumidor = atoi ( argv[1] );
    /* numero de produtores */
    n_produtor = atoi ( argv[2] );
    /* numero de Posição no vetor */
    n_vetor = atoi ( argv[3] );
    /* alocando o vetor com tamanho n_vetor */
    vetor_elementos = (int*) malloc (n_vetor*sizeof(int));
    
    printf ("Consumidores: [ %i ] Produtores: [ %i ] Tamanho Buffer: [ %i ]\n",n_consumidor,n_produtor,n_vetor);
    
    printf ("Inicializando semaforos!\n");
    
    mutex = (sem_t*) malloc (sizeof(sem_t));
    full = (sem_t*) malloc (sizeof(sem_t));
    empty = (sem_t*) malloc (sizeof(sem_t));
    
    sem_init ( mutex,0,1 );
    sem_init ( full,0,0 );
    sem_init ( empty,0,n_vetor );
    
    printf ("Semaforos iniciados com sucesso!\n");
    
    pthread_t *thread_ids_produtor = (pthread_t*) malloc (n_produtor*sizeof(pthread_t));
    pthread_t *thread_ids_consumidor = (pthread_t*) malloc (n_consumidor*sizeof(pthread_t));
    
    int i;
    /* Criando threads para produtor */
    int *thread_number_produtor = (int*) malloc (n_produtor*sizeof(int));
    for ( i = 0; i < n_produtor; i ++ )
    {
        thread_number_produtor[i] = i;
        pthread_create ( &thread_ids_produtor[i], NULL, produtor, &thread_number_produtor[i] );
    }
    /* Criando threads para consumidor */
    int *thread_number_consumidor = (int*) malloc (n_consumidor*sizeof(int));
    for ( i = 0; i < n_consumidor; i ++ )
    {
        thread_number_consumidor[i] = i;
        pthread_create ( &thread_ids_consumidor[i], NULL, consumidor, &thread_number_consumidor[i] );
    }
    /* main espera termino das threads */
    for ( i = 0; i < n_consumidor; i ++ )
        pthread_join ( thread_ids_consumidor[i], NULL );
    free ( thread_ids_consumidor );
    for ( i = 0; i < n_produtor; i ++ )
        pthread_join ( thread_ids_produtor[i], NULL );
    free ( thread_ids_produtor );
    
    return 0;
}

void consumir ()
{
    int consumido;
    consumido = vetor_elementos [out];
    out = (out+1)%n_vetor;
    printf ("Item consumido: [ %i ]\n",consumido);
//     sleep(1);
}

void produzir ()
{
    vetor_elementos [in] = ( 0 + rand() % 1024 );
    printf ("Item produzido: [ %i ]\n",vetor_elementos [in]);
    in = (in+1)%n_vetor;
//     sleep(1);
}

void* produtor (void *arg) 
{
    while (1)
    {
        sem_wait(empty);
        sem_wait(mutex);
        produzir();
        sem_post(mutex);
        sem_post(full);
        sleep(1);
    }
}

void* consumidor (void *arg)
{
    while (1)
    {
        sem_wait(full);
        sem_wait(mutex);
        consumir ();
        sem_post(mutex);
        sem_post(empty);
        sleep(1);
    }
}
