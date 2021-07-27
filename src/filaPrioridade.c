#include "filaPrioridade.h"

filaPrioridade *alocaFila(int **mapa) {
    filaPrioridade *fila = (filaPrioridade *) malloc(sizeof(filaPrioridade));
    estado *state = alocaEstado(mapa);
    fila->topo = state;
}

estado *alocaEstado(int **mapa) {
    estado *state = (estado *) malloc(sizeof(estado));
    state->mapa = mapa;
    state->jogadas = (int *) malloc(sizeof(int));
    state->valorHeuristica = 0.0;
    state->valorG = 0.0;
    state->prioridade = 0;

    return state;
}