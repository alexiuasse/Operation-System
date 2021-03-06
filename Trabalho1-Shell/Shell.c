#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "Getch.h" /* Biblioteca com a implementação da função getch */
#include "Lista.h" /* Biblioteca com a implementação de uma lista */

#define MAX_LINE 80 /* Tamanho máximo da linha de comando */

/*!
 * Função responsável por quebrar em tokens a string de
 * comando dado pelo usuário.
 * Os "comandos" são divididos por espaços ou tabulações, então a ideia
 * é pegar essa string de comando e a cada espaço ir colocando
 * na string de instruções comando
 */
int parse(char *linha, char **comando)
{
  char *token = "a", *subtoken;
  int cont = 0;
  
  while( token != NULL){
    //! atribui a token a primeira parte do comando que esta na string linha
    token = strtok_r(linha, " ,\t",&subtoken);
    if(token != NULL){
      //! Atribui para o vetor de ponteiros comando a substring recebida e em seguida incrementa o vetor
      *comando++ = token;
      //! Incrementando o contador de argumentos
      cont++;
    }
    //! Atribui para linha o restante de seus comandos
    linha = subtoken;
  }
  
  //! Finaliza o comando.
  *comando = '\0';
  //! Retorna o contador de elementos
  return cont;
}

void zumbi ()
{
  waitpid ( -1, NULL, WNOHANG );
}

/*
 * Criando processos
 */

void process ( char **argv, int flag )
{
  pid_t pid;
  pid = fork(); /* Criando processo filho */
  
  if ( pid == -1 )
  {
    printf ("\nERROR fork fail\n");
    exit (1);
  } else {
    if ( pid == 0 ) /* Processo filho */
    {
      puts("");
      if ( ( execvp ( *argv, argv ) ) < 0 ) /* execvp retorna -1 caso erro */
	perror("ERROR exec fail\n");
      exit(1);
    } else { /* Processo pai */
      if ( flag == 1 ){ /* Se tiver um & */
	/* manda um sinal */
	signal ( SIGCHLD, zumbi );
      }else{ /* Se não tiver um & */
	wait(NULL);
      }
    }
  }
}

/* Sair do shell, caso o usuário digite exit */
void shell_exit ( char *linha_comando )
{
  if ( strcmp ( linha_comando, "exit" ) == 0 )
  {
    fflush(stdout);
    puts("\nBye ;p");
    exit(1);
  }
}

/* Verificando a existencia de um & */
void verifica_E ( char **argv, int cont, int *flag )
{
  if (cont != 0 && strcmp(argv[cont-1],"&") == 0){ /* concorrer pai e filho */
    argv[cont-1] = '\0';
    *flag = 1;
  } else { //! Pai fica esperando o filho terminar
    *flag = 0;
  }
}

int main ( void )
{
  system("clear");
  
  char *argv[MAX_LINE/2 + 1]; /* Número máximo de argumentos, incluindo o nome do executável */
  char linha_comando [MAX_LINE]; /* Linha de comando dado pelo usuario */
  
  /*! Das variáveis:
   * flag , usada para saber se o comando possui '&' no final
   * cont_key , quantidade de caracteres
   * flag_key , manter captura de caracteres até ser pressionado enter
   * cont , responsável por pegar o retorno da quantidade de argumentos em argv
   * key , pega caracteres e coloca em linha_comando
   * ind , contador da lista
   * executar , manter o shell funcionando até que seja digitado exit
   */
  
  int flag, cont_key, flag_key, cont;
  int key, ind = -1, executar = 1;
  tipono *lista = NULL; // define lista do historico 
  
  while ( executar )
  {
    flag_key = 1;
    cont = 0;
    cont_key = 0;
    
    printf("iuasse-> ");
    
    fflush ( stdout ); /* força o esvaziamento do buffer de saída stdout (pesquise o manual) */
    
    while ( flag_key )
    {
      
      fflush(stdin); /* Limpar o buffer de entrada */
      
      key = getch();
      if(key == special){
	key = getch();
	if(key == special2){
	  key = getch();
	}
      }
      
      switch ( key )
      {
	
	case KEY_UP:
	  /* chama historico para frente */
	  if(lista != NULL && ind < quat(lista)-1){
	    ind++;
	    imprime_proximo(lista,ind,linha_comando);
	    cont_key = strlen(linha_comando)+1; 
	  }
	  break;
	  
	case backspace:
	  if(cont_key > 0){
	    // apaga do terminal
	    printf("\033[1D");//move pra esquerda
	    printf("\033[K");//apaga
	    /* finaliza a captura de comando */
	    linha_comando[cont_key] = '\0';
	    cont_key--;
	  }else{
	    ind = -1;
	  }
	  break;
	  
	case KEY_DOWN:
	  /* chama historico para tras */
	  if(lista != NULL && ind > 0){
	    ind --;
	    imprime_Anterior(lista,ind,linha_comando);
	    cont_key = strlen(linha_comando)+1;
	  }
	  break;
	  
	case '&':
	  /* caso & seja digitado juntamente com o comando */
	  linha_comando[cont_key] = ' ';
	  cont_key ++;
	  linha_comando[cont_key] = (char) key;
	  printf("%c", (char)key);
	  cont_key ++;
	  break;
	  
	case KEY_ENTER:
	  /* finaliza a captura de comando */
	  linha_comando[cont_key] = '\0';
	  ind = -1;
	  insereinicio(&lista,linha_comando);
	  flag_key = 0;
	  break;
	  
	default:
	  linha_comando[cont_key] = (char) key;
	  printf("%c", (char)key);
	  cont_key ++;
	  break;
      }
    }
    
    /* Sair do shell, caso o usuário digite exit */
    shell_exit ( linha_comando );
    
    /* Parseando a string de entrada (linha_comando) para a string de comandos (argv) */
    cont = parse( linha_comando, argv );
    
    /* Verificando a existencia de um & */
    verifica_E ( argv, cont, &flag );
    
    if (flag == 1 || flag == 0) //! Condição para garantir que o usuário digitou algo
      process ( argv, flag ); /* criar um processo filho para executar um comando */
      
      linha_comando[0] = '\0'; /* Resetando a string de entrada */
    
  }
  
  system("clear");
  
  return 0;
  
}
