#include "tabuleiro.h"
#include <stdlib.h>
#include <stdio.h>

void adicionarNaLista(node **inicio, int linha, int coluna) {
    node *novo = malloc(sizeof(node));
    novo->linha = linha;
    novo->coluna = coluna;
    novo->next = *inicio;
    *inicio = novo;
}

node* removerDaLista(node **inicio) {
    if (*inicio == NULL) return NULL;
    node *temp = *inicio;
    *inicio = (*inicio)->next;
    return temp;
}

Tabuleiro* criarTabuleiro(int linhas, int colunas) {
    Tabuleiro *tabuleiro = malloc(sizeof(Tabuleiro));
    tabuleiro->linhas = linhas;
    tabuleiro->colunas = colunas;
    tabuleiro->matriz = malloc(linhas * sizeof(Celula*));
    
    for (int i = 0; i < linhas; i++) {
        tabuleiro->matriz[i] = malloc(colunas * sizeof(Celula));
        for (int j = 0; j < colunas; j++) {
            tabuleiro->matriz[i][j].tipo = VAZIO;
            tabuleiro->matriz[i][j].visivel = true;
            tabuleiro->matriz[i][j].animaisVizinhos = 0;
        }
    }
    return tabuleiro;
}

void liberarTabuleiro(Tabuleiro* tabuleiro) {
    for (int i = 0; i < tabuleiro->linhas; i++)
        free(tabuleiro->matriz[i]);
    free(tabuleiro->matriz);
    free(tabuleiro);
}

void gerarAnimais(Tabuleiro* tabuleiro, float chanceAnimal) {
    for (int i = 0; i < tabuleiro->linhas; i++) {
        for (int j = 0; j < tabuleiro->colunas; j++) {
            int rnd = rand() % 100;
            
            if (rnd < (int)(chanceAnimal * 100))
                tabuleiro->matriz[i][j].tipo = ANIMAL;
            else
                tabuleiro->matriz[i][j].tipo = VAZIO;
            
            tabuleiro->matriz[i][j].visivel = true;
        }
    }
}

int contarAdjacentes(Tabuleiro *tabuleiro, int linha, int coluna) {
    int cont = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            
            int novaLinha = linha + i; 
            int novaColuna = coluna + j; 
            
            if (novaLinha >= 0 && novaLinha < tabuleiro->linhas && novaColuna >= 0 && novaColuna < tabuleiro->colunas) {
                if (tabuleiro->matriz[novaLinha][novaColuna].tipo == ANIMAL) {
                    cont++;
                }
            }
        }
    }
    return cont;
}

void calcularVizinhos(Tabuleiro* tabuleiro) {
    for (int i = 0; i < tabuleiro->linhas; i++) {
        for (int j = 0; j < tabuleiro->colunas; j++) {
            
            if (tabuleiro->matriz[i][j].tipo == ANIMAL) {
                tabuleiro->matriz[i][j].animaisVizinhos = -1; 
            } else {
                tabuleiro->matriz[i][j].animaisVizinhos = contarAdjacentes(tabuleiro, i, j);
            }
        }
    }
}

void abrirCelula(Tabuleiro* tabuleiro, int linha, int coluna) {
    if (linha < 0 || linha >= tabuleiro->linhas || coluna < 0 || coluna >= tabuleiro->colunas) return;
    
    if (!tabuleiro->matriz[linha][coluna].visivel) return;

    tabuleiro->matriz[linha][coluna].visivel = false;

    if (tabuleiro->matriz[linha][coluna].tipo == ANIMAL) return;

    if (tabuleiro->matriz[linha][coluna].animaisVizinhos > 0) return;

    node *lista = NULL;
    adicionarNaLista(&lista, linha, coluna);

    while (lista != NULL) {
        node *atual = removerDaLista(&lista);
        int linhaAtual = atual->linha;
        int colunaAtual = atual->coluna;
        free(atual);

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int novaLinha = linhaAtual + i;
                int novaColuna = colunaAtual + j;

                if (novaLinha >= 0 && novaLinha < tabuleiro->linhas && novaColuna >= 0 && novaColuna < tabuleiro->colunas) {
                    
                    if (tabuleiro->matriz[novaLinha][novaColuna].visivel) {
                        
                        tabuleiro->matriz[novaLinha][novaColuna].visivel = false; 

                        if (tabuleiro->matriz[novaLinha][novaColuna].animaisVizinhos == 0) {
                            adicionarNaLista(&lista, novaLinha, novaColuna);
                        }
                    }
                }
            }
        }
    }
}

bool verificarVitoria(Tabuleiro* tabuleiro) {
    for (int i = 0; i < tabuleiro->linhas; i++) {
        for (int j = 0; j < tabuleiro->colunas; j++) {
            if (tabuleiro->matriz[i][j].tipo != ANIMAL && tabuleiro->matriz[i][j].visivel) {
                return false; 
            }
        }
    }
    return true; 
}

void revelarAnimais(Tabuleiro* tabuleiro) {
    for (int i = 0; i < tabuleiro->linhas; i++) {
        for (int j = 0; j < tabuleiro->colunas; j++) {
            if (tabuleiro->matriz[i][j].tipo == ANIMAL) {
                tabuleiro->matriz[i][j].visivel = false; 
            }
        }
    }
}
