#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <stdbool.h>

typedef enum { VAZIO, ANIMAL, BOMBA } TipoCelula;

typedef struct {
    TipoCelula tipo;
    bool visivel;
} Celula;

typedef struct {
    int linhas;
    int colunas;
    Celula **matriz;
} Tabuleiro;

Tabuleiro* criarTabuleiro(int linhas, int colunas);
void liberarTabuleiro(Tabuleiro* tabuleiro);
void gerarAnimais(Tabuleiro* tabuleiro, float chanceBomba);
void abrirCelula(Tabuleiro* tabuleiro, int linha, int coluna);

#endif
