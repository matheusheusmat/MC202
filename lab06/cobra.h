#include <stdio.h>
#include <stdlib.h>


typedef struct matrix *matriz;

typedef struct No *p_no;

typedef struct fruit *fruta;

typedef struct matrix {
    int **dados;
    int linhas;
    int colunas;
} matrix;


typedef struct No {
    int coord_linha;
    int coord_coluna;
    struct No *prox;
    struct No *ant;
} No;


typedef struct fruit {
    int coord_linha;
    int coord_coluna;
} fruit;


void imprime_matriz(matriz mat);

matriz insere_dados(matriz mat, fruta fruta_atual, p_no cabeca, int tamanho);

matriz cria_matriz();

void cria_fruta(fruta fruta_atual);

void posicao_inicio(p_no cabeca, p_no cauda);

void copia_para_prox(p_no cabeca, int tamanho);

void movimenta_cobra(matriz mat, char movimento, p_no cabeca, int tamanho);

int comeu_fruta(p_no cabeca, fruta fruta_atual);

void aumenta_tamanho_primeiro(matriz mat, p_no cabeca, p_no cauda, int tamanho, char movimento);

p_no aumenta_tamanho(p_no cauda, int cauda_linha_ant, int cauda_coluna_ant);

char continua_jogo(matriz mat, p_no cabeca, int y, int x, int tamanho, char movimento, int modo_verif);

void imprime_final(matriz mat, char continua);

void destroi_matriz(matriz mat);

void destroi_lista(p_no atual);