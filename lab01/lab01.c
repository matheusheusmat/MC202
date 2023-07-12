#include <stdio.h>


void imprime_vetor(int vetor_u[], int tam_vetor_u) {
    /* Função que recebe o vetor a ser impresso após cada operação.
    */

    int i;
    for (i = 0; i <= tam_vetor_u; i++)
        printf("%d ", vetor_u[i]);
    printf("\n");
}


void op_banner(int tam_vetor_b, int vetor_b[], int tam_vetor_u, int vetor_u[]) {
    /* Realiza a "operação Banner", que recebe dois vetores: o primeiro,
    o vetor U a ser modificado, e o segundo, o vetor B. Todos os valores que
    estiverem no vetor U mas não em B serão alterados para 0, no vetor U.
    Portanto, é feita essa checagem e substituição.
    */

    int i, j, k, troca;
    for (i = 0; i <= tam_vetor_b; i++)
        scanf("%d", &vetor_b[i]); /* Entrada vetor B */
    for (j = 0; j <= tam_vetor_u; j++) {
        for (k = 0; k <= tam_vetor_b; k++) {
            if (vetor_u[j] == vetor_b[k]) {
            troca = 0;
            break;
            }
            else
            troca = 1;
        }
        if (troca)
        vetor_u[j] = 0;
    }
    imprime_vetor(vetor_u, tam_vetor_u);
}


void op_mobius(int tam_vetor_u, int vetor_u[]) {
    /* Realiza a "operação Mobius", que multiplica as entradas de posições
    ímpares do vetor U por determinado valor escalar M, alterando o vetor.
    */

    int valor_M, i;
    scanf("%d", &valor_M); /* Entrada valor M */
    for (i = 1; i <= tam_vetor_u; i += 2) {
        vetor_u[i] *= valor_M;
    }
    imprime_vetor(vetor_u, tam_vetor_u);
}


void op_mov_ciclico(int tam_vetor_u, int vetor_u[]) {
    /* Realiza o "movimento cíclico" do vetor U: o último elemento se desloca
    para a primeira posição e os demais valores se deslocam para a posição
    para a posição seguinte. O movimento ocorre P vezes, dado na entrada.
    Para tanto, utiliza-se o vetor U e um vetor auxiliar.
    */ 

    int valor_P, i, j, k, vetor_aux[tam_vetor_u], ultimo;
    scanf("%d", &valor_P); /* Entrada valor P */
    for (i = 0; i < valor_P; i++) {
        ultimo = vetor_u[tam_vetor_u];
        vetor_aux[0] = ultimo;
        for (j = 0; j < tam_vetor_u; j++) {
            vetor_aux[j + 1] = vetor_u[j];
        }
        for (k = 0; k <= tam_vetor_u; k++) 
        vetor_u[k] = vetor_aux[k];
    }
    imprime_vetor(vetor_u, tam_vetor_u);
}


void op_inverter(int tam_vetor_u, int vetor_u[]) {
    /* Operação de inversão do vetor U. Utiliza-se o vetor U e um vetor
    auxiliar. 
    */

    int vetor_aux[tam_vetor_u], i, k;
    k = 0;
    for (i = tam_vetor_u; i >= 0; i--) {
        vetor_aux[k] = vetor_u[i];
        k++;
    }
    for (k = 0; k <= tam_vetor_u; k++) 
        vetor_u[k] = vetor_aux[k];
    imprime_vetor(vetor_u, tam_vetor_u);
}

int main() {
    /* Código principal. Recebe o número T, correspondente à quantidade de valores
    no vetor U, o vetor U inicial, a quantidade de operações a serem realizadas e
    o número correspondente a cada operação. 
    */

    int qtd_T, tam_vetor_u, i, qtd_operacoes, num_op;
    scanf("%d", &qtd_T);
    tam_vetor_u = qtd_T - 1;
    int vetor_u[tam_vetor_u]; /* Cria-se o vetor */
    for (i = 0; i < qtd_T; i++) 
        scanf("%d", &vetor_u[i]); /* Coloca-se os valores no vetor */
    scanf("%d", &qtd_operacoes);
    for (i = 0; i < qtd_operacoes; i++) {
        scanf("%d", &num_op);
        if (num_op == 1) {
            int tam_vetor_b, qtd_B;
            scanf("%d", &qtd_B);
            tam_vetor_b = qtd_B - 1;
            int vetor_b[tam_vetor_b];
            op_banner (tam_vetor_b, vetor_b, tam_vetor_u, vetor_u);
        }
        if (num_op == 2) 
            op_mobius (tam_vetor_u, vetor_u);
        if (num_op == 3)
            op_mov_ciclico (tam_vetor_u, vetor_u);
        if (num_op == 4)
            op_inverter (tam_vetor_u, vetor_u);
    }
    return 0;
}