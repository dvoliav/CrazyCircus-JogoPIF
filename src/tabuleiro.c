#include "tabuleiro.h"
#include <stdlib.h>
#include <stdio.h>

Tabuleiro* criarTabuleiro(int linhas, int colunas) {
    Tabuleiro *t = malloc(sizeof(Tabuleiro));
    t->linhas = linhas;
    t->colunas = colunas;
    t->matriz = malloc(linhas * sizeof(Celula*));
    for (int i = 0; i < linhas; i++) {
        t->matriz[i] = malloc(colunas * sizeof(Celula));
        for (int j = 0; j < colunas; j++) {
            t->matriz[i][j].tipo = ANIMAL;
            t->matriz[i][j].visivel = true;
        }
    }
    return t;
}

void liberarTabuleiro(Tabuleiro* tabuleiro) {
    for (int i = 0; i < tabuleiro->linhas; i++)
        free(tabuleiro->matriz[i]);
    free(tabuleiro->matriz);
    free(tabuleiro);
}

void gerarAnimais(Tabuleiro* tabuleiro, float chanceBomba) {
    for (int i = 0; i < tabuleiro->linhas; i++) {
        for (int j = 0; j < tabuleiro->colunas; j++) {
            int rnd = rand() % 100;
            if (rnd < (int)(chanceBomba*100))
                tabuleiro->matriz[i][j].tipo = BOMBA;
            else
                tabuleiro->matriz[i][j].tipo = ANIMAL;
            tabuleiro->matriz[i][j].visivel = true;
        }
    }
}

void abrirCelula(Tabuleiro* tabuleiro, int linha, int coluna) {
    if (linha < 0 || linha >= tabuleiro->linhas || coluna < 0 || coluna >= tabuleiro->colunas) return;
    tabuleiro->matriz[linha][coluna].visivel = false;
}
