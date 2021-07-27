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

int *resolveMapa(int **mapa, int linhas, int colunas) {
    
    filaPrioridade *fila = alocaFila(mapa);

    

}