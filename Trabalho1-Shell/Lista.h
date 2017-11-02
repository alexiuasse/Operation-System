#include <stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct lestruturano{
	char valor[100];
	struct lestruturano *anterior;
	struct lestruturano *prox;
}tipono;

tipono *alocar(char *valor ){
	tipono *novono = NULL;
	novono = (tipono*) malloc (sizeof(tipono));
	strcpy(novono->valor ,valor);
	novono->prox = NULL;
	novono->anterior = NULL;
	return novono;
}

int quat(tipono *lista){
  int i = 0;
  while (lista != NULL ){
	  lista = lista->prox;
	  i++;
      }
      return i;
}


void removefim(tipono **lista){
	tipono *aux=NULL;
	aux=*lista;
	while(aux->prox!=NULL){
		aux=aux->prox;
	}
	(aux->anterior)->prox=NULL;
	free(aux);
}

void insereinicio(tipono **lista,char *valor){
	tipono *novono = alocar(valor);
	tipono * aux = *lista;
	if(*lista == NULL){
		*lista = novono;
		novono->anterior = NULL;
		novono->prox = NULL;
	}else
	{
		if(quat(aux) < 10){
		    novono->anterior = NULL;
		    (*lista)->anterior = novono;
		    novono->prox = *lista;
		    *lista = novono;
		}else{
		    removefim(lista);
		    novono->anterior = NULL;
		    (*lista)->anterior = novono;
		    novono->prox = *lista;
		    *lista = novono;
		}
		
	}
}

void imprime_Anterior (tipono *lista, int ind, char *comando)
{
  int i = 0;
    if (lista != NULL)
    {
      while (lista->prox != NULL && i < ind){
	  lista = lista->prox;
	  i++;
      }
      if(i == ind){
	printf("\r");
	printf("\033[K");
	printf ("iuasse-> %s ", lista->valor);
	strcpy(comando,lista->valor);
	
      }
     
    }
}


void imprime_proximo (tipono *lista, int ind, char *comando)
{
  int i = 0;
    if (lista != NULL)
    {
      while (lista->prox != NULL && i < ind){
	  lista = lista->prox;
	  i++;
      }
      if(i == ind){
	printf("\r");
	printf("\033[K");
	printf ("iuasse-> %s ", lista->valor);
	strcpy(comando,lista->valor);
	
      }
     
    }
}



