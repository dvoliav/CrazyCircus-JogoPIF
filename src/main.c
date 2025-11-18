#include "raylib.h"
#include "tabuleiro.h"
#include "faca.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

// Funções auxiliares
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

    // Carregar assets
    Texture2D fundo = LoadTexture("assets/fundoCrazyCircus.png");
    Texture2D palhacoParado = LoadTexture("assets/palhaco_parado.png");
    Texture2D palhacoJogando = LoadTexture("assets/palhaco_jogando.png");
    Texture2D faca1 = LoadTexture("assets/faca_estado1.png");
    Texture2D faca2 = LoadTexture("assets/faca_estado2.png");
    Texture2D faca3 = LoadTexture("assets/faca_estado3.png");

    // Tabuleiro
    int LINHAS = 12, COLUNAS = 12;
    Tabuleiro *tabuleiro = criarTabuleiro(LINHAS, COLUNAS);
    gerarAnimais(tabuleiro, 0.15f);
    calcularVizinhos(tabuleiro);

    // Cores das células
    Color **coresCelulas = malloc(LINHAS * sizeof(Color*));
    for (int i = 0; i < LINHAS; i++) {
        coresCelulas[i] = malloc(COLUNAS * sizeof(Color));
        for (int j = 0; j < COLUNAS; j++)
            coresCelulas[i][j] = GerarCorAleatoria();
    }

    // Grid
    float tamanhoCelula = 40;
    float espacamento = 4;
    float gridLargura = (tamanhoCelula + espacamento) * COLUNAS;
    float gridAltura = (tamanhoCelula + espacamento) * LINHAS;
    float margemSuperior = (ALTURA_TELA - gridAltura) / 2;
    float margemEsquerda = (LARGURA_TELA - gridLargura) / 2;

    // Palhaço
    float escalaPalhaco = 0.25f;
    Vector2 posPalhaco = {
        margemEsquerda - palhacoParado.width * escalaPalhaco - 20,
        ALTURA_TELA - palhacoParado.height * escalaPalhaco - 60
    };

    // Offset da mão do palhaço (ajustado para a faca sair da mão)
    Vector2 offsetMao = { palhacoParado.width * 0.01f, palhacoParado.height * 0.01f };

    // Faca
    Texture2D spritesFaca[3] = {faca1, faca2, faca3};
    Faca faca = criarFaca(spritesFaca, 0.25f);
    float velocidadeFaca = 1200.0f;
    float tempoFrameFaca = 0.1f;

    // Mensagem bomba
    char mensagem[128] = "Atire a faca para iniciar";
    Color corMensagem = WHITE;
    double timer = 0.0;
    
    // tempo começa depois de atirar faca
    bool iniciarJogo = false; 
    bool fimJogo = false; // acaba quando vence

    // Célula alvo
    int alvoLinha = -1;
    int alvoColuna = -1;

    while (!WindowShouldClose()) {

        if(iniciarJogo && !fimJogo){
            timer += GetFrameTime();
        }

        // Detectar clique
        if (!fimJogo && !faca.emMovimento && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            for (int i = 0; i < LINHAS; i++) {
                for (int j = 0; j < COLUNAS; j++) {
                    if (!tabuleiro->matriz[i][j].visivel) continue;

                    float x = margemEsquerda + j * (tamanhoCelula + espacamento);
                    float y = margemSuperior + i * (tamanhoCelula + espacamento);
                    Rectangle celulaRect = {x, y, tamanhoCelula, tamanhoCelula};

                    if (CheckCollisionPointRec(mouse, celulaRect)) {
                        iniciarJogo = true;

                        alvoLinha = i;
                        alvoColuna = j;
                        // Pos inicial da faca na mão do palhaço
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

        // Atualizar faca
        atualizarFaca(&faca, velocidadeFaca, tempoFrameFaca);

        // Verificar se a faca chegou ao destino
        if (!faca.emMovimento && alvoLinha != -1 && alvoColuna != -1) {
            
            if (tabuleiro->matriz[alvoLinha][alvoColuna].tipo == ANIMAL) {
                fimJogo = true;

                revelarAnimais(tabuleiro);

                snprintf(mensagem, sizeof(mensagem), "FIM DE JOGO! VOCE ACERTOU UM ANIMAL.");
                corMensagem = RED;
            } else {
                snprintf(mensagem, sizeof(mensagem), "Boa! Area segura.");
                corMensagem = GREEN;
            }
            abrirCelula(tabuleiro, alvoLinha, alvoColuna); 

            if(verificarVitoria(tabuleiro)){
                fimJogo = true;
                snprintf(mensagem, sizeof(mensagem), "VITORIA!");
                corMensagem = GOLD;
            }

            alvoLinha = alvoColuna = -1; // reset
        }

        // Desenhar
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(fundo, 0, 0, WHITE);
        // desenhar placar
        DrawRectangle(0, 0, LARGURA_TELA, 50, Fade(BLACK, 0.8f));
        
        DrawText(TextFormat("TEMPO: %03.0f", timer), 20, 15, 30, WHITE);
        
        int larguraMsg = MeasureText(mensagem, 20);
        DrawText(mensagem, LARGURA_TELA/2 - larguraMsg/2, 20, 20, corMensagem);

        for (int i = 0; i < LINHAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                float x = margemEsquerda + j * (tamanhoCelula + espacamento);
                float y = margemSuperior + i * (tamanhoCelula + espacamento);
                Rectangle rect = {x, y, tamanhoCelula, tamanhoCelula};

                if (tabuleiro->matriz[i][j].visivel) {
                    DrawRectangleRounded(rect, 0.2f, 6, coresCelulas[i][j]);
                    DrawRectangleLinesEx(rect, 1.5f, BLACK);
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

        // Palhaço
        Texture2D spritePalhaco = faca.emMovimento ? palhacoJogando : palhacoParado;
        DrawTextureEx(spritePalhaco, posPalhaco, 0.0f, escalaPalhaco, WHITE);

        // Faca
        desenharFaca(&faca);

        EndDrawing();
    }

    // Limpar memória
    for (int i = 0; i < LINHAS; i++) free(coresCelulas[i]);
    free(coresCelulas);
    liberarTabuleiro(tabuleiro);

    UnloadTexture(fundo);
    UnloadTexture(palhacoParado);
    UnloadTexture(palhacoJogando);
    UnloadTexture(faca1);
    UnloadTexture(faca2);
    UnloadTexture(faca3);

    CloseWindow();
    return 0;
}
