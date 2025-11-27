#include "tabuleiro.h"
#include <stdlib.h>

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
            tabuleiro->matriz[i][j].coberta = true;
            tabuleiro->matriz[i][j].bandeira = false;
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
            
            tabuleiro->matriz[i][j].coberta = true;
            tabuleiro->matriz[i][j].bandeira = false;
        }
    }
}

int contarAdjacentes(Tabuleiro *tabuleiro, int linha, int coluna) {
    int cont = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            
            int nl = linha + i; 
            int nc = coluna + j; 
            
            if (nl >= 0 && nl < tabuleiro->linhas && nc >= 0 && nc < tabuleiro->colunas) {
                if (tabuleiro->matriz[nl][nc].tipo == ANIMAL) {
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
    
    if (!tabuleiro->matriz[linha][coluna].coberta) return;

    tabuleiro->matriz[linha][coluna].coberta = false;
    tabuleiro->matriz[linha][coluna].bandeira = false;

    if (tabuleiro->matriz[linha][coluna].tipo == ANIMAL) return;

    if (tabuleiro->matriz[linha][coluna].animaisVizinhos > 0) return;

    node *lista = NULL;
    adicionarNaLista(&lista, linha, coluna);

    while (lista != NULL) {
        node *atual = removerDaLista(&lista);
        int la = atual->linha;
        int ca = atual->coluna;
        free(atual);

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int nl = la + i;
                int nc = ca + j;

                if (nl >= 0 && nl < tabuleiro->linhas && nc >= 0 && nc < tabuleiro->colunas) {
                    
                    if (tabuleiro->matriz[nl][nc].coberta) {
                        
                        tabuleiro->matriz[nl][nc].coberta = false; 
                        tabuleiro->matriz[nl][nc].bandeira = false;

                        if (tabuleiro->matriz[nl][nc].animaisVizinhos == 0) {
                            adicionarNaLista(&lista, nl, nc);
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
            if (tabuleiro->matriz[i][j].tipo != ANIMAL && tabuleiro->matriz[i][j].coberta) {
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
                tabuleiro->matriz[i][j].coberta = false; 
                tabuleiro->matriz[i][j].bandeira = false; 
            }
        }
    }
}
