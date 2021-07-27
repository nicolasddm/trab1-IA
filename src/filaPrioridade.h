#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int **mapa;
    int *jogadas;
    double valorHeuristica;
    double valorG;
    int prioridade;
    
} estado;

typedef struct {
    estado *topo;
    estado *cauda;
    
} filaPrioridade;

filaPrioridade *alocaFila(int **mapa);

estado *alocaEstado(int** mapa);