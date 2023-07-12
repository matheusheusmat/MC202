#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

// Código do cliente.
int main() {
    int i, n_op, data, pista;
    p_no_mapa mapa;
    p_no_visita visita;
    char nome_op[20], nome_cidade[20];
    mapa = cria_arv_mapa();
    visita = cria_arv_visita();
    scanf("%d", &n_op);
    for (i = 0; i < n_op; i++) {
        scanf("%s", nome_op);
        if (!strcmp(nome_op, "insere_visita")) {
            scanf("%s", nome_cidade);
            scanf("%d", &data);
            scanf("%d", &pista);
            mapa = insere_mapa(mapa, nome_cidade);
            visita = insere_visita(visita, data, nome_cidade, pista);
        }
        else if (!strcmp(nome_op, "exclui_visita")) {
            scanf("%d", &data);
            visita = exclui_visita(visita, data, nome_cidade);
            mapa = busca_mapa(mapa, nome_cidade);
        }
        else if (!strcmp(nome_op, "relatorio_data"))
            le_dados_rel_data(visita);
        else if (!strcmp(nome_op, "relatorio_pista"))
            le_dados_rel_pista(visita);
    }
    libera_mapa(mapa);
    libera_visita(visita);
    return 0;
}