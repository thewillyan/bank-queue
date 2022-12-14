#include "logtree.h"
#include <stdio.h>
#include <stdlib.h>

/*
Inicilicializa um Arvore Rubro Negra com um nulo de T ja alocado
Isso vai diminuir a quantidade de de nos nulos para a propriedade
Rubro Negra
*/
RBT *log_inicializar() {
  RBT *T = malloc(sizeof(RBT));
  Log *nulo = malloc(sizeof(Log));

  nulo->esq = nulo->dir = nulo->pai = NULL;
  nulo->cor = Negro;
  nulo->ops = nulo->chave = nulo->conta = nulo->caixa = -1;

  T->nulo = nulo;
  T->raiz = T->nulo;
  return T;
}

/*
Aqui vai criar um no da arvore com as informacoes de conta
classe, tempo, caixa e operacoes
 */
Log *log_criar_no(Log *pai, int conta, int classe, int timer, int caixa,
                  int ops) {
  Log *no;
  no = malloc(sizeof(Log));
  no->chave = timer;
  no->classe = (Classe)classe;
  no->conta = conta;
  no->caixa = caixa;
  no->ops = ops;
  no->pai = pai;
  no->esq = no->dir = NULL;
  // Segredo dos deuses ta aqui
  no->cor = Rubro;

  return no;
}

/*
 Isso aqui eh pra concertar as propriedades rubro negras
 Rotacionado a arvore a esquerda de um no X
    raiz                       raiz
     |                          |
     Y      log_rotesq(T, X)    X
    /  \        --->          /  \
  NULO  X                    Y  NULO
 */
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

/*
 Isso aqui eh pra concertar as propriedades rubro negras
 Rotacionado a arvore a direita de um no Y
 */
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

/*
Aqui eu registro um novo no na RBT na posicao mais adequada
onde a chave de cada no eh o timer, dps de inserido eu
concerto a arvore para manter as prop. Rubro Negras
*/
void log_registrar(RBT *T, int conta, int classe, int timer, int caixa,
                   int ops) {
  Log *no, *raiz = T->raiz, *pai = T->nulo;
  int chave = timer;

  while (raiz != T->nulo) {
    pai = raiz;
    if (chave <= raiz->chave)
      raiz = raiz->esq;
    else
      raiz = raiz->dir;
  }

  no = log_criar_no(pai, conta, classe, timer, caixa, ops);

  if (pai == T->nulo)
    T->raiz = no;
  else if (no->chave <= pai->chave)
    pai->esq = no;
  else
    pai->dir = no;

  no->dir = no->esq = T->nulo;
  log_concertar(T, no);
};

/*
Aqui retorna a quantidade de tempo que uma determinada classe
ocupou utilizando recursao, se a classe do no for igual a classe
do parametro eu retorno o tempo, senao eu retorno 0
*/
int log_obter_soma_por_classe(RBT *T, Log *no, Classe classe) {
  if (no == T->nulo) {
    return 0;
  } else {
    if (no->classe == classe) {
      return no->chave + log_obter_soma_por_classe(T, no->esq, classe) +
             log_obter_soma_por_classe(T, no->dir, classe);
    } else {
      return 0 + log_obter_soma_por_classe(T, no->esq, classe) +
             log_obter_soma_por_classe(T, no->dir, classe);
    }
  }
}

/*
Aqui retorna a quantidade de clientes que uma determinada classe
utilizando recursao, se a classe do no for igual a classe
do parametro eu retorno o 1, senao eu retorno 0
*/
int log_obter_contagem_por_classe(RBT *T, Log *no, Classe classe) {
  if (no == T->nulo) {
    return 0;
  } else {
    if (no->classe == classe) {
      return 1 + log_obter_contagem_por_classe(T, no->esq, classe) +
             log_obter_contagem_por_classe(T, no->dir, classe);
    } else {
      return 0 + log_obter_contagem_por_classe(T, no->esq, classe) +
             log_obter_contagem_por_classe(T, no->dir, classe);
    }
  }
}

/*
Utilizando as duas recursoes anteriores eu criou uma media entre elas
e retorno esse valor
*/
float log_media_por_classe(RBT *T, Log *no, Classe classe) {
  int clientes, tempo_total;
  float media;

  tempo_total = log_obter_soma_por_classe(T, no, classe);
  clientes = log_obter_contagem_por_classe(T, no, classe);

  if (clientes == 0)
    return 0;

  media = (float)tempo_total / (float)clientes;
  return media;
}

/*
Faz o percurso em ordem da arvore
*/
void log_emordem(RBT *T, Log *no) {
  if (no != T->nulo) {
    log_emordem(T, no->esq);
    printf("%d\n", no->chave);
    log_emordem(T, no->dir);
  }
}

/*
Retorna a altura em negros nao nulos da arvore para avaliar
as propriedades rubro negras
*/
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

/*
Retorna um endereco para o no com o maior tempo, portanto o MAXIMO da RBT,
ja que utilizamos o tempo como chave
*/
Log *log_maximo(RBT *T) {
  Log *no;
  if (T->raiz == T->nulo)
    return NULL;
  no = T->raiz;
  while (no->dir != T->nulo)
    no = no->dir;

  return no;
}

/*
Aqui ocorre a transversao em ordem da arvore para pegar as operacoes,
quantidade e tempo total de cada classe.
E eu retorno uma estrutura chamada TUBIAS que eh so um Struct que
possui como campos ops, clientes e tempo_total
Assim eu economizo 2 transversoes da arvore para cada classe
na hora de gerar o output
Poderia ser mais eficiente se fosse utilizado como chave a classe, mas
ficaria mais dificil de achar o tempo maximo da arvore
*/
Tubias log_tubias(RBT *T, Classe classe) {
  Tubias toba;
  Log *curr, *pre;
  toba.ops = toba.clientes = toba.tempo_total = 0;

  if (T->raiz == T->nulo)
    return toba;

  curr = T->raiz;
  while (curr != T->nulo) {

    if (curr->esq == T->nulo) {
      if (curr->classe == classe) {
        toba.ops += curr->ops;
        toba.clientes++;
        toba.tempo_total += curr->chave;
      }
      curr = curr->dir;
    } else {
      pre = curr->esq;
      while (pre->dir != T->nulo && pre->dir != curr)
        pre = pre->dir;

      if (pre->dir == T->nulo) {
        pre->dir = curr;
        curr = curr->esq;
      }

      else {
        pre->dir = T->nulo;

        if (curr->classe == classe) {
          toba.ops += curr->ops;
          toba.clientes++;
          toba.tempo_total += curr->chave;
        }
        curr = curr->dir;
      }
    }
  }

  return toba;
}