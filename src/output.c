#include "output.h"
#include "cliente.h"
#include "logtree.h"
#include <stdio.h>

/*
Recebe uma classe e retorna a String associada a esse enum,
ja que o C nao permite passar um enum como String
O parametro antigo eh utilizado para adequar o output do arquivo
de saida com o que se espera, pois ha uma secao que aparece comuns
*/
const char *nome_da_classe(Classe classe, int antigo) {
  switch (classe) {
  case NULO:
    return "NULO";
  case Premium:
    return "Premium";
  case Ouro:
    return "Ouro";
  case Prata:
    return "Prata";
  case Bronze:
    return "Bronze";
  case Leezu:
    return antigo ? "Comuns" : "Leezu";
  }
}

/*
Recebe um tempo e um arq de saida para escreve com o fprintf
*/
void o_tempo_total(int tempo, FILE *arq_out) {
  fprintf(arq_out, "Tempo total de atendimento: %d minutos.\n", tempo);
}

/*
Recebe dados do cliente e um arquivo de saida e escreve com o fprintf
*/
void o_tempo_cliente(int timer, int caixa, Classe classe, int conta, int ops,
                     FILE *arq_out) {
  fprintf(arq_out,
          "T = %d min: Caixa %d chama da categoria %s cliente da conta "
          "%d para realizar %d operacao(oes).\n",
          timer, caixa, nome_da_classe(classe, 0), conta, ops);
}

/*
Recebe uma RBT e um arquivo de saida, utiliza o log_tubias para fazer a
transversao da arvore e pegar ops. clientes e tempos e escreve no arquivo
com o fprintf
*/
void o_tempo_classe(RBT *T, FILE *arq_out) {
  Tubias toba;
  int i;
  int tempos[5], clientes[5], operacoes[5];

  for (i = 0; i < 5; i++) {
    toba = log_tubias(T, (Classe)i + 1);
    tempos[i] = toba.tempo_total;
    clientes[i] = toba.clientes;
    operacoes[i] = toba.ops;
  }

  for (i = 0; i < 5; i++) {
    fprintf(arq_out, "Tempo medio de espera dos %d clientes %s: %.2f\n",
            clientes[i], nome_da_classe(i + 1, 0),
            clientes[i] == 0 ? (float)0
                             : (float)tempos[i] / (float)clientes[i]);
  }

  for (i = 0; i < 5; i++) {
    fprintf(arq_out, "Quantidade media de operacoes por cliente %s = %.2f\n",
            nome_da_classe(i + 1, 0),
            clientes[i] == 0 ? (float)0
                             : (float)operacoes[i] / (float)clientes[i]);
  }
}

/*
Recebe os caixas e um arquivo de saida e para cada caixa ele escreve no
arquivo o tempo e a quantidade de clientes com o fprintf
*/
void o_caixas(Caixa *caixas, int tamanho, FILE *arq_out) {
  int i;
  for (i = 0; i < tamanho; i++) {
    fprintf(arq_out, "O caixa de número %d atendeu %d clientes.\n", i + 1,
            caixas[i].atendidos);
  }
}
