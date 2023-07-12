/* grafo.c for lab11 by heusmat */

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


// Cria o grafo, alocando memória para ele e sua lista de adjacências.
// Em seguida, o devolve.
p_grafo criar_grafo(int n) {
    int i;
    p_grafo g = malloc(sizeof(Grafo));
    g->n = n;
    g->adj = malloc(n * sizeof(No));
    for (i = 0; i < n; i++)
        g->adj[i] = NULL;
    return g;
}

// Insere um nó na lista ligada de adjacências, toda vez que há uma
// inserção de arestas.
p_no insere_na_lista(p_no lista, int num) {
    p_no novo = malloc(sizeof(No));
    novo->num = num;
    novo->prox = lista;
    return novo;
}

// Função para inserção de arestas. Dados dois vértices do grafo,
// o número de um vértice é inserido na lista de adjacência do outro,
// mutuamente.
void insere_aresta(p_grafo g, int u, int v) {
    g->adj[v] = insere_na_lista(g->adj[v], u);
    g->adj[u] = insere_na_lista(g->adj[u], v);
}

// Dado um número de um vértice, realiza a sua remoção da lista de
// adjacências de outro vértice.
p_no remove_da_lista(p_no lista, int num) {
    p_no proximo;
    if (lista == NULL)
        return NULL;
    else if (lista->num == num) {
        proximo = lista->prox;
        free(lista);
        return proximo;
    }
    else {
        lista->prox = remove_da_lista(lista->prox, num);
        return lista;
    }
}

// Função para remover um vértice da lista de adjacências de outro,
// mutuamente.
void remove_aresta(p_grafo g, int u, int v) {
    g->adj[u] = remove_da_lista(g->adj[u], v);
    g->adj[v] = remove_da_lista(g->adj[v], u);
}

// Realiza a liberação de cada lista ligada do nó, cuja memória é 
// dinamicamente alocada.
void libera_lista(p_no lista) {
    if (lista != NULL) {
        libera_lista(lista->prox);
        free(lista);
    }
}

// Realiza a liberação de memória alocada dinamicamente para o grafo.
// Para isso, é necessário liberar cada lista ligada (feita pela função
// libera_lista) que forma o vetor de adjacências.
void libera_grafo(p_grafo g) {
    int i;
    for (i = 0; i < g->n; i++)
        libera_lista(g->adj[i]);
    free(g->adj);
    free(g);
}

// Realiza a leitura de cada par de vértices para a inserção de arestas.
// A cada par, chama a função "insere_aresta".
void le_arestas(p_grafo g) {
    int i, qtd_arestas, u, v;
    scanf("%d", &qtd_arestas);
    for (i = 0; i < qtd_arestas; i++) {
        scanf("%d %d", &u, &v);
        insere_aresta(g, u, v);
    }
    printf("GRAFO AMZ CONSTRUIDO!\n");
}

// Realiza a "busca em profundidade" de um vértice do grafo, que encontra
// o caminho de uma determinada raiz escolhida até qualquer vértice conexo
// do grafo. 
void busca_em_profundidade(p_grafo g, int *pai, int p, int v) {
    p_no t;
    pai[v] = p;
    for (t = g->adj[v]; t != NULL; t = t->prox)
        if (pai[t->num] == -1)
            busca_em_profundidade(g, pai, v, t->num);
}

// Função que, dado um vértice, retorna um vetor que simula o caminho para
// qualquer outro vértice do grafo, cuja distância será calculada pela função
// "calc_distancia";
int *encontra_caminhos(p_grafo g, int s) {
    int i, *pai = malloc(g->n * sizeof(int));
    for (i = 0; i < g->n; i++)
        pai[i] = -1;
    busca_em_profundidade(g, pai, s, s);
    return pai;
}

// Recebendo o vetor "pai", calcula o número de vértices a serem percorridos
// entre dois vértices do grafo, somando à distância a cada iteração feita.
// É uma adaptação da função "imprime_caminho". Retorna a distância encontrada.
int calc_distancia(int v, int *pai) {
    int dist = 0;
    while (pai[v] != v) {
        v = pai[v];
        dist++;
    }
    return dist;
}

// Algoritmo de troca, importante para a ordenação do vetor.
void troca(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Ordena o vetor dado pela função "imprime_crescente". O algoritmo usado
// é o BubbleSort, lento, porém o volume de dados a ser ordenado é pequeno.
void ordenar(int *v, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = n - 1; j > i; j--)
            if (v[j] < v[j-1])
                troca(&v[j-1], &v[j]);
}

// Imprime os vértices adjacentes ao novo vértice do tipo C inserido em
// ordem crescente, como pede o enunciado. Para isso, são lidas as arestas,
// inseridas em um vetor dinamicamente alocado, e o vetor é, então, ordenado 
// pela função "ordenar".
void imprime_crescente(p_no novo, int qtd) {
    p_no t;
    int *arestas, i = 0;
    arestas = malloc(qtd * sizeof(int));
    for (t = novo; t != NULL; t = t->prox) {
        arestas[i] = t->num;
        i++;
    }
    ordenar(arestas, qtd);
    for (i = 0; i < qtd; i++)
        printf(" %d", arestas[i]);
    free(arestas);
    printf("\n");
}

// Realiza a inserção de um novo vértice do tipo C no grafo, caso a distância
// encontrada seja maior que a entrada, na função le_e_calc_distancia. Para isso,
// o vetor é realocado para um nó a mais de memória. Então, são lidos os vértices
// adjacentes ao vértice P correspondente, e são estabelecidas arestas entre estes
// e o novo vértice C. Por fim, a função "imprime_crescente" é chamada, para imprimir
// o nó novo e seus vértices adjacentes em ordem crescente.
void novo_centro(p_grafo g, int p) {
    p_no *aux, t;
    int novo, qtd_arestas = 1;
    g->n++;
    novo = (g->n)-1;
    aux = realloc(g->adj, g->n * sizeof(No));
    g->adj = aux;
    g->adj[g->n-1] = NULL;
    insere_aresta(g, novo, p);
    for (t = g->adj[p]->prox; t != NULL; t = t->prox) {
        insere_aresta(g, novo, t->num);
        qtd_arestas++;
    }
    printf("%d ADICIONADO E CONECTADO A", novo);
    imprime_crescente(g->adj[novo], qtd_arestas);
}

// Lê a entrada e calcula a distância entre dois vértices. Caso seja maior
// que "x", dado também na entrada, um novo vértice do tipo C é adicionado ao grafo.
void le_e_calc_distancia(p_grafo g) {
    int c, p, x, *pai, dist;
    scanf("%d %d %d", &c, &p, &x);
    pai = encontra_caminhos(g, c);
    dist = calc_distancia(p, pai);
    free(pai);
    printf("DISTANCIA %d -> %d = %d\n", c, p, dist);
    if (dist > x) {
        novo_centro(g, p);
    }
}

// Lê os vértices cuja aresta deve ser removida pela função "remove_aresta".
void le_remocao(p_grafo g) {
    int c, p;
    scanf("%d %d", &c, &p);
    remove_aresta(g, c, p);
    printf("ARESTA %d -> %d REMOVIDO\n", c, p);
}

// Identifica qual operação deve ser realizada:
// - Entrada 'D': operação de cálculo de distância.
// - Caso contrário, a operação é R, de remoção de aresta.
void le_operacoes(p_grafo g) {
    int i, qtd_op;
    char nome_op;
    scanf("%d", &qtd_op);
    for (i = 0; i < qtd_op; i++) {
        scanf(" %c", &nome_op);
        if (nome_op == 'D')
            le_e_calc_distancia(g);
        else
            le_remocao(g);
    }
}
