#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Biblioteca necessária para usar a função (strcpy,strcmp)

#define MAX_STR_LEN 30 // Define o tamanho máximo para as strings (nome do item e categoria)
#define MAX_ITENS 10 // Define o número máximo de itens que a lista pode conter
#define TAM_NOME 30 // Define o tamanho máximo para o nome do item
#define TAM_TIPO 20 // Define o tamanho máximo para o tipo do item

// =====================================================================================================================================================================================================================================================================================
// PART 1: Lista estática (VETOR DE STRINGS)
// =====================================================================================================================================================================================================================================================================================

typedef struct{
    char nome[TAM_NOME];  /* ex: "Espada de Ferro"  */
    char tipo[TAM_TIPO];    /* ex: "Arma Branca" ou "Arma de Fogo" ou "Kit Medico" ou "Granada" */
    int quantidade; /* ex: 3 */
} item;

typedef struct {
    item dados[MAX_ITENS]; // Array de itens
    int quantidade; // Contador de controle para o número de itens na lista
} ListaEstatica;

// =====================================================================================================================================================================================================================================================================================
// PART 2: Lista Encadeada (DE STRINGS)
// =====================================================================================================================================================================================================================================================================================

typedef struct No {
    item dado; // Estrutura do item
    struct No *proximo; // Ponteiro para o próximo Nó na lista
} No;

// =====================================================================================================================================================================================================================================================================================
// PART 3: Funções de Remoção de Itens
// =====================================================================================================================================================================================================================================================================================

// Função para remover item da Lista Estática pelo nome
int removerItemListaEstatica(ListaEstatica *lista, char *nomeItem) {
    if (lista == NULL || lista->quantidade == 0) {
        printf("❌ Erro: Lista vazia ou inválida!\n");
        return 0;
    }
    
    for (int i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->dados[i].nome, nomeItem) == 0) {
            printf("✓ Item '%s' removido da mochila!\n", nomeItem);
            
            // Desloca todos os elementos após o item encontrado uma posição para trás
            for (int j = i; j < lista->quantidade - 1; j++) {
                strcpy(lista->dados[j].nome, lista->dados[j + 1].nome);
                strcpy(lista->dados[j].tipo, lista->dados[j + 1].tipo);
                lista->dados[j].quantidade = lista->dados[j + 1].quantidade;
            }
            
            lista->quantidade--;
            return 1; // Sucesso
        }
    }
    
    printf("❌ Item '%s' não encontrado na mochila!\n", nomeItem);
    return 0; // Item não encontrado
}

// Função para remover item da Lista Encadeada pelo nome
int removerItemListaEncadeada(No **inicio, char *nomeItem) {
    if (*inicio == NULL) {
        printf("❌ Erro: Lista vazia!\n");
        return 0;
    }
    
    No *atual = *inicio;
    No *anterior = NULL;
    
    while (atual != NULL) {
        if (strcmp(atual->dado.nome, nomeItem) == 0) {
            printf("✓ Item '%s' removido da mochila!\n", nomeItem);
            
            if (anterior == NULL) {
                // Remove o primeiro nó
                *inicio = atual->proximo;
            } else {
                // Remove um nó do meio ou do final
                anterior->proximo = atual->proximo;
            }
            
            free(atual);
            return 1; // Sucesso
        }
        
        anterior = atual;
        atual = atual->proximo;
    }
    
    printf("❌ Item '%s' não encontrado na mochila!\n", nomeItem);
    return 0; // Item não encontrado
}

