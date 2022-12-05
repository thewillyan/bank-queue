#include "escalonador.h"
#include "fila_fifo.h"
#include "io.h"
#include "logtree.h"
#include "output.h"
#include <stdio.h>
#include <stdlib.h>

void e_inicializar(Escalonador *e, int caixas, int delta_t, int n_1, int n_2,
                   int n_3, int n_4, int n_5) {
  int disciplina[5] = {n_1, n_2, n_3, n_4, n_5};
  int i;

  e->fila_atual = 0;
  e->atendidos = 0;
  e->delta = delta_t;
  e->tam_caixas = caixas;

  for (i = 0; i < 5; i++) {
    e->filas[i] = f_inicializar();
    e->disciplina[i] = disciplina[i];
  }

  e->caixas = malloc(caixas * sizeof(Caixa));

  for (i = 0; i < caixas; i++) {
    e->caixas[i].atendidos = 0;
    e->caixas[i].timer = 0;
  }
}

int e_inserir_por_fila(Escalonador *e, int classe, int num_conta,
                       int qtde_operacoes) {
  return f_inserir(e->filas[--classe], num_conta, qtde_operacoes);
}

int e_consultar_prox_fila(Escalonador *e) {
  int disciplina = e->disciplina[e->fila_atual];
  int len = f_num_elementos(e->filas[e->fila_atual]);
  return (e->atendidos == disciplina || len == 0) ? (e->fila_atual + 1) % 5
                                                  : e->fila_atual;
}

int e_obter_prox_num_conta(Escalonador *e) {
  int num_conta, count, old_fila;

  old_fila = e->fila_atual;
  count = 0;
  do {
    e->fila_atual = e_consultar_prox_fila(e);
  } while (f_num_elementos(e->filas[e->fila_atual]) == 0 && ++count < 5);

  if (e->fila_atual != old_fila)
    e->atendidos = 0;

  num_conta = f_obter_proxima_chave(e->filas[e->fila_atual]);
  if (num_conta != 0)
    e->atendidos++;

  return num_conta;
}

int e_consultar_prox_num_conta(Escalonador *e) {
  int num_conta, count, prox_fila;

  prox_fila = e_consultar_prox_fila(e);
  count = 0;
  do {
    num_conta = f_consultar_proxima_chave(e->filas[prox_fila]);
    if (num_conta == 0)
      prox_fila = (prox_fila + 1) % 5;
  } while (num_conta == 0 && ++count < 5);

  return num_conta;
}

int e_consultar_prox_qtde_oper(Escalonador *e) {
  int qtde, count, prox_fila;

  prox_fila = e_consultar_prox_fila(e);
  count = 0;
  do {
    qtde = f_consultar_proximo_valor(e->filas[prox_fila]);
    if (qtde == 0)
      prox_fila = (prox_fila + 1) % 5;
  } while (qtde == 0 && ++count < 5);

  return qtde;
}

int e_consultar_qtde_clientes(Escalonador *e) {
  int qtde, i;
  qtde = 0;
  for (i = 0; i < 5; i++) {
    qtde += f_num_elementos(e->filas[i]);
  }
  return qtde;
};

int e_consultar_tempo_prox_cliente(Escalonador *e) {
  int ops;
  ops = e_consultar_prox_qtde_oper(e);
  return (!ops) ? -1 : ops * e->delta;
}

int e_conf_por_arquivo(Escalonador *e, char *nome_arq_conf) {
  int line_num, caixas, delta, *n, *cli_data;
  FILE *fp;
  char *line;
  size_t len = 0;

  fp = fopen(nome_arq_conf, "r");

  if (fp == NULL)
    return 0;

  line_num = 0;
  while (getline(&line, &len, fp) != -1) {
    line_num++;
    if (line_num == 1) {
      caixas = get_num(line);
    } else if (line_num == 2) {
      delta = get_num(line);
    } else if (line_num == 3) {
      n = get_nums(line);
      e_inicializar(e, caixas, delta, n[0], n[1], n[2], n[3], n[4]);
    } else {
      cli_data = get_client(line);
      e_inserir_por_fila(e, cli_data[0], cli_data[1], cli_data[2]);
    }
  }

  fclose(fp);
  return 1;
}

void e_rodar(Escalonador *e, char *nome_arq_in, char *nome_arq_out) {
  int t, i, ops, conta, clientes, tot_time;
  RBT *T = log_inicializar();
  FILE *arq_out;

  e_conf_por_arquivo(e, nome_arq_in);
  clientes = e_consultar_qtde_clientes(e);

  arq_out = fopen(nome_arq_out, "wt");
  if (arq_out == NULL)
    return;

  i = t = tot_time = 0;
  while (clientes > 0) {
    if (e->caixas[i].timer == t) {
      clientes--;
      e->caixas[i].atendidos++;
      e->caixas[i].timer += e_consultar_tempo_prox_cliente(e);

      ops = e_consultar_prox_qtde_oper(e);
      conta = e_obter_prox_num_conta(e);

      log_registrar(T, conta, e->fila_atual + 1, t, i + 1, ops);
      o_tempo_cliente(t, i + 1, e->fila_atual + 1, conta, ops, arq_out);
    }
    i = (i+1) % e->tam_caixas;
    if(i == 0) t++;
  }

  for (i = 0; i < e->tam_caixas; i++) {
    tot_time = (e->caixas[i].timer > tot_time) ? e->caixas[i].timer : tot_time;
  }

  o_tempo_total(tot_time, arq_out);
  o_tempo_classe(T, arq_out);
  o_caixas(e->caixas, e->tam_caixas, arq_out);

  fclose(arq_out);
}
