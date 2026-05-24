#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===================== DEFINIÇÕES =====================
#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct {
    char nome;
    int id;
} Peca;

// Fila
typedef struct {
    Peca vetor[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

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

// ===================== FILA =====================
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

void enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("  [ERRO] Fila cheia!\n");
        return;
    }
    f->vetor[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

Peca desenfileirar(Fila *f) {
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
void exibirEstado(Fila *f, Pilha *p) {
    printf("\nEstado atual:\n");
    printf("+------------------+------------------------------------------+\n");
    printf("| %-16s | ", "Fila de pecas");

    if (f->quantidade == 0) {
        printf("%-40s", "(vazia)");
    } else {
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
    printf("+--------+------------------------------+\n");
    printf("| Codigo | Acao                         |\n");
    printf("+--------+------------------------------+\n");
    printf("|   1    | Jogar peca                   |\n");
    printf("|   2    | Reservar peca                |\n");
    printf("|   3    | Usar peca reservada           |\n");
    printf("|   4    | Trocar peca atual            |\n");
    printf("|   5    | Troca multipla (3 pecas)     |\n");
    printf("|   6    | Visualizar estado atual      |\n");
    printf("|   0    | Sair                         |\n");
    printf("+--------+------------------------------+\n");
    printf("\nEscolha uma opcao: ");
}

// ===================== UTILITÁRIO: completar fila =====================
// Gera peças automaticamente até a fila estar cheia (quando possível)
void completarFila(Fila *f) {
    while (!filaCheia(f)) {
        Peca nova = gerarPeca();
        enfileirar(f, nova);
        printf("  >> Nova peca gerada automaticamente: [%c %d]\n", nova.nome, nova.id);
    }
}

// ===================== AÇÕES =====================

// 1. Jogar peça: remove a peça da frente da fila e gera uma nova
void jogarPeca(Fila *f) {
    if (filaVazia(f)) {
        printf("  [ERRO] Fila vazia!\n");
        return;
    }
    Peca removida = desenfileirar(f);
    printf("  >> Peca jogada: [%c %d]\n", removida.nome, removida.id);
    completarFila(f);
}

// 2. Reservar peça: move a frente da fila para o topo da pilha e repõe a fila
void reservarPeca(Fila *f, Pilha *p) {
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
    completarFila(f);
}

// 3. Usar peça reservada: remove do topo da pilha (peça não volta ao jogo)
void usarReserva(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("  [ERRO] Pilha de reserva vazia!\n");
        return;
    }
    Peca usada = desempilhar(p);
    printf("  >> Peca usada da reserva: [%c %d]\n", usada.nome, usada.id);
}

// 4. Trocar peça atual: troca a peça da frente da fila com o topo da pilha
void trocarPecaAtual(Fila *f, Pilha *p) {
    if (filaVazia(f)) {
        printf("  [ERRO] Fila vazia! Nao e possivel trocar.\n");
        return;
    }
    if (pilhaVazia(p)) {
        printf("  [ERRO] Pilha de reserva vazia! Nao e possivel trocar.\n");
        return;
    }

    // Remove a frente da fila e o topo da pilha
    Peca daFila  = desenfileirar(f);
    Peca daPilha = desempilhar(p);

    printf("  >> Trocando: fila [%c %d] <-> pilha [%c %d]\n",
           daFila.nome, daFila.id, daPilha.nome, daPilha.id);

    // A peça que estava na pilha vai para o INÍCIO da fila
    // Precisamos inserir na frente: ajustamos o índice início manualmente
    f->inicio = (f->inicio - 1 + TAM_FILA) % TAM_FILA;
    f->vetor[f->inicio] = daPilha;
    f->quantidade++;

    // A peça que estava na fila vai para o topo da pilha
    empilhar(p, daFila);

    printf("  >> Peca [%c %d] agora esta na frente da fila.\n", daPilha.nome, daPilha.id);
    printf("  >> Peca [%c %d] agora esta no topo da pilha.\n", daFila.nome, daFila.id);
}

// 5. Troca múltipla: alterna as 3 primeiras peças da fila com as 3 da pilha
void trocaMultipla(Fila *f, Pilha *p) {
    if (f->quantidade < 3) {
        printf("  [ERRO] A fila precisa ter pelo menos 3 pecas para troca multipla.\n");
        return;
    }
    if (p->topo < 2) {
        printf("  [ERRO] A pilha precisa ter pelo menos 3 pecas para troca multipla.\n");
        return;
    }

    printf("  >> Realizando troca multipla das 3 primeiras pecas...\n");

    // Guarda as 3 primeiras da fila (em ordem de frente para o terceiro)
    Peca filaTmp[3];
    for (int i = 0; i < 3; i++) {
        filaTmp[i] = desenfileirar(f);
    }

    // Guarda as 3 da pilha (topo, meio, base) — desempilhando em ordem
    Peca pilhaTmp[3];
    for (int i = 0; i < 3; i++) {
        pilhaTmp[i] = desempilhar(p);
    }
    // pilhaTmp[0] = antigo topo, [1] = meio, [2] = base

    // As peças da pilha entram na frente da fila (inserção reversa para manter ordem)
    // Queremos que o antigo topo fique na frente da fila
    // Inserimos da posição 2 ao 0 para que ao final [0] esteja na frente
    for (int i = 2; i >= 0; i--) {
        f->inicio = (f->inicio - 1 + TAM_FILA) % TAM_FILA;
        f->vetor[f->inicio] = pilhaTmp[i];
        f->quantidade++;
    }

    // As peças da fila vão para a pilha (empilhamos do índice 2 ao 0
    // para que filaTmp[0] fique no topo)
    for (int i = 2; i >= 0; i--) {
        empilhar(p, filaTmp[i]);
    }

    printf("  >> Troca multipla concluida!\n");
    printf("  Pecas da fila [%c %d][%c %d][%c %d] foram para a pilha.\n",
           filaTmp[0].nome, filaTmp[0].id,
           filaTmp[1].nome, filaTmp[1].id,
           filaTmp[2].nome, filaTmp[2].id);
    printf("  Pecas da pilha [%c %d][%c %d][%c %d] foram para a frente da fila.\n",
           pilhaTmp[0].nome, pilhaTmp[0].id,
           pilhaTmp[1].nome, pilhaTmp[1].id,
           pilhaTmp[2].nome, pilhaTmp[2].id);
}

// ===================== MAIN =====================
int main() {
    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preenche a fila inicial automaticamente
    printf("=== Inicializando jogo ===\n");
    completarFila(&fila);

    int opcao;
    do {
        exibirEstado(&fila, &pilha);
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n[Acao: Jogar peca]\n");
                jogarPeca(&fila);
                break;
            case 2:
                printf("\n[Acao: Reservar peca]\n");
                reservarPeca(&fila, &pilha);
                break;
            case 3:
                printf("\n[Acao: Usar peca reservada]\n");
                usarReserva(&pilha);
                break;
            case 4:
                printf("\n[Acao: Trocar peca atual]\n");
                trocarPecaAtual(&fila, &pilha);
                break;
            case 5:
                printf("\n[Acao: Troca multipla]\n");
                trocaMultipla(&fila, &pilha);
                break;
            case 6:
                printf("\n[Acao: Visualizar estado]\n");
                // o estado ja e exibido no topo do loop, mas exibimos de novo para clareza
                exibirEstado(&fila, &pilha);
                break;
            case 0:
                printf("\nEncerrando o programa. Ate mais!\n");
                break;
            default:
                printf("  [ERRO] Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}