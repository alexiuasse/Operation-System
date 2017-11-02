#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>


//mapeamento do teclado

#define special 27
#define special2 91
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_ENTER 10
#define SPACE 32
#define backspace 127


void init_attr(struct termios *old_attr,struct termios *new_attr){
	tcgetattr(0,&*old_attr);

	*new_attr=*old_attr;
	new_attr->c_lflag &=~ICANON;
	new_attr->c_cc[VMIN]=1;
	new_attr->c_cc[VTIME]=0;
}

int getch(){
	struct termios old_attr, new_attr;
	int c;

	init_attr(&old_attr,&new_attr);

	new_attr.c_lflag &=~ECHO;

	tcsetattr(STDIN_FILENO,TCSANOW,&new_attr);

	c = getchar();

	tcsetattr(STDIN_FILENO,TCSANOW,&old_attr);

	return c;
}

