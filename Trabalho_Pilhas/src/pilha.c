#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

// pilha (double)
void inicializarPilha(Pilha *p) { p->topo = -1; }
int pilhaVazia(Pilha *p) { return p->topo == -1; }
void empilhar(Pilha *p, double valor) { p->itens[++p->topo] = valor; }
double desempilhar(Pilha *p) {
    if (pilhaVazia(p)) { printf("Erro: pilha vazia.\n"); exit(1); }
    return p->itens[p->topo--];
}
double topoPilha(Pilha *p) { return pilhaVazia(p) ? 0 : p->itens[p->topo]; }

// pilha (char)
void inicializarPilhaChar(PilhaChar *p) { p->topo = -1; }
int pilhaCharVazia(PilhaChar *p) { return p->topo == -1; }
void empilharChar(PilhaChar *p, char c) { p->itens[++p->topo] = c; }
char desempilharChar(PilhaChar *p) {
    if (pilhaCharVazia(p)) { printf("Erro: pilha de char vazia.\n"); exit(1); }
    return p->itens[p->topo--];
}
char topoPilhaChar(PilhaChar *p) { return pilhaCharVazia(p) ? '\0' : p->itens[p->topo]; }

