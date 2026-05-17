#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// =============================================================================================================================================================================================
// Definições
// =============================================================================================================================================================================================
#define MAX 50      // Tamanho máximo do vetor
int comparacoes = 0;    // Contador global de comparações (busca)

// =============================================================================================================================================================================================
// STRUCTS
// =============================================================================================================================================================================================
// As structs são os "moldes" para criar nossos objetos

// Representa um item da mochila
typedef struct {
    char nome[30];       // Nome do item (ex: "Espada", "Poção")
    char tipo[20];       // Tipo do item (ex: "Arma", "Consumível")
    int  quantidade;     // Quantas unidades o jogador carrega
} Item;

// Representa um NÓ da lista encadeada
// Cada nó carrega um item E um ponteiro para o próximo nó
typedef struct No {
    Item dados;          // O item em si
    struct No* proximo;  // Endereço do próximo nó (ou NULL se for o último)
} No;

// Estrutura da mochila com VETOR
typedef struct {
    Item itens[MAX];        // Array fixo de itens
    int  tamanho;           // Quantos itens estão ocupados agora
} MochilaVetor;

// Estrutura da mochila com LISTA ENCADEADA
typedef struct {
    No* cabeca;             // Ponteiro para o primeiro nó (entrada da lista)
    int tamanho;            // Quantidade de itens na lista
} MochilaLista;

// =============================================================================================================================================================================================
// Inicializador das mochilas
// =============================================================================================================================================================================================

// Prepara a mochila de VETOR para uso
void inicializarVetor(MochilaVetor* m) {
    m->tamanho = 0;   // Começa vazia — nenhum slot ocupado
    // Os dados em itens[] existem na memória mas são "lixo" até tamanho > 0
}

// Prepara a mochila de LISTA para uso
void inicializarLista(MochilaLista* m) {
    m->cabeca  = NULL;  // Sem nenhum nó ainda — lista vazia
    m->tamanho = 0;
}

// =============================================================================================================================================================================================
// INSERÇÃO
// =============================================================================================================================================================================================

// ── VETOR ──────────────────────────────────────────────

void inserirItemVetor(MochilaVetor* m, Item novoItem){
    if (m->tamanho >= MAX)
    {
        printf("Mochila cheia, Não é possivel inserir");
        return;
    }
     // Coloca o item na próxima posição livre e avança o contador
    m->itens[m->tamanho] = novoItem;
    m->tamanho++;
}

// ── LISTA ENCADEADA ────────────────────────────────────

void inserirItemLista(MochilaLista* m, Item novoItem){
    // 1. Aloca memória para um novo nó no heap
    No* novo = (No*) malloc(sizeof(No));
     if (novo = NULL)
     {
        printf("Erro de memoria!\n");
        return;
    }
   
    // 2. Preenche o nó com os dados do item
    novo->dados = novoItem;
    novo->proximo = NULL;   // Por enquanto, não aponta para ninguém
    
    // 3. Insere no início da lista (mais simples e O(1))
    novo->proximo = m->cabeca;  // Novo nó aponta para quem era o primeiro
    m->cabeca = novo;       // Cabeça passa a ser o novo nó
    m->tamanho++;
}

// =============================================================================================================================================================================================
// REMOÇÃO
// =============================================================================================================================================================================================

// ── VETOR ──────────────────────────────────────────────
void removerItemVetor(MochilaVetor* m, char* nome){
    int encontrado = -1;

       // Passo 1: encontrar o índice do item
        for (int i = 0; i < m->tamanho; i++)
        {
            if (strcmp(m->itens[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }
        if (encontrado == -1) {
        printf("Item '%s' não encontrado.\n", nome);
        return;
}

    // Passo 2: "empurra" todos os elementos seguintes uma posição para trás
    // Isso preenche o "buraco" deixado pelo item removido
    for (int i = encontrado; i < m->tamanho; i++)
    {
        m->itens[i] = m->itens[i + 1];
    }
        m->tamanho--;
        printf("Item '%s' removido do vetor.\n", nome);
}

// ── LISTA ENCADEADA ────────────────────────────────────
void removerItemLista(MochilaLista* m, char* nome) {
    No* atual    = m->cabeca;
    No* anterior = NULL;

    // Percorre a lista procurando o nó com o nome desejado
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            // Caso 1: é o primeiro nó
            if (anterior == NULL) {
                m->cabeca = atual->proximo;
            } else {
                // Caso 2: está no meio ou fim — "pula" o nó atual
                anterior->proximo = atual->proximo;
            }
            free(atual);   // Libera a memória do nó removido!
            m->tamanho--;
            printf("Item '%s' removido da lista.\n", nome);
            return;
        }
        anterior = atual;
        atual    = atual->proximo;
    }
    printf("Item '%s' não encontrado na lista.\n", nome);
}       

// =============================================================================================================================================================================================
// LISTAGEM
// =============================================================================================================================================================================================

// ── VETOR ──────────────────────────────────────────────
void listarVetor(MochilaVetor* m) {
    if (m->tamanho == 0) {
        printf("Mochila (vetor) vazia.\n");
        return;
    }
    printf("\n=== MOCHILA [VETOR] ===\n");
    for (int i = 0; i < m->tamanho; i++) {
        printf("[%d] Nome: %-20s | Tipo: %-15s | Qtd: %d\n",
               i + 1,
               m->itens[i].nome,
               m->itens[i].tipo,
               m->itens[i].quantidade);
    }
}

// ── LISTA ENCADEADA ────────────────────────────────────
void listarLista(MochilaLista* m) {
    if (m->cabeca == NULL) {
        printf("Mochila (lista) vazia.\n");
        return;
    }
    printf("\n=== MOCHILA [LISTA ENCADEADA] ===\n");
    No* atual = m->cabeca;
    int i = 1;
    while (atual != NULL) {         // Caminha até o fim (NULL)
        printf("[%d] Nome: %-20s | Tipo: %-15s | Qtd: %d\n",
               i++,
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;     // Avança para o próximo nó
    }
}

// =============================================================================================================================================================================================
// BUSCA SEQUENCIAL (NAS DUAS ESTRUTURAS)
// =============================================================================================================================================================================================

// ── VETOR ──────────────────────────────────────────────
int buscarSequencialVetor(MochilaVetor* m, char* nome) {
    comparacoes = 0;   // Zera o contador antes de cada busca
    for (int i = 0; i < m->tamanho; i++) {
        comparacoes++;                             // Conta cada comparação
        if (strcmp(m->itens[i].nome, nome) == 0)
            return i;   // Retorna o índice onde achou
    }
    return -1;   // Não encontrado
}

// ── LISTA ENCADEADA ────────────────────────────────────
No* buscarSequencialLista(MochilaLista* m, char* nome) {
    comparacoes = 0;
    No* atual = m->cabeca;
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return atual;   // Retorna o ponteiro para o nó
        atual = atual->proximo;
    }
    return NULL;   // Não encontrado
}

// =============================================================================================================================================================================================
//  ORDENAÇÃO (BUBBLE SORT NO VETOR)
// =============================================================================================================================================================================================

void ordenarVetor(MochilaVetor* m) {
    // Bubble Sort: compara pares adjacentes e troca se estiver fora de ordem
    // Após cada passagem completa, o maior elemento "sobe" para o final
    for (int i = 0; i < m->tamanho - 1; i++) {
        for (int j = 0; j < m->tamanho - 1 - i; j++) {
            // strcmp retorna negativo se [j] vem antes de [j+1] alfabeticamente
            // retorna positivo se [j] deveria vir DEPOIS → precisa trocar
            if (strcmp(m->itens[j].nome, m->itens[j + 1].nome) > 0) {
                Item temp          = m->itens[j];
                m->itens[j]        = m->itens[j + 1];
                m->itens[j + 1]    = temp;
            }
        }
    }
    printf("Vetor ordenado alfabeticamente.\n");
}

// =============================================================================================================================================================================================
//  BUSCA BINÁRIA (SÓ NO VETOR ORDENADO)
// =============================================================================================================================================================================================

int buscarBinariaVetor(MochilaVetor* m, char* nome) {
    comparacoes = 0;
    int inicio = 0;
    int fim    = m->tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;   // Ponto central
        comparacoes++;

        int cmp = strcmp(m->itens[meio].nome, nome);

        if (cmp == 0) {
            return meio;           // Achou exatamente no meio!
        } else if (cmp < 0) {
            inicio = meio + 1;     // Nome buscado vem depois → descarta metade esquerda
        } else {
            fim = meio - 1;        // Nome buscado vem antes  → descarta metade direita
        }
    }
    return -1;   // Não encontrado
}

// =============================================================================================================================================================================================
//  METODO (MAIN)
// =============================================================================================================================================================================================

int main() {
    MochilaVetor mv;
    MochilaLista ml;
    inicializarVetor(&mv);
    inicializarLista(&ml);

    int opcao;
    do {
        printf("\n========== SISTEMA DE MOCHILA ==========\n");
        printf("1. Inserir item (nas duas estruturas)\n");
        printf("2. Remover item (nas duas estruturas)\n");
        printf("3. Listar itens do VETOR\n");
        printf("4. Listar itens da LISTA ENCADEADA\n");
        printf("5. Busca sequencial (nas duas)\n");
        printf("6. Ordenar VETOR + Busca Binária\n");
        printf("7. Comparar desempenho (sequencial vs binária)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o '\n' que sobrou no buffer

        if (opcao == 1) {
            Item novo;
            printf("Nome do item: ");   fgets(novo.nome, 30, stdin);
            novo.nome[strcspn(novo.nome, "\n")] = '\0';  // Remove o '\n' do fgets

            printf("Tipo do item: ");   fgets(novo.tipo, 20, stdin);
            novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

            printf("Quantidade: ");     scanf("%d", &novo.quantidade);
            getchar();

            inserirItemVetor(&mv, novo);
            inserirItemLista(&ml, novo);
            printf("Item inserido nas duas estruturas!\n");

        } else if (opcao == 2) {
            char nome[30];
            printf("Nome do item a remover: ");
            fgets(nome, 30, stdin);
            nome[strcspn(nome, "\n")] = '\0';
            removerItemVetor(&mv, nome);
            removerItemLista(&ml, nome);

        } else if (opcao == 3) {
            listarVetor(&mv);

        } else if (opcao == 4) {
            listarLista(&ml);

        } else if (opcao == 5) {
            char nome[30];
            printf("Nome para busca sequencial: ");
            fgets(nome, 30, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            int idx = buscarSequencialVetor(&mv, nome);
            printf("[VETOR]  Comparações: %d | ", comparacoes);
            if (idx != -1) printf("Encontrado na posição %d\n", idx + 1);
            else           printf("Não encontrado\n");

            No* no = buscarSequencialLista(&ml, nome);
            printf("[LISTA]  Comparações: %d | ", comparacoes);
            if (no != NULL) printf("Encontrado: %s (%d un.)\n", no->dados.nome, no->dados.quantidade);
            else            printf("Não encontrado\n");

        } else if (opcao == 6) {
            ordenarVetor(&mv);
            listarVetor(&mv);

            char nome[30];
            printf("Nome para busca BINÁRIA: ");
            fgets(nome, 30, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            int idx = buscarBinariaVetor(&mv, nome);
            printf("[BINÁRIA] Comparações: %d | ", comparacoes);
            if (idx != -1) printf("Encontrado na posição %d\n", idx + 1);
            else           printf("Não encontrado\n");

        } else if (opcao == 7) {
            // Compara sequencial vs binária no mesmo item
            ordenarVetor(&mv);
            char nome[30];
            printf("Item crítico para comparar buscas: ");
            fgets(nome, 30, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            buscarSequencialVetor(&mv, nome);
            int c_seq = comparacoes;

            buscarBinariaVetor(&mv, nome);
            int c_bin = comparacoes;

            printf("\n--- Comparativo de Desempenho ---\n");
            printf("Busca SEQUENCIAL: %d comparações\n", c_seq);
            printf("Busca BINÁRIA:    %d comparações\n", c_bin);
            printf("A binária foi %.1fx mais eficiente.\n",
                   c_seq > 0 ? (float)c_seq / c_bin : 1.0f);
        }

    } while (opcao != 0);

    // Libera a memória de todos os nós da lista antes de sair
    No* atual = ml.cabeca;
    while (atual != NULL) {
        No* prox = atual->proximo;
        free(atual);
        atual = prox;
    }

    printf("Saindo do jogo. Memória liberada!\n");
    return 0;
}