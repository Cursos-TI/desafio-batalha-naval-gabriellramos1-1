#include <stdio.h>
#include <string.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

// Símbolos no tabuleiro
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Mostra o tabuleiro na tela
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA) printf("~ ");       // água
            else if (tabuleiro[i][j] == NAVIO) printf("N ");  // navio
            else if (tabuleiro[i][j] == HABILIDADE) printf("* ");  // área afetada
        }
        printf("\n");
    }
    printf("\n");
}

// Cria a forma de cone (um V apontando pra baixo)
void criarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    memset(matriz, 0, TAM_HABILIDADE * TAM_HABILIDADE * sizeof(int));
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = meio - i; j <= meio + i; j++) {
            if (j >= 0 && j < TAM_HABILIDADE)
                matriz[i][j] = 1; // marca onde a habilidade atinge
        }
    }
}

// Cria uma cruz (linha e coluna central marcadas)
void criarCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    memset(matriz, 0, TAM_HABILIDADE * TAM_HABILIDADE * sizeof(int));
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        matriz[meio][i] = 1; // linha do meio
        matriz[i][meio] = 1; // coluna do meio
    }
}

// Cria um octaedro (losango)
void criarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    memset(matriz, 0, TAM_HABILIDADE * TAM_HABILIDADE * sizeof(int));
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(meio - i) + abs(meio - j) <= meio) {
                matriz[i][j] = 1; // forma o losango
            }
        }
    }
}

// Aplica a habilidade no tabuleiro, respeitando limites e mantendo navios
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    int offset = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linha = origemLinha + i - offset;
            int coluna = origemColuna + j - offset;

            // só aplica se estiver dentro do tabuleiro e não for navio
            if (linha >= 0 && linha < TAM_TABULEIRO && coluna >= 0 && coluna < TAM_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] != NAVIO) {
                    tabuleiro[linha][coluna] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // Começa com tudo como água
    memset(tabuleiro, AGUA, sizeof(tabuleiro));

    // Coloca alguns navios no mapa
    tabuleiro[2][2] = NAVIO;
    tabuleiro[1][4] = NAVIO;
    tabuleiro[4][4] = NAVIO;

    // Cria as formas das habilidades
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplica cada habilidade numa posição do tabuleiro
    aplicarHabilidade(tabuleiro, cone, 2, 5);       // Cone na parte de cima
    aplicarHabilidade(tabuleiro, cruz, 6, 2);       // Cruz mais à esquerda
    aplicarHabilidade(tabuleiro, octaedro, 5, 7);   // Octaedro na direita

    // Mostra o resultado
    exibirTabuleiro(tabuleiro);

    return 0;
}