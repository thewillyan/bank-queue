#ifndef logtree_h
#define logtree_h

#include "cliente.h"

typedef enum { Negro, Rubro } Cor;

typedef struct _log_no {
  Classe classe;
  Cor cor;
  int chave, caixa, conta, ops;
  struct _log_no *pai,*esq, *dir;
} Log;

typedef struct _tubias{
  int ops, clientes, tempo_total;
}Tubias;

typedef struct rbtree {
  Log *raiz;
  Log *nulo;
} RBT;

RBT *log_inicializar();

void log_registrar(RBT *T, int conta, int classe, int timer, int caixa, int ops);

int log_obter_soma_por_classe(RBT *T, Log *no, Classe classe);

int log_obter_contagem_por_classe(RBT *T, Log *no, Classe classe);

float log_media_por_classe(RBT *T, Log *no, Classe classe);

void log_emordem(RBT *T, Log *no);

int log_alt_negros(RBT *T);

Log* log_maximo(RBT *T);

Tubias log_tubias(RBT *T, Classe classe);

#endif