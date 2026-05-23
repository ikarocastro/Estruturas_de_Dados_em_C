
// Ver na prática como funciona a inversão de ordem com filas e pilhas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50


// Estrutura do nosso elemento 
typedef struct {
    char nome[30];
    int idade;
} Pessoa;

// Estrutura do nossa fila
typedef struct {
    Pessoa dados[MAX];
    int inicio, fim;
} Fila;

// Estrutura da nossa Pilha
typedef struct {
    Pessoa dados[MAX];
    int topo;
} Pilha;

void inicializarFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
}

void inicializarPilha(Pilha *p){
    p->topo = -1;
}

// Trazer as operações primeiro da fila depois da pilha

void inserirFila(Fila *f, Pessoa p){
    if(f->fim < MAX){
        f->dados[f->fim++] = p; 
    }
}

Pessoa removerFila(Fila *f){
    return f->dados[f->inicio++];
}

// Operações da Pilha

void push(Pilha *p, Pessoa pes){
    if(p->topo < MAX -1){ // ta testando se o topo chegou no maximo -1  ou seja atingiu o maximo dos indices
        p->dados[++p->topo] = pes;
    }
}

Pessoa pop(Pilha *p){
    return p->dados[p->topo--];// [p->topo--] decrementa o topo perdendo essa informação 
}

void exibirFila(Fila f){
    for (int i = f.inicio; i < f.fim; i++)
    {
        printf("Nome: %s | Idade: %d\n", f.dados[i].nome, f.dados[i].idade); // pegar da fila'f' os dados '.dados' do 'indice' e puxar o nome!
    }
    
}

int main() {

    Fila filaOriginal, filaInvertida;
    Pilha Auxiliar;
    
    inicializarFila(&filaOriginal);
    inicializarFila(&filaInvertida);
    inicializarPilha(&Auxiliar);
    
    Pessoa pessoas[] = { // Array de pessoas
        {"Carlos", 45}, {"Joana", 62}, {"Lucas", 30}, {"Maria", 75}
    };

    for (int i = 0; i < 4; i++){
        inserirFila(&filaOriginal, pessoas[i]); // "pessoas[i]" = array de pessoas
    }
    
    printf("Fila original: \n");
    exibirFila(filaOriginal);

    // Fila invertida
    
    while (filaOriginal.inicio < filaOriginal.fim){
        push(&Auxiliar, removerFila(&filaOriginal));
    }

    while (Auxiliar.topo >= 0){
        inserirFila(&filaInvertida, pop(&Auxiliar));
    }
    
    printf("Fila invertida:\n");
    exibirFila(filaInvertida);

    return 0;

}