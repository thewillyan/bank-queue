#include <stdlib.h>
#include <check.h>
#include "io.h"

int get_num(char* conf_line) {
    char* num_str = malloc(8);

    while(*conf_line != '=') {
        conf_line++;
    }

    do {
        conf_line++;
        if(*conf_line != ' ') {
            *num_str++ = *conf_line;
        }
    } while(*conf_line != '\0');

    return atoi(num_str);
}

START_TEST(get_num_test) {
    ck_assert(get_num("delta t = 1") == 1);
    ck_assert(get_num("qtde de caixas = 2  ") == 2);
} END_TEST
