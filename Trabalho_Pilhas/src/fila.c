#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
}

int filaVazia(Fila *f) {
    return f->frente > f->tras;
}

void enfileirar(Fila *f, char *valor) {
    if (f->tras + 1 >= MAX) {
        printf("Erro: fila cheia.\n");
        exit(1);
    }
    strcpy(f->itens[++f->tras], valor);
}

char* desenfileirar(Fila *f) {
    if (filaVazia(f)) {
        printf("Erro: fila vazia.\n");
        exit(1);
    }
    return f->itens[f->frente++];
}
