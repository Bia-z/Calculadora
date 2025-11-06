#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcoes.h"

// Funções auxiliares
int prioridade(char op) {
    switch (op) {
        case '^': return 4;
        case '*':
        case '/': return 3;
        case '+':
        case '-': return 2;
        default: return 0;
    }
}

int ehOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Tokenização (com tratamento de unário)
void quebrarExpressao(char *expr, Fila *entrada) {
    char token[50];
    int i = 0, j;

    while (expr[i] != '\0') {
        if (isspace(expr[i])) { i++; continue; }

        if (expr[i] == '-') {
            int k = i + 1;
            while (expr[k] != '\0' && isspace(expr[k])) k++;

            if (isdigit(expr[k])) {
                j = 0; token[j++] = '-'; i++;
                while (expr[i] != '\0' && isspace(expr[i])) i++;
                while (isdigit(expr[i]) || expr[i] == '.') token[j++] = expr[i++];
                token[j] = '\0'; enfileirar(entrada, token);
                continue;
            } else if (expr[k] == '(') {
                enfileirar(entrada, "0"); enfileirar(entrada, "-");
                i++; continue;
            } else {
                token[0] = '-'; token[1] = '\0'; enfileirar(entrada, token);
                i++; continue;
            }
        }

        if (isdigit(expr[i])) {
            j = 0;
            while (isdigit(expr[i]) || expr[i] == '.') token[j++] = expr[i++];
            token[j] = '\0'; enfileirar(entrada, token);
            continue;
        } else if (ehOperador(expr[i]) || expr[i] == '(' || expr[i] == ')') {
            token[0] = expr[i]; token[1] = '\0'; enfileirar(entrada, token);
        } else {
            printf("Erro: caractere inválido '%c'.\n", expr[i]); exit(1);
        }
        i++;
    }
}

// Infixa -> Pós-fixa
void converterPosfixa(Fila *entrada, Fila *saida) {
    PilhaChar operadores;
    inicializarPilhaChar(&operadores);

    while (!filaVazia(entrada)) {
        char *token = desenfileirar(entrada);

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            enfileirar(saida, token);
        } 
        else if (token[0] == '(') empilharChar(&operadores, '(');
        else if (token[0] == ')') {
            while (!pilhaCharVazia(&operadores) && topoPilhaChar(&operadores) != '(') {
                char temp[2] = {desempilharChar(&operadores), '\0'};
                enfileirar(saida, temp);
            }
            if (!pilhaCharVazia(&operadores)) desempilharChar(&operadores);
            else { printf("Erro: parênteses desbalanceados.\n"); exit(1); }
        } 
        else if (ehOperador(token[0])) {
            while (!pilhaCharVazia(&operadores)) {
                char t = topoPilhaChar(&operadores);
                if (t == '(') break;
                int pt = prioridade(t), ptoken = prioridade(token[0]);
                if (pt > ptoken || (pt == ptoken && token[0] != '^')) {
                    char temp[2] = {desempilharChar(&operadores), '\0'};
                    enfileirar(saida, temp);
                } else break;
            }
            empilharChar(&operadores, token[0]);
        } else {
            printf("Erro: token inesperado '%s'.\n", token); exit(1);
        }
    }

    while (!pilhaCharVazia(&operadores)) {
        char c = desempilharChar(&operadores);
        if (c == '(' || c == ')') { printf("Erro: parênteses desbalanceados.\n"); exit(1); }
        char temp[2] = {c, '\0'}; enfileirar(saida, temp);
    }
}

// Avaliar Pós-fixa
double avaliarPosfixa(Fila *posfixa) {
    Pilha valores;
    inicializarPilha(&valores);

    while (!filaVazia(posfixa)) {
        char *token = desenfileirar(posfixa);

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilhar(&valores, atof(token));
        } else if (ehOperador(token[0])) {
            double b = desempilhar(&valores), a = desempilhar(&valores), res;
            switch (token[0]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': if (b == 0) { printf("Erro: divisão por zero.\n"); exit(1); } res = a / b; break;
                case '^': res = pow(a, b); break;
                default: res = 0; break;
            }
            empilhar(&valores, res);
        } else {
            printf("Erro: token na pós-fixa inválido '%s'.\n", token); exit(1);
        }
    }

    if (pilhaVazia(&valores)) { printf("Erro: nada para retornar.\n"); exit(1); }
    return desempilhar(&valores);
}
