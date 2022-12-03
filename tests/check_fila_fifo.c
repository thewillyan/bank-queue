#include "../src/fila_fifo.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(test_inicializar) {
  Fila_FIFO *F = f_inicializar();
  ck_assert(F->prim == NULL);
  ck_assert(F->ult == NULL);
  ck_assert(F->tam == 0);
}
END_TEST

START_TEST(test_inserir_um_no) {
  Fila_FIFO *F = f_inicializar();
  int resp = f_inserir(F, 1, 10);
  ck_assert(resp == 1);
  ck_assert(F->prim->chave == 1);
  ck_assert(F->prim->valor == 10);
  ck_assert(F->prim->prox == NULL);
  ck_assert(F->prim->ant == NULL);
  ck_assert(F->ult->chave == 1);
  ck_assert(F->ult->valor == 10);
  ck_assert(F->ult->prox == NULL);
  ck_assert(F->ult->ant == NULL);
  ck_assert(F->tam == 1);
}
END_TEST

START_TEST(test_inserir_dois_nos) {
  Fila_FIFO *F = f_inicializar();
  f_inserir(F, 1, 10);
  f_inserir(F, 2, 20);
  ck_assert(F->prim->chave == 1);
  ck_assert(F->prim->ant == F->ult);
  ck_assert(F->ult->chave == 2);
  ck_assert(F->ult->valor == 20);
  ck_assert(F->ult->prox == F->prim);
  ck_assert(F->ult->ant == NULL);
  ck_assert(F->tam == 2);
}
END_TEST

START_TEST(test_inserir_tres_nos) {
  Fila_FIFO *F = f_inicializar();
  f_inserir(F, 1, 10);
  f_inserir(F, 2, 20);
  f_inserir(F, 3, 30);
  ck_assert(F->prim->chave == 1);
  ck_assert(F->prim->ant->ant == F->ult);
  ck_assert(F->ult->chave == 3);
  ck_assert(F->ult->prox->prox == F->prim);
  ck_assert(F->tam == 3);
}
END_TEST

START_TEST(test_inserir_chave_repetida) {
  Fila_FIFO *F = f_inicializar();
  f_inserir(F, 1, 10);
  int resp = f_inserir(F, 1, 20);
  ck_assert(resp == 0);
}
END_TEST

START_TEST(test_obter_uma_chave) {
  Fila_FIFO *F = f_inicializar();
  f_inserir(F, 1, 10);
  int chave = f_obter_proxima_chave(F);

  ck_assert(chave == 1);
  ck_assert(F->prim == NULL);
  ck_assert(F->ult == NULL);
  ck_assert(F->tam == 0);
}
END_TEST

START_TEST(test_obter_duas_chaves) {
  Fila_FIFO *F = f_inicializar();
  f_inserir(F, 1, 10);
  f_inserir(F, 2, 20);

  int chave1 = f_obter_proxima_chave(F);
  ck_assert(chave1 == 1);
  ck_assert(F->tam == 1);
  ck_assert(F->prim->chave == 2);
  ck_assert(F->ult->chave == 2);
  ck_assert(F->prim->prox == NULL);

  int chave2 = f_obter_proxima_chave(F);
  ck_assert(chave2 == 2);
  ck_assert(F->prim == NULL);
  ck_assert(F->ult == NULL);
  ck_assert(F->tam == 0);
}
END_TEST

START_TEST(test_obter_tres_chaves) {
  Fila_FIFO *F = f_inicializar();
  f_inserir(F, 1, 10);
  f_inserir(F, 2, 20);
  f_inserir(F, 3, 30);

  int chave1 = f_obter_proxima_chave(F);
  ck_assert(chave1 == 1);
  ck_assert(F->tam == 2);
  ck_assert(F->prim->chave == 2);
  ck_assert(F->ult->chave == 3);
  ck_assert(F->prim->prox == NULL);

  int chave2 = f_obter_proxima_chave(F);
  ck_assert(chave2 == 2);
  ck_assert(F->tam == 1);
  ck_assert(F->prim->chave == 3);
  ck_assert(F->ult->chave == 3);
  ck_assert(F->prim->prox == NULL);

  int chave3 = f_obter_proxima_chave(F);
  ck_assert(chave3 == 3);
  ck_assert(F->prim == NULL);
  ck_assert(F->ult == NULL);
  ck_assert(F->tam == 0);
}
END_TEST

START_TEST(test_obter_nenhuma_chave) {
  Fila_FIFO *F = f_inicializar();
  int chave = f_obter_proxima_chave(F);
  ck_assert(chave == 0);
}
END_TEST

START_TEST(test_consultar_prox_chave) {
  Fila_FIFO *F = f_inicializar();
  f_inserir(F, 1, 10);
  int chave = f_consultar_proxima_chave(F);
  ck_assert(chave == 1);
  ck_assert(F->tam == 1);
}
END_TEST

START_TEST(test_consultar_prox_chave_nula) {
  Fila_FIFO *F = f_inicializar();
  int chave = f_consultar_proxima_chave(F);
  ck_assert(chave == 0);
}
END_TEST

START_TEST(test_consultar_prox_valor) {
  Fila_FIFO *F = f_inicializar();
  f_inserir(F, 1, 10);
  int valor = f_consultar_proximo_valor(F);
  ck_assert(valor == 10);
  ck_assert(F->tam == 1);
}
END_TEST

START_TEST(test_consultar_prox_valor_nulo) {
  Fila_FIFO *F = f_inicializar();
  int valor = f_consultar_proximo_valor(F);
  ck_assert(valor == 0);
}
END_TEST

START_TEST(test_num_elementos) {
  Fila_FIFO *F = f_inicializar();
  ck_assert(f_num_elementos(F) == 0);
  f_inserir(F, 1, 10);
  ck_assert(f_num_elementos(F) == 1);
}
END_TEST

START_TEST(test_consultar_chave_na_pos) {
  Fila_FIFO *F = f_inicializar();
  f_inserir(F, 1, 10);
  f_inserir(F, 2, 20);
  f_inserir(F, 3, 30);

  ck_assert(f_consultar_chave_por_posicao(F, 1) == 1);
  ck_assert(f_consultar_chave_por_posicao(F, 2) == 2);
  ck_assert(f_consultar_chave_por_posicao(F, 3) == 3);
  ck_assert(F->tam == 3);
}
END_TEST

START_TEST(test_consultar_chave_na_pos_NULA) {
  Fila_FIFO *F = f_inicializar();
  f_inserir(F, 1, 10);
  ck_assert(f_consultar_chave_por_posicao(F, 2) == -1);
}
END_TEST

START_TEST(test_consultar_valor_na_pos) {
  Fila_FIFO *F = f_inicializar();
  f_inserir(F, 1, 10);
  f_inserir(F, 2, 20);
  f_inserir(F, 3, 30);

  ck_assert(f_consultar_valor_por_posicao(F, 1) == 10);
  ck_assert(f_consultar_valor_por_posicao(F, 2) == 20);
  ck_assert(f_consultar_valor_por_posicao(F, 3) == 30);
  ck_assert(F->tam == 3);
}
END_TEST

START_TEST(test_consultar_valor_na_pos_NULA) {
  Fila_FIFO *F = f_inicializar();
  f_inserir(F, 1, 10);
  ck_assert(f_consultar_valor_por_posicao(F, 2) == -1);
}
END_TEST

Suite *fila_fifo_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Fila_FIFO");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_inicializar);

  tcase_add_test(tc_core, test_inserir_um_no);
  tcase_add_test(tc_core, test_inserir_dois_nos);
  tcase_add_test(tc_core, test_inserir_tres_nos);
  tcase_add_test(tc_core, test_inserir_chave_repetida);

  tcase_add_test(tc_core, test_obter_uma_chave);
  tcase_add_test(tc_core, test_obter_duas_chaves);
  tcase_add_test(tc_core, test_obter_tres_chaves);
  tcase_add_test(tc_core, test_obter_nenhuma_chave);

  tcase_add_test(tc_core, test_consultar_prox_chave);
  tcase_add_test(tc_core, test_consultar_prox_chave_nula);
  tcase_add_test(tc_core, test_consultar_prox_valor);
  tcase_add_test(tc_core, test_consultar_prox_valor_nulo);

  tcase_add_test(tc_core, test_num_elementos);

  tcase_add_test(tc_core, test_consultar_chave_na_pos);
  tcase_add_test(tc_core, test_consultar_chave_na_pos_NULA);
  tcase_add_test(tc_core, test_consultar_valor_na_pos);
  tcase_add_test(tc_core, test_consultar_valor_na_pos_NULA);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = fila_fifo_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
