#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

int main() {
    char c;
    int linhas, colunas, cores;
    while(fscanf(stdin, "%c", &c) != EOF){
        if (c >= 48 && c <= 57){
            ungetc(c, stdin);
            scanf("%d", &linhas);
            scanf("%d", &colunas);
            scanf("%d", &cores);
            
            int **mapa = leMapa(linhas, colunas);
            printMapa(mapa, linhas, colunas);

            double tempo;
            tempo = timestamp();
            
            // TODO - Adicionar algoritmo A*
            int* solucao = resolveMapa(mapa, linhas, colunas, cores);
            
            tempo = timestamp() - tempo;
            printf("Resolve Mapa Tempo: %lf ms\n", tempo);
            
            // TODO - Adicionar estratégia de calcular h(n)
                // quantos elementos faltam / número de cores restantes.
            liberaMapa(mapa);
        }
    }

    return 0;
}