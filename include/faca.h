#ifndef FACA_H
#define FACA_H

#include "raylib.h"
#include <stdbool.h>

typedef struct {
    Vector2 pos;
    Vector2 destino;
    bool emMovimento;
    int frame;
    float tempoAnimacao;
    Texture2D sprites[3];
    float escala;
} Faca;

Faca criarFaca(Texture2D sprites[3], float escala);
void atualizarFaca(Faca *faca, float velocidade, float tempoFrame);
void desenharFaca(Faca *faca);

#endif
