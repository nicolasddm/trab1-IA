#include "pilha.h"

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