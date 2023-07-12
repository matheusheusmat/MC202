// pilha.c for lab07 by heusmat
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"

// Cria a pilha, que usa o método das listas ligadas.
p_pilha cria_pilha() {
    p_pilha p;
    p = malloc(sizeof(Pilha));
    p->topo = malloc(sizeof(No));
    p->topo->prox = NULL;
    p->topo->tam = 0;
    return p;
}

// Cria um novo topo para a pilha, uma vez que o vetor de 50
// posições do topo esteja cheio. Chamado pela função "empilha".
void cria_topo(p_pilha p) {
    p_no novo = malloc(sizeof(struct No));
    novo->tam = 0;
    novo->prox = p->topo;
    p->topo = novo;
}

// Empilha caracteres no vetor do topo da pilha. Caso o vetor
// de 50 posições esteja cheio, cria-se um novo topo.
void empilha(p_pilha p, char caracter) {
    if ((p->topo->tam + 1) > 50) {
        cria_topo(p);
        empilha(p, caracter);
    }
    else {
        p->topo->v[p->topo->tam] = caracter;
        p->topo->tam++;
    }
}

// Imprime a pilha recursivamente, do fundo até o topo.
void imprime_pilha(p_pilha p, p_no cam_atual) {
    int i;
    if (cam_atual->prox != NULL)
        imprime_pilha(p, cam_atual->prox);
    for (i = 0; i < cam_atual->tam; i++)
        printf("%c", cam_atual->v[i]);
}

// Remove uma quantidade dada na entrada de caracteres da pilha.
// Caso a essa quantidade seja maior que a de caracteres armazenados
// no vetor do topo, todos os caracteres são retirados, o topo é
// liberado e o próximo nó da lista torna-se o topo.
// O restante de caracteres é, então, retirado do novo topo, recursivamente.
void remove_pilha(p_pilha p, int qtd) {
    int dif;
    dif = p->topo->tam - qtd;
    if (dif > 0) 
        p->topo->tam = dif;
    else if (dif <= 0) {
        p_no proximo = p->topo->prox;
        free(p->topo);
        p->topo = proximo;
        if (dif < 0) {
            remove_pilha(p, abs(dif));
        }
    }
}

// Dada uma entrada em string EXEC ou DEL seguida de um número, 
// a função extrai o número da string e devolve-o em um int,
// para realização das operações.
int obter_qtd(char *string, int tam) {
    int i, j = 0, ini, qtd;
    char num[4];
    ini = strcspn(string, " ") + 1;
    for (i = ini; i < tam + 1; i++) {
        num[j] = string[i];
        j++;
    }
    qtd = atoi(num);
    return qtd;
}

// Libera a pilha. Para isso, deve liberar a lista ligada antes.
void destruir_pilha(p_pilha p) {
    destruir_lista(p->topo);
    free(p);
}

// Libera, recursivamente, a lista ligada que forma a pilha, do último
// ao primeiro nó (topo).
void destruir_lista(p_no topo) {
    if (topo->prox != NULL) 
        destruir_lista(topo->prox);
    free(topo);
}