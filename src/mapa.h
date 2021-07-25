#include <stdio.h>
#include <stdlib.h>

// funções de tratamento do mapa de entrada
int **alocaMapa(int linhas, int colunas);

void liberaMapa(int **mapa);

int **leMapa(int linhas, int colunas);

void printMapa(int **mapa, int linhas, int colunas);