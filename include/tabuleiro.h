#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <stdbool.h>

typedef enum { VAZIO, ANIMAL } TipoCelula;

typedef struct {
    TipoCelula tipo;
    bool visivel;
    bool bandeira;
    int animaisVizinhos;
} Celula;

typedef struct {
    int linhas;
    int colunas;
    Celula **matriz;
} Tabuleiro;

typedef struct node {
    int linha;
    int coluna;
    struct node *next;
} node;

Tabuleiro* criarTabuleiro(int linhas, int colunas);
void liberarTabuleiro(Tabuleiro* tabuleiro);
void gerarAnimais(Tabuleiro* tabuleiro, float chanceAnimal);
void calcularVizinhos(Tabuleiro *tabuleiro);
void abrirCelula(Tabuleiro*tabuleiro, int linha, int coluna);
bool verificarVitoria(Tabuleiro* tabuleiro);
void revelarAnimais(Tabuleiro* tabuleiro);

#endif
