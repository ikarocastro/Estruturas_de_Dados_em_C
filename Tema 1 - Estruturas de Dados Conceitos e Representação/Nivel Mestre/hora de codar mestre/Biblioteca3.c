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

// =============================================================
// OBJETIVOS DESTA PARTE 3:
// Modularizar o código com funções especializadas, aplicando boas práticas .
// - Passagem por valor (para exibição ) e por referência (para modificação).
// - Frunções para cada funcionalidade pricipal do sistema (cadastro, listagem, empréstimo, etc).
// - A função main() se torna um "orquestrador", chamando as outras. 
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
    int disponivel; // 1 para disponível, 0 para não, para sabermos se o livro está emprestado ou não
};

// Nova struct para armazenar informações do empréstimo
struct Emprestimo {
    int indiceLivro; // Índice do livro emprestado
    char nomeUsuario[TAM_STRING]; // Nome do usuário que fez o empréstimo
};

// Protótipos de funções para modularizar o código (serão implementadas posteriormente)
// Declarar Funções aqui permite que a 'main()' as chame antes de suas definições
void limparBufferEntrada(); // Função para limpar o buffer de entrada
void exibirMenu(); // Função para exibir o menu de opções
void cadastrarLivro(struct Livro* biblioteca, int* totalLivros); // Função para cadastrar um novo livro
void listarLivros(struct Livro* biblioteca, int totalLivros); // Função para listar
void realizarEmprestimo(struct Livro* biblioteca, struct Emprestimo* emprestimos, int* totalEmprestimos, int totalLivros); // Função para realizar um empréstimo
void listarEmprestimos(const struct Livro* biblioteca, const struct Emprestimo* emprestimos, int totalEmprestimos); // Função para listar os empréstimos realizados
void liberarMemoria(struct Livro* biblioteca, struct Emprestimo* emprestimos); // Função para liberar a memória alocada


//------ Função Principal (Main) ---------
// Agora main() é muito mais limpa. ela aloca memória, controla o menu.
// e delega as tarefas para  as funções especializadas, mantendo a organização e clareza do código.
int main() {
   
    struct Livro* biblioteca = (struct Livro*) calloc(MAX_LIVROS, sizeof(struct Livro)); // Aloca memória para o array de livros
    struct Emprestimo* emprestimos = (struct Emprestimo*) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));
 
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro falha ao alocar memória\n");
        return 1; // Encerra o programa com código de erro
    }

    int totalLivros = 0; // Contador para o número total de livros cadastrados
    int totalEmprestimos = 0; // Contador para o número total de empréstimos registrados
    int opcao; // Variável para armazenar a opção escolhida pelo usuário

    do{
        exibirMenu(); // Função para exibir o menu de opções para o usuário
        scanf("%d", &opcao); // Lê a opção escolhida pelo usuário
        limparBufferEntrada(); // Limpa o buffer de entrada para evitar problemas com fgets

        switch (opcao)
        {
        case 1: // Cadastro Livro
            // Passamos o endereço de 'totalLivros' (&)p ara que a função possa MODIFICAR o valor do contador de livros cadastrados
            cadastrarLivro(biblioteca, &totalLivros); // Chama a função para cadastrar um novo livro
            break;

        case 2: // Passamos apenas o valor de 'totalLivros' pois a função só precisa ler.
            listarLivros(biblioteca, totalLivros); // Chama a função para listar os livros cadastrados
            break;

        case 3: // Realizar Empréstimo
            realizarEmprestimo(biblioteca, emprestimos, &totalEmprestimos, totalLivros); // Chama a função para realizar um empréstimo
            break;
        
        case 4: // Listar Empréstimos
            listarEmprestimos(biblioteca, emprestimos, totalEmprestimos); //
            break;

        case 0: // Sair do programa
            printf("Encerrando o programa. Obrigado por usar o sistema de biblioteca!\n");
            break;

            default:
            printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
            printf("\nPressione Enter para continuar...");
            getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu
            break;



    }

} while (opcao != 0); // O loop continua até o usuário escolher sair (opção 0)

    liberarMemoria(biblioteca, emprestimos); // Chama a função para liberar a memória alocada

    return 0; // Encerra o programa com código de sucesso
}

    void limparBufferEntrada() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
    }

    void exibirMenu() {
        printf("===============================\n");
        printf("\n=== SISTEMA DE BIBLIOTECA PARTE 3 (MESTRE) ===\n");
        printf("===============================\n");
        printf("1. Cadastrar novo Livro\n");
        printf("2. Listar Todos os Livros\n");
        printf("3. Realizar Emprestimo\n");
        printf("4. Listar Emprestimos \n");
        printf("0. Sair\n");
        printf("--------------------------------\n");
        printf("Escolha uma opcao: ");
    }
    
    void cadastrarLivro(struct Livro* biblioteca, int* totalLivros) {
        printf("\n=== CADASTRO DE NOVO LIVRO ===\n");
        
        if (*totalLivros < MAX_LIVROS) {
            // O acesso aos campos é igual ao do array estático, mas agora usando o ponteiro
           
            printf("Digite o nome do livro: ");
            int indice = *totalLivros; // usa o valor apontado pelo ponteiro para o indice.
            fgets(biblioteca[indice].nome, TAM_STRING, stdin);
            // Demais leituras são iguais ao da Parte 1

            printf("Digite o autor do livro: ");
            fgets(biblioteca[indice].autor, TAM_STRING, stdin);
            
            printf("Digite a editora do livro: ");
            fgets(biblioteca[indice].editora, TAM_STRING, stdin);

            biblioteca[indice].nome[strcspn(biblioteca[indice].nome, "\n")] = '\0'; // Remove o \n
            biblioteca[indice].autor[strcspn(biblioteca[indice].autor, "\n")] = '\0'; // Remove o \n
            biblioteca[indice].editora[strcspn(biblioteca[indice].editora, "\n")] = '\0'; // Remove o \n

            printf("Digite a edicao do livro: ");
            scanf("%d", &biblioteca[indice].edicao);
            limparBufferEntrada(); // Limpa o \n deixado pelo scanf

            biblioteca[indice].disponivel = 1; // Marca o livro como disponível
            (*totalLivros)++; // Incrementa o contador de livros cadastrados
            printf("Livro cadastrado com sucesso!\n");
       
        } else {
            printf("Biblioteca cheia. Não e possivel cadastrar mais livros.\n");
        }
        printf("\nPressione Enter para continuar...");
        getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu
    }


    void listarLivros(struct Livro* biblioteca, int totalLivros) {
        printf("\n=== LISTA DE LIVROS CADASTRADOS ===\n");
        if (totalLivros == 0) {
            printf("Nenhum livro cadastrado ainda.\n");
        } else {
            for (int i = 0; i < totalLivros; i++) {
                printf("Livro %d:\n", i + 1);
                printf("Nome: %s\n", biblioteca[i].nome);
                printf("Autor: %s\n", biblioteca[i].autor);
                printf("Editora: %s\n", biblioteca[i].editora);
                printf("Edicao: %d\n", biblioteca[i].edicao);
                printf("Status: %s\n", biblioteca[i].disponivel ? "Disponivel" : "Indisponivel");
                printf("-----------------------------\n");
            }
            printf("-----------------------------\n");
        }
        printf("\nPressione Enter para continuar...");
        getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu
    }

    void realizarEmprestimo(struct Livro* biblioteca, struct Emprestimo* emprestimos, int* totalEmprestimos, int totalLivros) {
        printf("\n=== REALIZAR EMPRESTIMO ===\n");

        if(*totalEmprestimos >= MAX_EMPRESTIMOS) {
            printf("Limite de emprestimos atingido!\n");
        } else {
            printf("Livros disponiveis para emprestimo:\n");
            int livrosDisponiveis = 0;
            for (int i = 0; i < totalLivros; i++) {
                if (biblioteca[i].disponivel) {
                    printf("%d - %s\n", i + 1, biblioteca[i].nome);
                    livrosDisponiveis++;
                }
            }   
        
            if (livrosDisponiveis == 0){
                printf("Nenhum livro disponivel para emprestimo no momento.\n");
            }else{
                printf("Digite o numero do livro que deseja emprestar: ");
                int numLivro;
                scanf("%d", &numLivro);
                limparBufferEntrada(); // Limpa o buffer de entrada

                    int indice = numLivro - 1; // Converte para índice do array (0 a N-1)

                    // Validação da escolha do usuario
                    if(indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel) {
                        printf("Digite o nome do usuario que esta emprestando o livro: ");
                        fgets(emprestimos[*totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                        emprestimos[*totalEmprestimos].nomeUsuario[strcspn(emprestimos[*totalEmprestimos].nomeUsuario, "\n")] = '\0'; // Remove o \n depois do fgets

                        // Registra o empréstimo
                        emprestimos[*totalEmprestimos].indiceLivro = indice;
                        
                        // Atualiza o status do livro para não disponível
                        biblioteca[indice].disponivel = 0;

                        (*totalEmprestimos)++; // Incrementa o contador de empréstimos registrados
                        printf("Emprestimo realizado com sucesso!\n");
                    } else {
                        printf("Numero de livro inválido ou livro não disponível para emprestimo.\n");
            }
        }
        printf("\nPressione Enter para continuar...");
        getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu
    }
 }

 void listarEmprestimos(const struct Livro* biblioteca, const struct Emprestimo* emprestimos, int totalEmprestimos) {
            printf("\n=== LISTA DE EMPRESTIMOS REALIZADOS ===\n");
            if (totalEmprestimos == 0) {
                printf("Nenhum emprestimo registrado ainda.\n");

            } else {
                for (int i = 0; i < totalEmprestimos; i++) {
                    int indiceLivro = emprestimos[i].indiceLivro;
                    printf("------------------------------\n");
                    printf("Emprestimo %d:\n", i + 1);
                    printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
                    printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                }
                printf("-----------------------------\n");

            }
            printf("\nPressione Enter para continuar...");
            getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu
    }
 

    void liberarMemoria(struct Livro* biblioteca, struct Emprestimo* emprestimos) {
        free(biblioteca); // Libera a memória alocada para os livros
        free(emprestimos); // Libera a memória alocada para os empréstimos
        printf("Memoria liberada com sucesso. Encerrando o programa.\n");
    }

