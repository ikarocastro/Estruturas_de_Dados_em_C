#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Biblioteca necessária para usar a função (strcpy,strcmp)

#define MAX_STR_LEN 30 // Define o tamanho máximo para as strings (nome do item e categoria)
#define MAX_ITENS 10 // Define o número máximo de itens que a lista pode conter
#define TAM_NOME 30 // Define o tamanho máximo para o nome do item
#define TAM_TIPO 20 // Define o tamanho máximo para o tipo do item

// =====================================================================================================================================================================================================================================================================================
// Estrutura do Item
// =====================================================================================================================================================================================================================================================================================

typedef struct{
    char nome[TAM_NOME];  /* ex: "Espada de Ferro"  */
    char tipo[TAM_TIPO];    /* ex: "Arma Branca" ou "Arma de Fogo" ou "Kit Medico" ou "Granada" */
    int quantidade; /* ex: 3 */
} item;

//====================================================================================================================================================================================================================================================================================
// Funções
//====================================================================================================================================================================================================================================================================================

/* Remove o '\n' que fgets deixa no final da string */
static void limpar_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') s[len - 1] = '\0';
}

// =====================================================================================================================================================================================================================================================================================
/* Cadastra um novo item. Retorna 1 em sucesso, 0 se lotado. */
// =====================================================================================================================================================================================================================================================================================

int cadastrar_item(item inventario[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("Inventario cheio! Limite de %d itens.\n", MAX_ITENS);
        return 0;
    }

    item *novo = &inventario[*total];  /* aponta para a próxima posição */

    printf("Nome do item: ");
    fgets(novo->nome, TAM_NOME, stdin);
    limpar_newline(novo->nome);

    printf("Tipo (arma / municao / cura): ");
    fgets(novo->tipo, TAM_TIPO, stdin);
    limpar_newline(novo->tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->quantidade);
    getchar();  /* consome o '\n' que scanf deixa no buffer */

    (*total)++;
    printf("Item cadastrado! (%d/%d)\n", *total, MAX_ITENS);
    return 1;
}

// =====================================================================================================================================================================================================================================================================================
/* Exibe todos os itens cadastrados */
// ====================================================================================================================================================================================================================================================================================

void listar_itens(item inventario[], int total) {
    printf("\n=== Inventario (%d item(ns)) ===\n", total);
    for (int i = 0; i < total; i++) {
        printf("[%d] %-28s | %-18s | qtd: %d\n",
               i + 1,
               inventario[i].nome,
               inventario[i].tipo,
               inventario[i].quantidade);
    }
}

// =====================================================================================================================================================================================================================================================================================
// Busca sequencial 
// =====================================================================================================================================================================================================================================================================================

/*
 * Percorre o array linearmente comparando cada nome com a chave.
 * Retorna o índice do item encontrado, ou -1 se não existir.
 * Complexidade: O(n) — busca sequencial por definição.
 */
int busca_sequencial(const item inventario[], int total, const char *nome_chave) {
    for (int i = 0; i < total; i++) {
        if (strcmp(inventario[i].nome, nome_chave) == 0) {
            return i;  /* índice encontrado */
        }
    }
    return -1;  /* sentinela: item não existe */
}

// =====================================================================================================================================================================================================================================================================================
// Função para remover um item do inventário
// =====================================================================================================================================================================================================================================================================================

/*
 * Remove o item pelo nome, deslocando os elementos subsequentes
 * uma posição à esquerda (shift left) para manter a lista compacta.
 * Reutiliza busca_sequencial — sem duplicação de lógica.
 * Retorna 1 em sucesso, 0 se o item não for encontrado.
 */
int remover_item(item inventario[], int *total, const char *nome_item) {
    int idx = busca_sequencial(inventario, *total, nome_item);

    if (idx == -1) {
        printf("Item \"%s\" nao encontrado. Nenhum dado alterado.\n", nome_item);
        return 0;
    }

    /* Shift left: sobrescreve o item removido com os sucessores */
    for (int i = idx; i < *total - 1; i++) {
        inventario[i] = inventario[i + 1];
    }

    (*total)--;  /* decrementa o contador APÓS o shift */
    printf("Item \"%s\" removido. Itens restantes: %d/%d\n",
           nome_item, *total, MAX_ITENS);
    return 1;
}


// =====================================================================================================================================================================================================================================================================================
// Função para buscar um item do inventário
// =====================================================================================================================================================================================================================================================================================

/*
 * Busca um item pelo nome usando busca sequencial.
 * Exibe o item encontrado ou uma mensagem de erro.
 */
void buscar_item(const item inventario[], int total) {
    char nome_chave[TAM_NOME];

    printf("Nome do item a buscar: ");
    fgets(nome_chave, TAM_NOME, stdin);
    limpar_newline(nome_chave);

    int idx = busca_sequencial(inventario, total, nome_chave);

    if (idx == -1) {
        printf("Item \"%s\" nao encontrado no inventario.\n", nome_chave);
    } else {
        printf("Item encontrado:\n");
        printf("Nome: %s\n", inventario[idx].nome);
        printf("Tipo: %s\n", inventario[idx].tipo);
        printf("Quantidade: %d\n", inventario[idx].quantidade);
    }
}


int main(void){
    item inventario[MAX_ITENS];
    int  total = 0;
    int  opcao;
    char nome_alvo[TAM_NOME];

    do {
        printf("\n=== MOCHILA DO JOGADOR ===\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Buscar item\n");
        printf("4 - Listar itens\n");
        printf("0 - Sair\n> ");
        scanf("%d", &opcao);
        getchar();  /* limpa o '\n' residual do scanf */

        switch (opcao) {
            case 1:
                cadastrar_item(inventario, &total);
                listar_itens(inventario, total);   /* listagem automática */
                break;

            case 2:
                printf("Nome do item a remover: ");
                fgets(nome_alvo, TAM_NOME, stdin);
                limpar_newline(nome_alvo);
                remover_item(inventario, &total, nome_alvo);
                listar_itens(inventario, total);   /* listagem automática */
                break;

            case 3:
                buscar_item(inventario, total);
                break;  /* busca exibe o item, sem re-listar tudo */

            case 4:
                listar_itens(inventario, total);
                break;

            case 0:
                printf("Encerrando jogo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
