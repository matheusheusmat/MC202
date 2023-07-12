/* heap.h for lab09 by heusmat*/
#define PAI(i) ((i-1)/2)
#define F_ESQ(i) (2*i+1)
#define F_DIR(i) (2*i+2)

// Estrutura de um item da fila de prioridade: um código de
// processo P (num_P) e seu número de prioridade C (num_C).
// O número P é um identificador, mas pode ser usado para critério
// de desempate para dois C iguais, na inserção ou extração de máximos.
typedef struct Item {
    int num_P;
    int num_C;
} Item;

// Estrutura da fila de prioridade. Contém o vetor v, o número 
// atual de itens (n) e a quantidade de itens alocados para o vetor
// (tamanho).
typedef struct FP {
    Item *v;
    int n, tamanho;
} FP;

typedef FP * p_fp;

// Todas as funções detalhadas na implementação.
void troca(Item *a, Item *b);

p_fp criar_filaprio(int tam);

void sobe_no_heap(p_fp fprio, int k);

void desce_no_heap(p_fp fprio, int k);

void insere(p_fp fprio, Item item);

void muda_prioridade(p_fp fprio, int k, int valor);

Item extrai_maximo(p_fp fprio);

void procura_max(p_fp fprio);

void busca_e_muda_prio(p_fp fprio);

void libera_fila(p_fp fprio);