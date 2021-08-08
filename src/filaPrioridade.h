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

typedef struct coordenada{
    int linha;
    int coluna;
    struct coordenada *prox;
    struct coordenada *prev;
    
} coordenada;

estado *alocaEstado(int** mapa, int jogadasTam);

coordenada *alocaCoordenada(int lin, int col);

int contemCoordenada(coordenada* coord, coordenada* coordAdicionadas, int tamCoords);

void addCoordenada(coordenada* arrCoords, coordenada* coord, int tamPilha);

int addNextCoordenada(coordenada *novaCoord, coordenada *coord, coordenada* coordAdicionadas, int *tamCoords, int tamFila);

void addEstado(estado *newState, estado *state);

void retiraCoordenada(coordenada *coord);

void retiraEstado(estado *state);

void printEstados(estado *estados);

void printCoordenadas(coordenada *coords);