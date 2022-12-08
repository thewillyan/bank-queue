/*
Aluno - Matricula

André Willyan de Sousa - 537550
Marcelo Meireles Marques Filho - 536927
Said Cavalcante Rodrigues - 538349
*/
#include "escalonador.h"
#include "logtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define ENTRADA "entradas"
#define SAIDA_ESP "saidas-esperadas"
#define SAIDA_PROD "saidas-prod"

struct stat st = {0};

int check_if_dir_exists(char *name) {
  FILE *fp;
  if (stat(name, &st) == -1) {
    mkdir(name, 0700);
    printf("A pasta '%s' agora existe, adicione seus arquivos nela\n", name);
    return 1;
  }

  return 0;
}

char *get_num_to_file(char *entry) {
  char *buf = malloc(sizeof(char) * 5);
  int len = strlen(entry);
  char dict[4][5] = {"000", "00", "0", ""};
  strcpy(buf, dict[len - 1]);
  strncat(buf, entry, len);

  return buf;
}

char *nome_arq(char *pasta, int entrada, char *entry) {
  char *buf = malloc(sizeof(char) * 51);
  sprintf(buf, "%s/%s-%s.txt", pasta, entrada ? "entrada" : "saida",
          get_num_to_file(entry));
  return buf;
}

int main(int argc, char *argv[]) {
  char *nome_arq_in, *nome_arq_out;
  int en, s_e, s_p;
  Escalonador e;

  if (argc == 0) {
    printf("Nenhum parametro foi recebido");
    return EXIT_FAILURE;
  }

  en = check_if_dir_exists(ENTRADA);
  s_e = check_if_dir_exists(SAIDA_ESP);
  s_p = check_if_dir_exists(SAIDA_PROD);

  if (en || s_e)
    return EXIT_FAILURE;

  nome_arq_in = nome_arq(ENTRADA, 1, argv[1]);
  nome_arq_out = nome_arq(SAIDA_PROD, 0, argv[1]);

  e_rodar(&e, nome_arq_in, nome_arq_out);

  return EXIT_SUCCESS;
}
