#include "mapa.h"
#define MAXT 1000100 // defino o limite de tamanho como 1000100

int **alocaMapa(int linhas, int colunas){
    // aloca um vetor de n ponteiros para linhas
    int **mapa = malloc(linhas * sizeof(int*));

    // aloca um vetor com todos os elementos da mapa
    mapa[0] = malloc(linhas * colunas * sizeof(int));
    
    // ajusta os demais ponteiros de linhas
    for (int i = 1; i < linhas; i++)
        mapa[i] = mapa[0] + i * colunas;

    return mapa;
}

int **leMapa(int linhas, int colunas) {
    
    int **mapa = alocaMapa(linhas, colunas);

    for(int i = 0; i < linhas; ++i)
        for (int j = 0; j < colunas; ++j)
            scanf("%d", &mapa[i][j]);

    return mapa;
}

void liberaMapa(int **mapa){
    free(mapa);
}

void printMapa(int **mapa, int linhas, int colunas){
    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            printf("%d ", mapa[i][j]);
        }
        printf("\n");
    }    
}

int isSolved(estado *state, int linhas, int colunas) {
    // printf("Verifica se o nó está resolvido\n");
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (state->mapa[i][j] != state->mapa[0][0])
                return 0;
        }
    }
    return 1;
}

void atribuiMapa(int **mapaOrigem, int **mapaDestino, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            mapaDestino[i][j] = mapaOrigem[i][j];
}

void printCoordenadasMapa(coordenada *coordAdicionadas, int tamCoords) {
    printf("Coordenadas já adicionadas: \n");
    for (int i = 0; i < tamCoords; i++) {
        printf("(%d, %d) ", coordAdicionadas[tamCoords].linha, coordAdicionadas[tamCoords].coluna);
    }
    printf("\n");
}


int **pintaMapa(estado *state, int cor, int linhas, int colunas) {
    // printf("######################### PINTA MAPA ##########################\n");
    state->mapa;
    int **mapa = alocaMapa(linhas, colunas);
    atribuiMapa(state->mapa, mapa, linhas, colunas);
    int corAnterior = mapa[0][0];
    
    int dx[4] = {0,-1,0,1};
    int dy[4] = {1,0,-1,0};
    
    coordenada *coord = alocaCoordenada(0, 0);

    coordenada *pilha[MAXT];
    int tamPilha = 0;
    pilha[0] = coord;

    coordenada *coordAdicionadas = malloc(sizeof(coordenada) * linhas * colunas);
    int tamCoords = 0;
    coordAdicionadas[0] = *coord;

    while (tamPilha >= 0) {
        coordenada *coordAtual = top(pilha, tamPilha);
        tamPilha = pop(pilha, tamPilha);
        mapa[coordAtual->linha][coordAtual->coluna] = cor;
        for (int i = 0; i < 4; ++i) {
            coordenada *coordProx = alocaCoordenada((coordAtual->linha + dx[i]), (coordAtual->coluna + dy[i]));
            if (coordenadaValida(coordProx, linhas, colunas)) {
                if(mapa[coordProx->linha][coordProx->coluna] == corAnterior) {
                    tamPilha = push(pilha, tamPilha, coordProx, coordAdicionadas, &tamCoords);
                }
            }
        }
    }
    // printMapa(mapa, linhas, colunas);
    return mapa;
}

int *resolveMapa(int **mapa, int linhas, int colunas, int cores) {
    double cont = 0;
    estado *state = alocaEstado(mapa, cont);
    state->valorHeuristica = calculaHeuristica(mapa, cores, linhas, colunas);
    state->valorF = calculaF(state);
    printf("H(n): %lf, g(n): %lf\n", state->valorHeuristica, state->valorF);
    int i = 0;
    while (i < 800) {
        ++i;
        // Retirar o nó com menos f(n)
        estado* estadoMin = pegaMenorF(state);

        // Verificar se o nó está resolvido
        if (isSolved(estadoMin, linhas, colunas)) {
            printMapa(estadoMin->mapa, linhas, colunas);
            printJogadas(estadoMin->jogadas, cont);

            return estadoMin->jogadas;
        };
        // Pegar a cor atual == mapa[0][0]
        int corAtual = estadoMin->mapa[0][0];
        ++cont;

        // Itera por todas as cores // Colocar todos os nós filhos do nó na fila
        for (int cor = 1; cor <= cores; cor++) {
            // Se a cor for a msm não faz nada
            if (cor != corAtual) {
                // Se não tem vizinho com a cor não faz nada
                if (temAdjacencia(estadoMin, cor, linhas, colunas)) {
                    // Criar novo nó
                    estado* novoEstado = alocaEstado(estadoMin->mapa, cont);
                    
                    // Adicionar ao nó result a cor selecionada
                    novoEstado->jogadas = addJogada(estadoMin->jogadas, cor, cont);
                    
                    // Gerar o mapa do novo nó com a nova cor
                    novoEstado->mapa = pintaMapa(estadoMin, cor, linhas, colunas);
                    
                    // Calcula h(n), g(n) e f(n)
                    novoEstado->valorG = 0;
                    novoEstado->valorHeuristica = calculaHeuristica(novoEstado->mapa, cores, linhas, colunas);
                    novoEstado->valorF = calculaF(novoEstado);
                    printf("H(n): %lf, g(n): %lf\n", novoEstado->valorHeuristica, novoEstado->valorF);
    
                    // Adiciona nó na fila
                    addEstado(novoEstado, state);
                    state = novoEstado;
                    // printEstados(novoEstado);
                }
            }
        }
        retiraEstado(estadoMin);
    }
    estado* estadoMin = pegaMenorF(state);
    printJogadas(estadoMin->jogadas, cont);
    return estadoMin->jogadas;
}