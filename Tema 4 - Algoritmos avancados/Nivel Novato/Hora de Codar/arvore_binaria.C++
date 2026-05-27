#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

struct No{
    char nome[50];
    No* esquerda;
    No* direita;
};

No* criarNo(const char* valor){
    No* novoNo = new No;
    strcpy(novoNo->nome, valor);
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

void preOrdem(struct No* raiz) {
    if (raiz != NULL) {
        printf("%s ", raiz->nome);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void emOrdem(struct No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%s ", raiz->nome);
        emOrdem(raiz->direita);
    }
}

void posOrdem(struct No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%s ", raiz->nome);
    }
}

void liberarArvore(struct No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        delete raiz;
    }
}

int main(){

    struct No* raiz = criarNo("Raiz(Pai)");
    raiz->esquerda = criarNo("Esq(Filho)");
    raiz->direita = criarNo("Dir(Filho)");
    raiz->esquerda->esquerda = criarNo("Esq(filho) Esquerda(folha)");

    printf("Pre-Ordem: ");
    preOrdem(raiz);
    std::cout <<"\n"<< std::endl; // Para adicionar uma nova linha após a impressão da pré-ordem
    // std::cout é usado para imprimir uma nova linha, e std::endl é usado para garantir que a saída seja imediatamente exibida, além de adicionar uma nova linha.

    printf("\nEm-Ordem: ");
    emOrdem(raiz);
    std::cout <<"\n"; // Sem o std::endl, apenas para adicionar uma nova linha após a impressão da em-ordem
    
    printf("\nPos-Ordem: ");
    posOrdem(raiz);
    std::cout <<"\n"<< std::endl;

    liberarArvore(raiz);
    
    return 0;
}