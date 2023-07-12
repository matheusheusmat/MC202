/* heap.c for lab09 by heusmat */
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// Realiza a troca de dois itens dentro da fila, copiando
// o conteúdo de uma posição a outra do vetor.
void troca(Item *a, Item *b) {
    Item t = *a;
    *a = *b;
    *b = t;
}

// Cria a fila de prioridade, alocando memória para a estrutura
// e para o vetor de itens. O número de itens começa como zero.
p_fp criar_filaprio(int tam) {
    p_fp fprio = malloc(sizeof(FP));
    fprio->v = malloc(tam * sizeof(Item));
    fprio->n = 0; /* n = itens na fila */ 
    fprio->tamanho = tam; /* tam = espaço alocado */
    return fprio;
}

// Realiza a "subida" de um item na fila de prioridade. Pensando em
// uma árvore binária em forma de max-heap, caso um item inserido ou com
// sua prioridade modificada tenha maior prioridade que seu pai, é 
// feita a troca entre suas posições, para manter a estrutura de heap.
// Haverá a subida caso o item tenha maior número C que seu pai ou, em
// caso de número C igual, o número P é comparado. 
void sobe_no_heap(p_fp fprio, int k) {
    if (k > 0 && (fprio->v[PAI(k)].num_C < fprio->v[k].num_C || 
    (fprio->v[PAI(k)].num_C == fprio->v[k].num_C && 
    fprio->v[PAI(k)].num_P < fprio->v[k].num_P))) {
        troca(&fprio->v[k], &fprio->v[PAI(k)]);
        sobe_no_heap(fprio, PAI(k));
    }
}

// Realiza a "descida" de um item na fila de prioridade. Pensando em
// uma árvore binária em forma de max-heap, caso um item inserido ou com
// sua prioridade modificada tenha menor prioridade que um de seus filhos, é 
// feita a troca entre suas posições, para manter a estrutura de heap.
void desce_no_heap(p_fp fprio, int k) {
    int maior_filho;
    if (F_ESQ(k) < fprio->n) {
        maior_filho = F_ESQ(k);
        if (F_DIR(k) < fprio->n && 
        (fprio->v[F_ESQ(k)].num_C < fprio->v[F_DIR(k)].num_C || 
        (fprio->v[F_ESQ(k)].num_C == fprio->v[F_DIR(k)].num_C && 
        fprio->v[F_ESQ(k)].num_P < fprio->v[F_DIR(k)].num_P)))
            maior_filho = F_DIR(k);
        if (fprio->v[k].num_C < fprio->v[maior_filho].num_C || 
            (fprio->v[k].num_C == fprio->v[maior_filho].num_C && 
            fprio->v[k].num_P < fprio->v[maior_filho].num_P)) {
            troca(&fprio->v[k], &fprio->v[maior_filho]);
            desce_no_heap(fprio, maior_filho);
        }
    }
}

// Inserção de um item no final do heap. Após isso, sua posição
// pode ser modificada pela função 'sobe_no_heap', caso o item tenha
// maior prioridade que seu pai no heap.
void insere(p_fp fprio, Item item) {
    fprio->v[fprio->n] = item;
    fprio->n++;
    sobe_no_heap(fprio, fprio->n - 1);
}

// Dado a posição de um item e um novo valor para sua prioridade, realiza
// a troca da prioridade e a correção de sua posição, para a manutenção
// da estrutura de heap.
void muda_prioridade(p_fp fprio, int k, int valor) {
    if (fprio->v[k].num_C < valor) {
        fprio->v[k].num_C = valor;
        sobe_no_heap(fprio, k);
    }
    else {
        fprio->v[k].num_C = valor;
        desce_no_heap(fprio, k);
    }
}

// Dada a fila, devolve o item de máxima prioridade, com base
// nos critérios: maior C e, em caso de empate, maior P. O item
// encontrado é, então, posto no fim da fila e a fila é organizada
// novamente em forma de heap.
Item extrai_maximo(p_fp fprio) {
    Item item = fprio->v[0];
    troca(&fprio->v[0], &fprio->v[fprio->n - 1]);
    fprio->n--;
    desce_no_heap(fprio, 0);
    return item;
}

// Função que realiza um loop de extrai_maximo, retirando os K (num_K)
// itens de maior prioridade da fila.
void procura_max(p_fp fprio) {
    int j, num_K;
    Item atual;
    scanf("%d", &num_K);
    printf("PROCESSOS REMOVIDOS:");
    for (j = 0; j < num_K; j++) {
        atual = extrai_maximo(fprio);
        printf(" %d", atual.num_P);
    }
    printf("\n");
}

// Procura um item na fila e muda sua prioridade. Dados o número
// do processo P e o novo código de prioridade C, é feita uma busca
// simples pela posição i do item do número P procurado. Então, pela 
// função muda_prioridade, o código C é modificado.
void busca_e_muda_prio(p_fp fprio) {
    int i, p_proc, c_novo;
    scanf("%d %d", &p_proc, &c_novo);
    for (i = 0; i < fprio->n; i++) {
        if (fprio->v[i].num_P == p_proc)
            break;
    }
    c_novo = 500 - c_novo;
    muda_prioridade(fprio, i, c_novo);
}

// Libera a memória alocada dinamicamente para a fila
void libera_fila(p_fp fprio) {
    free(fprio->v);
    free(fprio);
}