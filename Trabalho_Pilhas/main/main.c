#include <stdio.h>
#include <string.h>
#include "../include/funcoes.h"

int main() {
    char expressao[MAX];
    Fila entrada, posfixa;

    inicializarFila(&entrada);
    inicializarFila(&posfixa);

    printf("Digite a expressao: ");
    if (!fgets(expressao, MAX, stdin)) return 0;
    expressao[strcspn(expressao, "\n")] = 0;

    quebrarExpressao(expressao, &entrada);
    converterPosfixa(&entrada, &posfixa);

    double resultado = avaliarPosfixa(&posfixa);
    printf("Resultado: %.2lf\n", resultado);

    return 0;
}
