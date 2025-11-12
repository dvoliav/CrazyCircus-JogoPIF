#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <stdbool.h>

typedef struct {
    bool temAnimal;
    bool foiAberta;
    int animaisAdj;
} Celula;

typedef struct {
    int totalLinhas;
    int totalColunas;
    Celula **grade;
} Tabuleiro;

Tabuleiro *criarTabuleiro(int linhas, int colunas);
void liberarTabuleiro(Tabuleiro *tabuleiro);
void imprimirTabuleiro(Tabuleiro *tabuleiro);
void gerarAnimais(Tabuleiro *tabuleiro, float porcentagem);

#endif
