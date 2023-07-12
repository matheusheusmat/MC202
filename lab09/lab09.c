/* lab09.c by heusmat */
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// Código do cliente.
int main() {
    int i, tam, aux, qtd_op;
    char nome_op;
    p_fp fprio;
    scanf("%d", &tam);
    fprio = criar_filaprio(tam);
    for (i = 0; i < tam; i++) {
        Item *atual;
        atual = malloc(sizeof(Item));
        scanf("%d %d", &atual->num_P, &aux);
        atual->num_C = 500 - aux;
        insere(fprio, *atual);
        free(atual);
    }
    scanf("%d", &qtd_op);
    for (i = 0; i < qtd_op; i++) {
        scanf(" %c", &nome_op);
        if (nome_op == 'R') 
            procura_max(fprio);
        else if (nome_op == 'M') 
            busca_e_muda_prio(fprio);
    }
    printf("FINALIZADO!");
    libera_fila(fprio);
}