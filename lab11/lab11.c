/* lab11.c by heusmat */
/* Happy holidays! */
#include <stdio.h>
#include "grafo.h"

// Código do cliente.
int main() {
    int qtd_centros, qtd_pontos;
    p_grafo g;
    scanf("%d %d", &qtd_centros, &qtd_pontos);
    g = criar_grafo(qtd_centros + qtd_pontos);
    le_arestas(g);
    le_operacoes(g);
    libera_grafo(g);
    return 0;
}