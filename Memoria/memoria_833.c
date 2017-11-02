#include<stdio.h>
#include<stdlib.h>

void main(int argc, char **argv){
    //for the 32 bits value
    unsigned int value = atoi(argv[1]);
    printf ("Page number: %u\nOffset: %u\n",value/4096,value%4096);
}