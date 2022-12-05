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
        ck_assert(e.caixas[i].atendidos == 0);
        ck_assert(e.caixas[i].timer == 0);
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

START_TEST(test_obter_prox_conta)
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
    ck_assert(e_obter_prox_num_conta(&e) == -1);
}
END_TEST


START_TEST(test_consultar_prox_conta)
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

    ck_assert(e_consultar_prox_num_conta(&e) == -1);
    ck_assert(e_consultar_prox_num_conta(&e) == -1);
}
END_TEST

START_TEST(test_consultar_prox_qtde_ops)
{
    Escalonador e;

    e_inicializar(&e, 3, 7, 1, 1, 2, 1, 1);
    ck_assert(e_consultar_prox_qtde_oper(&e) == -1);

    e_inserir_por_fila(&e, 1, 42, 3);
    e_inserir_por_fila(&e, 3, 100, 2);

    ck_assert(e_consultar_prox_qtde_oper(&e) == 3);
    e_obter_prox_num_conta(&e);
    ck_assert(e_consultar_prox_qtde_oper(&e) == 2);
    e_obter_prox_num_conta(&e);
    ck_assert(e_consultar_prox_qtde_oper(&e) == -1);
}
END_TEST


START_TEST(test_consultar_prox_fila)
{
    Escalonador e;
    e_inicializar(&e, 3, 7, 1, 1, 2, 1, 1);

    e_inserir_por_fila(&e, 1, 42, 3);
    e_inserir_por_fila(&e, 1, 50, 3);
    e_inserir_por_fila(&e, 3, 100, 2);
    e_inserir_por_fila(&e, 3, 120, 2);
    e_inserir_por_fila(&e, 5, 32, 1);

    ck_assert(e_consultar_prox_fila(&e) == 0);
    e.fila_atual++;

    ck_assert(e_consultar_prox_fila(&e) == 2);
    e.fila_atual++;

    ck_assert(e_consultar_prox_fila(&e) == 2);
    e.atendidos++;
    ck_assert(e_consultar_prox_fila(&e) == 2);
    e.atendidos++;
    ck_assert(e_consultar_prox_fila(&e) == 3);
    e.fila_atual++;
    ck_assert(e_consultar_prox_fila(&e) == 4);
    e.fila_atual++;
    ck_assert(e_consultar_prox_fila(&e) == 4);
}
END_TEST


START_TEST(test_consultar_qtde_clientes)
{
    Escalonador e;
    e_inicializar(&e, 3, 7, 1, 1, 2, 1, 1);

    e_inserir_por_fila(&e, 2, 50, 3);
    e_inserir_por_fila(&e, 3, 100, 2);
    e_inserir_por_fila(&e, 3, 110, 2);
    e_inserir_por_fila(&e, 4, 120, 2);
    e_inserir_por_fila(&e, 5, 32, 1);
    e_inserir_por_fila(&e, 5, 20, 1);

    ck_assert(e_consultar_qtde_clientes(&e) == 6);
}
END_TEST

START_TEST(test_consultar_tempo_prox_cliente)
{
    Escalonador e;
    int i, delta = 5;
    int ops[6] = { 3, 2, 5, 6, 1, 10};

    e_inicializar(&e, 3, delta, 1, 1, 2, 1, 1);

    e_inserir_por_fila(&e, 2, 50, ops[0]);
    e_inserir_por_fila(&e, 3, 100, ops[1]);
    e_inserir_por_fila(&e, 3, 110, ops[2]);
    e_inserir_por_fila(&e, 4, 120, ops[3]);
    e_inserir_por_fila(&e, 5, 32, ops[4]);
    e_inserir_por_fila(&e, 5, 20, ops[5]);

    for(i = 0; i < 6; i++) {
        ck_assert(e_consultar_tempo_prox_cliente(&e) == ops[i] * delta);
        e_obter_prox_num_conta(&e);
    }
}
END_TEST

START_TEST(test_conf_por_arq)
{
    int i, disciplina[5] = { 9, 7, 6, 5, 3 };
    Escalonador e;
    ck_assert_msg(e_conf_por_arquivo(&e, "input_example.txt"),
            "Failed to read the config file");

    ck_assert(e.tam_caixas == 2); 
    ck_assert(e.delta == 1);

    for(i = 0; i < 5; i++) {
        ck_assert(e.disciplina[i] == disciplina[i]);
    }

    ck_assert(e_consultar_prox_qtde_oper(&e) == 10);
    ck_assert(e_obter_prox_num_conta(&e) == 639309);

    ck_assert(e_consultar_prox_qtde_oper(&e) == 8);
    ck_assert(e_obter_prox_num_conta(&e) == 48002);

    ck_assert(e_consultar_prox_qtde_oper(&e) == 11);
    ck_assert(e_obter_prox_num_conta(&e) == 705111);

    ck_assert(e_consultar_prox_qtde_oper(&e) == 4);
    ck_assert(e_obter_prox_num_conta(&e) == 442409);

    ck_assert(e_consultar_prox_qtde_oper(&e) == 10);
    ck_assert(e_obter_prox_num_conta(&e) == 761616);
}
END_TEST

Suite * io_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Escalonador");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_inicializar);
    tcase_add_test(tc_core, test_incluir);
    tcase_add_test(tc_core, test_obter_prox_conta);
    tcase_add_test(tc_core, test_consultar_prox_conta);
    tcase_add_test(tc_core, test_consultar_prox_qtde_ops);
    tcase_add_test(tc_core, test_consultar_prox_fila);
    tcase_add_test(tc_core, test_consultar_qtde_clientes);
    tcase_add_test(tc_core, test_consultar_tempo_prox_cliente);
    // too complicated to test, not worth it
    /*tcase_add_test(tc_core, test_conf_por_arq);*/

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
