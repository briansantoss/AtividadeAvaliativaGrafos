#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INFINITO INT_MAX

// Estrutura para uma aresta na lista de adjacência
typedef struct Aresta {
    int destino;
    int peso; // tempo médio
    struct Aresta* prox;
} Aresta;

// Estrutura do grafo: lista de adjacência
typedef struct {
    Aresta* adjacentes;
} Vertice;

Vertice grafo[MAX_VERTICES];
int numVertices = 0;

// Função para adicionar uma aresta dirigida e ponderada
void adicionarAresta(int origem, int destino, int peso) {
    Aresta* nova = malloc(sizeof(Aresta));
    nova->destino = destino;
    nova->peso = peso;
    nova->prox = grafo[origem].adjacentes;
    grafo[origem].adjacentes = nova;
}

// Função utilitária para encontrar o vértice com menor distância ainda não visitado
int encontrarMenorDistancia(int dist[], bool visitado[]) {
    int min = INFINITO, indiceMin = -1;
    for (int i = 0; i < numVertices; i++) {
        if (!visitado[i] && dist[i] < min) {
            min = dist[i];
            indiceMin = i;
        }
    }
    return indiceMin;
}

// Algoritmo de Dijkstra
void dijkstra(int origem, int destino) {
    int dist[MAX_VERTICES];
    int anterior[MAX_VERTICES];
    bool visitado[MAX_VERTICES];

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INFINITO;
        anterior[i] = -1;
        visitado[i] = false;
    }

    dist[origem] = 0;

    for (int i = 0; i < numVertices - 1; i++) {
        int u = encontrarMenorDistancia(dist, visitado);
        if (u == -1) break;
        visitado[u] = true;

        for (Aresta* adj = grafo[u].adjacentes; adj != NULL; adj = adj->prox) {
            int v = adj->destino;
            int peso = adj->peso;

            if (!visitado[v] && dist[u] != INFINITO && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                anterior[v] = u;
            }
        }
    }

    // Exibe o resultado
    if (dist[destino] == INFINITO) {
        printf("Sem caminho entre %d e %d\n", origem, destino);
    } else {
        printf("Menor tempo entre %d e %d: %d minutos\n", origem, destino, dist[destino]);

        // Reconstrói o caminho
        printf("Caminho: ");
        int caminho[MAX_VERTICES];
        int tamanho = 0, atual = destino;
        while (atual != -1) {
            caminho[tamanho++] = atual;
            atual = anterior[atual];
        }
        for (int i = tamanho - 1; i >= 0; i--)
            printf("%d%s", caminho[i], i == 0 ? "\n" : " -> ");
    }
}

// Exemplo simples
void carregarGrafoDeExemplo() {
    numVertices = 6;

    adicionarAresta(0, 1, 10);
    adicionarAresta(0, 2, 15);
    adicionarAresta(1, 3, 12);
    adicionarAresta(2, 4, 10);
    adicionarAresta(3, 5, 2);
    adicionarAresta(4, 5, 5);
}

int main() {
    carregarGrafoDeExemplo();

    int origem, destino;

    printf("Sistema de Rotas Inteligentes\n");
    printf("Total de estacoes: %d (0 a %d)\n", numVertices, numVertices - 1);
    printf("Digite o numero da estacao de origem: ");
    scanf("%d", &origem);
    printf("Digite o numero da estação de destino: ");
    scanf("%d", &destino);

    if (origem >= 0 && origem < numVertices && destino >= 0 && destino < numVertices) {
        dijkstra(origem, destino);
    } else {
        printf("Entrada invalida.\n");
    }

    return 0;
}
