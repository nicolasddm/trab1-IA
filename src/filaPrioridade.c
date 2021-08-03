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

coordenada *alocaCoordenada(int lin, int col) {
    coordenada *coords = (coordenada *) malloc(sizeof(coordenada));

    coords->linha = lin;
    coords->coluna = col;
    printf("Aloca coordenada (%d, %d)\n", coords->linha, coords->coluna);

    return coords;
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
    estado *prevEstado = state->prev;
    printf("GET PROX\n");
    estado *proxEstado = state->prox;
    
    if (prevEstado != NULL) {
        printf("Ajusta ponteiros 1\n");
        prevEstado->prox = proxEstado;
        printf("prevEstado: %lf\n", prevEstado->valorF);   
    }

    if (proxEstado != NULL) {
        printf("Ajusta ponteiros 2\n");
        proxEstado->prev = prevEstado;
        printf("proxEstado: %lf\n", proxEstado->valorF);
    }
    
    printf("Ajusta ponteiros 3\n");
    state->prev = NULL;
    state->prox = NULL;
    printf("free state\n");
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