// fila.h for lab07 by heusmat
#define MAX 500

// Estrutura da fila, implementada na forma de vetor circular.
// O vetor tem capacidade para 500 caracteres. Os membros 'ini'
// e 'fim' são importantes para o enfileiramento e impressão da
// fila.
typedef struct Fila {
    char v[MAX];
    int ini, fim, N, tamanho;
} Fila;

typedef Fila * p_fila;

// Todas as funções detalhadas na implementação.
p_fila cria_fila();

void enfileira(p_fila f, char *string, int tam_str);

char desenfileira(p_fila f);

void imprime_fila(p_fila f);

void remove_newline(char *string);

void destruir_fila(p_fila f);
