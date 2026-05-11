#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define MAX_STRING 30
#define MAX_DADOS_ATACANTE 3
#define MAX_DADOS_DEFENSOR 2
#define TOTAL_MISSOES 5
#define MIN_TERRITORIOS_CONQUISTA 3

// ============================================================
// STRUCTS
// ============================================================

struct territorio {
    char nome[MAX_STRING];
    char cor[MAX_STRING];
    int tropas;
};

struct jogador {
    char nome[MAX_STRING];
    char cor[MAX_STRING];
    char* missao; // missão alocada dinamicamente
};

// ============================================================
// MISSÕES
// ============================================================

char* missoes[TOTAL_MISSOES] = {
    "Conquistar pelo menos 3 territorios seguidos",
    "Eliminar todas as tropas da cor Vermelha",
    "Possuir territorios com mais de 10 tropas no total",
    "Dominar ao menos 3 territorios com a sua cor",
    "Ter um territorio com 5 ou mais tropas"
};

// ============================================================
// FUNÇÕES AUXILIARES
// ============================================================

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ============================================================
// MOSTRAR MAPA
// ============================================================

void mostrarMapa(struct territorio* mapa, int tamanho) {

    printf("============= MAPA DO MUNDO =============\n");

    for (int i = 0; i < tamanho; i++) {

        printf("%d. %-10s (Exercito: %-10s, Tropas: %d)\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }

    printf("=========================================\n\n");
}

// ============================================================
// MOSTRAR MISSÃO
// ============================================================

void mostrarMissao(struct jogador* jogador) {

    printf("--- SUA MISSAO (%s) ---\n", jogador->cor);
    printf("%s\n\n", jogador->missao);
}

// ============================================================
// MENU
// ============================================================

void mostrarMenu() {

    printf("--- MENU DE ACOES ---\n");

    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
}

// ============================================================
// DADOS
// ============================================================

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

void rolarDados(int* dados, int n) {

    for (int i = 0; i < n; i++)
        dados[i] = (rand() % 6) + 1;
}

// ============================================================
// ATRIBUIR MISSÃO
// ============================================================

void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {

    int idx = rand() % totalMissoes;

    strcpy(destino, missoes[idx]);
}

// ============================================================
// VERIFICAR MISSÃO
// ============================================================

int verificarMissao(char* missao,
                    struct territorio* mapa,
                    int tamanho,
                    struct jogador* jogador) {

    // Missão 1
    if (strstr(missao, "3 territorios seguidos") != NULL) {

        int conquistados = 0;

        for (int i = 0; i < tamanho; i++) {

            if (strcmp(mapa[i].cor, jogador->cor) == 0)
                conquistados++;
        }

        return conquistados >= MIN_TERRITORIOS_CONQUISTA;
    }

    // Missão 2
    if (strstr(missao, "cor Vermelha") != NULL) {

        if (strcmp(jogador->cor, "Vermelha") == 0)
            return 0;

        for (int i = 0; i < tamanho; i++) {

            if (strcmp(mapa[i].cor, "Vermelha") == 0 &&
                mapa[i].tropas > 0)
                return 0;
        }

        return 1;
    }

    // Missão 3
    if (strstr(missao, "10 tropas no total") != NULL) {

        int totalTropas = 0;

        for (int i = 0; i < tamanho; i++) {

            if (strcmp(mapa[i].cor, jogador->cor) == 0)
                totalTropas += mapa[i].tropas;
        }

        return totalTropas > 10;
    }

    // Missão 4
    if (strstr(missao, "3 territorios com a sua cor") != NULL) {

        int count = 0;

        for (int i = 0; i < tamanho; i++) {

            if (strcmp(mapa[i].cor, jogador->cor) == 0)
                count++;
        }

        return count >= 3;
    }

    // Missão 5
    if (strstr(missao, "5 ou mais tropas") != NULL) {

        for (int i = 0; i < tamanho; i++) {

            if (strcmp(mapa[i].cor, jogador->cor) == 0 &&
                mapa[i].tropas >= 5)
                return 1;
        }

        return 0;
    }

    return 0;
}

// ============================================================
// COMBATE
// ============================================================
void atacar(struct territorio* atacante, struct territorio* defensor) {
    printf("\n=== BATALHA: %s vs %s ===\n", atacante->nome, defensor->nome);

    if (atacante->tropas < 2) {
        printf("O atacante precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }
    if (defensor->tropas < 1) {
        printf("O defensor nao possui tropas!\n");
        return;
    }

    int numDadosAtacante = atacante->tropas - 1;
    if (numDadosAtacante > MAX_DADOS_ATACANTE) numDadosAtacante = MAX_DADOS_ATACANTE;

    int numDadosDefensor = defensor->tropas;
    if (numDadosDefensor > MAX_DADOS_DEFENSOR) numDadosDefensor = MAX_DADOS_DEFENSOR;

    int dadosAtacante[MAX_DADOS_ATACANTE];
    int dadosDefensor[MAX_DADOS_DEFENSOR];

    rolarDados(dadosAtacante, numDadosAtacante);
    rolarDados(dadosDefensor, numDadosDefensor);
    ordenarDados(dadosAtacante, numDadosAtacante);
    ordenarDados(dadosDefensor, numDadosDefensor);

    printf("\nDados do Atacante (%s): ", atacante->nome);
    for (int i = 0; i < numDadosAtacante; i++) printf("[%d] ", dadosAtacante[i]);

    printf("\nDados do Defensor (%s): ", defensor->nome);
    for (int i = 0; i < numDadosDefensor; i++) printf("[%d] ", dadosDefensor[i]);
    printf("\n");

    int numComparacoes = numDadosAtacante < numDadosDefensor ? numDadosAtacante : numDadosDefensor;
    int baixasAtacante = 0, baixasDefensor = 0;

    printf("\n--- Resolucao ---\n");
    for (int i = 0; i < numComparacoes; i++) {
        printf("Atacante [%d] vs Defensor [%d] -> ", dadosAtacante[i], dadosDefensor[i]);
        if (dadosAtacante[i] > dadosDefensor[i]) {
            printf("Atacante vence! Defensor perde 1 tropa.\n");
            baixasDefensor++;
        } else {
            printf("Defensor vence! Atacante perde 1 tropa.\n");
            baixasAtacante++;
        }
    }

    atacante->tropas -= baixasAtacante;
    defensor->tropas  -= baixasDefensor;

    printf("\n--- Resultado ---\n");
    printf("Baixas do Atacante: %d | Tropas restantes: %d\n", baixasAtacante, atacante->tropas);
    printf("Baixas do Defensor: %d | Tropas restantes: %d\n", baixasDefensor, defensor->tropas);

    if (defensor->tropas <= 0) {
        defensor->tropas = 0;
        int tropasMover = (numDadosAtacante > 1) ? numDadosAtacante - 1 : 1;
        if (tropasMover > atacante->tropas) tropasMover = atacante->tropas;
        atacante->tropas -= tropasMover;
        defensor->tropas  = tropasMover;
        strcpy(defensor->cor, atacante->cor);

        printf("\n*** %s CONQUISTOU %s! ***\n", atacante->nome, defensor->nome);
        printf("    %d tropas avancam para ocupar o territorio.\n", tropasMover);
    } else {
        printf("\n%s resistiu ao ataque!\n", defensor->nome);
    }

    printf("\n--- Estado atual dos territorios ---\n");
    printf("%-20s | Cor: %-10s | Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("%-20s | Cor: %-10s | Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);
    printf("------------------------------------\n");
}

void selecionarEAtacar(struct territorio* mapa, int totalTerritorios) {
    if (totalTerritorios < 2) {
        printf("\nVoce precisa de pelo menos 2 territorios para atacar!\n");
        return;
    }

    printf("============================================================\n");
    printf("          SELECIONE O TERRITORIO ATACANTE              \n");
    printf("============================================================\n");

    printf("Territorios com tropas suficientes para atacar:\n\n");
    for (int i = 0; i < totalTerritorios; i++) {
        if (mapa[i].tropas >= 2)
            printf("  [%d] %-15s | Cor: %-10s | Tropas: %d  <- PODE ATACAR\n",
                   i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    int idxAtacante;
    printf("\nNumero do territorio ATACANTE: ");
    scanf("%d", &idxAtacante); limparBufferEntrada(); 
    idxAtacante--;

    // Validar atacante
    if (idxAtacante < 0 || idxAtacante >= totalTerritorios) {
        printf("\n Territorio invalido!\n");
        return;
    }
    
    if (mapa[idxAtacante].tropas < 2) {
        printf("\n Territorio invalido!\n");
        return;
    }

    // Mostrar atacante selecionado
    printf("\n============================================================\n");
    printf("         TERRITORIO ATACANTE SELECIONADO                \n");
    printf("============================================================\n\n");
    printf("   %s\n", mapa[idxAtacante].nome);
    printf("   Cor: %s\n", mapa[idxAtacante].cor);
    printf("   Tropas: %d\n\n", mapa[idxAtacante].tropas);

    // Mostrar opcoes de defesa
    printf("============================================================\n");
    printf("        SELECIONE O TERRITORIO DEFENSOR                 \n");
    printf("============================================================\n\n");
    printf("Territorios disponiveis para defesa:\n\n");
    
    for (int i = 0; i < totalTerritorios; i++) {
        if (i != idxAtacante) {
            printf("  [%d] %-15s | Cor: %-10s | Tropas: %d \n",
                   i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
    }

    int idxDefensor;
    printf("\nNumero do territorio DEFENSOR: ");
    scanf("%d", &idxDefensor); limparBufferEntrada(); 
    idxDefensor--;

    // Validar defensor
    if (idxDefensor < 0 || idxDefensor >= totalTerritorios) {
        printf("\n Territorio invalido!\n");
        return;
    }
    
    if (idxAtacante == idxDefensor) {
        printf("\n Um territorio nao pode atacar a si mesmo!\n");
        return;
    }

    // Confirmacao visual do ataque
    printf("\n============================================================\n");
    printf("           CONFIRMACAO DE ATAQUE                        \n");
    printf("============================================================\n\n");
    
    printf("   ATACANTE:\n");
    printf("       %s\n", mapa[idxAtacante].nome);
    printf("       Cor: %s\n", mapa[idxAtacante].cor);
    printf("       Tropas: %d\n\n", mapa[idxAtacante].tropas);
    
    printf("      VS\n\n");
    
    printf("  DEFENSOR:\n");
    printf("       %s\n", mapa[idxDefensor].nome);
    printf("       Cor: %s\n", mapa[idxDefensor].cor);
    printf("       Tropas: %d\n\n", mapa[idxDefensor].tropas);

    printf("=====================================================\n\n");

    // Executar ataque
    atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
}

// ============================================================
// MAIN
// ============================================================

int main() {

    srand(time(NULL));

    int opcao;

    // ========================================================
    // MAPA
    // ========================================================

    struct territorio mapa[MAX_TERRITORIOS] = {

        {"America", "Verde", 5},
        {"Europa", "Azul", 2},
        {"Asia", "Vermelha", 2},
        {"Africa", "Amarelo", 4},
        {"Oceania", "Branco", 1}
    };

    // ========================================================
    // JOGADOR
    // ========================================================

    struct jogador jogador1;

    strcpy(jogador1.nome, "Player 1");
    strcpy(jogador1.cor, "Azul");

    // alocação dinâmica da missão
    jogador1.missao = (char*) malloc(100 * sizeof(char));

    if (jogador1.missao == NULL) {

        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    // sorteia missão
    atribuirMissao(jogador1.missao,
                   missoes,
                   TOTAL_MISSOES);

    // ========================================================
    // LOOP DO JOGO
    // ========================================================

    do {

        limparTela();

        mostrarMapa(mapa, MAX_TERRITORIOS);

        mostrarMissao(&jogador1);

        mostrarMenu();

        printf("Escolha sua acao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:

                printf("\nVoce escolheu atacar!\n");

                selecionarEAtacar(mapa, MAX_TERRITORIOS);

                break;

            case 2:

                printf("\nMissao atual:\n%s\n",
                       jogador1.missao);

                break;

            case 0:

                printf("\nSaindo do jogo...\n");

                break;

            default:

                printf("\nOpcao invalida!\n");
        }

        // ========================================================
        // VERIFICAÇÃO AUTOMÁTICA DE VITÓRIA
        // ========================================================

        if (verificarMissao(jogador1.missao,
                            mapa,
                            MAX_TERRITORIOS,
                            &jogador1)) {

            printf("\n====================================\n");
            printf("MISSAO CUMPRIDA!\n");
            printf("VENCEDOR: %s\n", jogador1.nome);
            printf("====================================\n");

            break;
        }

        if(opcao != 0) {

            printf("\nPressione ENTER para continuar...");
            getchar();
            getchar();
        }

    } while(opcao != 0);

    // ========================================================
    // LIBERAR MEMÓRIA
    // ========================================================

    free(jogador1.missao);

    return 0;
}