#include <stdio.h>
#include <stdlib.h> // Para usar exit(), caso a lista não esteja ordenada para a busca binária
#include <string.h> // Para usar strcmp para comparar strings

// DECLARAÇÕES DAS FUNÇÕES (PROTOTIPOS)

// Busca Sequencial Iterativa
int buscaSequencialIterativa(const char* jogador[], int tamanho, const char* item);
int buscaSequencialRecursiva(const char* jogador[], int tamanho, const char* item);
int buscaSequencialRecursiva_aux(const char* jogador[], int tamanho, const char* item, int indice);

// Busca Binária Iterativa
int buscaBinariaIterativa(const char* jogador[], int tamanho, const char* item);
int buscaBinariaRecursiva(const char* jogador[], int tamanho, const char* item);
int buscaBinariaRecursiva_aux(const char* jogador[], const char* item, int inicio, int fim);

// Função auxiliar para imprimir os resultados de forma organizada
void imprimirResultado(const char* nomeDaBusca, const char* item, int resultado);

// FUNÇÃO PRINCIPAL MAIN    

int main() {
    // IMPORTANTE: Para a busca binária funcionar corretamente, a lista deve estar ordenada alfebeticamente
    // Lista de jogadores (ordenada para a busca binária)
    const char* jogadores[] = {
        "Alice",
        "Bob",
        "Charlie",
        "David",
        "Kaio",
        "Frank",
        "Grace",
        "Heidi",
        "Ivan",
        "Judy"
    };
    // Calcula o número de itens na lista
    // sizeof(listaDeCompras) -> tamanho total do array em bytes
    // sizeof(jogadores[0]) -> tamanho de um elemento (um ponteiro char*) em bytes
    // A divisão nos dá o número de elementos
    // Estou entregando ao programa o tamanho da mionha lista 
    int tamanho = sizeof(jogadores) / sizeof(jogadores[0]);

    // Jogador a ser buscado
    const char* jogadorExistente = "grace";
    const char* jogadorInexistente = "Lele";
   
    printf("\n--- DEMOSTRACAO DE ALGORITIMOS DE BUSCA EM TEXTO ---\n");
    printf("Lista Utilizada: [Alice, Bob, Charlie, David, Kaio, Frank, Grace, Heidi, Ivan, Judy]");
    printf("=======================================================================================\n\n");


    // ---- Testando a Busca Seuquencial ----
    
    printf("--- 1. BUSCA SEQUENCIAL ---\n");
    // A: Versão Iterativa
    int res1 = buscaSequencialIterativa(jogadores, tamanho, jogadorExistente);
    imprimirResultado("Sequencial Interativo", jogadorExistente, res1);

    int res2 = buscaSequencialIterativa(jogadores, tamanho, jogadorInexistente);
    imprimirResultado("Sequencial Iterativo", jogadorInexistente, res2);
    printf("\n");

    // B: VERSÃO RECURSIVA
    int res3 = buscaSequencialRecursiva(jogadores, tamanho, jogadorExistente);
    imprimirResultado("Sequencial Recursiva", jogadorExistente, res3);

    int res4 = buscaBinariaRecursiva(jogadores, tamanho, jogadorExistente);
    imprimirResultado("Sequencial Recursiva", jogadorInexistente, res4);
    printf("=======================================================================================\n\n");


    // Testando Busca Binária

    printf("--- 2. BUSCA BINARIA (REQUER LISTA ORDENADA) ---");
    // A: VERSÃO ITERATIVA
    int res5 = buscaBinariaIterativa(jogadores, tamanho, jogadorExistente);
    imprimirResultado("Sequencial Binario", jogadorExistente, res5);

    int res6 = buscaBinariaIterativa(jogadores, tamanho, jogadorInexistente);
    imprimirResultado("Sequencial Binario", jogadorInexistente, res6);

    // B: VERSÃO RECURSIVA
    int res7 = buscaBinariaRecursiva(jogadores, tamanho, jogadorExistente);
    imprimirResultado("Sequencial Recursiva", jogadorExistente, res7);

    int res8 = buscaBinariaRecursiva(jogadores, tamanho, jogadorInexistente);
    imprimirResultado("Sequencial Recursiva", jogadorInexistente, res8);
    printf("=========================================================================================\n\n");

    return 0;   // Indica que o programa terminou com sucesso!

}

// IMPLEMENTAÇÃO DAS FUNÇÕES

// ========================================================================================================================================================================================
// BUSCA SEQUENCIAL
// ========================================================================================================================================================================================
// Percorre a lista elemento por elemento, do incio ao fim,
// até encontrar o item ou chegar ao fim da lista
// Não requer que a lista esteje ordenada
// ========================================================================================================================================================================================

int buscaSequencialIterativa(const char* jogadores[], int tamanho, const char* item){
    // Um laço "for" percorre cada índice da lista, de 0 até '-1'
        for(int i = 0; i < tamanho; i++){
            //strcmp(str1,str2) compara duas strings
            // Retorna 0 se elas forem identicas
            if (strcmp(jogadores[i], item) == 0){
                // Se as strings forem iguais, encontramos o item
                return 1; // retorna o índice atual
            }
        } 
        // Se o laço terminar e não tivermos retornado nada,
        // Significa que o item não está na lista.
        return -1;
}

int buscaSequencialRecursiva(const char* jogador[], int tamanho, const char* item){
    // A lógica recursiva real está na função auxiliar
    // Começamos a buscar a partir do indice 0
    return buscaSequencialRecursiva_aux(jogador, tamanho, item, 0);
}

int buscaSequencialRecursiva_aux(const char* jogador[], int tamanho, const char* item, int indice){
    // CASO BASE 1: FALHA (Fim da Lista)
    // Se o indice atual for igual ou maior que o tamanho da lista,
    // Significa que já percorremos todos os elementos com sucesso.

    if (indice >= tamanho)
    {
        return -1; // Item não encontrado
    }
    
    //CASO BASE 2: SUCESSO 
    // Compara o item na posição "índice" atual com o item procurado 
    if (strcmp(jogador[indice], item) == 0){
        return indice; // Item encontrado! Retorne o índice
    }
 
    // PASSO RECURSIVO
    // se não for nenhum dos casos base, o item ainda pode estar no resto da lista
    // chamamos a função novamente, mas agora para o proximo indice (indice + 1)
    return buscaSequencialRecursiva_aux(jogador, tamanho, item, indice + 1);
}

// =======================================================================================================================================================================================================
// 2. BUSCA BINÁRIA
// =======================================================================================================================================================================================================
// Algortimo "dividir para conquistar"
// A cada passo, ele olha para o elemento do meio da lista (ou sub-lista)
// Se o item do meio for o procurado a busca termina
// Se o item procurado for menor, ele descarta a metade direita e busca na esquerda
// Se for maior, descarta a metade esquerda e busca na direita
// Requer que a lista esteja ORDENADA
//=======================================================================================================================================================================================================

int buscaBinariaIterativa(const char* jogador[], int tamanho, const char* item){
    int inicio = 0;
    int fim = tamanho - 1;
    int meio;

    while (inicio <= fim) {
        // Calcula o Indice do meio
        // Usar inicio + (fim - inicio) / 2 evita overflow para listas muito grandes
        meio = inicio + (fim - inicio) / 2;
        
        int comparacao = strcmp(jogador[meio], item);

        if (comparacao == 0){ // encontrou
            return meio;
        }
        else if (comparacao > 0 ){
            // O item do meio vem depois do jogador procurado
            // Portanto o item só pode estar na metade esquerda
            fim = meio - 1;
        } else { // comparacao < 0
            // O item do meio vem antes do item procurado
            // Portanto, o item só pode estar na metade direita
            inicio = meio + 1;
        }
    }
    
    return -1;
}

int buscaBinariaRecursiva(const char* jogador[], int tamanho, const char* item){
    // Inicia a busca recursiva em toda a lista, do indice 0 até o "tamanho -1".
    return buscaBinariaRecursiva_aux(jogador, item, 0, tamanho - 1);
}

int buscaBinariaRecursiva_aux(const char* jogador[], const char* item, int inicio, int fim){
    // CASO BASE 1: FALHA (Espaço de busca inválido)
    // Se o 'inicio' ultrapassar o 'fim', a sub-lista é vazia, o item não está aqui.
    if (inicio > fim)
    {
        return -1;
    }
    
    // PASSO RECURSIVO E CASO BASE DE SUCESSO
    int meio = inicio + (fim - inicio) /2;
    int comparacao = strcmp(jogador[meio], item);

    if (comparacao == 0)
    {
        // CASO BASE 2: SUCESSO
        return meio; // Encontramos o item
    } else if (comparacao > 0){
        // O item está na metade esquerda
        // Chamamos a função novamente, mas com um novo fim
        return buscaBinariaRecursiva_aux(jogador, item, inicio, meio - 1);
    } else {
        // O item está na metade direita
        return buscaBinariaRecursiva_aux(jogador, item, meio + 1, fim);
    }
}

// ==========================================================================================================================================================================================================================
// FUNÇÃO AUXILIAR DE IMPRESSÃO
// ==========================================================================================================================================================================================================================

void imprimirResultado(const char* nomeDaBusca, const char* item, int resultado) {
    printf("[%s] Buscando por \"%s\"... \n", nomeDaBusca, item);

    if (resultado != -1) {
        printf(" -> Resultado: Item encontrado no índice %d.\n", resultado);
    } else {
        printf(" -> Resultado: Item nao encontrado na lista.\n");
    }
}