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
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (state->mapa[i][j] != state->mapa[0][0]) 
                return 0;
        }
    }
    return 1;
}

int coordenadaValida(coordenada *coordProx, int linhas, int colunas) {
    return (coordProx->linha >= 0 && coordProx->linha < linhas && coordProx->coluna >= 0 && coordProx->coluna < colunas);
}

int **pintaMapa(estado *state, int cor, int linhas, int colunas) {
    int corAnterior = state->mapa[0][0];
    printf("cor atual %d\n", corAnterior);
    int dx[4] = {0,-1,0,1};
    int dy[4] = {1,0,-1,0};
    coordenada *pilha[MAXT];
    int tamPilha = -1;
    coordenada *coord = alocaCoordenada(0, 0);
    tamPilha = push(pilha, tamPilha, coord);
    printf("adiciona coordenada na pilha\n");
    while (tamPilha >= 0) {
        coordenada *coordAtual = top(pilha, tamPilha);
        printf("coordenadaAtual: (%d, %d)\n", coordAtual->linha, coordAtual->coluna);
        tamPilha = pop(pilha, tamPilha);
        printf("Retiradoooooooo\n");
        coordAtual = top(pilha, tamPilha);
        printf("coordenadaAtual2: (%d, %d), tamPilha: %d\n", coordAtual->linha, coordAtual->coluna, tamPilha);
        state->mapa[coordAtual->linha][coordAtual->coluna] = cor;
        printf("Recebe a nova cor %d\n", state->mapa[coordAtual->linha][coordAtual->coluna]);
        for (int i = 0; i < 4; ++i) {
            coordenada *coordProx = alocaCoordenada((coordAtual->linha + dx[i]), (coordAtual->coluna + dy[i]));
            
            if (coordenadaValida(coordProx, linhas, colunas)) {
                printf("coordenadaValida\n");
                if(*state->mapa[coordProx->linha, coordProx->coluna] == corAnterior) {
                    printf("adiciona nova coordenada\n");
                    tamPilha = push(pilha, tamPilha, coordProx);
                }
            }
        }
    }
    printMapa(state->mapa, linhas, colunas);
    
    return state->mapa;
}

int *resolveMapa(int **mapa, int linhas, int colunas, int cores) {
    double cont = 0;
    estado *state = alocaEstado(mapa, cont);
    state->valorHeuristica = calculaHeuristica(mapa);
    state->valorF = calculaF(state);
    int i = 0;
    while (i < 7) {
        ++i;
        // Retirar o nó com menos f(n)
        estado* estadoMin = pegaMenorF(state);

        // Verificar se o nó está resolvido
        printf("Verificar se o nó está resolvido\n");
        if (isSolved(estadoMin, linhas, colunas)) {
            return estadoMin->jogadas;
        };
        // Pegar a cor atual == mapa[0][0]
        int corAtual = estadoMin->mapa[0][0];
        printf("Pegar a cor atual == mapa[0][0]: %d\n", corAtual);
        ++cont;

        // Itera por todas as cores // Colocar todos os nós filhos do nó na fila
        for (int i = 1; i <= cores; i++) {
            // Se a cor for a msm não faz nada
            if (i != corAtual) {
                // Se não tem vizinho com a cor não faz nada
                printf("Se não tem vizinho com a cor não faz nada\n");
                if (temAdjacencia(estadoMin, i)) {
                    printf("Tem Adjacencia \n");
                    // Criar novo nó
                    estado* novoEstado = alocaEstado(estadoMin->mapa, cont);
                    printf("aloca Novo estado \n");
                    
                    // Adicionar ao nó result a cor selecionada
                    novoEstado->jogadas = addJogada(estadoMin->jogadas, i, cont);
                    printf("Adicionou jogadas \n");
                    
                    // Gerar o mapa do novo nó com a nova cor
                    printf("Gerar o mapa do novo nó com a nova cor\n");
                    novoEstado->mapa = pintaMapa(novoEstado, i, linhas, colunas);
                    
                    // Calcula h(n), g(n) e f(n)
                    novoEstado->valorG = cont;
                    novoEstado->valorHeuristica = calculaHeuristica(novoEstado->mapa);
                    novoEstado->valorF = calculaF(novoEstado);
                    printf("Calcula valores \n");
    
                    // Adiciona nó na fila
                    addEstado(novoEstado, state);
                    printf("Adiciona novo estado \n");
                    state = novoEstado;
                    printEstados(novoEstado);
                }
            }
        }
        retiraEstado(estadoMin);
    }
    estado* estadoMin = pegaMenorF(state);
    printJogadas(estadoMin->jogadas, cont);
    return estadoMin->jogadas;
}