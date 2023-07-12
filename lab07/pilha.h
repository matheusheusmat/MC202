// pilha.h for lab07 by heusmat

// Estrutura de um nó de lista ligada, formato da pilha.
// Cada nó tem um vetor de até 50 caracteres, membro que armazena
// a quantidade de caracteres atualmente no vetor, e um ponteiro
// para o próximo nó (na pilha, abaixo dele).
typedef struct No {
    char v[50];
    int tam;
    struct No *prox;
} No;

typedef struct No * p_no;

// Estrutura da pilha, que contém apenas o nó topo.
typedef struct Pilha {
    p_no topo;
} Pilha;

typedef struct Pilha * p_pilha;

// Todas as funções detalhadas na implementação.
p_pilha cria_pilha();

void cria_topo(p_pilha p);

void empilha(p_pilha p, char caracter);

void imprime_pilha(p_pilha p, p_no cam_atual);

void remove_pilha(p_pilha p, int qtd);

int obter_qtd(char *string, int tam);

void destruir_pilha(p_pilha p);

void destruir_lista(p_no topo);