// lab07.c by heusmat
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fila.h"
#include "pilha.h"

// Código do cliente.
int main() {
    char string[MAX], caracter;
    int tam_str, qtd, i;
    p_fila fila;
    p_pilha pilha;
    fila = cria_fila();
    pilha = cria_pilha();
    fgets(string, 500, stdin);
    while ((strncmp(string, "EXIT", 4)) != 0) {
        remove_newline(string);
        tam_str = strlen(string);
        if ((strncmp(string, "EXEC", 4) == 0)) {
            qtd = obter_qtd(string, tam_str);
            for (i = 0; i < qtd; i++) {
                caracter = desenfileira(fila);
                empilha(pilha, caracter);
            }
        }
        else if ((strncmp(string, "DEL", 3) == 0)) {
            qtd = obter_qtd(string, tam_str);
            remove_pilha(pilha, qtd);
        }
        else
            enfileira(fila, string, tam_str);
        imprime_fila(fila);
        printf("PILHA ATUAL: ");
        imprime_pilha(pilha, pilha->topo);
        printf("\n####\n");
        fgets(string, 500, stdin);
    }
    destruir_fila(fila);
    destruir_pilha(pilha);
    return 0;
}