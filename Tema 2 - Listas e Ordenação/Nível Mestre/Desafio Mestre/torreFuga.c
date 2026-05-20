/*
 * Sistema de Priorização e Montagem da Torre de Fuga
 * Bibliotecas necessárias conforme especificação
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ========================================================
 * STRUCT
 * ======================================================== */

typedef struct {
    char nome[30];
    char tipo[20];
    int  prioridade;
} Componente;

/* ========================================================
 * VARIÁVEL GLOBAL: contagem de comparações
 * ======================================================== */
int totalComparacoes = 0;

/* ========================================================
 * FUNÇÃO: mostrarComponentes
 * Exibe o vetor formatado com nome, tipo e prioridade
 * ======================================================== */
void mostrarComponentes(Componente vetor[], int tamanho) {
    printf("\n%-30s %-20s %s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%-30s %-20s %d\n",
               vetor[i].nome,
               vetor[i].tipo,
               vetor[i].prioridade);
    }
    printf("------------------------------------------------------------\n");
}

/* ========================================================
 * FUNÇÃO: bubbleSortNome
 * Ordena por nome (string) usando Bubble Sort
 * Conta o número de comparações realizadas
 * ======================================================== */
void bubbleSortNome(Componente vetor[], int tamanho) {
    totalComparacoes = 0;
    Componente temp;

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - 1 - i; j++) {
            totalComparacoes++;
            /* Compara os nomes dos componentes adjacentes */
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                /* Troca os componentes de posição */
                temp          = vetor[j];
                vetor[j]      = vetor[j + 1];
                vetor[j + 1]  = temp;
            }
        }
    }
}

/* ========================================================
 * FUNÇÃO: insertionSortTipo
 * Ordena por tipo (string) usando Insertion Sort
 * Conta o número de comparações realizadas
 * ======================================================== */
void insertionSortTipo(Componente vetor[], int tamanho) {
    totalComparacoes = 0;
    Componente chave;

    for (int i = 1; i < tamanho; i++) {
        chave = vetor[i];
        int j = i - 1;

        /* Desloca elementos maiores que a chave para frente */
        while (j >= 0) {
            totalComparacoes++;
            if (strcmp(vetor[j].tipo, chave.tipo) > 0) {
                vetor[j + 1] = vetor[j];
                j--;
            } else {
                break;
            }
        }
        vetor[j + 1] = chave;
    }
}

/* ========================================================
 * FUNÇÃO: selectionSortPrioridade
 * Ordena por prioridade (int) usando Selection Sort
 * Conta o número de comparações realizadas
 * ======================================================== */
void selectionSortPrioridade(Componente vetor[], int tamanho) {
    totalComparacoes = 0;
    Componente temp;

    for (int i = 0; i < tamanho - 1; i++) {
        int indiceMenor = i;

        /* Encontra o elemento de menor prioridade no restante */
        for (int j = i + 1; j < tamanho; j++) {
            totalComparacoes++;
            if (vetor[j].prioridade < vetor[indiceMenor].prioridade) {
                indiceMenor = j;
            }
        }

        /* Troca o menor encontrado com o elemento atual */
        if (indiceMenor != i) {
            temp              = vetor[i];
            vetor[i]          = vetor[indiceMenor];
            vetor[indiceMenor] = temp;
        }
    }
}

/* ========================================================
 * FUNÇÃO: buscaBinariaPorNome
 * Realiza busca binária por nome no vetor já ordenado por nome
 * Retorna o índice do componente encontrado, ou -1 se não encontrar
 * Aplicável apenas após bubbleSortNome
 * ======================================================== */
int buscaBinariaPorNome(Componente vetor[], int tamanho, char nome[]) {
    int inicio = 0;
    int fim    = tamanho - 1;
    int comparacoesBusca = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBusca++;
        int cmp = strcmp(vetor[meio].nome, nome);

        if (cmp == 0) {
            /* Componente encontrado */
            printf("\n[BUSCA BINARIA] Comparacoes realizadas: %d\n", comparacoesBusca);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\n[BUSCA BINARIA] Comparacoes realizadas: %d\n", comparacoesBusca);
    return -1; /* Não encontrado */
}

/* ========================================================
 * FUNÇÃO: medirTempo
 * Mede o tempo de execução de um algoritmo de ordenação
 * Recebe ponteiro para a função do algoritmo
 * ======================================================== */
void medirTempo(void (*algoritmo)(Componente[], int), Componente vetor[], int tamanho) {
    clock_t inicio = clock();
    algoritmo(vetor, tamanho);
    clock_t fim = clock();

    double tempoMs = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
    printf("[DESEMPENHO] Tempo de execucao: %.4f ms\n", tempoMs);
    printf("[DESEMPENHO] Numero de comparacoes: %d\n", totalComparacoes);
}

/* ========================================================
 * FUNÇÃO: removerNewline
 * Remove o '\n' deixado pelo fgets no final da string
 * ======================================================== */
void removerNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/* ========================================================
 * FUNÇÃO PRINCIPAL
 * ======================================================== */
int main() {
    Componente componentes[20];
    int total = 0;
    int ordenadoPorNome = 0; /* Controla se busca binária está disponível */
    int opcao;

    printf("=============================================\n");
    printf("   TORRE DE FUGA - SISTEMA DE COMPONENTES   \n");
    printf("=============================================\n");

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Bubble Sort (ordenar por nome)\n");
        printf("3. Insertion Sort (ordenar por tipo)\n");
        printf("4. Selection Sort (ordenar por prioridade)\n");
        printf("5. Busca binaria por nome\n");
        printf("6. Exibir componentes\n");
        printf("0. Sair\n");
        printf("==========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); /* Limpa o '\n' do buffer após scanf */

        switch (opcao) {

            /* ------------------------------------------
             * OPÇÃO 1: Cadastro de componentes
             * ------------------------------------------ */
            case 1: {
                int qtd;
                printf("\nQuantos componentes deseja cadastrar (max 20)? ");
                scanf("%d", &qtd);
                getchar();

                if (qtd < 1 || qtd > 20) {
                    printf("Quantidade invalida. Informe entre 1 e 20.\n");
                    break;
                }

                total = qtd;
                ordenadoPorNome = 0;

                for (int i = 0; i < total; i++) {
                    printf("\n--- Componente %d ---\n", i + 1);

                    printf("Nome (max 29 caracteres): ");
                    fgets(componentes[i].nome, 30, stdin);
                    removerNewline(componentes[i].nome);

                    printf("Tipo (ex: controle, suporte, propulsao): ");
                    fgets(componentes[i].tipo, 20, stdin);
                    removerNewline(componentes[i].tipo);

                    printf("Prioridade (1 a 10): ");
                    scanf("%d", &componentes[i].prioridade);
                    getchar();

                    /* Garante que a prioridade esteja no intervalo válido */
                    if (componentes[i].prioridade < 1 || componentes[i].prioridade > 10) {
                        printf("Prioridade fora do intervalo. Ajustada para 1.\n");
                        componentes[i].prioridade = 1;
                    }
                }

                printf("\nCadastro concluido!\n");
                mostrarComponentes(componentes, total);
                break;
            }

            /* ------------------------------------------
             * OPÇÃO 2: Bubble Sort por nome
             * ------------------------------------------ */
            case 2: {
                if (total == 0) {
                    printf("\nNenhum componente cadastrado.\n");
                    break;
                }
                printf("\n[BUBBLE SORT] Ordenando por nome...\n");
                medirTempo(bubbleSortNome, componentes, total);
                ordenadoPorNome = 1;
                mostrarComponentes(componentes, total);
                break;
            }

            /* ------------------------------------------
             * OPÇÃO 3: Insertion Sort por tipo
             * ------------------------------------------ */
            case 3: {
                if (total == 0) {
                    printf("\nNenhum componente cadastrado.\n");
                    break;
                }
                printf("\n[INSERTION SORT] Ordenando por tipo...\n");
                medirTempo(insertionSortTipo, componentes, total);
                ordenadoPorNome = 0; /* Ordem por nome desfeita */
                mostrarComponentes(componentes, total);
                break;
            }

            /* ------------------------------------------
             * OPÇÃO 4: Selection Sort por prioridade
             * ------------------------------------------ */
            case 4: {
                if (total == 0) {
                    printf("\nNenhum componente cadastrado.\n");
                    break;
                }
                printf("\n[SELECTION SORT] Ordenando por prioridade...\n");
                medirTempo(selectionSortPrioridade, componentes, total);
                ordenadoPorNome = 0; /* Ordem por nome desfeita */
                mostrarComponentes(componentes, total);
                break;
            }

            /* ------------------------------------------
             * OPÇÃO 5: Busca binária por nome
             * Disponível apenas após Bubble Sort por nome
             * ------------------------------------------ */
            case 5: {
                if (total == 0) {
                    printf("\nNenhum componente cadastrado.\n");
                    break;
                }
                if (!ordenadoPorNome) {
                    printf("\nA busca binaria requer ordenacao por nome (opcao 2) primeiro.\n");
                    break;
                }

                char nomeBusca[30];
                printf("\nDigite o nome do componente-chave: ");
                fgets(nomeBusca, 30, stdin);
                removerNewline(nomeBusca);

                int indice = buscaBinariaPorNome(componentes, total, nomeBusca);

                if (indice != -1) {
                    printf("\n[MONTAGEM FINAL] Componente-chave encontrado!\n");
                    printf("  Nome      : %s\n", componentes[indice].nome);
                    printf("  Tipo      : %s\n", componentes[indice].tipo);
                    printf("  Prioridade: %d\n", componentes[indice].prioridade);
                    printf("\n>>> TORRE DE FUGA ATIVADA! BOA SORTE! <<<\n");
                } else {
                    printf("\n[MONTAGEM FINAL] Componente-chave nao encontrado.\n");
                    printf(">>> TORRE NAO PODE SER ATIVADA. <<<\n");
                }
                break;
            }

            /* ------------------------------------------
             * OPÇÃO 6: Exibir componentes
             * ------------------------------------------ */
            case 6: {
                if (total == 0) {
                    printf("\nNenhum componente cadastrado.\n");
                    break;
                }
                mostrarComponentes(componentes, total);
                break;
            }

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}