#include <stdlib.h>
#include <stdio.h>

typedef struct estado {
    int **mapa;
    int *jogadas;
    double valorHeuristica;
    double valorG;
    double valorF;
    struct estado *prox;
    struct estado *prev;
    
} estado;

estado *alocaEstado(int** mapa, int jogadasTam);

void addEstado(estado *newState, estado *state);

void printEstados(estado *estados);

void retiraEstado(estado *state);