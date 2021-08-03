#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "aEstrela.h"


// funções de tratamento do mapa de entrada
int **alocaMapa(int linhas, int colunas);

void liberaMapa(int **mapa);

int **leMapa(int linhas, int colunas);

void printMapa(int **mapa, int linhas, int colunas);

int isSolved(estado *state, int linhas, int colunas);

int **pintaMapa(estado *state, int cor, int linhas, int colunas);

int *resolveMapa(int **mapa, int linhas, int colunas, int cores);