#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ultron.h"


void imprime_matriz(matriz mat) {
    /* Recebe a matriz resultante de cada operação como parâmetro, 
    imprimindo-a elemento a elemento.*/

    int i, j;
    for (i = 0; i < mat->linhas; i++) {
        for (j = 0; j < mat->colunas; j++)
            printf("%d ", mat->dados[i][j]);
        printf("\n");
    }
    printf("###\n");
}


void organiza_linha(matriz mat, int linha) {
    /* Função chamada pela função "adiciona colunas", para reorganizar
    cada linha em ordem numérica. Nela, adiciona-se o elemento na linha
    de acordo com as seguintes regras (contidas em três "if"):
    - Se for menor que o primeiro elemento da linha (já ordenada), o novo
    elemento torna-se o primeiro, e os demais são movidos uma posição à frente.
    - Se for maior que o último elemento, é adicionado à linha na posição
    seguinte à este.
    - Caso nenhuma dessas condiçôes seja satisfeita, é feita uma busca:
    passando elemento a elemento, caso o elemento a ser inserido for
    maior que um elemento na posição (j) do vetor e menor que o elemento
    (j + 1), os elementos nas posições (j + 1) em diante são deslocados
    uma posição à frente, e o novo elemento é adicionado em (j + 1).
    */

    int j, k, num_atual;
    scanf("%d", &num_atual);
    for (j = 0; j < mat->colunas; j++) {
        if (num_atual > mat->dados[linha][mat->colunas - 1]) {
            mat->dados[linha][mat->colunas] = num_atual;
            break;
        }
        else if (num_atual < mat->dados[linha][0]) {
            for (k = mat->colunas; k > 0; k--)
                mat->dados[linha][k] = mat->dados[linha][k - 1];
            mat->dados[linha][0] = num_atual;
            break;
        }
        else if (num_atual >= mat->dados[linha][j] && num_atual <= mat->dados[linha][j + 1]) {
            for (k = mat->colunas; k > j + 1; k--)
                mat->dados[linha][k] = mat->dados[linha][k - 1];
            mat->dados[linha][j + 1] = num_atual;
            break;
        }
    }
}


void realoca_linhas(matriz mat, int adiciona) {
    /* São realocadas as linhas, conforme as especificações do enunciado:
    Se o número de linhas ocupadas (guardado no membro mat->linhas) for
    igual ao número de linhas alocadas para a matriz(mat->l_alocadas),
    dobra-se o número de linhas alocadas.
    Caso as linhas ocupadas seja menor ou igual a 1/4 das linhas alocadas,
    o número de linhas alocadas é reduzido à metade.
    */

    int **nova_matriz, i;
    if (adiciona)
        mat->l_alocadas *= 2;
    else
        mat->l_alocadas /= 2;
    nova_matriz = malloc(mat->l_alocadas * sizeof(int *));
    for (i = 0; i < mat->l_alocadas; i++)
        nova_matriz[i] = malloc(mat->c_alocadas * sizeof(int));
    for (i = 0; i < mat->linhas; i++)
        nova_matriz[i] = mat->dados[i];
    mat->dados = nova_matriz;
}


void realoca_colunas(matriz mat, int adiciona) {
    /* São realocadas as colunas, conforme as especificações do enunciado:
    Se o número de colunas ocupadas (guardado no membro mat->colunas) for
    igual ao número de colunas alocadas para a matriz(mat->l_alocadas),
    dobra-se o número de colunas alocadas.
    Caso as colunas ocupadas seja menor ou igual a 1/4 das colunas alocadas,
    o número de colunas alocadas é reduzido à metade.
    */

    int **nova_matriz, i;
    if (adiciona)
        mat->c_alocadas *= 2;
    else
        mat->c_alocadas /= 2;
    nova_matriz = malloc(mat->l_alocadas * sizeof(int *));
    for (i = 0; i < mat->l_alocadas; i++)
        nova_matriz[i] = malloc(mat->c_alocadas * sizeof(int));
    for (i = 0; i < mat->linhas; i++)
        nova_matriz[i] = mat->dados[i];
    mat->dados = nova_matriz;
}


void verifica_mem(matriz mat) {
    /* Realiza a verificação se a matriz precisa ser realocada,
    conforme especificações dadas no enunciado.
    - Dobrar a dimensão alocada, caso esteja cheia de valores.
    - Reduzir a dimensão alocada à metade, caso 1/4 ou menos dela
    estiver preenchida por valores.
    */

    float linhas = mat->linhas;
    float colunas = mat->colunas;
    float linhas_aloc = mat->l_alocadas;
    float colunas_aloc = mat->c_alocadas;
    if (mat->linhas == mat->l_alocadas)
        realoca_linhas(mat, 1);
    if (mat->colunas == mat->c_alocadas)
        realoca_colunas(mat, 1);
    if (linhas / linhas_aloc <= 0.25)
        realoca_linhas(mat, 0);
    if (colunas / colunas_aloc <= 0.25)
        realoca_colunas(mat, 0);
}


void adiciona_linha(matriz mat, int linha) {
    /* Adiciona uma linha, já ordenada, ao final da matriz. Caso não
    haja alocação de memória suficiente na matriz para esta linha, é
    realizada a realocação.
    */

    int j;
    if (mat->linhas == mat->l_alocadas)
        realoca_linhas(mat, 1);
    for (j = 0; j < mat->colunas; j++)
        scanf("%d", &mat->dados[linha][j]);
    mat->linhas++;
}


void adiciona_coluna(matriz mat, int coluna) {
    /* Adiciona uma coluna à matriz, um elemento dado na entrada
    por linha. Após isso, a linha precisa ser ordenada.*/

    int i;
    if (mat->colunas == mat->c_alocadas)
        realoca_colunas(mat, 1);
    for (i = 0; i < mat->linhas; i++)
        organiza_linha(mat, i);
    mat->colunas++;
}


void retira_linha(matriz mat) {
    /* Retira uma linha, especificada na entrada, da matriz. 
    Após isso, as linhas são reorganizadas.
    */

    int i, linha;
    scanf("%d", &linha);
    for (i = linha; i < mat->linhas - 1; i++)
        mat->dados[i] = mat->dados[i + 1];
    mat->dados[i] = malloc(mat->c_alocadas * sizeof(int));
    mat->linhas--;
}


void retira_coluna(matriz mat) {
    /* Retira uma coluna, especificada na entrada, da matriz. 
    Após isso, as demais colunas são reorganizadas.
    */

    int i, j, coluna;
    scanf("%d", &coluna);
    for (i = 0; i < mat->linhas; i++)
        for (j = coluna; j < mat->colunas - 1; j++)
            mat->dados[i][j] = mat->dados[i][j + 1];
    mat->colunas--;
}


void le_operacao(matriz mat) {
    /* Realiza a leitura da operação a ser feita em seguida, dada
    na entrada: se é IN ou OUT (adição ou remoção) e L ou C (de linha
    ou coluna).
    */

    char nome_op[3], op_l_ou_c;
    scanf("%s %c", nome_op, &op_l_ou_c);
        if ((strcmp(nome_op, "IN") == 0) && (op_l_ou_c == 'L'))
            adiciona_linha(mat, mat->linhas);
        else if ((strcmp(nome_op, "IN") == 0) && (op_l_ou_c == 'C'))
            adiciona_coluna(mat, mat->colunas);
        else if ((strcmp(nome_op, "OUT") == 0) && (op_l_ou_c == 'L'))
            retira_linha(mat);
        else if ((strcmp(nome_op, "OUT") == 0) && (op_l_ou_c == 'C'))
            retira_coluna(mat);
}


matriz criar_linhas(matriz mat, int linhas, int colunas) {
    /* Insere vetores, dados em entrada, na matriz. A inserção
    é feita linha a linha. Após isso, os vetores são guardados no
    registro mat->dados, um "ponteiro duplo".
    */

    int i, j;
    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
            scanf("%d", &mat->dados[i][j]);
    return mat;
}


matriz alocar_inicial() {
    /* Realiza a alocação inicial de memória da matriz, de acordo
    com o número de linhas (quantidade de vetores) e colunas (tamanho
    de cada vetor dados na entrada.
    As dimensões são armazenadas no registro "mat".
    */

    int i, colunas, linhas;
    matriz mat;
    mat = malloc(sizeof(struct matrix));
    scanf("%d %d", &linhas, &colunas);
    mat->linhas = linhas;
    mat->colunas = colunas;
    mat->l_alocadas = linhas;
    mat->c_alocadas = colunas;
    mat->dados = malloc(linhas * sizeof(int *));
    for (i = 0; i < linhas; i++)
        mat->dados[i] = malloc(colunas * sizeof(int));
    return criar_linhas(mat, linhas, colunas);
}

