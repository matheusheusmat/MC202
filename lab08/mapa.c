#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"



// Aloca memória para a árvore binária de busca MAPA
p_no_mapa cria_arv_mapa() {
    p_no_mapa mapa = malloc(sizeof(No_mapa));
    mapa = NULL;
    return mapa;
}

// Aloca memória e cria a árvore binária de busca VISITA.
p_no_visita cria_arv_visita() {
    p_no_visita visita = malloc(sizeof(No_visita));
    visita = NULL;
    return visita;
}

// Insere um novo nó na árvore binária de busca MAPA, recursivamente
// e de maneira ordenada. Após a inserção em seu lugar correto, a cidade
// inserida é impressa. Devolve a raiz da árvore com a nova inserção.
p_no_mapa insere_mapa(p_no_mapa raiz, char *nome_cidade) {
    p_no_mapa novo;
    if (raiz == NULL) {
        novo = malloc(sizeof(No_mapa));
        novo->esq = novo->dir = NULL;
        strcpy(novo->cidade, nome_cidade);
        novo->qtd_vis = 1;
        printf("ARVORE: MAPA\nCIDADE: %s\nINSERIDO COM SUCESSO!\n####\n", nome_cidade);
        return novo;
    }
    if (strcmp(nome_cidade, raiz->cidade) == 0) {
        raiz->qtd_vis++;
        return raiz;
    }
    else if (strcmp(nome_cidade, raiz->cidade) < 0)
        raiz->esq = insere_mapa(raiz->esq, nome_cidade);
    else
        raiz->dir = insere_mapa(raiz->dir, nome_cidade);
    return raiz;
}

// Insere um novo nó na árvore binária de busca VISITA, recursivamente
// e de maneira ordenada. Após a inserção em seu lugar correto, a data da
// visita é impressa, bem como a cidade visitada. Devolve a raiz da árvore
// com a nova inserção.
p_no_visita insere_visita(p_no_visita raiz, int data, char *nome_cidade, int pista) {
    p_no_visita novo;
    if (raiz == NULL) {
        novo = malloc(sizeof(No_visita));
        novo->esq = novo->dir = NULL;
        novo->data = data;
        strcpy(novo->cidade, nome_cidade);
        novo->pista = pista;
        printf("ARVORE: VISITA\nDATA: %d\nCIDADE: %s\nINSERIDO COM SUCESSO!\n####\n", data, nome_cidade);
        return novo;
    }
    if (data < raiz->data)
        raiz->esq = insere_visita(raiz->esq, data, nome_cidade, pista);
    else
        raiz->dir = insere_visita(raiz->dir, data, nome_cidade, pista);
    return raiz;
}

// Imprime o relatório de datas, com todas as visitas em ordem cronológica,
// da mais antiga para a mais nova. A cada nó que está para ser
// impresso, é feita a verificação para ver se a data está dentro do
// período desejado. Após isso, são impressas data e cidade.
void impr_rel_data(p_no_visita visita, int ini, int fim) {
    if (visita != NULL) {
        impr_rel_data(visita->esq, ini, fim);
        if (visita->data >= ini && visita->data <= fim) {
            printf("DATA: %d\n", visita->data);
            printf("CIDADE: %s\n####\n", visita->cidade);
        }
        impr_rel_data(visita->dir, ini, fim);
    }
}

// Lê os dados necessários para a impressão do relatório de data:
// a data de início e a data de fim do período procurado.
void le_dados_rel_data(p_no_visita visita) {
    int ini, fim;
    scanf("%d", &ini);
    scanf("%d", &fim);
    printf("--VISITAS--\n");
    impr_rel_data(visita, ini, fim);
}


// Imprime o relatório de pistas em ordem cronológica decrescente,
// isto é, da visita mais recente para a mais antiga. Antes da impressão,
// é verificado se a visita está no período procurado e se nela foi
// encontrada alguma pista (visita->pista = 1). Se as condições são
// satisfeitas, são impressas a data e a cidade.
void impr_rel_pista(p_no_visita visita, int ini, int fim) {
    if (visita != NULL) {
        impr_rel_pista(visita->dir, ini, fim);
        if (visita->data >= ini && visita->data <= fim && visita->pista) {
            printf("DATA: %d\n", visita->data);
            printf("CIDADE: %s\n####\n", visita->cidade);
        }
        impr_rel_pista(visita->esq, ini, fim);
    }
}

// Lê os dados necessários para a impressão do relatório de pistas:
// a data de início e de fim do período.
void le_dados_rel_pista(p_no_visita visita) {
    int ini, fim;
    scanf("%d", &ini);
    scanf("%d", &fim);
    printf("--PISTAS--\n");
    impr_rel_pista(visita, ini, fim);
}

// Função utilizada pela função "busca_mapa" para remover um nó
// da árvore MAPA. Para isso, é feita a cópia do nó sucessor ao que será
// removido para uma posição condizente da árvore. Como a referência ao nó
// retirado é perdida, ocorre um pequeno vazamento de memória.
void remover_sucessor_mapa(p_no_mapa raiz) {
    p_no_mapa t = raiz->dir; 
    p_no_mapa pai = raiz; 
    while (t->esq != NULL) {
        pai = t;
        t = t->esq;
    }
    if (pai->esq == t)
        pai->esq = t->dir;
    else
        pai->dir = t->dir;
    strcpy(raiz->cidade, t->cidade); 
    raiz->qtd_vis = t->qtd_vis;
}

// Função utilizada pela função "exclui_visita" para remover um nó
// da árvore VISITA. Para isso, é feita a cópia do nó sucessor ao que será
// removido para uma posição condizente da árvore. Como a referência ao nó
// retirado é perdida, ocorre um pequeno vazamento de memória.
void remover_sucessor_visita(p_no_visita raiz) {
    p_no_visita t = raiz->dir;
    p_no_visita pai = raiz;
    while (t->esq != NULL) {
        pai = t;
        t = t->esq;
    }
    if (pai->esq == t)
        pai->esq = t->dir;
    else
        pai->dir = t->dir;
    strcpy(raiz->cidade, t->cidade);
    raiz->data = t->data;
    raiz->pista = t->pista;
}

// Função usada para procurar uma dada cidade na árvore MAPA. Quando
// esta é encontrada, caso o número de visitas seja igual a 1, a cidade
// é removida da árvore. Caso contrário, subtrai-se 1 do campo qtd_vis
// (quantidade de visitas) do nó que contém a cidade procurada.
p_no_mapa busca_mapa(p_no_mapa raiz, char *nome_cidade) {
    if (!strcmp(raiz->cidade, nome_cidade) && raiz->qtd_vis - 1) {
        raiz->qtd_vis--;
        printf("CIDADE: %s\nQUANTIDADE DE VISITAS RESTANTES: %d\n####\n",
               nome_cidade, raiz->qtd_vis);
        return raiz;
    }
    else {
        if (!strcmp(raiz->cidade, nome_cidade))
            printf("CIDADE: %s\nQUANTIDADE DE VISITAS RESTANTES: 0\n####\n", nome_cidade);
        if (raiz == NULL)
            return NULL;
        if (strcmp(nome_cidade, raiz->cidade) < 0)
            raiz->esq = busca_mapa(raiz->esq, nome_cidade);
        else if (strcmp(nome_cidade, raiz->cidade) > 0)
            raiz->dir = busca_mapa(raiz->dir, nome_cidade);
        else if (raiz->esq == NULL)
            return raiz->dir;
        else if (raiz->dir == NULL)
            return raiz->esq;
        else 
            remover_sucessor_mapa(raiz);
        return raiz;
    }
}

// Exclui uma visita da árvore de visitas, dada uma data. É feita, então,
// a busca e remoção do nó.
p_no_visita exclui_visita(p_no_visita raiz, int data, char *nome_cidade) {
    if (data == raiz->data)
        strcpy(nome_cidade, raiz->cidade);
    if (raiz == NULL)
        return NULL;
    if (data < raiz->data)
        raiz->esq = exclui_visita(raiz->esq, data, nome_cidade);
    else if (data > raiz->data)
        raiz->dir = exclui_visita(raiz->dir, data, nome_cidade);
    else if (raiz->esq == NULL)
        return raiz->dir;
    else if (raiz->dir == NULL)
        return raiz->esq;
    else 
        remover_sucessor_visita(raiz);
    return raiz;
}

// Libera a memória alocada dinamicamente para a árvore MAPA.
void libera_mapa(p_no_mapa raiz) {
    if (raiz != NULL) {
        libera_mapa(raiz->esq);
        libera_mapa(raiz->dir);
        free(raiz);
    }
}

// Libera a memória alocada dinamicamente para a árvore VISITA.
void libera_visita(p_no_visita raiz) {
        if (raiz != NULL) {
        libera_visita(raiz->esq);
        libera_visita(raiz->dir);
        free(raiz);
    }
}