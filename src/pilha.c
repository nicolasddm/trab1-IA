#include "pilha.h"

int contemCoordenada(coordenada* coord, coordenada* coordAdicionadas, int tamCoords) {
    for(int i = 0; i <= tamCoords; ++i){
        if ((coordAdicionadas[i].linha == coord->linha) && (coordAdicionadas[i].coluna == coord->coluna)) {
            printf("Já foi\n");
            return 1;
        }
    }
    return 0;
}

int push(coordenada** pilha, int tam, coordenada* coord, coordenada* coordAdicionadas, int *tamCoords) {
   
    if (!contemCoordenada(coord, coordAdicionadas, *tamCoords)) {
        ++tam;
        pilha[tam] = coord;
        *tamCoords += 1;
        addCoordenada(coordAdicionadas, coord, *tamCoords);
    }
    return tam;
}

int pop(coordenada** pilha, int tam) {
    tam--;
    return tam;
}

coordenada *top(coordenada** pilha, int tam) {
    return pilha[tam];
}