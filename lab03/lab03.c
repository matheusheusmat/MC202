// lab03.c by heusmat
#include <stdio.h>
#include "represa.h"

int main() {
    /* Código do cliente, que recebe apenas a quantidade de represas a serem
    analisadas. Do restante, a estrutura de "represa_atual" e os protótipos
    de funções estão na interface "represa.h", e as funções, na implementação
    "represa.c"
    */

    int qtd_represas, i;
    represa represa_atual;
    scanf("%d", &qtd_represas);
    for (i = 0; i < qtd_represas; i++) {
        represa_atual = le_detalhes();
        represa_atual.media = calc_media(represa_atual.qtd_niveis, represa_atual.niveis);
        represa_atual.alerta = define_alerta(represa_atual.qtd_niveis, represa_atual.niveis,
                                             represa_atual.capmax);
        organiza_nome(represa_atual.nome);
        imprime_detalhes(represa_atual.nome, represa_atual.qtd_niveis,
                         represa_atual.media, represa_atual.alerta);
    }
    return 0;
}