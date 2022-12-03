#include <stdlib.h>
#include <check.h>
#include "../src/escalonador.h"

START_TEST(test_inicializar)
{
    int i, disciplina[5] = { 5, 4, 3, 2, 1};
    Escalonador e;

    e_inicializar(&e, 10, 7, 5, 4, 3, 2, 1);

    ck_assert_msg(e.delta == 7, "Wrong delta!");
    ck_assert_msg(e.atendidos == 0, "Wrong served number!");
    ck_assert_msg(e.fila_atual == 0, "Wrong current queue");

    for(i = 0; i < 10; i++) {
        ck_assert(e.timers[i] == 0);
    }

    for(i = 0; i < 5; i++) {
        ck_assert_msg(e.disciplina[i] == disciplina[i], "Discipline missmached!");
        ck_assert_msg(e.filas[i]->tam == 0, "Fila_FIFO isn't empty!");
    }

}
END_TEST

START_TEST(test_incluir)
{
    Escalonador e;

    e_inicializar(&e, 3, 7, 1, 1, 2, 1, 1);
    e_inserir_por_fila(&e, 1, 42, 3);
    e_inserir_por_fila(&e, 1, 50, 3);
    e_inserir_por_fila(&e, 3, 100, 2);
    e_inserir_por_fila(&e, 3, 120, 2);
    e_inserir_por_fila(&e, 5, 32, 1);

    ck_assert(e.filas[0]->tam == 2);
    ck_assert(f_obter_proxima_chave(e.filas[0]) == 42);
    ck_assert(f_obter_proxima_chave(e.filas[0]) == 50);

    ck_assert(e.filas[2]->tam == 2);
    ck_assert(f_obter_proxima_chave(e.filas[2]) == 100);
    ck_assert(f_obter_proxima_chave(e.filas[2]) == 120);

    ck_assert(e.filas[4]->tam == 1);
    ck_assert(f_obter_proxima_chave(e.filas[4]) == 32);
}
END_TEST

START_TEST(test_obter_prox)
{
    Escalonador e;

    e_inicializar(&e, 3, 7, 1, 1, 2, 1, 1);
    e_inserir_por_fila(&e, 1, 42, 3);
    e_inserir_por_fila(&e, 1, 50, 3);
    e_inserir_por_fila(&e, 3, 100, 2);
    e_inserir_por_fila(&e, 3, 120, 2);
    e_inserir_por_fila(&e, 5, 32, 1);

    ck_assert(e_obter_prox_num_conta(&e) == 42);
    ck_assert(e_obter_prox_num_conta(&e) == 100);
    ck_assert(e_obter_prox_num_conta(&e) == 120);
    ck_assert(e_obter_prox_num_conta(&e) == 32);
    ck_assert(e_obter_prox_num_conta(&e) == 50);
    ck_assert(e_obter_prox_num_conta(&e) == 0);
}
END_TEST


START_TEST(test_consultar_prox)
{
    Escalonador e;

    e_inicializar(&e, 3, 7, 1, 1, 2, 1, 1);
    e_inserir_por_fila(&e, 1, 42, 3);
    e_inserir_por_fila(&e, 1, 50, 3);
    e_inserir_por_fila(&e, 3, 100, 2);
    e_inserir_por_fila(&e, 3, 120, 2);
    e_inserir_por_fila(&e, 5, 32, 1);

    ck_assert(e_consultar_prox_num_conta(&e) == 42);
    ck_assert(e_consultar_prox_num_conta(&e) == 42);
    e_obter_prox_num_conta(&e);

    ck_assert(e_consultar_prox_num_conta(&e) == 100);
    e_obter_prox_num_conta(&e);

    ck_assert(e_consultar_prox_num_conta(&e) == 120);
    e_obter_prox_num_conta(&e);

    ck_assert(e_consultar_prox_num_conta(&e) == 32);
    e_obter_prox_num_conta(&e);

    ck_assert(e_consultar_prox_num_conta(&e) == 50);
    e_obter_prox_num_conta(&e);

    ck_assert(e_consultar_prox_num_conta(&e) == 0);
    ck_assert(e_consultar_prox_num_conta(&e) == 0);
}
END_TEST

Suite * io_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Escalonador");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_inicializar);
    tcase_add_test(tc_core, test_incluir);
    tcase_add_test(tc_core, test_obter_prox);
    tcase_add_test(tc_core, test_consultar_prox);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = io_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
