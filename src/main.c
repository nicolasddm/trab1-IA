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
            liberaMapa(mapa);
        }
    }

    return 0;
}