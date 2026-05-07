#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  // necessário para srand(time(NULL))

#define MAX_TERRITORIOS 5 // Definindo o número máximo de territórios
#define MAX_STRING 30 // Definindo o tamanho máximo para strings
#define MAX_DADOS_ATACANTE 3
#define MAX_DADOS_DEFENSOR 2

// Definição da struct para representar um território
struct territorio {
    char nome[MAX_STRING]; // Usando a constante em vez de literal
    char cor[MAX_STRING];  // Usando a constante em vez de literal
    int tropas;
};

//função de limpar o buff de entrada para evitar problemas com fgets e scanf
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função auxiliar para ordenar dados em ordem DECRESCENTE (bubble sort simples)
void ordenarDados(int* dados, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (dados[j] < dados[j + 1]) {
                int temp = dados[j];
                dados[j] = dados[j + 1];
                dados[j + 1] = temp;
            }
        }
    }
}

// Rola 'n' dados e armazena os resultados no array
void rolarDados(int* dados, int n) {
    for (int i = 0; i < n; i++) {
        dados[i] = (rand() % 6) + 1; // Gera número entre 1 e 6
    }
}

// ----------------------------------- Cadastrar Territorio -----------------------------------
void cadastrarTerritorio(struct territorio* mapa, int* totalTerritorios) {
    if (*totalTerritorios < MAX_TERRITORIOS) {
        printf("\n=== CADASTRO DE NOVO TERRITORIO ===\n");

        printf("Digite o nome do territorio: ");
        fgets(mapa[*totalTerritorios].nome, MAX_STRING, stdin); // para buscar o nome do território usando 'fgets' para permitir espaços
        mapa[*totalTerritorios].nome[strcspn(mapa[*totalTerritorios].nome, "\n")] = '\0'; // Remove o \n

        printf("Digite a cor do territorio: ");
        fgets(mapa[*totalTerritorios].cor, MAX_STRING, stdin);
        mapa[*totalTerritorios].cor[strcspn(mapa[*totalTerritorios].cor, "\n")] = '\0'; // Remove o \n

        printf("Digite a quantidade de tropas no territorio: ");
        scanf("%d", &mapa[*totalTerritorios].tropas);
        limparBufferEntrada(); // Limpa o \n deixado pelo scanf

        (*totalTerritorios)++; // Incrementa o contador de territórios cadastrados
        printf("Territorio cadastrado com sucesso!\n");
    } else {
        printf("Limite de territorios atingido!\n");
    }
}

// ----------------------------------- Listar Territorios -----------------------------------
void listarTerritorios(struct territorio* mapa, int totalTerritorios) {
    if (totalTerritorios == 0) {
        printf("\nNenhum territorio cadastrado!\n");
        return;
    }
    printf("\n=== LISTA DE TERRITORIOS ===\n");
    for (int i = 0; i < totalTerritorios; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("-----------------------------\n");
    }
}

// ----------------------------------- Atacar Territorio -----------------------------------
void atacar(struct territorio* atacante, struct territorio* defensor) {
    printf("\n=== BATALHA: %s vs %s ===\n", atacante->nome, defensor->nome);

    // --- Validações antes do ataque ---
    if (atacante->tropas < 2) {
        printf("O atacante precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }
    if (defensor->tropas < 1) {
        printf("O defensor nao possui tropas!\n");
        return;
    }

    // Calcula quantos dados cada lado vai rolar
    // Atacante: máximo 3 dados, mas nunca mais que (tropas - 1)
    // O "-1" é porque ele precisa deixar ao menos 1 tropa no território
    int numDadosAtacante = atacante->tropas - 1;
    if (numDadosAtacante > MAX_DADOS_ATACANTE)
        numDadosAtacante = MAX_DADOS_ATACANTE;

    // Defensor: máximo 2 dados, limitado pelas tropas disponíveis
    int numDadosDefensor = defensor->tropas;
    if (numDadosDefensor > MAX_DADOS_DEFENSOR)
        numDadosDefensor = MAX_DADOS_DEFENSOR;

    // Arrays para armazenar os resultados dos dados
    int dadosAtacante[MAX_DADOS_ATACANTE];
    int dadosDefensor[MAX_DADOS_DEFENSOR];

    // Rola e ordena os dados de ambos
    rolarDados(dadosAtacante, numDadosAtacante);
    rolarDados(dadosDefensor, numDadosDefensor);
    ordenarDados(dadosAtacante, numDadosAtacante);
    ordenarDados(dadosDefensor, numDadosDefensor);

    // Exibe os dados rolados
    printf("\nDados do Atacante (%s): ", atacante->nome);
    for (int i = 0; i < numDadosAtacante; i++)
        printf("[%d] ", dadosAtacante[i]);

    printf("\nDados do Defensor (%s): ", defensor->nome);
    for (int i = 0; i < numDadosDefensor; i++)
        printf("[%d] ", dadosDefensor[i]);
    printf("\n");

    // --- Resolução das batalhas ---
    // Compara par a par (o menor número de dados entre os dois define quantas batalhas ocorrem)
    int numComparacoes = numDadosAtacante < numDadosDefensor
                            ? numDadosAtacante
                            : numDadosDefensor;

    int baixasAtacante = 0;
    int baixasDefensor = 0;

    printf("\n--- Resolucao ---\n");
    for (int i = 0; i < numComparacoes; i++) {
        printf("Atacante [%d] vs Defensor [%d] -> ", dadosAtacante[i], dadosDefensor[i]);

        // Empate ou vitória do defensor: atacante perde tropa
        if (dadosAtacante[i] > dadosDefensor[i]) {
            printf("Atacante vence! Defensor perde 1 tropa.\n");
            baixasDefensor++;
        } else {
            // Empate favorece defensor — atacante perde
            printf("Defensor vence! Atacante perde 1 tropa.\n");
            baixasAtacante++;
        }
    }

    // Aplica as baixas
    atacante->tropas -= baixasAtacante;
    defensor->tropas -= baixasDefensor;

    // --- Resultado final ---
    printf("\n--- Resultado ---\n");
    printf("Baixas do Atacante: %d | Tropas restantes: %d\n", baixasAtacante, atacante->tropas);
    printf("Baixas do Defensor: %d | Tropas restantes: %d\n", baixasDefensor, defensor->tropas);

    if (defensor->tropas <= 0) {
        defensor->tropas = 0; // Garante que não fique negativo

        // REQUISITO 1: Transferência de domínio — ocorre quando o defensor chega a 0 tropas
        int tropasMover = numDadosAtacante; // Move o mesmo número de tropas que dados rolados (entre 1 e 3)
        atacante->tropas -= tropasMover;    // Retira tropas do território de origem
        defensor->tropas = tropasMover;     // Ocupa o território conquistado com essas tropas

        strcpy(defensor->cor, atacante->cor); // Muda o dono: copia a cor do atacante para o defensor

        printf("\n*** %s CONQUISTOU %s! ***\n", atacante->nome, defensor->nome);
        printf("    %d tropas avancam para ocupar o territorio.\n", tropasMover);
    } else {
        printf("\n%s resistiu ao ataque!\n", defensor->nome);
    }

    // REQUISITO 2: Exibição dos dados atualizados de ambos os territórios após o ataque
    printf("\n--- Estado atual dos territorios ---\n");
    printf("%-20s | Cor: %-10s | Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("%-20s | Cor: %-10s | Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);
    printf("------------------------------------\n");
}

// ----------------------------------- Selecionar e Atacar -----------------------------------
void selecionarEAtacar(struct territorio* mapa, int totalTerritorios) {
    if (totalTerritorios < 2) {
        printf("\nVoce precisa de pelo menos 2 territorios para atacar!\n");
        return;
    }

    // Lista territórios com aviso de elegibilidade — melhora a interface
    printf("\n=== SELECIONE OS TERRITORIOS ===\n");
    for (int i = 0; i < totalTerritorios; i++) {
        if (mapa[i].tropas >= 2)
            printf("[%d] %-15s | Cor: %-10s | Tropas: %d  <- pode atacar\n",
                i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        else
            printf("[%d] %-15s | Cor: %-10s | Tropas: %d  (tropas insuficientes para atacar)\n",
                i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    int idxAtacante, idxDefensor;

    printf("\nNumero do territorio ATACANTE: ");
    scanf("%d", &idxAtacante);
    limparBufferEntrada();
    idxAtacante--; // Converte para índice 0-based

    printf("Numero do territorio DEFENSOR: ");
    scanf("%d", &idxDefensor);
    limparBufferEntrada();
    idxDefensor--;

    // Valida os índices escolhidos
    if (idxAtacante < 0 || idxAtacante >= totalTerritorios ||
        idxDefensor < 0 || idxDefensor >= totalTerritorios) {
        printf("Territorio invalido!\n");
    } else if (idxAtacante == idxDefensor) {
        printf("Um territorio nao pode atacar a si mesmo!\n");
    } else {
        atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
    }
}

// ----------------------------------- Liberar Memória -----------------------------------
void liberarMapa(struct territorio** mapa) {
    free(*mapa);  // Liberação da memória alocada — corrige o memory leak
    *mapa = NULL; // Boa prática: evita ponteiro solto (dangling pointer)
}

// ============================================================================= Main =====================================================================================================

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios (só uma vez, no início)

    // ALOCÇÃO DINÂMICA DE MEMÓRIA
    struct territorio* mapa = malloc(MAX_TERRITORIOS * sizeof(struct territorio)); // Array para armazenar os territórios

    // Validação do malloc — boa prática essencial
    if (mapa == NULL) {
        printf("Erro: falha ao alocar memoria.\n");
        return 1;
    }

    int totalTerritorios = 0; // Contador de territórios cadastrados
    int opcao;

    do {
        // Exibe o menu de opções para o usuário
        printf("===============================\n");
        printf("\n=== SISTEMA DE MAPA DE RISCO ===\n");
        printf("===============================\n");
        printf("1. Cadastrar Territorio\n");
        printf("2. Listar Territorios\n");
        printf("3. Atacar Territorio\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");

        // Lê a opção escolhida pelo usuário
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o \n deixado pelo scanf

        // Processamento da opção escolhida
        switch (opcao) {
            case 1:
                cadastrarTerritorio(mapa, &totalTerritorios);
                break;

            case 2:
                listarTerritorios(mapa, totalTerritorios);
                break;

            case 3:
                selecionarEAtacar(mapa, totalTerritorios);
                break;

            case 4: // Sair
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    liberarMapa(&mapa); // Chama a função dedicada para liberar a memória

    return 0;
}