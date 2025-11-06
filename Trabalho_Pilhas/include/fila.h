#ifndef FILA_H
#define FILA_H

#define MAX 1000

typedef struct {
    char itens[MAX][50];
    int frente, tras;
} Fila;

void inicializarFila(Fila *f);
int filaVazia(Fila *f);
void enfileirar(Fila *f, char *valor);
char* desenfileirar(Fila *f);

#endif
