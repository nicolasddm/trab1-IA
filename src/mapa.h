#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "filaPrioridade.h"

// funções de tratamento do mapa de entrada
int **alocaMapa(int linhas, int colunas);

void liberaMapa(int **mapa);

int **leMapa(int linhas, int colunas);

void printMapa(int **mapa, int linhas, int colunas);

int *resolveMapa(int **mapa, int linhas, int colunas);