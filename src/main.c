#include "raylib.h"
#include "tabuleiro.h"
#include <stdlib.h>
#include <time.h>

// Função auxiliar para limitar valores
float ClampFloat(float valor, float min, float max) {
    if (valor < min) return min;
    if (valor > max) return max;
    return valor;
}

// Função para escurecer uma cor suavemente
Color EscurecerCor(Color cor, float fator) {
    return (Color){
        (unsigned char)ClampFloat(cor.r * fator, 0, 255),
        (unsigned char)ClampFloat(cor.g * fator, 0, 255),
        (unsigned char)ClampFloat(cor.b * fator, 0, 255),
        cor.a
    };
}

// Gera uma cor aleatória entre tons suaves de azul, vermelho e amarelo
Color GerarCorAleatoria() {
    int tipo = GetRandomValue(0, 2);
    Color corBase;

    switch (tipo) {
        case 0: corBase = (Color){80, 120, 200, 255}; break;  // Azul suave
        case 1: corBase = (Color){200, 80, 80, 255}; break;   // Vermelho suave
        default: corBase = (Color){230, 200, 90, 255}; break; // Amarelo suave
    }

    float fator = 0.9f + (GetRandomValue(0, 10) / 100.0f);
    return EscurecerCor(corBase, fator);
}

int main(void) {
    const int LARGURA_TELA = 1280;
    const int ALTURA_TELA = 720;

    InitWindow(LARGURA_TELA, ALTURA_TELA, "Crazy Circus 🎪");
    SetTargetFPS(60);
    ToggleFullscreen();

    // Carregar imagem de fundo
    Texture2D fundo = LoadTexture("assets/fundoCrazyCircus.png");

    // Criar tabuleiro lógico
    int LINHAS = 12;
    int COLUNAS = 12;
    Tabuleiro *tabuleiro = criarTabuleiro(LINHAS, COLUNAS);

    // Gerar cores para cada célula
    Color **coresCelulas = malloc(LINHAS * sizeof(Color *));
    for (int i = 0; i < LINHAS; i++) {
        coresCelulas[i] = malloc(COLUNAS * sizeof(Color));
        for (int j = 0; j < COLUNAS; j++) {
            coresCelulas[i][j] = GerarCorAleatoria();
        }
    }

    // Parâmetros de tamanho e espaçamento
    float tamanhoCelula = 40;
    float espacamento = 4;

    // Calcular o tamanho total do tabuleiro
    float gridLargura = (tamanhoCelula + espacamento) * COLUNAS;
    float gridAltura = (tamanhoCelula + espacamento) * LINHAS;

    // Centralizar o tabuleiro, com mais espaço inferior para o palhaço
    float margemSuperior = (ALTURA_TELA - gridAltura) / 2 - 50;
    float margemEsquerda = (LARGURA_TELA - gridLargura) / 2;

    while (!WindowShouldClose()) {
        BeginDrawing();

        // --- DESENHO DO FUNDO (sem redimensionamento extra, sem tarjas) ---
        DrawTexture(fundo, 0, 0, WHITE);

        // --- DESENHO DO TABULEIRO ---
        for (int i = 0; i < LINHAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                float x = margemEsquerda + j * (tamanhoCelula + espacamento);
                float y = margemSuperior + i * (tamanhoCelula + espacamento);

                // Desenha o corpo da célula
                DrawRectangleRounded(
                    (Rectangle){x, y, tamanhoCelula, tamanhoCelula},
                    0.2f,
                    6,
                    coresCelulas[i][j]
                );

                // Aplica um leve sombreamento na borda para destacar sem exagerar
                Color sombra = EscurecerCor(coresCelulas[i][j], 0.6f);
                DrawRectangleLinesEx(
                    (Rectangle){x, y, tamanhoCelula, tamanhoCelula},
                    1.5f,
                    sombra
                );
            }
        }

        EndDrawing();
    }

    // Libera memória
    for (int i = 0; i < LINHAS; i++) {
        free(coresCelulas[i]);
    }
    free(coresCelulas);
    liberarTabuleiro(tabuleiro);
    UnloadTexture(fundo);
    CloseWindow();

    return 0;
}
