#ifndef logtree_h
#define logtree_h
typedef enum classe {
  NULO = 0,
  Premium = 1,
  Ouro = 2,
  Prata = 3,
  Bronze = 4,
  Leezu = 5
} Classe;

typedef enum { Negro, Rubro } Cor;

typedef struct _log_no {
  Classe chave;
  Cor cor;
  float timer;
  int caixa;
  int conta;
  struct _log_no *pai;
  struct _log_no *esq;
  struct _log_no *dir;
} Log;

typedef struct rbtree {
  Log *raiz;
  Log *nulo;
} RBT;

RBT *log_inicializar();

void log_registrar(RBT *T, int conta, int classe, float timer, int caixa);

int log_obter_soma_por_classe(RBT *T, Log *no, Classe classe);

int log_obter_contagem_por_classe(RBT *T, Log *no, Classe classe);

float log_media_por_classe(RBT *T, Log *no, Classe classe);

void log_emordem(RBT *T, Log *no);

int log_alt_negros(RBT *T);

#endif
