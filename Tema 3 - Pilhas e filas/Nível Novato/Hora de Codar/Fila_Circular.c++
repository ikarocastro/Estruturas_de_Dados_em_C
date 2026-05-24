// veja a implementação de uma fila circular em C de pessoas. Essa prática é fundamental para criar a fila das peças no Tetris Stack,
// necessitando apenas da criação de uma estrutura que represente peças.
/*Testando pela primeia vez subescrever os codigos em C para C++*/

#include <stdio.h>
#include <stdlib.h>

// ===========================================================================================================================================================================================================
// DECLARAÇÃO DE ESTRUTUTURAS
// ===========================================================================================================================================================================================================
typedef struct {
    char nome[30];
    int idade;
} Pessoa;

/*Temos a Struct Pessoa, onde cada pessoa vai ter um nome e uma idade*/

#define MAX 5

/*Struct para a fila*/

typedef struct {
    Pessoa itens[MAX]; // Criamos um array de pessoas chamado (itens) e referenciando o tamanho (MAX 5) da fila
    int inicio;
    int fim;
    int total;
} Fila;

// ===========================================================================================================================================================================================================
// DECLARAÇÃO DE FUNÇÕES
// ===========================================================================================================================================================================================================

/*Precisamos agora de uma função para inicializar nossa fila e para saber se ela está cheia ou vazia!*/

void inicializarFila(Fila *f){ /* O (*f) está referenciando os valores bases que definimos na nossa struct Fila*/
    f->inicio = 0; // Aponta pro inicio do vetor
    f->fim = 0; // 0 por que não contem nenhum dado ali
    f->total = 0; // 0 por que a fila está vazia, vai definir se a fila está cheia ou vazia!
}
/* Declaramos nossa função de inicializar fila declarando que ela estpa vazia em ambas as partes dela*/
/* Declaramos tambem duas funções do tipo INT que retornam se nossa fila está cheia ou vazia!*/
int filaCheia(Fila *f){
    return f->total == MAX;
}
/* Dizemos que ela está cheia se retunar que o total da fila (f->total) for igual a MAX*/

int filaVazia(Fila *f){
    return f->total == 0;
}
/* Dizemos que a fila está vazia se retornar o (f->total) igual a zero*/

// ===========================================================================================================================================================================================================
// CHAMAR E IMPLEMENTAR AS FUNÇÕES BÁSICAS (INSERÇÃO, REMOÇÃO)
// ===========================================================================================================================================================================================================

void inserir(Fila *f, Pessoa p){
    if (filaCheia(f))
    {
        printf("Fila cheia! Nao e possivel inserir!");
    }
    
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;

}

void remover(Fila *f, Pessoa *p){ // Referenciamos a fila (Fila *f) e o elemento (Pessoa *p)
    if (filaVazia(f)){ // Confere se a fila está vazia!
        printf("Fila vazia, Não é possivel remover!");
        return;
    }    
    // Se não estever vazia ele cai nesse bloco de código

    *p = f->itens[f->inicio];   /* Pega o ponteiro do elemento (*p) e passsa pra ele quem vai ser removido (f->intens[f->inicio]) */
    f->inicio = (f->inicio + 1) % MAX;  // Vou precisar atualizar quem está no inicio, já que eu removi o elemento, vamos atualizar de acordo com a lógica circular
    f->total--; // Significa que o tamanho total da minha fila diminuiu 

}    

// ===========================================================================================================================================================================================================
// FUNÇÃO DE EXIBIÇÃO
// ===========================================================================================================================================================================================================

void mostrarFila(Fila *f){
    printf("Fila: ");   // indicando que vou exibir uma fila

    /* Vamos percorrer toda a fila para saber todos os elementos que estão dentro dela para que eu consiga exibi-los*/
    // IDX é o nosso indice da fila!
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX)
    {
       printf("[%s, %d] ", f->itens[idx].nome, f->itens[idx].idade);
    }
    
        printf("\n");
}



// ===========================================================================================================================================================================================================
// FUNÇÃO PRINCIPAL (MAIN)
// ===========================================================================================================================================================================================================
int main(void){
    /* O que a gente fez antes só passa a funcionar assim que declararmos essas dois valores no caso a Fila recebe (f) e a chamada da função (inicializarFila(&f))*/
    Fila f;
    inicializarFila(&f); // inicializa a fila

    // Declaramos "p1 e p1" que são variavei do tipo "Pessoa"
    Pessoa p1 = {"Joao", 25};
    Pessoa p2 = {"Maria", 30};
    
    // Insere algumas pessoas na fila
    inserir(&f, p1);
    inserir(&f, p2);

    mostrarFila(&f); // Mostra a fila antes da remoção

    // Remove uma pessoa da fila
    Pessoa removida;
    remover(&f, &removida); // (&removida) por enquanto é uma estrutura vazia pois ainda não recebeu um valor, ela vai receber a partir do elemento que está no inicio no caso (p1)
    printf("Pessoa removida: %s, %d\n", removida.nome, removida.idade);

    mostrarFila(&f); // Mostra a fila após a remoção!

    return 0;
}
