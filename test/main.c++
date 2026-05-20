#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int quantidade;
    char nome[30];
    char tipo[10];
} Carro;

int main(void){
    int numero = 10;
    char nome = 'k';

    printf("hello world!\n");
    printf("%d", numero);
    printf("\n");
    printf("%c", nome);

}

