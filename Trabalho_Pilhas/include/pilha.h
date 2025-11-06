#ifndef PILHA_H
#define PILHA_H

#define MAX 1000

typedef struct {
    double itens[MAX];
    int topo;
} Pilha;

typedef struct {
    char itens[MAX];
    int topo;
} PilhaChar;

// funções da pilha (double)
void inicializarPilha(Pilha *p);
int pilhaVazia(Pilha *p);
void empilhar(Pilha *p, double valor);
double desempilhar(Pilha *p);
double topoPilha(Pilha *p);

// funções da pilha (char)
void inicializarPilhaChar(PilhaChar *p);
int pilhaCharVazia(PilhaChar *p);
void empilharChar(PilhaChar *p, char c);
char desempilharChar(PilhaChar *p);
char topoPilhaChar(PilhaChar *p);

#endif

