#include <stdio.h>
#include <stdlib.h>

// ===================== DEFINIÇÕES =====================
#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct {
    char nome;
    int id;
} Peca;

// Fila Circular
typedef struct {
    Peca vetor[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} FilaCircular;

// Pilha
typedef struct {
    Peca vetor[TAM_PILHA];
    int topo;
} Pilha;

// ===================== GERADOR DE PEÇAS =====================
int proximoId = 1;
char tipos[] = {'I', 'O', 'T', 'L'};

Peca gerarPeca() {
    Peca p;
    p.nome = tipos[(proximoId - 1) % 4];
    p.id = proximoId++;
    return p;
}

// ===================== FILA CIRCULAR =====================
void inicializarFila(FilaCircular *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int filaCheia(FilaCircular *f) {
    return f->quantidade == TAM_FILA;
}

int filaVazia(FilaCircular *f) {
    return f->quantidade == 0;
}

void enfileirar(FilaCircular *f, Peca p) {
    if (filaCheia(f)) {
        printf("  [ERRO] Fila cheia!\n");
        return;
    }
    f->vetor[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

Peca desenfileirar(FilaCircular *f) {
    Peca p = f->vetor[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return p;
}

// ===================== PILHA =====================
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, Peca peca) {
    if (pilhaCheia(p)) {
        printf("  [ERRO] Pilha cheia!\n");
        return;
    }
    p->topo++;
    p->vetor[p->topo] = peca;
}

Peca desempilhar(Pilha *p) {
    Peca peca = p->vetor[p->topo];
    p->topo--;
    return peca;
}

// ===================== EXIBIÇÃO =====================
void exibirEstado(FilaCircular *f, Pilha *p) {
    printf("\nEstado atual:\n");
    printf("+------------------+------------------------------------------+\n");
    printf("| %-16s | ", "Fila de pecas");

    if (f->quantidade == 0) {
        printf("%-40s", "(vazia)");
    } else {
        // monta string da fila
        char buf[200] = "";
        int pos = 0;
        for (int i = 0; i < f->quantidade; i++) {
            int idx = (f->inicio + i) % TAM_FILA;
            char tmp[16];
            sprintf(tmp, "[%c %d] ", f->vetor[idx].nome, f->vetor[idx].id);
            int len = 0;
            while (tmp[len]) buf[pos++] = tmp[len++];
        }
        buf[pos] = '\0';
        printf("%-40s", buf);
    }
    printf("|\n");

    printf("+------------------+------------------------------------------+\n");
    printf("| %-16s | ", "Pilha de reserva");

    if (p->topo == -1) {
        printf("%-40s", "(vazia)");
    } else {
        char buf[200] = "";
        int pos = 0;
        // exibe do topo para a base
        char tmp[32] = "(Topo -> Base): ";
        int k = 0;
        while (tmp[k]) buf[pos++] = tmp[k++];
        for (int i = p->topo; i >= 0; i--) {
            char seg[16];
            sprintf(seg, "[%c %d] ", p->vetor[i].nome, p->vetor[i].id);
            int j = 0;
            while (seg[j]) buf[pos++] = seg[j++];
        }
        buf[pos] = '\0';
        printf("%-40s", buf);
    }
    printf("|\n");
    printf("+------------------+------------------------------------------+\n");
}

void exibirMenu() {
    printf("\nOpcoes de Acao:\n");
    printf("+--------+---------------------+\n");
    printf("| Codigo | Acao                |\n");
    printf("+--------+---------------------+\n");
    printf("|   1    | Jogar peca          |\n");
    printf("|   2    | Reservar peca       |\n");
    printf("|   3    | Usar peca reservada |\n");
    printf("|   0    | Sair                |\n");
    printf("+--------+---------------------+\n");
    printf("\nEscolha uma opcao: ");
}

// ===================== AÇÕES =====================
void jogarPeca(FilaCircular *f) {
    if (filaVazia(f)) {
        printf("  [ERRO] Fila vazia!\n");
        return;
    }
    Peca removida = desenfileirar(f);
    printf("  >> Peca jogada: [%c %d]\n", removida.nome, removida.id);

    Peca nova = gerarPeca();
    enfileirar(f, nova);
    printf("  >> Nova peca gerada: [%c %d]\n", nova.nome, nova.id);
}

void reservarPeca(FilaCircular *f, Pilha *p) {
    if (filaVazia(f)) {
        printf("  [ERRO] Fila vazia!\n");
        return;
    }
    if (pilhaCheia(p)) {
        printf("  [ERRO] Pilha de reserva cheia!\n");
        return;
    }
    Peca reservada = desenfileirar(f);
    empilhar(p, reservada);
    printf("  >> Peca reservada: [%c %d]\n", reservada.nome, reservada.id);

    Peca nova = gerarPeca();
    enfileirar(f, nova);
    printf("  >> Nova peca gerada: [%c %d]\n", nova.nome, nova.id);
}

void usarReserva(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("  [ERRO] Pilha de reserva vazia!\n");
        return;
    }
    Peca usada = desempilhar(p);
    printf("  >> Peca usada da reserva: [%c %d]\n", usada.nome, usada.id);
}

// ===================== MAIN =====================
int main() {
    FilaCircular fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca());
    }

    int opcao;
    do {
        exibirEstado(&fila, &pilha);
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("  [ERRO] Entrada invalida!\n");
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1: jogarPeca(&fila);          break;
            case 2: reservarPeca(&fila, &pilha); break;
            case 3: usarReserva(&pilha);        break;
            case 0: printf("\nSaindo...\n");      break;
            default: printf("  [ERRO] Opcao invalida!\n"); break;
        }
    } while (opcao != 0);

    return 0;
}