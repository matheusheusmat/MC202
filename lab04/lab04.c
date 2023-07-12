#include <stdlib.h>
#include <stdio.h>


typedef struct vector {
    int *dados;
    int tam;
} vector;

typedef struct vector *vetor;


void le_vetor(int *v, int tam) {
    /* Realiza a leitura de cada tropa, dadas na entrada.
    */

    int i;
    for (i = 0; i < tam; i++)
        scanf("%d", &v[i]);
}


void imprime_vetor(int *v, int tam, int num) {
    /* Função de impressão para cada sub-tropa forte, após ser descoberta
    na função "subtropa".
    */

    int i;
    printf("Sub-tropa Forte %d: ", num);
    for (i = 0; i < tam; i++)
        printf("%d ", v[i]);
    printf("\n");
}


void imprime_elite(int *v, int tam) {
    /* Impressão da "sub-tropa de elite", obtida na função "subtropa_elite". 
    */

    int i;
    printf("Sub-tropa Elite: ");
    for (i = 0; i < tam; i++)
        printf("%d ", v[i]);
    printf("\n");
}


int subtropa(int *v, int tam) {
    /* Define a "sub-tropa forte" para cada tropa, isto é, o
    sub-vetor sequencial cujos elementos possuem a maior soma.
    Para isso, são feitas todas as combinações possíveis de sub-vetores
    sequenciais dentro de um vetor e calculada sua soma. A cada nova maior
    soma encontrada, o sub-vetor é armazenado no vetor "maior_subvetor".
    Ao final das combinações, a tropa de entrada é modificada, tornando-se o
    "maior_subvetor".
    */

    int i, j, k, indice, soma, tam_aux, maior_soma, tam_maior_sub;
    int *v_aux, *maior_subvetor;
    v_aux = malloc(tam * sizeof(int));
    maior_subvetor = malloc(tam * sizeof(int));
    maior_soma = v[0];
    maior_subvetor[0] = v[0];
    tam_maior_sub = 1;
    for (i = 0; i < tam; i++) {
        indice = 1;
        soma = v[i];
        v_aux[0] = v[i];
        tam_aux = 1;
        if (soma > maior_soma) { 
            maior_soma = soma;
            maior_subvetor[0] = v[i];
            tam_maior_sub = 1;
        }
        for (j = i + 1; j < tam; j++) {
            soma += v[j];
            v_aux[indice] = v[j];
            tam_aux++;
            if (soma > maior_soma) {
                maior_soma = soma;
                for (k = 0; k < tam_aux; k++) 
                    maior_subvetor[k] = v_aux[k];
                tam_maior_sub = tam_aux;
            }
            indice++;
        }
    }
    for (i = 0; i < tam_maior_sub; i++)
        v[i] = maior_subvetor[i];
    free(maior_subvetor);
    free(v_aux);
    return tam_maior_sub;
}


void subtropa_inicial(int *v_atual, vetor v_subtropas, int tam) {
    /* Adiciona a primeira sub-tropa forte ao vetor de sub-tropas.
    */

    int i;
    for (i = 0; i < tam; i++)
        v_subtropas->dados[i] = v_atual[i];
}


void adiciona_subtropa(int *v_atual, vetor v_subtropas, int tam) {
    /* Adiciona a segunda e as seguintes sub-tropas ao vetor de sub-tropas,
    com necessidade de haver a realocação do vetor que contém todas as sub-tropas,
    pois seu tamanho precisa ser alterado.
    */

    int *v_aux, i, j = 0, novo_tam_el;
    novo_tam_el = v_subtropas->tam + tam;
    v_aux = malloc(novo_tam_el * sizeof(int));
    for (i = 0; i < v_subtropas->tam; i++)
        v_aux[i] = v_subtropas->dados[i];
    for (i = v_subtropas->tam; i < novo_tam_el; i++) {
        v_aux[i] = v_atual[j];
        j++;
    }
    free(v_subtropas->dados);
    v_subtropas->dados = malloc(novo_tam_el * sizeof(int));
    for (i = 0; i < novo_tam_el; i++)
        v_subtropas->dados[i] = v_aux[i];
    free(v_aux);
}


void normaliza_vetor(vetor v_elite, vetor v_subtropas) {
    /* Realiza a "normalização" do vetor de subtropas, que é a subtração
    de cada um de seus valores pela média destes. O vetor normalizado é, então,
    armazenado na estrutura "v_elite".
    */

    int media = 0, i;
    for (i = 0; i < v_subtropas->tam; i++) {
        media += (v_subtropas->dados[i]);
    }
    media /= v_subtropas->tam;
    for (i = 0; i < v_subtropas->tam; i++) {
        v_elite->dados[i] = (v_subtropas->dados[i] - media);
    }
}


int subtropa_elite(vetor v_elite, vetor v_subtropas) {
    /* Encontra a "sub-tropa elite", isto é, o maior sub-vetor de "v_subtropas" após
    a normalização (já realizada e armazenada em "v_elite"). O modo de funcionamento é
    semelhante a encontrar uma "sub-tropa forte". A verificação de maior sub-vetor contínuo
    é feita sobre o vetor normalizado "v_elite", mas o retorno é armazenado em "v_subtropas".
    */

    int i, j, k, indice, soma, tam_aux_sub, tam_aux_elite, maior_soma, tam_maior_sub;
    int *v_aux_sub, *v_aux_elite, *maior_subvetor;
    v_aux_sub = malloc((v_subtropas->tam) * sizeof(int));
    v_aux_elite = malloc((v_subtropas->tam) * sizeof(int));
    maior_subvetor = malloc((v_subtropas->tam) * sizeof(int));
    maior_soma = v_elite->dados[0];
    maior_subvetor[0] = v_subtropas->dados[0];
    tam_maior_sub = 1;
    for (i = 0; i < v_subtropas->tam; i++) {
        indice = 1;
        soma = v_elite->dados[i];
        v_aux_elite[0] = v_elite->dados[i];
        v_aux_sub[0] = v_subtropas->dados[i];
        tam_aux_sub = 1;
        tam_aux_elite = 1;
        if (soma > maior_soma) { 
            maior_soma = soma;
            maior_subvetor[0] = v_subtropas->dados[i];
            tam_maior_sub = 1;
        }
        for (j = i + 1; j < v_subtropas->tam; j++) {
            soma += v_elite->dados[j];
            v_aux_elite[indice] = v_elite->dados[j];
            v_aux_sub[indice] = v_subtropas->dados[j];
            tam_aux_elite++;
            tam_aux_sub++;
            if (soma > maior_soma) {
                maior_soma = soma;
                for (k = 0; k < tam_aux_elite; k++) 
                    maior_subvetor[k] = v_aux_sub[k];
                tam_maior_sub = tam_aux_sub;
            }
            indice++;
        }
    }
    for (i = 0; i < tam_maior_sub; i++)
        v_elite->dados[i] = maior_subvetor[i];
    free(v_aux_sub);
    free(v_aux_elite);
    free(maior_subvetor);
    return tam_maior_sub;
}


int main() {
    // Código principal.

    int qtd_vetores, i, tam;
    int *v_atual;
    vetor v_subtropas;
    v_subtropas = malloc(sizeof(vector));
    scanf("%d", &qtd_vetores);
    for (i = 0; i < qtd_vetores; i++) {
        scanf("%d", &tam);
        v_atual = malloc(tam * sizeof(int));
        le_vetor(v_atual, tam);
        tam = subtropa(v_atual, tam);
        imprime_vetor(v_atual, tam, i + 1);
        if (i == 0) {
            v_subtropas->dados = malloc(tam * sizeof(int));
            v_subtropas->tam = tam;
            subtropa_inicial(v_atual, v_subtropas, tam);
        }
        else {
            adiciona_subtropa(v_atual, v_subtropas, tam);
            v_subtropas->tam += tam;
        }
        free(v_atual);
    }
    
    vetor v_elite;
    v_elite = malloc(sizeof(vector));
    v_elite->dados = malloc((v_subtropas->tam) * sizeof(int));
    normaliza_vetor(v_elite, v_subtropas);
    v_elite->tam = subtropa_elite(v_elite, v_subtropas);
    imprime_elite(v_elite->dados, v_elite->tam);
    free(v_elite->dados);
    free(v_elite);
    free(v_subtropas->dados);
    free(v_subtropas);
    return 0;
}