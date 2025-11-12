#include "raylib.h"

int main(void) {
    InitWindow(800, 450, "Circo das Facas 🎯");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Bem-vindo ao Circo das Facas!", 190, 200, 20, DARKBLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
