#include <stdio.h>
#include "raylib.h"
#include "tabuleiro.h"

int main(void) {
    // --- Obtém resolução do monitor principal ---
    int larguraTela = GetMonitorWidth(0);
    int alturaTela  = GetMonitorHeight(0);

    // --- Inicializa a janela em tela cheia real ---
    InitWindow(larguraTela, alturaTela, "Crazy Circus");
    ToggleFullscreen(); // Garante o modo tela cheia nativo

    // --- Criação do tabuleiro 12x12 ---
    Tabuleiro *tabuleiro = criarTabuleiro(12, 12);

    // --- Carrega a imagem de fundo ---
    Texture2D imagemCenario = LoadTexture("assets/fundoCrazyCircus.png");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        // Permite alternar entre tela cheia e modo janela
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            // --- Escala proporcional da imagem ---
            float escalaLargura = (float)GetScreenWidth() / imagemCenario.width;
            float escalaAltura  = (float)GetScreenHeight() / imagemCenario.height;
            float escalaFinal = (escalaLargura > escalaAltura) ? escalaLargura : escalaAltura;

            float posX = (GetScreenWidth()  - (imagemCenario.width * escalaFinal)) / 2.0f;
            float posY = (GetScreenHeight() - (imagemCenario.height * escalaFinal)) / 2.0f;

            DrawTextureEx(imagemCenario, (Vector2){posX, posY}, 0.0f, escalaFinal, WHITE);

        EndDrawing();
    }

    // --- Libera recursos ---
    UnloadTexture(imagemCenario);
    liberarTabuleiro(tabuleiro);
    CloseWindow();

    return 0;
}
