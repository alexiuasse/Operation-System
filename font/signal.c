/*
 * Alex matos iuasse
 * UFMT
 * Tratar sinais
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void trata_signal2 ( int num );

main ()
{
    if ( signal (SIGINT,&trata_signal2) == SIG_ERR)
    {
        perror("Erro no tratamento de sinal");
        exit(1);
    }
    for (;;)
    {
        printf("Executando laço!\n");
        sleep(1);
    }      
}   

void trata_signal2 ( int num )
{
    printf("HahaYehYeh Pegadinha do Malandro!\n");
}