/* grafo.h for lab11 by heusmat */

// Estrutura de um nó da lista ligada, que armazena o número correspondente
// aos vértices adjacentes a um vértice. Há, também, um ponteiro para o próximo
// nó.
typedef struct No {
    int num;
    struct No *prox;
} No;

typedef No * p_no;

// Estrutura do grafo, em versão de lista de adjacências. Cada posição do vetor
// "adj" corresponde a um vértice. O item na posição corresponde à lista ligada que
// armazena os números de vértices adjacentes a este, ou seja, entre tais vértices
// há uma aresta. 
typedef struct {
    p_no *adj;
    int n;
} Grafo;

typedef Grafo * p_grafo;

/* Funções detalhadas na implementação */
p_grafo criar_grafo(int n);

p_no insere_na_lista(p_no lista, int num);

void insere_aresta(p_grafo g, int u, int v);

p_no remove_da_lista(p_no lista, int num);

void remove_aresta(p_grafo g, int u, int v);

void libera_lista(p_no lista);

void libera_grafo(p_grafo g);

void le_arestas(p_grafo g);

void busca_em_profundidade(p_grafo g, int *pai, int p, int v);

int *encontra_caminhos(p_grafo g, int s);

int calc_distancia(int v, int *pai);

void troca(int *a, int *b);

void ordenar(int *v, int n);

void imprime_crescente(p_no novo, int qtd);

void novo_centro(p_grafo g, int p);

void le_e_calc_distancia(p_grafo g);

void le_remocao(p_grafo g);

void le_operacoes(p_grafo g);
