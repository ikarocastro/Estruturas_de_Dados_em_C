#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Biblioteca nessecária para usar a função (strcpy,strcmp)

// Definições de constantes para o comprimento máximo que cada texto pode ter
#define MAX_STR_LEN 50 // Define o tamanho máximo para as strings (nome do item e categoria)

// PART 1: Lista estática (VETOR DE STRINGS) 
// Uma lista estática é uma estrutura de dados com tamanho fixo
// implementada usando um vetor (ou array)
// Toda memória necessária é alocada de uma só vez, quando a variável é declarada 

// Defini uma constante para o numero máximo de itens que nossa lista pode conter 
#define TAM_MAX 10 // Define o tamanho máximo de itens na lista estática

// Estrutura que representa a lista estática

typedef struct {
    char dados[TAM_MAX][MAX_STR_LEN]; // Matriz: 10 linhas (itens) e 50 colunas (caracteres por item)
    int quantidade; // Este é nosso contador de controle. Ele informa quantos itens estão realmente armazenados na lista. Ele é incrementado cada vez que um novo item é adicionado e decrementado quando um item é removido. Ele é essencial para evitar acessar posições vazias ou fora do limite do vetor, garantindo a integridade dos dados e o funcionamento correto da lista.
} ListaEstatica;

// Funções da Lista Estática

// Esta função prepara a lista para ser usada
// Ela simplismente define o contador quantidade como 0 zero, indicando que a lista está vazia
// Recebemos um ponteiro (* Lista) para modificar a variável original passada para função
void inicializarListaEstatica(ListaEstatica *lista);

// Esta função adiciona um novo item à lista
void inserirListaEstatica(ListaEstatica *lista, const char* texto);
// Esta função remove um item da lista, se ele existir
void removerListaEstatica(ListaEstatica *lista, const char* texto);
// Esta função verifica se um item existe na lista, retornando 1 (verdadeiro) ou 0 (falso)
void listarListaEstatica(const ListaEstatica *lista);

// =====================================================================================================================================================================================================================================================================================
// PART 2: Lista Encadeada (DE STRINGS)
// Uma lista encadeada é uma estrutura de dados de tamanho dinâmico
// Ela é composta por "Nós" separados na memória
// Onde cada Nó contém um dado e um ponteiro que "aponta" para o próximo Nó da lista
// =====================================================================================================================================================================================================================================================================================


// Estrutura Nó (cada elemento da lista)
// -char* dado: Este é um ponteiro. Ele não armazena o texto em si, mas sim o endereço
// de memória onde o texto está guardado
// Isso é muito flexivel, pois cada texto possui um tamanho diferente, e alocamos apenas a memória necessária para cada um.
// -struct No *proximo: Este é o ponteiro que cria a ligação. Ele armazena o endereço do próximo Nó na lista.
// O ultimo Nó da lista terá seu ponteiro apontado para NULL.

typedef struct No {
    char* dado; // Ponteiro para o texto do item
    struct No *proximo; // Ponteiro para o próximo Nó na lista
} No;

typedef No *ListaEncadeada; // Definimos ListaEncadeada como um ponteiro para No, facilitando a manipulação da lista

// Funções da Lista Encadeada

// Uma lista encadeada vazia é representada por um ponteiro de cabeça que aponta para NULL
// Esta função simplesmente atribui NULL ao ponteiro que representa nossa lista


// Esta função adiciona um novo item à lista
void inserirListaEncadeada(ListaEncadeada *lista, const char* texto);
// Esta função remove um item da lista, se ele existir
void removerListaEncadeada(ListaEncadeada *lista, const char* texto);
// Esta função verifica se um item existe na lista, retornando 1 (verdadeiro) ou 0 (falso)
void listarListaEncadeada(const ListaEncadeada *lista);
// Função para liberar a memória alocada pela lista encadeada
void liberarListaEncadeada(ListaEncadeada *lista); 

// =====================================================================================================================================================================================================================================================================================
// Função Principal Main e Menus 
// =====================================================================================================================================================================================================================================================================================

void menuListaEstatica();
void menuListaEncadeada();

int main() {
    int opcao;
        do{
          printf("\n--- MANIPULACAO DE LISTAS (TEXTO) ---\n");
            printf("1. Lista Estatica \n");
            printf("2. Lista Encadeada \n");
            printf("0. Sair do Programa\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    menuListaEstatica();
                    break;
                case 2:
                    menuListaEncadeada();
                    break;
                case 0:
                    printf("Saindo do programa...\n");
                    break;
                default:
                    printf("Opcao invalida. Tente novamente.\n");
            }  
        } while (opcao != 0);
        
        return 0;
}

// =====================================================================================================================================================================================================================================================================================
// IMPLEMTENTAÇÃO DAS FUNÇÕES - LISTA ESTÁTICA
// =====================================================================================================================================================================================================================================================================================

void inicializarListaEstatica(ListaEstatica *lista){
    lista->quantidade = 0; // Define a quantidade de itens como 0, indicando que a lista está vazia
}

void inserirListaEstatica(ListaEstatica *lista, const char* texto){
    // Primeiro ele verifica se lista->quantidade já atingiu o limete TAM_MAX
    // Se sim, a lista está cheia e a função retorna.
    if (lista->quantidade == TAM_MAX) {
        printf("Erro: Lista cheia. Nao e possivel inserir mais itens.\n");
        return; // Sai da função se a lista estiver cheia
    }
        // Copia o texto para a posição correta na matriz de dados
        // A função strcpy é usada para copiar a string do texto para a posição da matriz correspondente ao contador quantidade
        // O contador quantidade indica quantos itens já estão na lista, então ele aponta para a próxima posição disponível
        strcpy(lista->dados[lista->quantidade], texto);
        // Usamos uma função de para manipulção de dados a biblioteca (strcpy)  para copiar o texto para a posição correta na matriz de dados da lista. O contador quantidade é usado para determinar onde o novo item deve ser inserido, garantindo que os itens sejam armazenados de forma contígua e organizada.
        lista->quantidade++; // Incrementa o contador de quantidade após adicionar o item
        printf("Item '%s' inserido com sucesso!\n", texto);
 }

    // A função removerListaEstatica é responsável por remover um item específico da lista, se ele existir. Ela segue os seguintes passos:
    // 1. Procura o item na lista usando um loop for. Ele compara cada
    // item da lista com o texto fornecido usando a função strcmp, que retorna 0 se as strings forem iguais. Se encontrar o item, ele armazena a posição em uma variável pos e sai do loop.
    // 2. Se o item não for encontrado (pos continua -1), a função
    // exibe uma mensagem de erro e retorna, saindo da função.
    // 3. Se o item for encontrado, a função usa outro loop for para deslocar os itens seguintes para a esquerda, preenchendo o espaço deixado pelo item removido. Ele copia cada item seguinte para a posição atual usando strcpy.
    // 4. Após o loop, o contador de quantidade é decrementado para refletir
    // a remoção do item, e uma mensagem de sucesso é exibida.

void removerListaEstatica(ListaEstatica *lista, const char* texto){
    int i, pos = -1;
    // Primeiro ele procura o item na lista usando um loop for
    for (i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->dados[i], texto) == 0) { // strcmp compara as strings e retorna 0 se forem iguais
            pos = i; // Se encontrar o item, armazena a posição em pos
            break; // Sai do loop após encontrar o item
        }
    }
    // tratamento de erro: Se o loop continuar e pos continuar -1, o item não foi encontrado.
    if (pos == -1) { // Se pos ainda for -1, significa que o item não foi encontrado
        printf("Erro: Texto '%s' nao encontrado na lista.\n", texto);
        return; // Sai da função se o item não for encontrado
    }

    // Se o item for encontrado, o próximo passo é remover o item da lista
    // Para isso, ele usa outro loop for para deslocar os itens seguintes para a esquerda, preenchendo o espaço deixado pelo item removido
    for (i = pos; i < lista->quantidade - 1; i++) {
        strcpy(lista->dados[i], lista->dados[i + 1]); // Copia o próximo item para a posição atual
    }

    // Atualização do contador: finalmente, quantidade e decrementado para refletir que a lista tem um item a menos.
    lista->quantidade--; // Decrementa o contador de quantidade após remover o item
    printf("Item '%s' removido com sucesso!\n", texto);

}

void listarListaEstatica(const ListaEstatica *lista){
    if(lista->quantidade == 0){
        printf("A lista esta vazia.\n");
        return; // Sai da função se a lista estiver vazia
    }
    printf("Intens da lista Estatica: [");
    for (int i = 0; i < lista->quantidade; i++){
        printf("\"%s\" ", lista->dados[i]);
     }
    printf("]\n");
}
    
// =====================================================================================================================================================================================================================================================================================
// IMPLEMTENTAÇÃO DAS FUNÇÕES - LISTA ENCADEADA
// =====================================================================================================================================================================================================================================================================================

// Uma lista encadeada vazia é representada por um ponteiro de cabeça que aponta para NULL
// Essa função simplesmente atribui NULL ao ponteiro que representa nossa lista
void incializarListaEncadeada(ListaEncadeada *lista){
    *lista = NULL; // Atribui NULL ao ponteiro que representa a lista, indicando que ela está vazia
}

void inserirListaEncadeada(ListaEncadeada *lista, const char* texto){
    // 1. Alocar memória para o NOVO NÓ
    // Alocação do Nó: malloc(sizeof(No)) pede ao sistema operacional memória suficiente para um Nó
    // Novo Nó agora aponta para essa memória
    No* novoNo = (No*) malloc(sizeof(No));

    if (novoNo == NULL) { // Verificação de alocação: Se malloc retornar NULL, significa que a alocação falhou
        printf("Erro: Falha na alocacao de memoria.\n");
        return; // Sai da função se a alocação falhar
    }

    // 2. Alocar memória para STRING DENTRO DO NÓ
    // strlen(texto) + 1 para incluir o caractere nulo '\0' no final
    // Alocação da string: malloc(strlen(texto)+1) aloca memória para o texto
    // strlen conta os caracteres, e o +1 é vital para o caractere nulo (\0) que finaliza toda a string em C

    novoNo->dado = (char*) malloc(strlen(texto) + 1);
  
    if (novoNo->dado == NULL) { // Verificação de alocação: Se malloc retornar NULL, significa que a alocação falhou
            printf("Erro: Falha na alocacao de memoria para o texto.\n");
            free(novoNo); // Libera a memória do Nó já alocada para evitar vazamento
            return; // Sai da função se a alocação falhar
        }    


    // 3. Copiar o texto para a memória recém-alocada
    // Cópia do texto: strcpy copia o texto de entrada para a a´rea de memória recém-alocada apontada por novoNo->dado
    strcpy(novoNo->dado, texto);

    // 4. Ligar o novo Nó a çista
    // O ponteirop do novo Nó passa a apontar para o que era o antigo Nó da lista
    novoNo->proximo = *lista; // O ponteiro do novo Nó aponta para o que era o antigo Nó da lista (pode ser NULL se a lista estava vazia)
    // A cabeça da lista (*lista) é atualizada para o que era o antigo primeiro Nó da lista
    *lista = novoNo; // A cabeça da lista é atualizada para apontar para o novo Nó, tornando-o o primeiro elemento da lista

    printf("Texto \"%s\" inserido com sucesso!\n", texto);

    }

    void removerListaEncadeada(ListaEncadeada *lista, const char* texto){
        No *atual = *lista; // Ponteiro para percorrer a lista, começando pela cabeça
        No *anterior = NULL; // Ponteiro para manter o Nó anterior durante a busca

        // 1. Procurar o item na lista usando um loop while
        while (atual != NULL && strcmp(atual->dado, texto) != 0) { // Enquanto não chegar ao final da lista
            anterior = atual; // Atualiza o ponteiro anterior para o Nó atual
            atual = atual->proximo; // Move para o próximo Nó na lista
        }

        if (atual == NULL) { // Se atual for NULL, o item não foi encontrado
            printf("Erro: Texto \"%s\" nao encontrado na lista.\n", texto);
            return; // Sai da função se o item não for encontrado
        }

        // Se o Nó a ser removido for o primeiro (anterior == NULL), a cabeça da lista (*lista) passa a ser o segundo Nó (atual->proximo)
        // Se estiver no meio/fim, o ponteiro proximo do Nó anterior "Pula" o atual e aponta para atual->proximo
        if (anterior == NULL) { // O Nó a ser removido é o primeiro da lista
            *lista = atual->proximo; // A cabeça da lista passa a ser o segundo Nó
        } else { // O Nó a ser removido está no meio ou no fim da lista
            anterior->proximo = atual->proximo; // O ponteiro do Nó anterior "pula" o atual e aponta para o próximo Nó
        }

        // liberação de Memória (MUITO IMPORTANTE): Para evitar vazamento de memória (memory leak), é essencial liberar a memória alocada para o Nó removido e para a string dentro do Nó
        // Primeiro, free(atual->dado): libera a memória que foi usada para guardar o texto
        // Depois, free(atual): libera a memória do Nó em si

        free(atual->dado); // Libera a memória alocada para o texto
        free(atual); // Libera a memória alocada para o Nó
        printf("Texto \"%s\" removido com sucesso!\n", texto);
    
    }


    void listarListaEncadeada(const ListaEncadeada *lista){
        No *temp = *lista; // Ponteiro para percorrer a lista, começando pela cabeça
        if (temp == NULL) { // Se a cabeça da lista for NULL, a lista está vazia
            printf("A lista esta vazia.\n");
            return; // Sai da função se a lista estiver vazia
        }
        printf("Itens da Lista Encadeada: [");
        while (temp != NULL) { // Enquanto não chegar ao final da lista
            printf("\"%s\" ", temp->dado); // Imprime o texto do Nó atual
            temp = temp->proximo; // Move para o próximo Nó na lista
        }
        printf("]\n");
    }

    // Função para liberar toda a memória da lista encadeada no final
    // Ela percorre todos os Nós da lista, um por um, e aplica a mesma lógica de liberação dupla (free(dado))
    // E depois free(no) para cada um deles, garantindo que nenhuma memória alocada seja deixada para trás quando o programa terminar ou quando a lista não for mais necessária.
    void liberarListaEncadeada(ListaEncadeada *lista) {
        No *atual = *lista; // Ponteiro para percorrer a lista, começando pela cabeça
        No *proximo; // Ponteiro para armazenar o próximo Nó durante a liberação
        while (atual != NULL) { // Enquanto não chegar ao final da lista
            proximo = atual->proximo; // Armazena o próximo Nó antes de liberar o atual
            free(atual->dado); // Libera a memória alocada para o texto do Nó atual
            free(atual); // Libera a memória alocada para o Nó atual
            atual = proximo; // Move para o próximo Nó na lista
        }
        *lista = NULL; // Após liberar toda a lista, define a cabeça como NULL para indicar que a lista está vazia
    }

// =====================================================================================================================================================================================================================================================================================
// MENUS
// =====================================================================================================================================================================================================================================================================================

void menuListaEstatica(){
    ListaEstatica lista;
    inicializarListaEstatica(&lista);
    int opcao;
    char texto[MAX_STR_LEN];

    do {
        printf("\n--- MENU LISTA ESTATICA ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("0. Voltar ao menu anterior\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer do Enter

        switch (opcao) {
            case 1:
                printf("Digite o texto para inserir: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = 0; // Remove quebra de linha
                inserirListaEstatica(&lista, texto);
                break;
            case 2:
                printf("Digite o texto para remover: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = 0; // Remove quebra de linha
                removerListaEstatica(&lista, texto);
                break;
            case 3:
                listarListaEstatica(&lista);
                break;
            case 0:
                printf("Voltando ao menu anterior...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

void menuListaEncadeada(){
    ListaEncadeada lista = NULL;
    int opcao;
    char texto[MAX_STR_LEN];

    do {
        printf("\n--- MENU LISTA ENCADEADA ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("0. Voltar ao menu anterior\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer do Enter

        switch (opcao) {
            case 1:
                printf("Digite o texto para inserir: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = 0; // Remove quebra de linha
                inserirListaEncadeada(&lista, texto);
                break;
            case 2:
                printf("Digite o texto para remover: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = 0; // Remove quebra de linha
                removerListaEncadeada(&lista, texto);
                break;
            case 3:
                listarListaEncadeada(&lista);
                break;
            case 0:
                printf("Voltando ao menu anterior...\n");
                liberarListaEncadeada(&lista);
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}
