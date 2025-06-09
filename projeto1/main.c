#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 3
#define COLS 3
#define VERTICES (ROWS * COLS)


char labirinto[ROWS][COLS] = {
    {'S', '.', '#'},
    {'.', '.', '.'},
    {'#', '.', 'E'}
};

int matrizAdj[VERTICES][VERTICES];

// Transforma o índice (i, j) da posição da matriz em um índice k num vetor
int getIndex(int i, int j) { return i * COLS + j; }

/**
 * Retorna verdadeiro caso a posição (i, j) seja válida na matriz
 * e falso caso contrário 
 */
bool posValida(int i, int j) {
    return i >= 0 && i < ROWS && j >= 0 && j < COLS && labirinto[i][j] != '#';
}

// A matriz de adjacência é gerada dinamicamente dado o labirinto
void construirGrafo() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (labirinto[i][j] == '#') continue;

            int atual = getIndex(i, j);

            // Trata adequadamente posição imediatamente acima
            if (posValida(i - 1, j))
                matrizAdj[atual][getIndex(i - 1, j)] = 1;

            // Trata adequadamente posição imediatamente abaixo
            if (posValida(i + 1, j))
                matrizAdj[atual][getIndex(i + 1, j)] = 1;

            // Trata adequadamente posição imediatamente a esquerda
            if (posValida(i, j - 1))
                matrizAdj[atual][getIndex(i, j - 1)] = 1;

            // Trata adequadamente posição imediatamente a direita
            if (posValida(i, j + 1))
                matrizAdj[atual][getIndex(i, j + 1)] = 1;
        }
    }
}

void BFS(int inicio) {
    bool visitado[VERTICES] = {false};
    int fila[VERTICES];
    int frente = 0, tras = 0;

    fila[tras++] = inicio;
    visitado[inicio] = true;

    printf("BFS: ");

    while (frente < tras) {
        int atual = fila[frente++];
        printf("%d ", atual);

        for (int i = 0; i < VERTICES; i++) {
            if (matrizAdj[atual][i] && !visitado[i]) {
                fila[tras++] = i;
                visitado[i] = true;
            }
        }
    }

    printf("\n");
}

void DFSUtil(int atual, bool* visitado) {
    visitado[atual] = true;
    printf("%d ", atual);

    for (int i = 0; i < VERTICES; i++) {
        if (matrizAdj[atual][i] && !visitado[i]) {
            DFSUtil(i, visitado);
        }
    }
}

void DFS(int inicio) {
    bool visitado[VERTICES] = {false};
    printf("DFS: ");
    DFSUtil(inicio, visitado);
    printf("\n");
}

// Função utilitária para localização da posição de início ("Start") e fim ("End")
int encontrarIndice(char alvo) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (labirinto[i][j] == alvo)
                return getIndex(i, j);
    return -1;
}

int main() {
    construirGrafo();

    int inicio = encontrarIndice('S');
    int fim = encontrarIndice('E');

    printf("Inicio: %d, Fim: %d\n", inicio, fim);

    BFS(inicio);
    DFS(inicio);

    return 0;
}
