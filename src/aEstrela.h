#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

double calculaHeuristica(int **mapa);

double calculaF(estado *state);

estado *pegaMenorF(estado *estados);

int *addJogada(int *jogadas, int cor, int tamJogadas);

void printJogadas(int* jogadas, int tamJogadas);

int temAdjacencia(estado* state, int cor);