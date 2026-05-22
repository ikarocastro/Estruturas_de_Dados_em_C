#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    char nome[30];
    int idade;
} Pessoa;

typedef struct {
    Pessoa itens[MAX];
    int topo; // Referencia tudo com a variavel topo
} Pilha;

// Passo 2: verificação e inicializaão

void inicializarPilha(Pilha *p){
    p->topo = -1; // -1 é o valor que representa que minha pilha está vazia!
}

int pilhaVazia(Pilha *p){
    return p->topo == -1; // Como o "topo" é nosso paramêtro ele retorna verdadeiro se (p->topo == -1) ou seja indicando que não tem nada na minha pilha
}

int pilhaCheia(Pilha *p){
    return p->topo == MAX -1; // Retorna se o maximo da pilha tiver sido alcançado ele retorna false ou seja  está cheia!
}


/* Push para inserir na pilha!*/
void push(Pilha *p, Pessoa nova){
    if (pilhaCheia(p))
    {
        printf("Pilha esta cheia. Nao e possivel inserir!");
        return;
    }

    p->topo++;
    p->itens[p->topo] = nova;

}

/* Pop para remover da pilha!*/
void pop(Pilha *p, Pessoa *removida){
    if (pilhaVazia(p))
    {
        printf("Pilha vazia. nao e possivel remover!");
    }
    
    *removida = p->itens[p->topo];
    p->topo--;
}

/* Só visualiza não remove!*/
void peek(Pilha *p, Pessoa *visualizacao){
    if (pilhaVazia(p))
    {
        printf("Pilha vazia. nada para espiar!");
    }
    
    *visualizacao = p->itens[p->topo];
}

/* Função mostrar pilha!*/

void mostrarPilha(Pilha *p){
    printf("Pilha (topo -> base): \n");
    for (int i = p->topo; i >= 0; i--)
    {
        printf("[%s, %d]\n", p->itens[i].nome, p->itens[i].idade );
    }
    printf("\n");
}


int main() {
    // Criando instancia

    Pilha p; // Variavel p do tipo pilha
    inicializarPilha(&p);

    Pessoa a = {"Ana", 20};
    Pessoa b = {"Bruno", 35};
    Pessoa c = {"Carlos", 28};

    push(&p, a);
    push(&p, b);
    push(&p, c);

    mostrarPilha(&p);

    Pessoa removida;
    pop(&p, &removida);
    printf("Pessoa removida: %s, %d\n", removida.nome, removida.idade);

    mostrarPilha(&p);

    Pessoa topo;
    peek(&p, &topo);
    printf("Topo atual: %s, %d\n", topo.nome, topo.idade);
   
    return 0;

}