#include <stdio.h>
#include "raylib.h"
#include "tabuleiro.h"

int main(void) {
    // Configurações da janela do jogo
    const int larguraJanela = 800;
    const int alturaJanela = 600;
    InitWindow(larguraJanela, alturaJanela, "🎪 Campo Minado do Palhaço 🎯");

    // Criação do tabuleiro 12x12
    Tabuleiro *tabuleiro = criarTabuleiro(12, 12);

    SetTargetFPS(60);

    // Loop principal do jogo (por enquanto só exibe o texto)
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Tabuleiro 12x12 criado! (Veja no terminal)", 140, 280, 20, DARKBLUE);
        EndDrawing();
    }

    // Mostra o tabuleiro no terminal
    imprimirTabuleiro(tabuleiro);

    // Libera memória antes de sair
    liberarTabuleiro(tabuleiro);

    CloseWindow();
    return 0;
}
