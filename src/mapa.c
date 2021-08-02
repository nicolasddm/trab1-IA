#include "mapa.h"

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

int **pintaMapa(estado *state, int cor) {
    return state->mapa;
}

int *resolveMapa(int **mapa, int linhas, int colunas, int cores) {
    double cont = 0;
    estado *state = alocaEstado(mapa, cont);
    state->valorHeuristica = calculaHeuristica(mapa);
    state->valorF = calculaF(state);
    int i = 0;
    while (i < 2) {
        ++i;
        // Retirar o nó com menos f(n)
        estado* estadoMin = pegaMenorF(state);

        // Verificar se o nó está resolvido
        if (isSolved(estadoMin, linhas, colunas)) {
            return estadoMin->jogadas;
        };
        // Pegar a cor atual == mapa[0][0]
        int corAtual = estadoMin->mapa[0][0];
        ++cont;

        // Itera por todas as cores // Colocar todos os nós filhos do nó na fila
        for (int i = 0; i < cores; i++) {
            // Se a cor for a msm não faz nada
            if (i != corAtual) {
                // Se não tem vizinho com a cor não faz nada
                if (temAdjacencia(estadoMin, i)) {
                    // printf("Tem Adjacencia \n");
                    // Criar novo nó
                    estado* novoEstado = alocaEstado(estadoMin->mapa, cont);
                    // printf("aloca Novo estado \n");
                    
                    // Adicionar ao nó result a cor selecionada
                    novoEstado->jogadas = addJogada(estadoMin->jogadas, i, cont);
                    // printf("Adicionou jogadas \n");
                    
                    // Gerar o mapa do novo nó com a nova cor
                    novoEstado->mapa = pintaMapa(novoEstado, i);
                    // printf("pinta mapa fake\n");
                    
                    // Calcula h(n), g(n) e f(n)
                    novoEstado->valorG = cont;
                    novoEstado->valorHeuristica = calculaHeuristica(novoEstado->mapa);
                    novoEstado->valorF = calculaF(novoEstado);
                    // printf("Calcula valores \n");
    
                    // Adiciona nó na fila
                    addEstado(novoEstado, state); //PROBLEMA AQUI SOBRESCREVENDO
                    printf("Adiciona novo estado \n");
                    state = novoEstado;
                    printEstados(novoEstado);
                }
            }
        }
        retiraEstado(estadoMin);
    }

}