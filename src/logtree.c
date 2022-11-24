#include "logtree.h"
#include <stdio.h>
#include <stdlib.h>

RBT *log_inicializar() {
  RBT *T = malloc(sizeof(RBT));
  Log *nulo = malloc(sizeof(Log));

  nulo->esq = nulo->dir = nulo->pai = NULL;
  nulo->chave = (Classe)0;
  nulo->cor = Negro;
  nulo->conta = nulo->caixa = -1;

  T->nulo = nulo;
  T->raiz = T->nulo;
  return T;
}

Log *log_criar_no(Log *pai, int conta, int classe, float timer, int caixa) {
  Log *no;
  no = malloc(sizeof(Log));
  no->chave = (Classe)classe;
  no->conta = conta;
  no->timer = timer;
  no->caixa = caixa;
  no->pai = pai;
  no->esq = no->dir = NULL;
  // Segredo dos deuses ta aqui
  no->cor = Rubro;

  return no;
}

void log_rotesq(RBT *T, Log *x) {
  Log *y = x->dir;
  x->dir = y->esq;

  if (y->esq != T->nulo)
    y->esq->pai = x;

  y->pai = x->pai;

  if (x->pai == T->nulo)
    T->raiz = y;
  else if (x == x->pai->esq)
    x->pai->esq = y;
  else
    x->pai->dir = y;

  y->esq = x;
  x->pai = y;
}

void log_rotdir(RBT *T, Log *y) {
  Log *x = y->esq;
  y->esq = x->dir;

  if (x->dir != T->nulo)
    x->dir->pai = y;

  x->pai = y->pai;

  if (y->pai == T->nulo)
    T->raiz = x;
  else if (y == y->pai->esq)
    y->pai->esq = x;
  else
    y->pai->dir = x;

  x->dir = y;
  y->pai = x;
}

/* A parada aqui eh que a gente so quer violar duas propriedades
Ou a propriedade 2 - a raiz eh Negro
ou a propriedade 4 - se um no eh Rubro, entao todos os seu filhos sao Negros
NUNCA JAMAIS JOSIAS VIOLE A REGRA 5 da altura de Negros
*/
void log_concertar(RBT *T, Log *caba) {
  Log *tio;
  while (T->raiz != caba && caba->cor == Rubro && caba->pai->cor == Rubro) {
    if (caba->pai == caba->pai->pai->esq) {
      tio = caba->pai->pai->dir;

      // Caso 1
      if (tio->cor == Rubro) {
        caba->pai->cor = Negro;
        tio->cor = Negro;
        caba = caba->pai->pai;
        caba->cor = Rubro;
      } else {
        if (caba == caba->pai->dir) {
          caba = caba->pai;
          log_rotesq(T, caba);
        }
        caba->pai->cor = Negro;
        caba->pai->pai->cor = Rubro;
        log_rotdir(T, caba->pai->pai);
      }

    } else {
      tio = caba->pai->pai->esq;

      if (tio->cor == Rubro) {
        caba->pai->cor = Negro;
        tio->cor = Negro;
        caba = caba->pai->pai;
        caba->cor = Rubro;
      } else {
        if (caba == caba->pai->esq) {
          caba = caba->pai;
          log_rotdir(T, caba);
        }
        caba->pai->cor = Negro;
        caba->pai->pai->cor = Rubro;
        log_rotesq(T, caba->pai->pai);
      }
    }
  }

  T->raiz->cor = Negro;
}

void log_registrar(RBT *T, int conta, int classe, float timer, int caixa) {
  Log *no, *raiz = T->raiz, *pai = T->nulo;
  Classe chave = (Classe)classe;

  while (raiz != T->nulo) {
    pai = raiz;
    if (chave <= raiz->chave)
      raiz = raiz->esq;
    else
      raiz = raiz->dir;
  }

  no = log_criar_no(pai, conta, classe, timer, caixa);

  if (pai == T->nulo)
    T->raiz = no;
  else if (no->chave <= pai->chave)
    pai->esq = no;
  else
    pai->dir = no;

  no->dir = no->esq = T->nulo;
  log_concertar(T, no);
};

int log_obter_soma_por_classe(RBT *T, Log *no, Classe classe) {
  if (no == T->nulo) {
    return 0;
  } else {
    if (no->chave == classe) {
      return no->timer + log_obter_soma_por_classe(T, no->esq, classe) +
             log_obter_soma_por_classe(T, no->dir, classe);
    } else {
      if (no->chave < classe) {
        return 0 + log_obter_soma_por_classe(T, no->dir, classe);
      } else {
        return 0 + log_obter_soma_por_classe(T, no->esq, classe);
      }
    }
  }
}

int log_obter_contagem_por_classe(RBT *T, Log *no, Classe classe) {
  if (no == T->nulo) {
    return 0;
  } else {
    if (no->chave == classe) {
      return 1 + log_obter_contagem_por_classe(T, no->esq, classe) +
             log_obter_contagem_por_classe(T, no->dir, classe);
    } else {
      if (no->chave < classe) {
        return 0 + log_obter_contagem_por_classe(T, no->dir, classe);
      } else {
        return 0 + log_obter_contagem_por_classe(T, no->esq, classe);
      }
    }
  }
}

float log_media_por_classe(RBT *T, Log *no, Classe classe) {
  int clientes, tempo_total;
  float media;

  tempo_total = log_obter_soma_por_classe(T, no, classe);
  clientes = log_obter_contagem_por_classe(T, no, classe);
  media = (float)tempo_total / (float)clientes;
  return media;
}

void log_emordem(RBT *T, Log *no) {
  if (no != T->nulo) {
    log_emordem(T, no->esq);
    printf("%d\n", no->chave);
    log_emordem(T, no->dir);
  }
}

int log_alt_negros(RBT *T) {
  int alt = 0;
  Log *no = T->raiz;

  while (no != T->nulo) {
    if (no->cor == Negro)
      alt++;
    no = no->esq;
  }
  return alt;
}
