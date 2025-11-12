#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <stdbool.h>

// Cada célula representa um "quadrado" do campo
typedef struct {
    bool temAnimal;     // Diz se há um bicho escondido (bomba)
    bool foiAberta;     // Indica se o jogador já abriu essa célula
    int animaisAdj;     // Quantos animais há nas células vizinhas
} Celula;

// Estrutura principal do tabuleiro
typedef struct {
    int totalLinhas;
    int totalColunas;
    Celula **grade;     // Ponteiro para a matriz de células
} Tabuleiro;

// Funções principais do tabuleiro
Tabuleiro *criarTabuleiro(int linhas, int colunas);
void liberarTabuleiro(Tabuleiro *tabuleiro);
void imprimirTabuleiro(Tabuleiro *tabuleiro);

#endif
