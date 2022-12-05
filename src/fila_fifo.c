#include "fila_fifo.h"
#include <stdio.h>
#include <stdlib.h>

Node *f_criar_no(Fila_FIFO *f, int valor, int chave) {
  Node *no = malloc(sizeof(Node));
  no->valor = valor;
  no->chave = chave;
  no->prox = f->ult;
  no->ant = NULL;
  return no;
}

Fila_FIFO *f_inicializar() {
  Fila_FIFO *fila = malloc(sizeof(Fila_FIFO));
  fila->prim = fila->ult = NULL;
  fila->tam = 0;
  return fila;
}

int f_buscar_chave(Fila_FIFO *f, int chave) {
  Node *aux = f->ult;
  while (aux != NULL && aux->chave != chave)
    aux = aux->prox;
  return aux == NULL ? 0 : aux->chave;
}

int f_inserir(Fila_FIFO *f, int chave, int valor) {
  Node *no;
  if (f_buscar_chave(f, chave))
    return 0;

  no = f_criar_no(f, valor, chave);

  if (f->prim == NULL)
    f->prim = no;
  else
    f->ult->ant = no;

  f->ult = no;
  f->tam++;
  return 1;
}

int f_obter_proxima_chave(Fila_FIFO *f) {
  Node *no = f->prim;
  int chave;

  if (no == NULL)
    return -1;

  chave = no->chave;
  f->prim = no->ant;
  if (f->ult == no)
    f->ult = NULL;
  else
    f->prim->prox = NULL;
  f->tam--;
  free(no);

  return chave;
}

int f_consultar_proxima_chave(Fila_FIFO *f) {
  return f->prim == NULL ? 0 : f->prim->chave;
}

int f_consultar_proximo_valor(Fila_FIFO *f) {
  return f->prim == NULL ? 0 : f->prim->valor;
}

int f_num_elementos(Fila_FIFO *f) { return f->tam; }

Node *f_no_na_posicao(Fila_FIFO *f, int posicao) {
  Node *aux = f->prim;
  int i = 1;
  if (posicao > f->tam)
    return NULL;
  while (i != posicao) {
    aux = aux->ant;
    i++;
  }
  return aux;
}

int f_consultar_chave_por_posicao(Fila_FIFO *f, int posicao) {
  Node *aux = f_no_na_posicao(f, posicao);
  return aux == NULL ? -1 : aux->chave;
}

int f_consultar_valor_por_posicao(Fila_FIFO *f, int posicao) {
  Node *aux = f_no_na_posicao(f, posicao);
  return aux == NULL ? -1 : aux->valor;
}
