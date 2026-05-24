/* SOBRE: A ByteBros, desenvolvedora de jogos voltados para o ensino de lógica e programação, está desenvolvendo um novo título chamado Tetris Stack,
 um jogo eletrônico no qual os jogadores precisam organizar e posicionar peças utilizando estruturas de dados fundamentais como parte das mecânicas de jogo.*/

 /* OBJETIVO: Designaram você como desenvolvedor(a) técnico(a) responsável pela estrutura de controle de peças do jogo, incluindo a implementação do sistema de fila de peças futuras. Seu trabalho é verificar se as regras de entrada,
 saída e troca entre as estruturas estão funcionando e se refletem a lógica do jogo.*/

 /* IMPLEMENTAÇÃO: Agora, você implementará um programa em C que simula a fila de peças futuras do Tetris Stack. As peças têm um tipo (como 'I', 'O', 'T', 'L'),
  que representa suas formas e um identificador numérico (id) exclusivo. O programa oferecerá ao jogador a opção de visualizar a fila,
  jogar uma peça (remoção da frente) ou adicionar uma nova peça ao final da fila.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

// ===========================================================================================================================================================================================================
// Structs
// ===========================================================================================================================================================================================================
typedef struct {
    char nome; // Tipo da peça (I, O, T, L)
    int id;    // Identificador numérico exclusivo
} Peca;

typedef struct {
    Peca itens[MAX]; // Array de peças na fila
    int inicio;
    int fim;
    int total;
} FilaPecas;

// ===========================================================================================================================================================================================================
// Funções para manipulação da fila de peças
// ===========================================================================================================================================================================================================

void inicializarFila(FilaPecas *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(FilaPecas *f) {
    return f->total == MAX;
}

int filaVazia(FilaPecas *f) {
    return f->total == 0;
}

void inserirPeca(FilaPecas *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia! Nao e possivel inserir a peca!\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void removerPeca(FilaPecas *f, Peca *p) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nao e possivel remover a peca!\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void mostrarFila(FilaPecas *f) {
    printf("Fila de Pecas: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c, %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

void gerarPecaAleatoria(Peca *p, int id) {
    char tipos[] = {'I', 'O', 'T', 'L', 'S'};
    p->nome = tipos[rand() % 5];
    p->id = id;
}

// ===========================================================================================================================================================================================================
// Função principal para testar a implementação
// ===========================================================================================================================================================================================================

int main() {
    FilaPecas fila;
    inicializarFila(&fila);

    int nextId = 1;
    int opcao;

    // Preenche a fila inicial com 4 peças aleatórias
    for (int i = 0; i < 4; i++) {
        Peca p;
        gerarPecaAleatoria(&p, nextId++);
        inserirPeca(&fila, p);
    }

    printf("=== Tetris Stack ===\n");
    mostrarFila(&fila);

    do {
        printf("\n--- Menu ---\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca removida;
                removerPeca(&fila, &removida);
                if (!filaVazia(&fila)) {
                    printf("Peca jogada: [%c, %d]\n", removida.nome, removida.id);
                }
                mostrarFila(&fila);
                break;
            }
            case 2: {
                Peca nova;
                gerarPecaAleatoria(&nova, nextId++);
                inserirPeca(&fila, nova);
                if (!filaCheia(&fila)) {
                    printf("Nova peca inserida: [%c, %d]\n", nova.nome, nova.id);
                }
                mostrarFila(&fila);
                break;
            }
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}