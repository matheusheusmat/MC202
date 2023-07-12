// represa.c for lab03.c by heusmat
#include <stdio.h>
#include "represa.h"


represa le_detalhes() {
    /* Lê as entradas e as armazena nos membros da estrutura "represa".
    As entradas são, respectivamente: nome da represa, sua capacidade máxima,
    a quantidade de níveis medidos e o vetor de suas medições.
    */
    int i;
    represa represa_atual;
    scanf("%s", represa_atual.nome);
    scanf("%f", &represa_atual.capmax);
    scanf("%d", &represa_atual.qtd_niveis);
    for (i = 0; i < represa_atual.qtd_niveis; i++) 
        scanf("%d", &represa_atual.niveis[i]);
    return represa_atual;
}


int calc_media(int qtd_niveis, int niveis[]) {
    /* Realiza o cálculo da média dos valores, e a armazena na estrutura "represa",
    em seu membro "media".
    */

    int i, soma_parcial, media;
    soma_parcial = 0;
    for (i = 0; i < qtd_niveis; i++) 
        soma_parcial += niveis[i];
    media = (soma_parcial / qtd_niveis);
    return media;
}


int define_alerta(int qtd_niveis, int niveis[], float capmax) {
    /* Compara os elementos do vetor de medições com a capacidade máxima da
    represa. Caso algum deles superar 90% da capacidade, é retornado 1 para
    o membro "alerta" da estrutura, tornando-o verdadeiro, e a mensagem de alerta
    será emitida. Caso contrário, não.
    */

    int i, valor_atual;
    for (i = 0; i < qtd_niveis; i++) {
        if ((niveis[i] / capmax) > 0.9) {
            valor_atual = 1;
            break;
        }
        else
            valor_atual = 0;
    }
    return valor_atual;
}


void organiza_nome(char nome[]) {
    /* Padroniza o nome de acordo com as especificações: primeiramente, é verificado se o
    vetor "nome" da represa possui o prefixo "represa_de_". Caso positivo, os elementos
    são movidos para frente, removendo o prefixo. Após isso, as letras maiúsculas são passadas
    para minúsculas (somando-se 32, de acordo com a tabela ASCII). Os underscores ("_") são
    substituídos por espaços (" ") e, quando detecta-se uma letra, a padronização é parada,
    e é marcado o fim do vetor por "\0".
    */

    int i;
    if (nome[0] == 'r' && nome[1] == 'e' && nome[2] == 'p' && nome[3] == 'r' && nome[4] == 'e'
    && nome[5] == 's' && nome[6] == 'a' && nome[7] == '_' && nome[8] == 'd' && nome[9] == 'e'
    && nome[10] == '_')
        for (i = 0; i < 100; i++)
            nome[i] = nome[i + 11];
    for (i = 0; i < 100; i++) {
        if (nome[i] >= 65 && nome[i] <=+ 90)
            nome[i] += 32;
        else if (nome[i] == 95)
            nome[i] = 32;
        else if (nome[i] >= 48 && nome[i] <= 57) {
            nome[i] = '\0';
            i = 100;
        }
    }
}


void imprime_detalhes(char nome[], int qtd_niveis, int media, int alerta) {
    /* Código de impressão dos seguintes atributos da estrutura represa: nome,
    quantidade de níveis medidos, média dos níveis e, caso "alerta" seja verdadeiro,
    é imprimida a mensagem de atenção.
    */

    printf("NOME: %s\n", nome);
    printf("QTD NIVEIS: %d\n", qtd_niveis);
    printf("MEDIA: %d\n", media);
    if (alerta)
        printf("CAPACIDADE ACIMA DE 90%% DA MAXIMA!\n");
    printf("#####\n");
}