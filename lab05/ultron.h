#include <stdio.h>
#include <stdlib.h>


typedef struct matrix *matriz;

typedef struct matrix {
    /* Registro que armazena as linhas e colunas da matriz 
    ocupadas por valores, as linhas e colunas alocadas, e a
    matriz em si, armazenada no ponteiro duplo **dados.
    OBS: por "linhas", entenda vetor.
    Por "colunas", entenda elementos de cada vetor.
    */

    int linhas;
    int colunas;
    int **dados;
    int l_alocadas;
    int c_alocadas;
} matrix;

// Detalhes de cada função na implementação.

void imprime_matriz(matriz mat);

void organiza_linha(matriz mat, int linha);

void realoca_linhas(matriz mat, int adiciona);

void realoca_colunas(matriz mat, int adiciona);

void verifica_mem(matriz mat);

void adiciona_linha(matriz mat, int linha);

void adiciona_coluna(matriz mat, int coluna);

void retira_linha(matriz mat);

void retira_coluna(matriz mat);

void le_operacao(matriz mat);

matriz criar_linhas(matriz mat, int linhas, int colunas);

matriz alocar_inicial();