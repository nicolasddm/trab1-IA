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
    coords->linha = 0;
    coords->coluna = 0;
    coords->linha = lin;
    coords->coluna = col;
    coords->prox = NULL;
    coords->prev = NULL;
    return coords;
}

int contemCoordenada(coordenada* coord, coordenada* coordAdicionadas, int tamCoords) {
    for(int i = 0; i <= tamCoords; ++i){
        if ((coordAdicionadas[i].linha == coord->linha) && (coordAdicionadas[i].coluna == coord->coluna)) {
            return 1;
        }
    }
    return 0;
}

void addCoordenada(coordenada* arrCoords, coordenada* novaCoord, int tamCoords){
    arrCoords[tamCoords] = *novaCoord;
    // printf("AddCoordenada (%d, %d)\n", arrCoords[tamCoords].linha, arrCoords[tamCoords].coluna);
}


int addNextCoordenada(coordenada *novaCoord, coordenada *coord, coordenada* coordAdicionadas, int *tamCoords, int tamFila) {
    if (!contemCoordenada(novaCoord, coordAdicionadas, *tamCoords)) {
        novaCoord->prox = coord;
        coord->prev = novaCoord;
        novaCoord->prev = NULL;
        *tamCoords += 1;
        addCoordenada(coordAdicionadas, novaCoord, *tamCoords);
        return 1;
    }
    return 0;
}


void retiraCoordenada(coordenada *coord) {
    // printf("retira coordenada: (%d,%d)\n", coord->linha, coord->coluna);
    // printf("GET PREV\n");
    coordenada *prevCoord = coord->prev;
    // printf("GET PROX\n");
    coordenada *proxCoord = coord->prox;
    
    if (prevCoord != NULL) {
        prevCoord->prox = proxCoord;
    }

    if (proxCoord != NULL) {
        proxCoord->prev = prevCoord;
    }
    
    coord->prev = NULL;
    coord->prox = NULL;

    free(coord);
}

void addEstado(estado *newState, estado *state) {
    newState->prox = state;
    state->prev = newState;
    newState->prev = NULL;
}

void retiraEstado(estado *state) {
    // printf("state: %lf\n", state->valorF);
    // printf("GET PREV\n");
    estado *prevEstado = state->prev;
    // printf("GET PROX\n");
    estado *proxEstado = state->prox;
    
    if (prevEstado != NULL) {
        prevEstado->prox = proxEstado;
    }

    if (proxEstado != NULL) {
        proxEstado->prev = prevEstado;
    }
    
    state->prev = NULL;
    state->prox = NULL;

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

void printCoordenadas(coordenada *coords) {
    coordenada *coord;
    for (coord = coords; NULL != coord; coord = coord->prox) {
        // printf("Valor da Coordenada: (%d,%d) \n", coord->linha, coord->coluna);
    }
    for (coord = coords->prev; NULL != coord; coord = coord->prev) {
        // printf("Valor da Coordenada: (%d,%d) \n", coord->linha, coord->coluna);
    }
}