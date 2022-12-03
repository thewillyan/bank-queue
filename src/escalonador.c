#include <stdlib.h>
#include <stdio.h>
#include "escalonador.h"
#include "fila_fifo.h"

void e_inicializar(Escalonador *e, int caixas, int delta_t, int n_1, int n_2,
        int n_3,int n_4, int n_5)
{
    int disciplina[5] = { n_1, n_2, n_3, n_4, n_5 };
    int i;

    e->fila_atual = 0;
    e->atendidos = 0;
    e->delta = delta_t;
    e->caixas = malloc(caixas * sizeof(int));

    for(i = 0; i < 5; i++) {
        e->filas[i] = f_inicializar();
        e->disciplina[i] = disciplina[i];
    }

    for(i = 0; i < caixas; i++)
        e->caixas[i] = 0;
}

int e_inserir_por_fila (Escalonador *e, int classe, int num_conta,
        int qtde_operacoes)
{
    int i = classe - 1;
    return f_inserir(e->filas[i], num_conta, qtde_operacoes);
}

int e_obter_prox_num_conta(Escalonador *e) {
    int num_conta, count, disciplina;

    count = 0;
    do {
        num_conta = f_obter_proxima_chave(e->filas[e->fila_atual]);
        if (num_conta == 0){
            e->fila_atual = (e->fila_atual + 1) % 5;
            e->atendidos = 0;
        }
    } while(num_conta == 0 && ++count < 5);
    
    disciplina = e->disciplina[e->fila_atual];

    if(num_conta != 0) e->atendidos++;

    if(e->atendidos == disciplina) {
        e->fila_atual = (e->fila_atual + 1) % 5;
        e->atendidos = 0;
    }

    return num_conta;
}

/*int e_consultar_prox_num_conta (Escalonador *e) {*/

/*}*/

/*int e_consultar_prox_qtde_oper (Escalonador *e);*/
/*int e_consultar_prox_fila (Escalonador *e);*/
/*int e_consultar_qtde_clientes (Escalonador *e);*/
/*int e_consultar_tempo_prox_cliente (Escalonador *e);*/
/*int e_conf_por_arquivo (Escalonador *e, char *nome_arq_conf);*/
/*void e_rodar (Escalonador *e, char *nome_arq_in, char *nome_arq_out);*/

