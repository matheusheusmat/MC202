#include <stdio.h>
#include <stdlib.h>
#include "cobra.h"
 
 
int main() {
    // Código do cliente, responsável pela utilização das funções.
 
    int comeu_ou_nao, cauda_linha_ant, cauda_coluna_ant;
    matriz mat;
    fruta fruta_atual;
    p_no cabeca, cauda;
    int tamanho = 1;
    char movimento, continua;
    mat = cria_matriz();
    fruta_atual = malloc(sizeof(fruit));
    cabeca = malloc(sizeof(No));
    cauda = malloc(sizeof(No));
    cria_fruta(fruta_atual);
    posicao_inicio(cabeca, cauda);
    insere_dados(mat, fruta_atual, cabeca, tamanho);
    imprime_matriz(mat);
    continua = 's';
    while (continua == 's') {
        scanf(" %c", &movimento);
        cauda_linha_ant = cauda->coord_linha;
        cauda_coluna_ant = cauda->coord_coluna;
        continua = continua_jogo(mat, cabeca, cabeca->coord_linha, cabeca->coord_coluna, tamanho, movimento, 1);
        if (continua != 's')
            break;
        movimenta_cobra(mat, movimento, cabeca, tamanho);
        comeu_ou_nao = comeu_fruta(cabeca, fruta_atual);
        if (comeu_ou_nao) {
            if (tamanho == 1)
                aumenta_tamanho_primeiro(mat, cabeca, cauda, tamanho, movimento);
            else
                cauda = aumenta_tamanho(cauda, cauda_linha_ant, cauda_coluna_ant);
            tamanho++;
            insere_dados(mat, fruta_atual, cabeca, tamanho);
            imprime_matriz(mat);
            continua = continua_jogo(mat, cabeca, cabeca->coord_linha, cabeca->coord_coluna, tamanho, movimento, 2);
            if (continua != 's')
                break;
            cria_fruta(fruta_atual);
            insere_dados(mat, fruta_atual, cabeca, tamanho);
        }
        else 
            insere_dados(mat, fruta_atual, cabeca, tamanho);
        imprime_matriz(mat);
    }
 
    imprime_final(mat, continua);
    destroi_matriz(mat);
    destroi_lista(cauda);
    free(fruta_atual);
    return 0;
}
