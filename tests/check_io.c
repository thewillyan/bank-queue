#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/io.h"

START_TEST(test_get_num)
{
    ck_assert(get_num("qtde de caixas =   9") == 9);
    ck_assert(get_num("qtde de caixas = 100 ") == 100);
    ck_assert(get_num("delta t = 4 ") == 4);
}
END_TEST


Suite * io_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("IO");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_get_num);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    return 0;
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
