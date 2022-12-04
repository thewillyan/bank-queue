#ifndef output_h
#define output_h

#include "escalonador.h"
#include "cliente.h"
#include "logtree.h"
#include <stdio.h>


void o_tempo_total(int  tempo, FILE *arq_out);
void o_tempo_cliente(int timer, int caixa, Classe classe, int conta, int ops,
                     FILE *arq_out);
void o_tempo_classe(RBT *T, FILE *arq_out);
void o_caixas(Caixa *caixas,int tamanho, FILE *arq_out);

#endif