#ifndef io_h
#define io_h

#include "cliente.h"

int get_num(char* conf_line);
int* get_nums(char* conf_line);
int* get_client(char* conf_line);
void class_to_str(Classe classe, char* dest);

#endif
