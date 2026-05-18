#include <stdio.h>
#include <stdlib.h> // Para as funções rand(), srand()
#include <time.h>  // para a função time gerando numeros aleatorios

// Define o tamanho das listas que serão geradas
// Facilita a alteração para testes com mais ou menos elementos 
#define TAMANHO 10

// --- DECLARAÇÃO DAS FUNÇÕES (PROTÓTIPO) ---
// Informa ao compilador sobre a existencia e a "assinatura" das funções
// que serão implementadas mais abaixo

// Funções para gerar os diferentes tipos de listas
void gerarListaOrdenada(int lista[], int n);
void gerarListaInversa(int lista[], int n);
void gerarListaAleatoria(int lista[], int n);

// Funções de ordenação
void bubbleSort(int lista[], int n);
void insertionSort(int lista[], int n);
void selectionSort(int lista[], int n);

// Funções auxiliares
void imprimirLista(const char* titulo, const int lista[], int n);
void copiarLista(int destino[], const int origem[], int n);

// FUNÇÃO PRINCIPAL (MAIN)
// O programa inicia sua execução aqui

int main(){
    // Semeia o gerador de numeros aleatorios com a hora atual
    // Isso garante que a lista aleatoria seja diferente a cada execução do programa
    // Deve ser chamada apenas uma vez
    srand(time(NULL));

    // Declara os três tipos de lista que servirão como nossos casos de teste
    int listaOrdenada[TAMANHO];
    int listaInversa[TAMANHO];
    int listaAleatoria[TAMANHO];

    // Preenche as listas com os padrões desejados
    printf(" -- GERANDO LISTAS DE ENTRADA -- \n");
    gerarListaOrdenada(listaOrdenada, TAMANHO);
    gerarListaInversa(listaInversa, TAMANHO);
    gerarListaAleatoria(listaAleatoria, TAMANHO);
    printf("---------------------------------------\n\n");

    // Declara uma lista temporaria que será usada para receber uma CÓPIA
    // Dos dados antes de cada ordenação. isso é CRUCIAL para garantir que 
    // cada algoritimo receba a mesma lista de entrada original
    int listaTemp[TAMANHO];

    // ======================================================================================================================================================================================================
    // 1. TESTANDO BUBBLE SORT
    // ======================================================================================================================================================================================================

    printf("============== BUBBLE SORT ==============\n");

    // a) Melhor caso: Lista já ordenada
    copiarLista(listaTemp, listaOrdenada, TAMANHO);
    bubbleSort(listaTemp, TAMANHO);
    imprimirLista("Bubble Sort | Melhor caso (Ja ordenada)", listaTemp, TAMANHO);

    // b) Pior Caso: Lista em ordem inversa
    copiarLista(listaTemp, listaInversa, TAMANHO);
    bubbleSort(listaTemp, TAMANHO);
    imprimirLista("Bubble Sort | pior caso (ordem inversa)", listaTemp, TAMANHO);
    
    // c) Caso Médio: Lista aleatória
    copiarLista(listaTemp, listaAleatoria, TAMANHO);
    bubbleSort(listaTemp, TAMANHO);
    imprimirLista("Bubble Sort | Caso Medio (aleatoria)", listaTemp, TAMANHO);
    printf("\n");



    // ============================================================================================================================================================================================================
    // 2. TESTANDO O INSERTION SORT
    // ============================================================================================================================================================================================================
   
    printf("========== 2. INSERTION SORT ============ \n");

    // a) Melhor Caso: Lista já ordenada
    copiarLista(listaTemp, listaOrdenada, TAMANHO);
    insertionSort(listaTemp, TAMANHO);
    imprimirLista("Insertion Sort | Melhor caso (ja ordenada)", listaTemp, TAMANHO);

    // b) Pior Caso: Lista em ordem inversa
    copiarLista(listaTemp, listaInversa, TAMANHO);
    insertionSort(listaTemp, TAMANHO);
    imprimirLista("Insertion Sort | Pior caso (ordem inversa)", listaTemp, TAMANHO);

    // c) Caso Média: Lista aleatória
    copiarLista(listaTemp, listaAleatoria, TAMANHO);
    insertionSort(listaTemp, TAMANHO);
    imprimirLista("Insertion Sort | Caso medio (aleatorio)", listaTemp, TAMANHO);
    printf("\n");


    // ============================================================================================================================================================================================================
    // 3. TESTANDO O SELECTION SORT
    // ============================================================================================================================================================================================================
   
    printf("============ 3. SELECTION SORT ===============\n");

    // a) Melhor Caso: Lista já ordenada
    copiarLista(listaTemp, listaOrdenada, TAMANHO);
    selectionSort(listaTemp, TAMANHO);
    imprimirLista("Selection Sort | Melhor Caso (ja ordenada)", listaTemp, TAMANHO);

    //b) Pior Caso: Lista em ordem inversa
    copiarLista(listaTemp, listaInversa, TAMANHO);
    selectionSort(listaTemp, TAMANHO);
    imprimirLista("Selection Sort | Pior Caso (ordem inversa)", listaTemp, TAMANHO);

    //c) Caso Medio: Lista Aleatoria
    copiarLista(listaTemp, listaAleatoria, TAMANHO);
    selectionSort(listaTemp, TAMANHO);
    imprimirLista("Selection Sort | Caso Medio (aleatoria)", listaTemp, TAMANHO);
    printf("\n");

    return 0; // Fim do programa
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES DE ORDENAÇÃO ---

void bubbleSort(int lista[], int n){
    int j, temp;
    int trocou; // Flag de otimização

    // Laço externo controla o numero de passagens pela lista
    // Após cada passagem 'i', o i-ésimo maior elemento estará no lugar certo
    for (int i = 0; i < n - 1; i++)
    {
        trocou = 0; // No inicio de cada passagem, assumimos que nao haverá trocas

        // Laço interno percorre a lista, comparando elementos adjacentes
        // O limite é 'n - i - 1' porque os elementos no final já estão ordenados
        for ( j = 0; j < n - i - 1; j++)
        {   //se o elemento atual for menor que o próximo
            if (lista[j] > lista[j + 1]){
                // troca eles de lugar
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
                trocou = 1; // Marca que uma troca ocorreu 

            }
            
        }
        
        // OTIMIZAÇÃO: Se após uma mensagem completa nenhuma troca for feita.
        // a lista já está ordenada e podemos parar o algoritimo
        if(trocou == 0){
            break;
        }

    }
    
}

void insertionSort(int lista[], int n){
    int i, chave, j;

    // Começamos do segundo elemento (índice 1), pois o primeiro já é uma sub-lista ordenada
    for (i = 1; i < n; i++){
        // 'chave' é o elemento que queremos inserir na parte ordenada
        chave = lista[i];
        // 'j' aponta para o último elemento da parte ordenada
        j = i - 1;

        // Move os elementos da parte ordenada que são maiores que a 'chave'
        // uma posição para a direita, para abrir espaço para a inserção
        while (j >= 0 && lista[j] > chave){
            lista[j + 1] = lista[j];
            j = j - 1;
        }

        // Insere a 'chave' na posição correta (o "buraco" aberto)
        lista[j + 1] = chave;
    }
}

void selectionSort(int lista[], int n){
    int j, indice_min, temp;

    // Laço externo percorre a lista para definir a fronteira entre
    // a parte ordenada e a não ordenada 
    for (int i = 0; i < n - 1; i++){
        // Assume que o primeiro elemento da parte não ordenada é o menor
        indice_min = i;

    // Laço interno percorre a parte não ordenada para encontrar o menor elemento 
    for (j = i + 1; j < n; j++){
        // Se encontrar um elemento menor que o minimo atual...
            if (lista[j] < lista[indice_min])
            {   // Atualiza o indice do minimo 
                indice_min = j;
            }
        
        }
        
        // Se o menor elemento não for o primeiro da parte não ordenada,
        // troca-los de lugar
        if (indice_min != i)
        {
            temp = lista[i];
            lista[i] = lista[indice_min];
            lista[indice_min] = temp;
        }
    }
}

// --- IMPLEMENTAÇÕES DAS FUNÇÕES AUXILIARES ---

void gerarListaOrdenada(int lista[], int n){
    for (int i = 0; i < n; i++)
    {
        lista[i] = i + 1;
    }
    imprimirLista("Original - Ordenada", lista, n);
}

void copiarLista(int destino[], const int origem[], int n){
    for (int i = 0; i < n; i++){
        destino[i] = origem[i];
    }
}

void imprimirLista(const char* titulo, const int lista[], int n){
    printf("%s:\n", titulo);
    for (int i = 0; i < n; i++){
        printf("%d ", lista[i]);
    }
    printf("\n\n");
}

void gerarListaInversa(int lista[], int n){
    for (int i = 0; i < n; i++){
        lista[i] = n - i;
    }
    imprimirLista("Original - Inversa", lista, n);
}

void gerarListaAleatoria(int lista[], int n){
    for (int i = 0; i < n; i++){
        lista[i] = rand() % 100 + 1;
    }
    imprimirLista("Original - Aleatoria", lista, n);
}
