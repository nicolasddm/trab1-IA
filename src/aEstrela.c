#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>
#define MAXT 1000100 // defino o limite de tamanho como 1000100


double pegaRegioes(int **mapa, int cores, int linhas, int colunas) {
    // printf("######################### CALCULA HEURISTICA ##########################\n");
        
    int dx[4] = {0,-1,0,1};
    int dy[4] = {1,0,-1,0};
    
    coordenada *coord = alocaCoordenada(0, 0);
    coordenada *coordAdicionadas = (coordenada *) malloc(sizeof(coordenada) * linhas * colunas);
    int tamCoords = 0;
    coordAdicionadas[0] = *coord;
   
    coordenada *pilha[MAXT];
    int tamPilha = 0;
    pilha[0] = coord;

    int corInicial = mapa[0][0];
    int preenchido = 0;

    while (tamPilha >= 0) {
        coordenada *coordAtual = top(pilha, tamPilha);
        preenchido++;
        tamPilha = pop(pilha, tamPilha);
        for (int i = 0; i < 4; ++i) {
            coordenada *coordProx = alocaCoordenada((coordAtual->linha + dx[i]), (coordAtual->coluna + dy[i]));
            if (coordenadaValida(coordProx, linhas, colunas) && mapa[coordProx->linha][coordProx->coluna] == corInicial) {
                tamPilha = push(pilha, tamPilha, coordProx, coordAdicionadas, &tamCoords);
            }
        }
    }  
    printf("Falta preencher: %lf\n", ((double) ((linhas * colunas) - preenchido)) / ((double) linhas * colunas));
    return ((double) ((linhas * colunas) - preenchido));
}

void initDistancia(int **mapaDistancia, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            mapaDistancia[i][j] = 10000;
}

coordenada* pegaMenorDistancia(coordenada* coordenadas, int **mapaDistancia, int linhas, int colunas) {
    coordenada *coordenadaMenor = coordenadas;
    coordenada *coords = malloc(sizeof(coordenada));

    for (coords = coordenadas; NULL != coords; coords = coords->prox) {
        // printf("Coordenada: (%d,%d); distancia: %d\n", coords->linha, coords->coluna, mapaDistancia[coords->linha][coords->coluna]);
        if (mapaDistancia[coordenadaMenor->linha][coordenadaMenor->coluna] > mapaDistancia[coords->linha][coords->coluna]) {
            coordenadaMenor = coords;
        }
    }
    for (coords = coordenadas; NULL != coords; coords = coords->prev) {
        if (mapaDistancia[coordenadaMenor->linha][coordenadaMenor->coluna] > mapaDistancia[coords->linha][coords->coluna]) {
            coordenadaMenor = coords;
        }
    }

    // printf("Valor da menor Coordenada: %d\n", mapaDistancia[coordenadaMenor->linha][coordenadaMenor->coluna]);
    return coordenadaMenor;
}

double maiorDistancia(int **mapaDistancia, int linhas, int colunas) {
    int maiorDistancia = 0;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if(maiorDistancia < mapaDistancia[i][j]) {
                maiorDistancia = mapaDistancia[i][j];
            }
        }
    }
    // printf("maiorDistancia: %d\n", maiorDistancia);
    return (double) maiorDistancia;       
}

double calculaHeuristica(int **mapa, int cores, int linhas, int colunas) {
    // printf("######################### CALCULA HEURISTICA ##########################\n");
    // if (linhas > 80 && colunas > 80) {
    //     return (pegaRegioes(mapa, cores, linhas, colunas) / cores);
    // }
    
    int **mapaDistancia = alocaMapa(linhas, colunas);
    int **mapaDistancia2 = alocaMapa(linhas/2, colunas/2);
    initDistancia(mapaDistancia, linhas, colunas);
    initDistancia(mapaDistancia2, linhas/2, colunas/2);
    
    int dx[4] = {0,-1,0,1};
    int dy[4] = {1,0,-1,0};
    
    coordenada *coord = alocaCoordenada(0, 0);
    int tamFila = 0;
    
    coordenada *coordAdicionadas = (coordenada *) malloc(sizeof(coordenada) * linhas * colunas);
    int tamCoords = 0;
    coordAdicionadas[0] = *coord;
    mapaDistancia[0][0] = 0;
    while (tamFila >= 0) {
        coordenada *coordAtual = pegaMenorDistancia(coord, mapaDistancia, linhas, colunas);
        int corAtual = mapa[coordAtual->linha][coordAtual->coluna];
        for (int i = 0; i < 4; ++i) {
            coordenada *coordProx = alocaCoordenada((coordAtual->linha + dx[i]), (coordAtual->coluna + dy[i]));
            if (coordenadaValida(coordProx, linhas, colunas)) {
                
                if(addNextCoordenada(coordProx, coord, coordAdicionadas, &tamCoords, tamFila)){
                    tamFila++;
                    coord = coordProx;
                }
                if(mapa[coordProx->linha][coordProx->coluna] == corAtual) {
                    if (mapaDistancia[coordAtual->linha][coordAtual->coluna] < mapaDistancia[coordProx->linha][coordProx->coluna]) {
                        mapaDistancia[coordProx->linha][coordProx->coluna] = mapaDistancia[coordAtual->linha][coordAtual->coluna];
                    }
                } else {
                    if((mapaDistancia[coordAtual->linha][coordAtual->coluna] + 1) < mapaDistancia[coordProx->linha][coordProx->coluna]){
                        mapaDistancia[coordProx->linha][coordProx->coluna] = mapaDistancia[coordAtual->linha][coordAtual->coluna] + 1;
                    }
                }
            } 
        }
        if((coord->linha == linhas/2 && coord->coluna == colunas/2) && mapaDistancia[coord->linha][coord->coluna] != 0) {
            printf("######################################## CHEGOU NO MEIO #######################################");
            break;
        } else if(((coord->linha == (linhas/2) + ((linhas/2)/2)) && (coord->coluna == (colunas/2) + ((colunas/2)/2))) && mapaDistancia[coord->linha][coord->coluna] != 0) {
            printf("######################################## CHEGOU NO 3/4 #######################################");
            break;
        }
        // printMapa(mapaDistancia, linhas, colunas);
        if(coord->linha == coordAtual->linha && coord->coluna == coordAtual->coluna) {
            if (coordAtual->prox != NULL) {
                coord = coordAtual->prox;
            } else if(coordAtual->prev != NULL) {
                coord = coordAtual->prev;
            }
        }
        
        retiraCoordenada(coordAtual);
        // printf("coord: (%d, %d)\n", coord->linha, coord->coluna);
        printCoordenadas(coord);
        tamFila--;
    }
    if(mapaDistancia[linhas/2][colunas/2] != 0) {
        return (mapaDistancia[linhas/2][colunas/2] + (pegaRegioes(mapa, cores, linhas, colunas) / cores));
    }
    if(mapaDistancia[(linhas/2) + ((linhas/2)/2)][(colunas/2) + ((colunas/2)/2)] != 0) {
        return (mapaDistancia[(linhas/2) + ((linhas/2)/2)][(colunas/2) + ((colunas/2)/2)] + (pegaRegioes(mapa, cores, linhas, colunas) / cores));
    }
    if(mapaDistancia[linhas-1][colunas-1] != 0) {
        return (mapaDistancia[linhas-1][colunas-1] + (pegaRegioes(mapa, cores, linhas, colunas) / cores));
    }
    
    return (maiorDistancia(mapaDistancia, linhas, colunas) + (pegaRegioes(mapa, cores, linhas, colunas) / cores));
}

double calculaF(estado *state) {
    return state->valorHeuristica + state->valorG;
}

estado *pegaMenorF(estado *estados) {
    estado *estadoMenor = estados;
    estado *state;

    for (state = estados; NULL != state; state = state->prox) {
        if (estadoMenor->valorF > state->valorF) {
            estadoMenor = state;
        }
    }

    // printf("Valor do menor Estado: %lf\n", estadoMenor->valorF);
    return estadoMenor;
}

int *addJogada(int *jogadas, int cor, int tamJogadas) {
    int *novasJogadas = (int *) malloc(sizeof(int) * (tamJogadas+1));
    // printf("Novas jogadas: ");
    int i = 0;
    for (i = 0; i < (tamJogadas); ++i) {
        novasJogadas[i] = jogadas[i];
        // printf("i: %d, jogadas[i]: %d, novasJogadas[i]: %d \n", i, jogadas[i], novasJogadas[i]);
    }
    novasJogadas[i] = cor;
    // printf("i: %d, cor: %d, novasJogadas[i]: %d \n", i, cor, novasJogadas[i]);
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
    int **mapa = state->mapa;
    int corAtual = mapa[0][0];

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