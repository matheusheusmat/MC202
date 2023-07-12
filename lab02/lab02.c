// lab02.c by heusmat
#include <stdio.h>
#include <string.h>
#define MAX 100


void cria_matriz_A(int matriz[][MAX], int N) {
    /* Função responsável por criar a matriz_A, logo após receber
    suas dimensões, de acordo com as especificações (colunas de largura
    3, começando pelo branco (1), intercaladas.)
    */

    int n_listras, i, j, k;
    n_listras = N / 3;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            matriz[i][j] = 0;
    }
    for (i = 0; i < N; i++) {
        for (k = 0; k < n_listras; k += 2) {
            for (j = 0; j < 3; j++)
                matriz[i][j + k * 3] = 1;
        }
    }
}


void imprime_matriz(int matriz[][MAX], int num_N) {
    /* Imprime a matriz de saída após cada operação realizada,
    linha por linha.
    */

    int i, j;
    printf("\n");
    for (i = 0; i < num_N; i++) {
        for (j = 0; j < num_N; j++)
            printf("%d ", matriz[i][j]);
        printf("\n");
    }
}


void transposta(int mat_ent[][MAX], int mat_saida[][MAX], int num_N) {
    /* Realiza a transposição da matriz de entrada, isto é, o 
    elemento da i-ésima linha e j-ésima coluna é armazenado
    na j-ésima linha e i-ésima coluna da matriz auxiliar.

    Em todas as funções a partir dessa, com exceção de main(), 
    após realizar a operação, copia-se a matriz auxiliar na
    matriz de saída, que pode ser A ou B, servindo como acumulador.
    Além disso, imprime-se a matriz de saída, chamando-se a função
    'imprime_matriz'.
    */

    int i, j, mat_aux[MAX][MAX];
    for (i = 0; i < num_N; i++) {
        for (j = 0; j < num_N; j++)
            mat_aux[i][j] = mat_ent[j][i];
    }
    for (i = 0; i < num_N; i++) {
        for (j = 0; j < num_N; j++)
            mat_saida[i][j] = mat_aux[i][j];
    }
    imprime_matriz(mat_saida, num_N);
}


void soma(int mat_ent1[][MAX], int mat_ent2[][MAX], int mat_saida[][MAX], int num_N) {
    /* Realiza a soma matricial das matrizes de entrada e
    armazena a matriz resultante na matriz de saída.
    */

    int i, j, mat_aux[MAX][MAX];
    for (i = 0; i < num_N; i++) {
        for (j = 0; j < num_N; j++) {
            if (mat_ent1[i][j] + mat_ent2[i][j] > 1)
                mat_aux[i][j] = 1;
            else
                mat_aux[i][j] = mat_ent1[i][j] + mat_ent2[i][j];
        }
    }
    for (i = 0; i < num_N; i++) {
        for (j = 0; j < num_N; j++)
            mat_saida[i][j] = mat_aux[i][j];
    }
    imprime_matriz(mat_saida, num_N);
}


void multi_elem(int mat_ent1[][MAX], int mat_ent2[][MAX], int mat_saida[][MAX], int num_N) {
    /* Realiza a multiplicação elemento a elemento das matrizes de entrada e
    armazena o resultado na matriz de saída.
    */

    int i, j, mat_aux[MAX][MAX];
    for (i = 0; i < num_N; i++) {
        for (j = 0; j < num_N; j++)
            mat_aux[i][j] = mat_ent1[i][j] * mat_ent2[i][j];
    }
    for (i = 0; i < num_N; i++) {
        for (j = 0; j < num_N; j++)
            mat_saida[i][j] = mat_aux[i][j];
    }
    imprime_matriz(mat_saida, num_N);
}


void multi_mat(int mat_ent1[][MAX], int mat_ent2[][MAX], int mat_saida[][MAX], int num_N) {
    int i, j, k, mat_aux[MAX][MAX], soma_parcial;
    /* Realiza a multiplicação matricial das matrizes de entrada e armazena
    o resultado na matriz de saída. A cada operação de linha x coluna, é usado
    "soma_parcial" para acumular o valor e colocá-lo na matriz auxiliar.
    */

    for (i = 0; i < num_N; i++) {
        for (j = 0; j < num_N; j++) {
            soma_parcial = 0;
            for (k = 0; k < num_N; k++)
                soma_parcial += mat_ent1[i][k] * mat_ent2[k][j];
        if (soma_parcial > 1)
            mat_aux[i][j] = 1;
        else
            mat_aux[i][j] = soma_parcial;
        }
    }
    for (i = 0; i < num_N; i++) {
        for (j = 0; j < num_N; j++)
            mat_saida[i][j] = mat_aux[i][j];
    }
    imprime_matriz(mat_saida, num_N);
}


void bordas(int mat_ent[][MAX], int mat_saida[][MAX], int num_N) {
    /* Delimita as "bordas" do objeto representado, isto é, armazena o
    "contorno" do objeto na matriz de saída. Para isso, todo pixel branco (valor = 1)
    que estiver cercado de píxeis brancos, é considerado "interior" do
    objeto, logo, é "apagado" (valor = 0).
    */

    int i, j, mat_aux[MAX][MAX];
    for (i = 0; i < num_N; i++) {
        if (i == 0 || i == num_N - 1) /* As bordas da matriz não são alteradas */
            for (j = 0; j < num_N; j++) /* (linhas superior e inferior, primeira e última colunas) */
                mat_aux[i][j] = mat_ent[i][j];
        else
            for (j = 0; j < num_N; j += num_N - 1)
                mat_aux[i][j] = mat_ent[i][j];
    }
    for (i = 1; i < num_N - 1; i++) {
        for (j = 1; j < num_N - 1; j++) {
            if (mat_ent[i][j] == 1) /* Verificação se o píxel branco (valor = 1) é borda ou não*/
                if ((mat_ent[i][j + 1] == 0 || mat_ent[i][j - 1] == 0 || mat_ent[i + 1][j] == 0 || mat_ent [i - 1][j] == 0 ||
                mat_ent[i + 1][j + 1] == 0 || mat_ent[i + 1][j - 1] == 0 || mat_ent[i - 1][j + 1] == 0 || mat_ent[i - 1][j - 1] == 0))
                    mat_aux[i][j] = 1; /* Caso positivo, é armazenado como 1 na matriz auxiliar*/
                else
                    mat_aux[i][j] = 0; /* Caso negativo, é armazenado como 0 na matriz auxiliar*/
            else
                mat_aux[i][j] = 0;
        }
    }
    for (i = 0; i < num_N; i++) {
        for (j = 0; j < num_N; j++)
            mat_saida[i][j] = mat_aux[i][j];
    }
    imprime_matriz(mat_saida, num_N);
}


int main() {
    /* Código principal, que recebe as dimensões da matriz quadrada,
    a quantidade de operações e o nome de cada operação, bem como a(s)
    matriz(es) de entrada e a matriz de saída.
    */

    int num_N, qtd_op, i, j;
    char nome_op[12], mat_1, mat_2, mat_saida;
    scanf("%d", &num_N);
    int matriz_A[MAX][MAX], matriz_B[MAX][MAX];
    cria_matriz_A(matriz_A, num_N);
    for (i = 0; i < num_N; i++) { /* Copia matriz_A para matriz_B */
        for (j = 0; j < num_N; j++)
            matriz_B[i][j] = matriz_A[i][j];
    }
    scanf("%d", &qtd_op);
    for (i = 0; i < qtd_op; i++) {
        scanf("%s ", nome_op);
        if (strcmp(nome_op, "TRANSPOSTA") == 0) {
            scanf("%c %c", &mat_1, &mat_saida);
            if (mat_1 == 'A') {
                if (mat_saida == 'A')
                    transposta(matriz_A, matriz_A, num_N);
                else
                    transposta(matriz_A, matriz_B, num_N);
            }
            else {
                if (mat_saida == 'A')
                    transposta(matriz_B, matriz_A, num_N);
                else
                    transposta(matriz_B, matriz_B, num_N);
            }
        }
        else if (strcmp(nome_op, "SOMA") == 0) {
            scanf("%c %c %c", &mat_1, &mat_2, &mat_saida);
            if (mat_1 != mat_2)
                if (mat_saida == 'A')
                    soma(matriz_A, matriz_B, matriz_A, num_N);
                else
                    soma(matriz_A, matriz_B, matriz_B, num_N);
            else
                if (mat_1 == 'A')
                    if (mat_saida == 'A')
                        soma(matriz_A, matriz_A, matriz_A, num_N);
                    else
                        soma(matriz_A, matriz_A, matriz_B, num_N);
                else
                    if (mat_saida == 'A')
                        soma(matriz_B, matriz_B, matriz_A, num_N);
                    else
                        soma(matriz_B, matriz_B, matriz_B, num_N);
        }
        else if (strcmp(nome_op, "MULTI_ELEM") == 0) {
            scanf("%c %c %c", &mat_1, &mat_2, &mat_saida);
            if (mat_1 != mat_2)
                if (mat_saida == 'A')
                    multi_elem(matriz_A, matriz_B, matriz_A, num_N);
                else
                    multi_elem(matriz_A, matriz_B, matriz_B, num_N);
            else
                if (mat_1 == 'A')
                    if (mat_saida == 'A')
                        multi_elem(matriz_A, matriz_A, matriz_A, num_N);
                    else
                        multi_elem(matriz_A, matriz_A, matriz_B, num_N);
                else
                    if (mat_saida == 'A')
                        multi_elem(matriz_B, matriz_B, matriz_A, num_N);
                    else
                        multi_elem(matriz_B, matriz_B, matriz_B, num_N);
        }
        else if (strcmp(nome_op, "MULTI_MAT") == 0) {
            scanf("%c %c %c", &mat_1, &mat_2, &mat_saida);
            if (mat_1 == 'A')
                if (mat_2 == 'A')
                    if (mat_saida == 'A')
                        multi_mat(matriz_A, matriz_A, matriz_A, num_N);
                    else
                        multi_mat(matriz_A, matriz_A, matriz_B, num_N);
                else
                    if (mat_saida == 'A')
                        multi_mat(matriz_A, matriz_B, matriz_A, num_N);
                    else
                        multi_mat(matriz_A, matriz_B, matriz_B, num_N);
            else
                if (mat_2 == 'A')
                    if (mat_saida == 'A')
                        multi_mat(matriz_B, matriz_A, matriz_A, num_N);
                    else
                        multi_mat(matriz_B, matriz_A, matriz_B, num_N);
                else
                    if (mat_saida == 'A')
                        multi_mat(matriz_B, matriz_B, matriz_A, num_N);
                    else
                        multi_mat(matriz_B, matriz_B, matriz_B, num_N);
        }
        else if (strcmp(nome_op, "BORDAS") == 0) {
            scanf("%c %c", &mat_1, &mat_saida);
            if (mat_1 == 'A')
                if (mat_saida == 'A')
                    bordas(matriz_A, matriz_A, num_N);
                else
                    bordas(matriz_A, matriz_B, num_N);
            else
                if (mat_saida == 'A')
                    bordas(matriz_B, matriz_A, num_N);
                else
                    bordas(matriz_B, matriz_B, num_N);
        }
    }
    return 0;
}
