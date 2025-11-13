#include "faca.h"
#include <math.h>

Faca criarFaca(Texture2D sprites[3], float escala) {
    Faca f;
    f.emMovimento = false;
    f.frame = 0;
    f.tempoAnimacao = 0.0f;
    f.escala = escala;
    for (int i = 0; i < 3; i++) f.sprites[i] = sprites[i];
    f.pos = (Vector2){0, 0};
    f.destino = (Vector2){0, 0};
    return f;
}

void atualizarFaca(Faca *faca, float velocidade, float tempoFrame) {
    if (!faca->emMovimento) return;

    Vector2 direcao = {faca->destino.x - faca->pos.x, faca->destino.y - faca->pos.y};
    float distancia = sqrt(direcao.x*direcao.x + direcao.y*direcao.y);

    if (distancia < velocidade * GetFrameTime()) {
        faca->emMovimento = false;
        faca->pos = faca->destino;
        faca->frame = 0;
        faca->tempoAnimacao = 0.0f;
    } else {
        direcao.x /= distancia;
        direcao.y /= distancia;
        faca->pos.x += direcao.x * velocidade * GetFrameTime();
        faca->pos.y += direcao.y * velocidade * GetFrameTime();

        faca->tempoAnimacao += GetFrameTime();
        if (faca->tempoAnimacao >= tempoFrame) {
            faca->frame = (faca->frame + 1) % 3;
            faca->tempoAnimacao = 0.0f;
        }
    }
}

void desenharFaca(Faca *faca) {
    if (faca->emMovimento) {
        DrawTextureEx(faca->sprites[faca->frame], faca->pos, 0.0f, faca->escala, WHITE);
    }
}
