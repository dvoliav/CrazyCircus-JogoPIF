#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tabuleiro.h"

Tabuleiro *criarTabuleiro(int linhas, int colunas) {
    Tabuleiro *tabuleiro = malloc(sizeof(Tabuleiro));
    tabuleiro->totalLinhas = linhas;
    tabuleiro->totalColunas = colunas;
    tabuleiro->grade = malloc(linhas * sizeof(Celula *));
    for (int i = 0; i < linhas; i++) {
        tabuleiro->grade[i] = malloc(colunas * sizeof(Celula));
        for (int j = 0; j < colunas; j++) {
            tabuleiro->grade[i][j].temAnimal = false;
            tabuleiro->grade[i][j].foiAberta = false;
            tabuleiro->grade[i][j].animaisAdj = 0;
        }
    }
    return tabuleiro;
}

void liberarTabuleiro(Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->totalLinhas; i++) free(tabuleiro->grade[i]);
    free(tabuleiro->grade);
    free(tabuleiro);
}

void imprimirTabuleiro(Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->totalLinhas; i++) {
        for (int j = 0; j < tabuleiro->totalColunas; j++) {
            if (tabuleiro->grade[i][j].temAnimal)
                printf("[X] ");
            else
                printf("[ ] ");
        }
        printf("\n");
    }
    printf("\n");
}


void gerarAnimais(Tabuleiro *tabuleiro, float porcentagem) {
    srand(time(NULL));
    int totalCelulas = tabuleiro->totalLinhas * tabuleiro->totalColunas;
    int totalAnimais = (int)(totalCelulas * porcentagem);
    int animaisGerados = 0;
    while (animaisGerados < totalAnimais) {
        int linha = rand() % tabuleiro->totalLinhas;
        int coluna = rand() % tabuleiro->totalColunas;
        if (!tabuleiro->grade[linha][coluna].temAnimal) {
            tabuleiro->grade[linha][coluna].temAnimal = true;
            animaisGerados++;
        }
    }
}
