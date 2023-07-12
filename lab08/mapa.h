// mapa.h for lab08 by heusmat

// Estrutura de um nó da árvore MAPA. Comporta o nome da cidade
// e a quantidade de visitas que esta recebeu.
typedef struct No_mapa {
    char cidade[20];
    int qtd_vis;
    struct No_mapa *esq, *dir, *pai;
} No_mapa;

typedef No_mapa * p_no_mapa;

// Estrutura de um nó da árvore VISITA. É composto pela data de visita,
// nome da cidade visitada e um inteiro representando se alguma
// pista foi encontrada (1) ou não (0).
typedef struct No_visita {
    int data;
    char cidade[20];
    int pista;
    struct No_visita *esq, *dir, *pai;
} No_visita;

typedef No_visita * p_no_visita;

// Funções detalhadas na implementação.
p_no_visita cria_arv_visita();

p_no_mapa cria_arv_mapa();

p_no_mapa insere_mapa(p_no_mapa raiz, char *nome_cidade);

p_no_visita insere_visita(p_no_visita raiz, int data, char *nome_cidade, int pista);

void impr_rel_data(p_no_visita visita, int ini, int fim);

void le_dados_rel_data(p_no_visita visita);

void impr_rel_pista(p_no_visita visita, int ini, int fim);

void le_dados_rel_pista(p_no_visita visita);

void remover_sucessor_mapa(p_no_mapa raiz);

void remover_sucessor_visita(p_no_visita raiz);

p_no_mapa busca_mapa(p_no_mapa raiz, char *nome_cidade);

p_no_visita exclui_visita(p_no_visita raiz, int data, char *nome_cidade);

void libera_mapa(p_no_mapa raiz);

void libera_visita(p_no_visita raiz);