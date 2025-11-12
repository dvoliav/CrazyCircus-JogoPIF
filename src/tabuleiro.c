#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"

// Cria o tabuleiro e aloca memória dinamicamente
Tabuleiro *criarTabuleiro(int linhas, int colunas) {
    // Cria o espaço para a estrutura principal
    Tabuleiro *tabuleiro = malloc(sizeof(Tabuleiro));
    tabuleiro->totalLinhas = linhas;
    tabuleiro->totalColunas = colunas;

    // Aloca a matriz de ponteiros (cada linha aponta pra um vetor de células)
    tabuleiro->grade = malloc(linhas * sizeof(Celula *));
    for (int i = 0; i < linhas; i++) {
        tabuleiro->grade[i] = malloc(colunas * sizeof(Celula));
        for (int j = 0; j < colunas; j++) {
            // Inicializa todas as células vazias
            tabuleiro->grade[i][j].temAnimal = false;
            tabuleiro->grade[i][j].foiAberta = false;
            tabuleiro->grade[i][j].animaisAdj = 0;
        }
    }

    return tabuleiro;
}

// Libera toda a memória alocada para o tabuleiro
void liberarTabuleiro(Tabuleiro *tabuleiro) {
    for (int i = 0; i < tabuleiro->totalLinhas; i++) {
        free(tabuleiro->grade[i]);
    }
    free(tabuleiro->grade);
    free(tabuleiro);
}

// Mostra o tabuleiro no terminal (para testes iniciais)
void imprimirTabuleiro(Tabuleiro *tabuleiro) {
    printf("\n=== TABULEIRO DO CIRCO ===\n");
    for (int i = 0; i < tabuleiro->totalLinhas; i++) {
        for (int j = 0; j < tabuleiro->totalColunas; j++) {
            printf("[ ] ");
        }
        printf("\n");
    }
    printf("===========================\n");
}
