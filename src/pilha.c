#include "pilha.h"

int push(coordenada** pilha, int tam, coordenada* coord) {
    printf("entraPush %d\n", tam);
    ++tam;
    printf("add TAM %d\n", tam);
    pilha[tam] = coord;
    printf("atribui coordenada (%d, %d)\n", pilha[tam]->linha, pilha[tam]->coluna);
}

int pop(coordenada** pilha, int tam) {
    printf("Retira coordenada do tam %d : %d\n", tam, tam > 0);
    if (tam >= 0) {
        free(pilha[tam]);
        tam--;
    }
}

coordenada *top(coordenada** pilha, int tam) {
    return pilha[tam];
}