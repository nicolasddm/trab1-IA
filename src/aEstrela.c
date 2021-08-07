#include "aEstrela.h"
#include <stdio.h>
#include <stdlib.h>
#define MAXT 1000100 // defino o limite de tamanho como 1000100


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

int coordenadaValida(coordenada *coordProx, int linhas, int colunas) {
    return (coordProx->linha >= 0 && coordProx->linha < linhas && coordProx->coluna >= 0 && coordProx->coluna < colunas);
}

int temAdjacencia(estado* state, int cor, int linhas, int colunas) {
    printf("######################### TEM ADJACENCIA ##########################\n");
    int **mapa = state->mapa;
    int corAtual = mapa[0][0];
    printf("cor atual %d; cor iterada: %d\n", corAtual, cor);

    int dx[4] = {0,-1,0,1};
    int dy[4] = {1,0,-1,0};

    coordenada *coord = alocaCoordenada(0, 0);

    coordenada *pilha[MAXT];
    int tamPilha = 0;
    pilha[0] = coord;
    
    coordenada *coordAdicionadas = (coordenada *) malloc(sizeof(coordenada) * linhas * colunas);
    int tamCoords = 0;
    coordAdicionadas[0] = *coord;

    while(tamPilha >= 0) {
        coordenada *coordAtual = top(pilha, tamPilha);
        // printf("coordenadaAtual: (%d, %d)\n", coordAtual->linha, coordAtual->coluna);
        tamPilha = pop(pilha, tamPilha);
        
        for (int i = 0; i < 4; ++i) {
            coordenada *coordProx = alocaCoordenada((coordAtual->linha + dx[i]), (coordAtual->coluna + dy[i]));
            // printf("linha: %d, coluna: %d\n",coordAtual->linha, coordAtual->coluna);
            if (coordenadaValida(coordProx, linhas, colunas)) {
                // printf("coordenadaValida; corA: %d, corAtual: %d, cor: %d\n", mapa[coordProx->linha][coordProx->coluna], corAtual, cor);
                if (mapa[coordProx->linha][coordProx->coluna] == corAtual) {
                    // printf("adiciona nova coordenada\n");
                    tamPilha = push(pilha, tamPilha, coordProx, coordAdicionadas, &tamCoords);
                } else if(mapa[coordProx->linha][coordProx->coluna] == cor) {
                    return 1;
                }
            }
        }
    }
    return 0;
}