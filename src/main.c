#include "raylib.h"
#include "tabuleiro.h"
#include "faca.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

float ClampFloat(float valor, float min, float max) {
    if (valor < min) return min;
    if (valor > max) return max;
    return valor;
}

Color EscurecerCor(Color cor, float fator) {
    return (Color){
        (unsigned char)ClampFloat(cor.r * fator, 0, 255),
        (unsigned char)ClampFloat(cor.g * fator, 0, 255),
        (unsigned char)ClampFloat(cor.b * fator, 0, 255),
        cor.a
    };
}

Color GerarCorAleatoria() {
    int tipo = GetRandomValue(0, 2);
    Color corBase;
    switch (tipo) {
        case 0: corBase = (Color){80, 120, 200, 255}; break;
        case 1: corBase = (Color){200, 80, 80, 255}; break;
        default: corBase = (Color){230, 200, 90, 255}; break;
    }
    float fator = 0.9f + (GetRandomValue(0, 10) / 100.0f);
    return EscurecerCor(corBase, fator);
}

int main(void) {
    srand(time(NULL));
    const int LARGURA_TELA = 1280;
    const int ALTURA_TELA = 720;
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Crazy Circus 🎪");
    SetTargetFPS(60);

    Texture2D fundo = LoadTexture("assets/fundoCrazyCircus.png");
    Texture2D palhacoParado = LoadTexture("assets/palhaco_parado.png");
    Texture2D palhacoJogando = LoadTexture("assets/palhaco_jogando.png");
    Texture2D faca1 = LoadTexture("assets/faca_estado1.png");
    Texture2D faca2 = LoadTexture("assets/faca_estado2.png");
    Texture2D faca3 = LoadTexture("assets/faca_estado3.png");
    Texture2D texturaBandeira = LoadTexture("assets/logo.png");

    int LINHAS = 12, COLUNAS = 12;
    Tabuleiro *tabuleiro = criarTabuleiro(LINHAS, COLUNAS);
    gerarAnimais(tabuleiro, 0.15f);
    calcularVizinhos(tabuleiro);

    Color **coresCelulas = malloc(LINHAS * sizeof(Color*));
    for (int i = 0; i < LINHAS; i++) {
        coresCelulas[i] = malloc(COLUNAS * sizeof(Color));
        for (int j = 0; j < COLUNAS; j++)
            coresCelulas[i][j] = GerarCorAleatoria();
    }

    float tamanhoCelula = 40;
    float espacamento = 4;
    float gridLargura = (tamanhoCelula + espacamento) * COLUNAS;
    float gridAltura = (tamanhoCelula + espacamento) * LINHAS;
    float margemSuperior = (ALTURA_TELA - gridAltura) / 2;
    float margemEsquerda = (LARGURA_TELA - gridLargura) / 2;

    float escalaPalhaco = 0.25f;
    Vector2 posPalhaco = {
        margemEsquerda - palhacoParado.width * escalaPalhaco - 20,
        ALTURA_TELA - palhacoParado.height * escalaPalhaco - 60
    };

    Vector2 offsetMao = { palhacoParado.width * 0.01f, palhacoParado.height * 0.01f };

    Texture2D spritesFaca[3] = {faca1, faca2, faca3};
    Faca faca = criarFaca(spritesFaca, 0.25f);
    float velocidadeFaca = 1200.0f;
    float tempoFrameFaca = 0.1f;

    double timer = 0.0;
    
    bool iniciarJogo = false; 
    bool fimJogo = false;

    int alvoLinha = -1;
    int alvoColuna = -1;

    while (!WindowShouldClose()) {

        if(iniciarJogo && !fimJogo){
            timer += GetFrameTime();
        }

        Vector2 mouse = GetMousePosition();

        // ----------- MARCAR BANDEIRA (CLIQUE DIREITO) ----------------
        if (!fimJogo && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            for (int i = 0; i < LINHAS; i++) {
                for (int j = 0; j < COLUNAS; j++) {

                    if (!tabuleiro->matriz[i][j].visivel) continue;

                    float x = margemEsquerda + j * (tamanhoCelula + espacamento);
                    float y = margemSuperior + i * (tamanhoCelula + espacamento);
                    Rectangle celulaRect = {x, y, tamanhoCelula, tamanhoCelula};

                    if (CheckCollisionPointRec(mouse, celulaRect)) {
                        tabuleiro->matriz[i][j].bandeira = !tabuleiro->matriz[i][j].bandeira;
                        break;
                    }
                }
            }
        }

        // ----------- ATIRAR FACA (CLIQUE ESQUERDO) ----------------
        if (!fimJogo && !faca.emMovimento && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < LINHAS; i++) {
                for (int j = 0; j < COLUNAS; j++) {

                    if (!tabuleiro->matriz[i][j].visivel) continue;
                    if (tabuleiro->matriz[i][j].bandeira) continue;

                    float x = margemEsquerda + j * (tamanhoCelula + espacamento);
                    float y = margemSuperior + i * (tamanhoCelula + espacamento);
                    Rectangle celulaRect = {x, y, tamanhoCelula, tamanhoCelula};

                    if (CheckCollisionPointRec(mouse, celulaRect)) {
                        iniciarJogo = true;

                        alvoLinha = i;
                        alvoColuna = j;

                        faca.pos = (Vector2){
                            posPalhaco.x + offsetMao.x * escalaPalhaco,
                            posPalhaco.y + offsetMao.y * escalaPalhaco
                        };
                        faca.destino = (Vector2){
                            x + tamanhoCelula/2 - faca.sprites[0].width*faca.escala/2,
                            y + tamanhoCelula/2 - faca.sprites[0].height*faca.escala/2
                        };

                        faca.emMovimento = true;
                        faca.frame = 0;
                        faca.tempoAnimacao = 0.0f;
                        
                        break;
                    }
                }
            }
        }

        atualizarFaca(&faca, velocidadeFaca, tempoFrameFaca);

        if (!faca.emMovimento && alvoLinha != -1 && alvoColuna != -1) {
            
            if (tabuleiro->matriz[alvoLinha][alvoColuna].tipo == ANIMAL) {
                fimJogo = true;
                revelarAnimais(tabuleiro);  
            } 

            abrirCelula(tabuleiro, alvoLinha, alvoColuna); 

            if(verificarVitoria(tabuleiro)){
                fimJogo = true;
            }

            alvoLinha = alvoColuna = -1;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(fundo, 0, 0, WHITE);

        // ➤ TIMER SEM TARJA
        int minutos = timer / 60;
        int segundos = (int)timer % 60;
        DrawText(TextFormat("%02d:%02d", minutos, segundos), 20, 20, 30, WHITE);

        // (Removido completamente mensagens superiores)

        // -------- DESENHAR TABULEIRO --------
        for (int i = 0; i < LINHAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                float x = margemEsquerda + j * (tamanhoCelula + espacamento);
                float y = margemSuperior + i * (tamanhoCelula + espacamento);
                Rectangle rect = {x, y, tamanhoCelula, tamanhoCelula};

                if (tabuleiro->matriz[i][j].visivel) {
                    DrawRectangleRounded(rect, 0.2f, 6, coresCelulas[i][j]);
                    DrawRectangleLinesEx(rect, 1.5f, BLACK);

                    if (tabuleiro->matriz[i][j].bandeira) {

                        float escalaLogo = tamanhoCelula * 1.25f; 
                        float proporcao = (float)texturaBandeira.width / texturaBandeira.height;

                        float w = escalaLogo;
                        float h = escalaLogo;

                        if (proporcao > 1) {
                            h /= proporcao;
                        } else {
                            w *= proporcao;
                        }

                        float posX = x + (tamanhoCelula - w) / 2;
                        float posY = y + (tamanhoCelula - h) / 2;

                        Rectangle src = {0, 0, texturaBandeira.width, texturaBandeira.height};
                        Rectangle dst = {posX, posY, w, h};

                        DrawTexturePro(texturaBandeira, src, dst, (Vector2){0, 0}, 0, WHITE);
                    }

                } else {
                    if (tabuleiro->matriz[i][j].tipo == ANIMAL) {
                        DrawCircle(x + tamanhoCelula/2, y + tamanhoCelula/2, 12, RED);
                    } 
                    else if (tabuleiro->matriz[i][j].animaisVizinhos > 0) {

                        DrawRectangleRounded(rect, 0.2f, 6, RAYWHITE); 
                        DrawRectangleLinesEx(rect, 1.5f, LIGHTGRAY);

                        char num[2];
                        sprintf(num, "%d", tabuleiro->matriz[i][j].animaisVizinhos);
                        
                        Color c = BLACK;
                        if (tabuleiro->matriz[i][j].animaisVizinhos == 1) c = BLUE;
                        else if (tabuleiro->matriz[i][j].animaisVizinhos == 2) c = DARKGREEN;
                        else if (tabuleiro->matriz[i][j].animaisVizinhos == 3) c = RED;

                        int txtW = MeasureText(num, 20);
                        DrawText(num, x + tamanhoCelula/2 - txtW/2, y + 10, 20, c);
                    }
                }
            }
        }

        Texture2D spritePalhaco = faca.emMovimento ? palhacoJogando : palhacoParado;
        DrawTextureEx(spritePalhaco, posPalhaco, 0.0f, escalaPalhaco, WHITE);

        desenharFaca(&faca);

        EndDrawing();
    }

    for (int i = 0; i < LINHAS; i++) free(coresCelulas[i]);
    free(coresCelulas);
    liberarTabuleiro(tabuleiro);

    UnloadTexture(fundo);
    UnloadTexture(palhacoParado);
    UnloadTexture(palhacoJogando);
    UnloadTexture(faca1);
    UnloadTexture(faca2);
    UnloadTexture(faca3);
    UnloadTexture(texturaBandeira);

    CloseWindow();
    return 0;
}
