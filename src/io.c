#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cliente.h"
#include "io.h"

int get_num(char* conf_line) {
    char num_str[8];
    int i = 0;

    while(*conf_line != '=')
        conf_line++;

    do {
        conf_line++;
        if(*conf_line != ' ') {
            num_str[i++] = *conf_line;
        }
    } while(*conf_line != '\0');

    return atoi(num_str);
}

int* get_nums(char* conf_line) {
    char txt_buffer[8];
    int i, *nums, *result;

    nums = malloc(5 * sizeof(int));
    result = nums;
    i = 0;

    while(*conf_line != '{')
        conf_line++;

    do {
        conf_line++;
        if(*conf_line == ',' || *conf_line == '}') {
            txt_buffer[i] = '\0';
            *nums++  = atoi(txt_buffer);
            i = 0;
        } else if(*conf_line != ' ') {
            txt_buffer[i++] = *conf_line;
        }
    } while(*conf_line != '}');

    return result;
}

int get_class(char* class_name) {
    int result;
    if(strcmp("Premium", class_name) == 0) {
        result = 1;
    } else if(strcmp("Ouro", class_name) == 0) {
        result = 2;
    } else if(strcmp("Prata", class_name) == 0) {
        result = 3;
    } else if(strcmp("Bronze", class_name) == 0) {
        result = 4;
    } else if(strcmp("Leezu", class_name) == 0) {
        result = 5;
    } else {
        result = 0;
    }
    return result;
}

int get_acount(char* acount_str) {
    return atoi(acount_str + 5);
}

int get_operations(char* ops) {
    char num_str[8];
    int i = 0;

    while(isdigit(*ops)) {
        num_str[i++]= *ops++;
    }
    num_str[i] = '\0';

    return atoi(num_str);
}

// returns a array of integers of the following format:
// [Class, Acount, Operations]
int* get_client(char* conf_line) {
    char txt_buffer[16];
    int i, len, *nums;

    nums = malloc(3 * sizeof(int));
    i = 0;
    len = 0;

    do {
        if (*conf_line == '-' || *conf_line == '\0') {
            txt_buffer[i] = '\0';
            if(len == 0) {
                nums[len++] = get_class(txt_buffer);
            } else if(len == 1) {
                nums[len++] = get_acount(txt_buffer);
            } else {
                nums[len++] = get_operations(txt_buffer);
            }
            i = 0;
        } else if(*conf_line != ' ') {
            txt_buffer[i++] = *conf_line;
        }
        conf_line++;
    } while(len < 3);

    return nums;
}

void class_to_str(Classe classe, char* dest) {
    char dict[5][16] = { "Premium", "Ouro", "Prata", "Bronze", "Leezu" };
    strcpy(dest, dict[classe - 1]);
}
