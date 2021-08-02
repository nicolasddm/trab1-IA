#include "filaPrioridade.h"

estado *alocaEstado(int **mapa, int jogadasTam) {
    estado *state = (estado *) malloc(sizeof(estado));
    if (state == NULL){
        fprintf(stderr, "Falha na alocação de memória\n");
        exit(4);
    }
    state->mapa = mapa;
    state->jogadas = (int *) malloc(sizeof(int) * (jogadasTam+1));
    state->valorHeuristica = 0.0;
    state->valorG = 0.0;
    state->valorF = 0;
    state->prox = NULL;
    state->prev = NULL;

    return state;
}

void addEstado(estado *newState, estado *state) {
    printf("state: %lf\n", state->valorF);
    printf("newState: %lf\n", newState->valorF);
    newState->prox = state;
    state->prev = newState;
    newState->prev = NULL;
}

void retiraEstado(estado *state) {
    printf("state: %lf\n", state->valorF);
    printf("GET PREV\n");
    if (state->prev != NULL) {
        estado *prevEstado = state->prev;
        printf("prevEstado: %lf\n", prevEstado->valorF);
    }
    

    
    if (state->prox != NULL) {
        estado *proxEstado = state->prox;
        printf("proxEstado: %lf\n", proxEstado->valorF);
    }
    
    

    prevEstado->prox = proxEstado;
    proxEstado->prev = prevEstado;
    state->prev = state->prox = NULL;
    free(state);
}

void printEstados(estado *estados) {
    estado *state;
    for (state = estados; NULL != state; state = state->prox) {
        printf("Valor F do Estado: %lf \n", state->valorF);
    }
    for (state = estados->prev; NULL != state; state = state->prev) {
        printf("Valor F do Estado: %lf \n", state->valorF);
    }
}