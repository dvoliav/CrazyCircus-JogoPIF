#ifndef RECORDES_H
#define RECORDES_H

typedef struct {
    char nome[6];
    double tempo;
} Recorde;

void carregarRecordes(Recorde lista[10], int *quantidade);
void salvarRecordes(Recorde lista[10], int quantidade);
void adicionarRecorde(Recorde lista[10], int *quantidade, const char nome[6], double tempo);
void ordenarRecordes(Recorde lista[10], int quantidade);

#endif