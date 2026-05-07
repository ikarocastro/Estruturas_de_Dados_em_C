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
    int disponivel; // 1 para disponível, 0 para não, para sabermos se o livro está emprestado ou não
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
    // Estamos agora usando ponteiros em vez de arrays estáticos

    // Usamos calloc para o array de livros. calloc(num_elementos, tamanho_do_elemento)
    // Vantagem: inicializa toda a memória alocada com zero, o que é útil para garantir que os campos de disponibilidade dos livros comecem como 0 (não disponíveis).
    biblioteca = (struct Livro*)calloc(MAX_LIVROS, sizeof(struct Livro));

    // Usamos malloc para o array de empréstimos. malloc(tamanho_total_em_bytes)
    // Vantagem: é mais simples e direta quando não precisamos da inicialização automática de memória, como no caso dos empréstimos, onde os dados serão preenchidos posteriormente.
    emprestimos = (struct Emprestimo*)malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    // VERIFICAÇÃO: Verificar se a alocação de memória foi bem-sucedida
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro ao alocar memoria. Encerrando o programa.\n");
        return 1; // Encerra o programa com código de erro
    }

    int totalLivros = 0; // Contador para o número total de livros cadastrados
    int totalEmprestimos = 0; // Contador para o número total de empréstimos registrados
    int opcao; // Variável para armazenar a opção escolhida pelo usuário

    
    do{
        //Exibe o menu de opções para o usuário
        printf("===============================\n");
        printf("\n=== SISTEMA DE BIBLIOTECA PARTE 2 ===\n");
        printf("===============================\n");
        printf("1. Cadastrar novo Livro\n");
        printf("2. Listar Todos os Livros\n");
        printf("3. Realizar Emprestimo\n");
        printf("4. Listar Emprestimos \n");
        printf("0. Sair\n");
        printf("--------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o buffer de entrada para evitar problemas com fgets

        switch (opcao)
        {
        case 1: // Cadastro Livro
            /* code */
            printf("\n=== CADASTRO DE NOVO LIVRO ===\n");
            if (totalLivros < MAX_LIVROS) {
                // O acesso aos campos é igual ao do array estático, mas agora usando o ponteiro
                printf("Digite o nome do livro: ");
                fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin); // para buscar o nome do livro, autor e editora usando 'fgets' para permitir espaços
                
                // Demais leituras são iguais ao da Parte 1
                printf("Digite o autor do livro: ");
                fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);
                
                printf("Digite a editora do livro: ");
                fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0'; // Remove o \n
                biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0'; // Remove o \n
                biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0'; // Remove o \n

                printf("Digite a edicao do livro: ");
                scanf("%d", &biblioteca[totalLivros].edicao);
                limparBufferEntrada(); // Limpa o \n deixado pelo scanf

                biblioteca[totalLivros].disponivel = 1; // Marca o livro como disponível
                totalLivros++; // Incrementa o contador de livros cadastrados
                printf("Livro cadastrado com sucesso!\n");
           
            } else {
                printf("Biblioteca cheia. Não e possivel cadastrar mais livros.\n");
            }
            printf("\nPressione Enter para continuar...");
            getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu
            break;
        
        case 2: // Listagem de Livros
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
                    printf("Disponivel: %s\n", biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
                }
                printf("-----------------------------\n");
            }
                
                printf("\nPressione Enter para continuar...");
                getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu
                break;
            
        case 3: // Realizar Empréstimo
            printf("\n=== REALIZAR EMPRESTIMO ===\n");
           
                    // Verifica se o limite de empréstimos foi atingido
                if(totalEmprestimos >= MAX_EMPRESTIMOS) {
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
                
                    if (livrosDisponiveis = 0){
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
                                fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                                emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = '\0'; // Remove o \n depois do fgets

                                // Registra o empréstimo
                                emprestimos[totalEmprestimos].indiceLivro = indice;
                                
                                // Atualiza o status do livro para não disponível
                                biblioteca[indice].disponivel = 0;

                                totalEmprestimos++; // Incrementa o contador de empréstimos registrados
                                printf("Emprestimo realizado com sucesso!\n");
                            } else {
                                printf("Numero de livro inválido ou livro não disponível para emprestimo.\n");
                    }
                }
            }
            printf("\nPressione Enter para continuar...");
            getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu
            break;

        case 4: // Listar Empréstimos
            printf("\n=== LISTA DE EMPRESTIMOS ===\n");
            if (totalEmprestimos == 0) {
                printf("Nenhum emprestimo realizado.\n");
            } else {
                for (int i = 0; i < totalEmprestimos; i++) {
                    // Usa o indice armazenado no emprestimo para buscar o nome do livro na biblioteca
                    int indiceLivro = emprestimos[i].indiceLivro;
                    printf("-----------------------------\n");
                    printf("Emprestimo %d:\n", i + 1);
                    printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                    printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
                    printf("-----------------------------\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu
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
        }
    } while (opcao != 0); // O loop continua até o usuário escolher sair (opção 0)

    // 4. LIBERAÇÃO DE MEMÓRIA
    // Antes de terminar o programa, é ESSENCIAL liberar a memória alocada que foi alocada dinamicamente para evitar vazamentos de memória.
    free(biblioteca); // Libera a memória alocada para o array de livros
    free(emprestimos); // Libera a memória alocada para o array de
    
    printf("Memoria liberada. Encerrando o programa.\n");
    
    return 0; // Encerra o programa com código de sucesso
}

