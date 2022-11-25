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

START_TEST(test_get_nums)
{
    int *nums = get_nums("disciplina de escalonamento = {7,6,4,3,2}");
    int i, expected_result[5] = {7,6,4,3,2};

    for(i = 0; i < 5; i++) {
        ck_assert(nums[i] == expected_result[i]);
    }
    
    nums = get_nums("disciplina de escalonamento =   { 9, 7, 5, 4, 1} ");
    int expected_result2[5] = {9, 7, 5, 4, 1};

    for(i = 0; i < 5; i++) {
        ck_assert(nums[i] == expected_result2[i]);
    }

}
END_TEST

START_TEST(test_get_client)
{
    int *result = get_client("Leezu - conta 64433 - 11 operacao(oes)");
    int expected_result[3] = { 5, 64433, 11 };
    int i;

    for(i = 0; i < 3; i++) {
        ck_assert(result[i] == expected_result[i]);
    }

    result = get_client("Premium - conta 847399 - 6 operacao(oes)");
    int expected_result2[3] = {1, 847399, 6};

    for(i = 0; i < 3; i++) {
        ck_assert(result[i] == expected_result2[i]);
    }
}
END_TEST

Suite * io_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("IO");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_get_num);
    tcase_add_test(tc_core, test_get_nums);
    tcase_add_test(tc_core, test_get_client);
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
