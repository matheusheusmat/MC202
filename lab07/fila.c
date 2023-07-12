// fila.c for lab07 by heusmat
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

// Cria a fila circular, com vetor circular de tamanho MAX = 500, 
// conforme dado pelo exercício, que armazenará os caracteres. Também,
// há os indicadores de início (ini) e fim, importantes na impressão
// e no enfileiramento de caracteres.
p_fila cria_fila() {
    p_fila f;
    f = malloc(sizeof(Fila));
    f->ini = 0;
    f->fim = 0;
    f->N = MAX;
    f->tamanho = 0;
    return f;
}

// Enfileira um caracter no fim da fila, e o fim passa a apontar para
// a posição seguinte do vetor, onde o próximo caracter será inserido.
void enfileira(p_fila f, char *string, int tam_str) {
    int i;
    for (i = 0; i < tam_str; i++) {
        f->v[f->fim] = string[i];
        f->fim = (f->fim + 1) % f->N;
    }
    f->tamanho += tam_str;
}

// Retira o caracter da fileira para passá-lo, posteriormente, à
// pilha.
char desenfileira(p_fila f) {
    int caracter = f->v[f->ini];
    f->ini = (f->ini + 1) % f->N;
    f->tamanho--;
    return caracter;
} 

// Imprime a fila da seguinte maneira: 
// - Caso a posição ini esteja antes da posição fim, o vetor é
// impresso de ini até fim.
// - Caso a posição ini esteja depois de fim, a impressão é feita
// de ini até o final do vetor (posição 499), e depois do início
// (posição 0) até a posição fim.
void imprime_fila(p_fila f) {
    int i;
    printf("FILA ATUAL: ");
    if (f->ini < f->fim) {
    for (i = f->ini; i < f->fim; i++)
        printf("%c", f->v[i]);
    }
    else if (f->ini > f->fim) {
        for (i = f->ini; i < MAX; i++)
            printf("%c", f->v[i]);
        for (i = 0; i < f->fim; i++)
            printf("%c", f->v[i]);
    }
    printf("\n");
}

// Retira o "\n" que indica nova linha, dado na entrada pela
// função "fgets".
void remove_newline(char *string) {
    int tam;
    tam = strcspn(string, "\n");
    string[tam] = '\0';
}

// Libera o espaço alocado para a fila.
void destruir_fila(p_fila f) {
    free(f);
}