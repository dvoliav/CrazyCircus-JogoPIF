#include "recordes.h"
#include <stdio.h>
#include <string.h>

void carregarRecordes(Recorde lista[10], int *quantidade) {
    FILE *arq = fopen("recordes.txt", "r");
    if (!arq) {
        *quantidade = 0;
        return;
    }

    *quantidade = 0;

    char tempoStr[10];
    while (*quantidade < 10 && fscanf(arq, "%5s %9s", lista[*quantidade].nome, tempoStr) == 2) {
        int min, seg;
        sscanf(tempoStr, "%d:%d", &min, &seg);
        lista[*quantidade].tempo = min * 60 + seg;
        (*quantidade)++;
    }

    fclose(arq);
}

void salvarRecordes(Recorde lista[10], int quantidade) {
    FILE *arq = fopen("recordes.txt", "w");
    if (!arq) return;

    for (int i = 0; i < quantidade; i++) {
        int min = (int)lista[i].tempo / 60;
        int seg = (int)lista[i].tempo % 60;
        fprintf(arq, "%s %02d:%02d\n", lista[i].nome, min, seg);
    }

    fclose(arq);
}

void ordenarRecordes(Recorde lista[10], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        for (int j = i + 1; j < quantidade; j++) {
            if (lista[j].tempo < lista[i].tempo) {
                Recorde temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }
}

void adicionarRecorde(Recorde lista[10], int *quantidade, const char nome[6], double tempo) {
    if (*quantidade < 10) {
        strcpy(lista[*quantidade].nome, nome);
        lista[*quantidade].tempo = tempo;
        (*quantidade)++;
    } 
    else {
        if (tempo < lista[9].tempo) {
            strcpy(lista[9].nome, nome);
            lista[9].tempo = tempo;
        }
    }

    ordenarRecordes(lista, *quantidade);

    if (*quantidade > 10) {
        *quantidade = 10;
    }
}
