#include <stdio.h>
#include <stdlib.h>
#include "ultron.h"


int main() {
    matriz mat;
    int n_op, i;
    mat = alocar_inicial();
    scanf("%d", &n_op);
    for (i = 0; i < n_op; i++) {
        le_operacao(mat);
        verifica_mem(mat);
        imprime_matriz(mat);
    }
    for (i = 0; i < mat->l_alocadas; i++)
        free(mat->dados[i]);
    free(mat->dados);
    printf("COMBINACAO MATRICIAL FINALIZADA!");
    return 0;
}

