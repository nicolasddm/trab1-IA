#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

double calculaHeuristica(int **mapa);

double calculaF(estado *state);

estado *pegaMenorF(estado *estados);

int *addJogada(int *jogadas, int cor, int tamJogadas);

void printJogadas(int* jogadas, int tamJogadas);

int coordenadaValida(coordenada *coordProx, int linhas, int colunas);

int temAdjacencia(estado* state, int cor, int linhas, int colunas);