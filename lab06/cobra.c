#include <stdio.h>
#include <stdlib.h>
#include "cobra.h"


void imprime_matriz(matriz mat) {
    int i, j;
    for (i = 0; i < mat->linhas; i++) {
        for (j = 0; j < mat->colunas; j++) {
            if (mat->dados[i][j] == 0)
                printf("_ ");
            else if (mat->dados[i][j] == 1)
                printf("# ");
            else if (mat->dados[i][j] == -1)
                printf("* ");
        }
        printf("\n");
    }
    printf("\n");
}


matriz insere_dados(matriz mat, fruta fruta_atual, p_no cabeca, int tamanho) {
    int i, j;
    p_no atual;
    atual = cabeca;
    for (i = 0; i < mat->linhas; i++)
        for (j = 0; j < mat->colunas; j++)
            mat->dados[i][j] = 0;
    mat->dados[fruta_atual->coord_linha][fruta_atual->coord_coluna] = -1;
    while (tamanho != 0) {
        mat->dados[atual->coord_linha][atual->coord_coluna] = 1;
        if (tamanho != 1)
            atual = atual->prox;
        tamanho--;
    }
    return mat;
}


matriz cria_matriz() {
    int i;
    matriz mat;
    mat = malloc(sizeof(struct matrix));
    scanf("%d %d", &mat->linhas, &mat->colunas);
    mat->dados = malloc(mat->linhas * sizeof(int *));
    for (i = 0; i < mat->linhas; i++)
        mat->dados[i] = malloc(mat->colunas * sizeof(int));
    return mat;
}


void cria_fruta(fruta fruta_atual) {
    char nome[5];
    scanf("%s %d %d", nome, &fruta_atual->coord_linha, &fruta_atual->coord_coluna);
}


void posicao_inicio(p_no cabeca, p_no cauda) {
    char nome[5];
    int coord_linha, coord_coluna;
    scanf("%s %d %d", nome, &coord_linha, &coord_coluna);
    cabeca->coord_linha = coord_linha;
    cabeca->coord_coluna = coord_coluna;
    cauda->coord_linha = coord_linha;
    cauda->coord_coluna = coord_coluna;
    cabeca->ant = NULL;
    cabeca->prox = NULL;
    cauda->ant = NULL;
    cauda->prox = NULL;
}


void copia_para_prox(p_no cabeca, int tamanho) {
    int coord_linha_ant, coord_coluna_ant, coord_coluna_novo, coord_linha_novo;
    p_no atual;
    coord_linha_ant = cabeca->coord_linha;
    coord_coluna_ant = cabeca->coord_coluna;
    atual = cabeca;
    while (tamanho > 1) {
        atual = atual->prox;
        coord_coluna_novo = atual->coord_coluna;
        coord_linha_novo = atual->coord_linha;
        atual->coord_coluna = coord_coluna_ant;
        atual->coord_linha = coord_linha_ant;
        coord_coluna_ant = coord_coluna_novo;
        coord_linha_ant = coord_linha_novo;
        tamanho--;
    }
}


void movimenta_cobra(matriz mat, char movimento, p_no cabeca, int tamanho) {
    if (movimento == 'w') {
        if (tamanho > 1)
            copia_para_prox(cabeca, tamanho);
        cabeca->coord_linha--;
        if (cabeca->coord_linha < 0)
            cabeca->coord_linha = mat->linhas - 1;
    }

    else if (movimento == 's') {
        if (tamanho > 1)
            copia_para_prox(cabeca, tamanho);
        cabeca->coord_linha++;
        if (cabeca->coord_linha > mat->linhas - 1)
            cabeca->coord_linha = 0;
    }
    else if (movimento == 'a') {
        if (tamanho > 1)
            copia_para_prox(cabeca, tamanho);
        cabeca->coord_coluna--;
        if (cabeca->coord_coluna < 0)
            cabeca->coord_coluna = mat->linhas - 1;
    }
    else if (movimento == 'd') {
        if (tamanho > 1)
            copia_para_prox(cabeca, tamanho);
        cabeca->coord_coluna++;
        if (cabeca->coord_coluna > mat->colunas - 1)
            cabeca->coord_coluna = 0;
    }
}

int comeu_fruta(p_no cabeca, fruta fruta_atual) {
    if (cabeca->coord_coluna == fruta_atual->coord_coluna
    && cabeca->coord_linha == fruta_atual->coord_linha)
        return 1;
    else
        return 0;
}


void aumenta_tamanho_primeiro(matriz mat, p_no cabeca, p_no cauda, int tamanho, char movimento) {
    if (movimento == 'w') {
        cauda->coord_linha = cabeca->coord_linha + 1;
        cauda->coord_coluna = cabeca->coord_coluna;
        if (cauda->coord_linha > mat->linhas - 1)
            cauda->coord_linha = 0;
    }
    else if (movimento == 's') {
        cauda->coord_linha = cabeca->coord_linha - 1;
        cauda->coord_coluna = cabeca->coord_coluna;
        if (cauda->coord_linha < 0)
            cauda->coord_linha = mat->linhas - 1;
    }
    else if (movimento == 'a') {
        cauda->coord_coluna = cabeca->coord_coluna + 1;
        cauda->coord_linha = cabeca->coord_linha;
        if (cauda->coord_coluna > mat->colunas + 1)
            cauda->coord_coluna = 0;
    }
    else if (movimento == 'd') {
        cauda->coord_coluna = cabeca->coord_coluna - 1;
        cauda->coord_linha = cabeca->coord_linha;
        if (cauda->coord_coluna < 0)
            cauda->coord_coluna = mat->colunas - 1;
    }
    cabeca->prox = cauda;
    cauda->ant = cabeca;
}


p_no aumenta_tamanho(p_no cauda, int cauda_linha_ant, int cauda_coluna_ant) {
    p_no novo;
    novo = malloc(sizeof(No));
    p_no atual;
    atual = cauda;
    novo->ant = atual;
    atual->prox = novo;
    novo->coord_linha = cauda_linha_ant;
    novo->coord_coluna = cauda_coluna_ant;
    return novo;
}


char continua_jogo(matriz mat, p_no cabeca, int y, int x, int tamanho, char movimento, int modo_verif) {
    int i, j;
    p_no atual;
    atual = cabeca;
    if (modo_verif == 1) {
        if (movimento == 'w') {
            y--;
            if (y < 0)
                y = mat->linhas - 1;
        }
        else if (movimento == 's') {
            y++;
            if (y > mat->linhas - 1)
                y = 0;
        }
        else if (movimento == 'a') {
            x--;
            if (x < 0)
                x = mat->colunas - 1;
        }
        else if (movimento == 'd') {
            x++;
            if (x > mat->colunas - 1)
                x = 0;
        }
        while (tamanho > 1) {
            atual = atual->prox;
            if (y == atual->coord_linha 
            && x == atual->coord_coluna)
                return 'd';
            tamanho--;
        }
        return 's';
    }
    else {
        for (i = 0; i < mat->linhas; i++) {
            for (j = 0; j < mat->colunas; j++) {
                if (mat->dados[i][j] != 1)
                    return 's';
            }
        }
        return 'v';
    }
}


void imprime_final(matriz mat, char continua) {
    if (continua == 'v')
        printf("YOU WIN");
    else {
        imprime_matriz(mat);
        printf("GAME OVER");
    }
}


void destroi_matriz(matriz mat) {
    int i;
    for (i = 0; i < mat->linhas; i++)
        free(mat->dados[i]);
    free(mat->dados);
    free(mat);
}


void destroi_lista(p_no atual) {
    if (atual != NULL) {
        destroi_lista(atual->ant);
        free(atual);
    }
}