#include "../src/logtree.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(test_inicializar) {
  RBT *T = log_inicializar();
  ck_assert(T->nulo->cor == Negro);
  ck_assert(T->nulo->pai == NULL);
  ck_assert(T->nulo->esq == NULL);
  ck_assert(T->nulo->dir == NULL);
  ck_assert(T->raiz == T->nulo);
}
END_TEST

START_TEST(test_registrar) {
  RBT *T = log_inicializar();
  log_registrar(T, 1, Premium, 33, 1, 1);
  log_registrar(T, 2, Ouro, 34, 2, 1);
  log_registrar(T, 3, Prata, 35, 3, 1);
  ck_assert(T->raiz->chave == 34);
  ck_assert(T->raiz->esq->chave == 33);
  ck_assert(T->raiz->dir->chave == 35);
}
END_TEST

START_TEST(test_obter_soma_por_classe) {
  RBT *T = log_inicializar();
  log_registrar(T, 1, Premium, 10, 1, 1);
  log_registrar(T, 2, Premium, 20, 2, 1);
  log_registrar(T, 3, Premium, 30, 3, 1);
  log_registrar(T, 4, Premium, 40, 3, 1);
  ck_assert(log_obter_soma_por_classe(T, T->raiz, Premium) == 100);
  ck_assert(log_obter_soma_por_classe(T, T->raiz, Ouro) == 0);
}
END_TEST

START_TEST(test_obter_contagem_por_classe) {
  RBT *T = log_inicializar();
  log_registrar(T, 1, Premium, 10, 1, 1);
  log_registrar(T, 2, Premium, 20, 2, 1);
  log_registrar(T, 3, Premium, 30, 3, 1);
  log_registrar(T, 4, Premium, 40, 3, 1);
  log_registrar(T, 5, Premium, 40, 3, 1);
  log_registrar(T, 6, Premium, 40, 3, 1);
  ck_assert(log_obter_contagem_por_classe(T, T->raiz, Premium) == 6);
  ck_assert(log_obter_contagem_por_classe(T, T->raiz, Ouro) == 0);
}
END_TEST

START_TEST(test_media_por_classe) {
  RBT *T = log_inicializar();
  log_registrar(T, 1, Premium, 10, 1, 1);
  log_registrar(T, 2, Premium, 20, 2, 2);
  log_registrar(T, 3, Premium, 30, 3, 3);
  log_registrar(T, 4, Premium, 40, 3, 4);
  log_registrar(T, 5, Premium, 50, 3, 5);
  log_registrar(T, 6, Premium, 60, 3, 6);
  ck_assert(log_media_por_classe(T, T->raiz, Premium) == 35);
  ck_assert(log_media_por_classe(T, T->raiz, Ouro) == 0);
}
END_TEST

START_TEST(test_alt_negros) {
  RBT *T = log_inicializar();
  log_registrar(T, 1, Premium, 10, 1, 1);
  log_registrar(T, 2, Premium, 20, 2, 1);
  log_registrar(T, 3, Premium, 30, 3, 1);
  ck_assert(log_alt_negros(T) == 1);

  log_registrar(T, 4, Premium, 40, 3, 1);
  ck_assert(log_alt_negros(T) == 2);

  log_registrar(T, 5, Premium, 40, 3, 1);
  log_registrar(T, 6, Premium, 40, 3, 1);
  log_registrar(T, 7, Premium, 40, 3, 1);
  log_registrar(T, 8, Premium, 40, 3, 1);
  log_registrar(T, 9, Premium, 40, 3, 1);
  log_registrar(T, 10, Premium, 40, 3, 1);
  ck_assert(log_alt_negros(T) == 3);
}
END_TEST

START_TEST(test_maximo) {
  RBT *T = log_inicializar();
  log_registrar(T, 1, Premium, 10, 1, 1);
  log_registrar(T, 2, Premium, 20, 2, 1);
  log_registrar(T, 3, Premium, 30, 3, 1);
  log_registrar(T, 4, Premium, 40, 3, 1);
  log_registrar(T, 5, Premium, 50, 3, 10);
  log_registrar(T, 6, Premium, 60, 3, 10);
  log_registrar(T, 7, Premium, 70, 3, 10);
  log_registrar(T, 8, Premium, 80, 3, 10);
  log_registrar(T, 9, Premium, 90, 3, 10);
  log_registrar(T, 10, Premium, 110, 3, 20);
  Log *no = log_maximo(T);
  ck_assert(no->chave == 110);
}
END_TEST
START_TEST(test_maximo_nulo) {
  RBT *T = log_inicializar();
  ck_assert(log_maximo(T) == NULL);
}
END_TEST

START_TEST(test_tubias) {
  RBT *T = log_inicializar();
  log_registrar(T, 1, Premium, 10, 1, 10);
  log_registrar(T, 2, Premium, 20, 2, 10);
  log_registrar(T, 3, Premium, 30, 3, 10);
  log_registrar(T, 4, Premium, 40, 3, 10);
  log_registrar(T, 5, Premium, 50, 3, 10);
  log_registrar(T, 6, Premium, 60, 3, 10);
  log_registrar(T, 7, Premium, 70, 3, 10);
  log_registrar(T, 8, Premium, 80, 3, 10);
  log_registrar(T, 9, Premium, 90, 3, 10);
  log_registrar(T, 10, Premium, 110, 3, 20);
  Tubias toba = log_tubias(T, Premium);
  ck_assert(toba.clientes == 10);
  ck_assert(toba.ops == 110);
  ck_assert(toba.tempo_total == 560);
}
END_TEST

START_TEST(test_tubias_nulo) {
  RBT *T = log_inicializar();
  log_registrar(T, 1, Premium, 10, 1, 10);
  log_registrar(T, 2, Premium, 20, 2, 10);
  log_registrar(T, 3, Premium, 30, 3, 10);
  Tubias toba = log_tubias(T, Ouro);
  ck_assert(toba.clientes == 0);
  ck_assert(toba.ops == 0);
  ck_assert(toba.tempo_total == 0);
}
END_TEST

Suite *logtree_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Logtree");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_inicializar);
  tcase_add_test(tc_core, test_registrar);
  tcase_add_test(tc_core, test_obter_soma_por_classe);
  tcase_add_test(tc_core, test_obter_contagem_por_classe);
  tcase_add_test(tc_core, test_media_por_classe);
  tcase_add_test(tc_core, test_alt_negros);
  tcase_add_test(tc_core, test_maximo);
  tcase_add_test(tc_core, test_maximo_nulo);
  tcase_add_test(tc_core, test_tubias);
  tcase_add_test(tc_core, test_tubias_nulo);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = logtree_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
