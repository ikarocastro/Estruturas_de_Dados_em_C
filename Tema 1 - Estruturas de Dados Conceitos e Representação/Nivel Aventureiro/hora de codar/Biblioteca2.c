// =============================================================
// PRÁTICA: SISTEMA DE BIBLIOTECA - PARTE 1
//
// OBJETIVO DESTA PARTE 1:
// Implementar o cadastro e a listagem de livros usando um array estático.
// Foco em structs, entrada/saída de dados e organização básica.

// =============================================================
//OBJETIVO DESTA PARTE 2:
//adicionar a funcionalidade de emprestomos e introduzir a alocação dinâmica.
// - Os arrays de livros e emprestimos são alocados em malloc/calloc.
// - Nova Struct para empréstimos
// - Liberação de memória com free() ao final do programa
// =============================================================


#include <stdio.h> // Biblioteca padrão para entrada e saída de dados
#include <stdlib.h> // Biblioteca padrão para funções de alocação de memória, controle de processos, conversões e outras utilidades
#include <string.h>// Biblioteca.h - Definição da struct Livro e protótipos de funções para strcspn e outras operações de string

//  ------- Constantes Globais ---------
#define MAX_LIVROS 50 // Capacidade máxima de livros na biblioteca
#define TAM_STRING 100 // Tamanho máximo para strings
#define MAX_EMPRESTIMOS 100 // Capacidade máxima de empréstimos registrados

//------- Definição da (Struct) Livro ---------

     //Vetores do tipo char para armazenar o nome, autor e editora do livro, cada um com um tamanho definido por TAM_STRING.
struct Livro {
    char nome [TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 para disponível, 0 para não
};

// Nova struct para armazenar informações do empréstimo
struct Emprestimo {
    int indiceLivro; // Índice do livro emprestado
    char nomeUsuario[TAM_STRING]; // Nome do usuário que fez o empréstimo
};


//funçAo de limpar o buff de entrada para evitar problemas com fgets e scanf
void limparBufferEntrada() {  
    int c; 
    while ((c = getchar()) != '\n' && c != EOF); 
}

//------ Função Principal (Main) ---------
int main() {
    // 1. ALOCÇÃO DINÂMICA DE MEMÓRIA
    // Agora, em vez de usar um array estático, usamos ponteiros
    struct Livro* biblioteca;
    struct Emprestimo* emprestimos;
    
    // Usamos calloc para o array de livros. calloc(num_elementos, tamanho_do_elemento)
    // Vantagem: inicializa toda a memória alocada com zero, o que é útil para garantir que os campos de disponibilidade dos livros comecem como 0 (não disponíveis).
    biblioteca = (struct Livro*)calloc(MAX_LIVROS, sizeof(struct Livro));

    // Usamos malloc para o array de empréstimos. malloc(tamanho_total_em_bytes)
    // Vantagem: é mais simples e direta quando não precisamos da inicialização automática de memória, como no caso dos empréstimos, onde os dados serão preenchidos posteriormente.
    emprestimos = (struct Emprestimo*)malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    // VERIFICAÇÃO: Verificar se a alocação de memória foi bem-sucedida
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro ao alocar memória. Encerrando o programa.\n");
        return 1; // Encerra o programa com código de erro
    }




}


