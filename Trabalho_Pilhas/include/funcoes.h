#ifndef FUNCOES_H
#define FUNCOES_H

#include "pilha.h"
#include "fila.h"

int prioridade(char op);
int ehOperador(char c);
void quebrarExpressao(char *expr, Fila *entrada);
void converterPosfixa(Fila *entrada, Fila *saida);
double avaliarPosfixa(Fila *posfixa);

#endif
