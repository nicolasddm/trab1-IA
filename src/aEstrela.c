#include "aEstrela.h"

double calculaHeuristica(int **mapa) {
    //calcula heuristica
    return 1.0;
}

double calculaF(estado *state) {
    return state->valorG + state->valorHeuristica;
}

estado *pegaMenorF(estado *estados) {
    estado *estadoMenor = estados;
    estado *state;

    for (state = estados; NULL != state; state = state->prox) {
        printf("Valor do estado: %lf\n", state->valorF);
        if (estadoMenor->valorF > state->valorF) {
            estadoMenor = state;
        }
    }

    printf("Valor do menor Estado: %lf\n", estadoMenor->valorF);
    return estadoMenor;
}

int *addJogada(int *jogadas, int cor, int tamJogadas) {
    int *novasJogadas = (int *) malloc(sizeof(int) * (tamJogadas+1));
    printf("Novas jogadas: ");
    int i = 0;
    for (i = 0; i < (tamJogadas); ++i) {
        novasJogadas[i] = jogadas[i];
        printf("i: %d, jogadas[i]: %d, novasJogadas[i]: %d \n", i, jogadas[i], novasJogadas[i]);
    }
    novasJogadas[i] = cor;
    printf("i: %d, cor: %d, novasJogadas[i]: %d \n", i, cor, novasJogadas[i]);
    printJogadas(novasJogadas, tamJogadas);
    return novasJogadas;
}

void printJogadas(int* jogadas, int tamJogadas) {
    printf("Print Jogadas: \n");
    printf("tamJogadas: %d\n", tamJogadas);
    for (int i = 0; i < (tamJogadas+1); ++i) {
        printf("%d ", jogadas[i]);
    }
    printf("\n");
}

int temAdjacencia(estado* state, int cor) {
    // Verificar se tem adjacencia
    return 1;
}