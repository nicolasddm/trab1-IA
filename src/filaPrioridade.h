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

typedef struct {
    int linha;
    int coluna;
    
} coordenada;

estado *alocaEstado(int** mapa, int jogadasTam);

coordenada *alocaCoordenada(int lin, int col);

void addCoordenada(coordenada* arrCoords, coordenada* coord, int tamPilha);

void addEstado(estado *newState, estado *state);

void printEstados(estado *estados);

void retiraEstado(estado *state);