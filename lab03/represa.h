// represa.h for lab03.c by heusmat
#define MAX 1000
#include <stdio.h>

typedef struct {
    /* Definição da estrutura "represa", que contém o vetor "nome" (nome da
    represa), o float "capmax" (capacidade máxima da represa), o int "qtd_niveis"
    (a quantidade de níveis medidos), o vetor de int "niveis" (valor de cada
    nível medido, o int "media" (média dos valores do vetor "niveis") e
    o int "alerta" (caso seja igual a 1, é impresso o alerta).
    */

    char nome[100];
    float capmax;
    int qtd_niveis;
    int niveis[MAX];
    int media;
    int alerta;
} represa;

// Explicações detalhadas das funções na implementação "represa.c".

represa le_detalhes();

int calc_media(int qtd_niveis, int niveis[]);

void organiza_nome(char nome[]);

int define_alerta(int qtd_niveis, int niveis[], float capmax);

void imprime_detalhes(char nome[], int qtd_niveis, int media, int alerta);