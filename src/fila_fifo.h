#ifndef fila_fifo_h
#define fila_fifo_h
#include "logtree.h"

typedef struct node{
    int valor;
    int chave;
    struct node*prox;
    struct node*ant;
}Node;

typedef struct fila{
    Node *prim;
    Node *ult;
    Classe classe;
    int tam;   
}Fila_FIFO;

Fila_FIFO * f_inicializar (Classe classe);
int f_inserir (Fila_FIFO *f, int chave, int valor);
int f_obter_proxima_chave (Fila_FIFO *f);
int f_consultar_proxima_chave (Fila_FIFO *f);
int f_consultar_proximo_valor (Fila_FIFO *f);
int f_num_elementos (Fila_FIFO *f);
int f_consultar_chave_por_posicao (Fila_FIFO *f, int posicao);
int f_consultar_valor_por_posicao (Fila_FIFO *f, int posicao);
#endif