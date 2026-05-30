#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>

/* =========================================================
   Estrutura que representa um cômodo da mansão.
   Cada sala possui um nome e dois ponteiros para as salas
   vizinhas: uma à esquerda e outra à direita.
   ========================================================= */
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/* ---------------------------------------------------------
   criarSala()
   Aloca dinamicamente uma nova sala com o nome fornecido
   e inicializa seus ponteiros filhos como NULL (sem saídas).
   Retorna um ponteiro para a sala criada.
   --------------------------------------------------------- */
Sala *criarSala(const char *nome) {
    Sala *nova = (Sala *)malloc(sizeof(Sala));

    if (nova == NULL) {
        std::cerr << "Erro: memoria insuficiente para criar a sala '" << nome << "'.\n";
        exit(1);
    }

    strncpy(nova->nome, nome, sizeof(nova->nome) - 1);
    nova->nome[sizeof(nova->nome) - 1] = '\0';
    nova->esquerda = NULL;
    nova->direita  = NULL;

    return nova;
}

/* ---------------------------------------------------------
   explorarSalas()
   Permite a navegação interativa do jogador pela árvore.
   A cada sala visitada, exibe o nome do cômodo e, caso
   existam saídas, solicita ao jogador que escolha entre
   ir para a esquerda (e), para a direita (d) ou sair (s).
   A exploração termina quando o jogador alcança um nó-folha
   (sala sem saídas) ou decide sair.
   --------------------------------------------------------- */
void explorarSalas(Sala *atual) {
    if (atual == NULL) {
        std::cout << "\n[ Caminho sem saida — voce voltou para o ponto anterior. ]\n";
        return;
    }

    std::cout << "\n==================================\n";
    std::cout << "  Voce esta em: " << atual->nome << "\n";
    std::cout << "==================================\n";

    /* Verifica se é um nó-folha (sem saídas) */
    if (atual->esquerda == NULL && atual->direita == NULL) {
        std::cout << "  >> Nao ha mais saidas. Fim do caminho!\n";
        return;
    }

    /* Exibe as saídas disponíveis */
    std::cout << "  Saidas disponiveis:\n";
    if (atual->esquerda != NULL)
        std::cout << "    [e] Esquerda " << atual->esquerda->nome << "\n";
    if (atual->direita  != NULL)
        std::cout << "    [d] Direita " << atual->direita->nome << "\n";
    std::cout << "    [s] Sair do jogo\n";

    char opcao;
    std::cout << "\n  Sua escolha: ";
    std::cin >> opcao;

    if (opcao == 'e' || opcao == 'E') {
        if (atual->esquerda != NULL)
            explorarSalas(atual->esquerda);
        else
            std::cout << "  >> Nao ha saida a esquerda daqui.\n";

    } else if (opcao == 'd' || opcao == 'D') {
        if (atual->direita != NULL)
            explorarSalas(atual->direita);
        else
            std::cout << "  >> Nao ha saida a direita daqui.\n";

    } else if (opcao == 's' || opcao == 'S') {
        std::cout << "\n  Voce decidiu sair da mansao. Ate a proxima, detetive!\n";

    } else {
        std::cout << "  >> Opcao invalida. Tente novamente.\n";
        explorarSalas(atual); /* repete a mesma sala */
    }
}

/* ---------------------------------------------------------
   liberarMapa()
   Percorre a árvore em pós-ordem e libera a memória de
   cada sala alocada dinamicamente com malloc().
   --------------------------------------------------------- */
void liberarMapa(Sala *raiz) {
    if (raiz == NULL) return;
    liberarMapa(raiz->esquerda);
    liberarMapa(raiz->direita);
    free(raiz);
}

/* ---------------------------------------------------------
   main()
   Monta o mapa completo da mansão conectando as salas em
   uma árvore binária e inicia a exploração a partir do
   Hall de Entrada (raiz da árvore).

   Estrutura da mansão:
                     Hall de Entrada
                    /               \
           Sala de Estar           Biblioteca
            /        \              /       \
        Cozinha     Jardim      Escritório  Sala de Troféus
        /    \                              /
    Adega  Varanda                      Porão Secreto
   --------------------------------------------------------- */
int main(void) {
    /* --- Criação das salas --- */
    Sala *hall          = criarSala("Hall de Entrada");
    Sala *salaEstar     = criarSala("Sala de Estar");
    Sala *biblioteca    = criarSala("Biblioteca");
    Sala *cozinha       = criarSala("Cozinha");
    Sala *jardim        = criarSala("Jardim");
    Sala *escritorio    = criarSala("Escritorio");
    Sala *salaTrofeus   = criarSala("Sala de Trofeus");
    Sala *adega         = criarSala("Adega");
    Sala *varanda       = criarSala("Varanda");
    Sala *poraoSecreto  = criarSala("Porao Secreto");

    /* --- Conexão dos nós (montagem da árvore) --- */
    hall->esquerda       = salaEstar;
    hall->direita        = biblioteca;

    salaEstar->esquerda  = cozinha;
    salaEstar->direita   = jardim;

    biblioteca->esquerda = escritorio;
    biblioteca->direita  = salaTrofeus;

    cozinha->esquerda    = adega;
    cozinha->direita     = varanda;

    salaTrofeus->esquerda = poraoSecreto;

    /* --- Abertura do jogo --- */
    std::cout << "================================================\n";
    std::cout << "   DETECTIVE QUEST — Exploracao da Mansao\n";
    std::cout << "================================================\n";
    std::cout << "  Você e um detetive investigando um crime\n";
    std::cout << "  ocorrido em uma mansao misteriosa.\n";
    std::cout << "  Explore os comodos para encontrar pistas!\n";
    std::cout << "  (Use 'e' para esquerda, 'd' para direita,\n";
    std::cout << "   's' para sair)\n";
    std::cout << "================================================\n";

    /* --- Início da exploração --- */
    explorarSalas(hall);

    /* --- Encerramento --- */
    std::cout << "\n================================================\n";
    std::cout << "  Obrigado por jogar Detective Quest!\n";
    std::cout << "================================================\n";

    /* --- Libera toda a memória alocada --- */
    liberarMapa(hall);

    return 0;
}