#include "logtree.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    RBT *T = log_inicializar();
    log_registrar(T, 777, 1, 37, 2);
    log_registrar(T, 777, 1, 37, 2);
    log_registrar(T, 777, 1, 37, 2);
    log_registrar(T, 777, 2, 37, 2);
    log_registrar(T, 777, 2, 37, 2);
    log_registrar(T, 777, 2, 37, 2);
    log_registrar(T, 777, 2, 39, 2);
    log_registrar(T, 777, 3, 37, 2);
    log_registrar(T, 777, 3, 37, 2);
    log_registrar(T, 777, 3, 37, 2);
    log_registrar(T, 777, 3, 37, 2);
    log_registrar(T, 777, 3, 37, 2);
    log_registrar(T, 777, 4, 37, 2);
    log_registrar(T, 777, 4, 37, 2);
    log_registrar(T, 777, 4, 37, 2);
    log_registrar(T, 777, 5, 37, 2);
    log_registrar(T, 777, 5, 37, 2);
    log_registrar(T, 777, 5, 37, 2);
    log_registrar(T, 777, 5, 37, 2);
    log_registrar(T, 777, 5, 37, 2);
    log_registrar(T, 777, 5, 37, 2);
    log_emordem(T, T->raiz);
    printf("Altura em negros %d\n", log_alt_negros(T));
    printf("Media %f\n", log_media_por_classe(T, T->raiz, 2));
    return EXIT_SUCCESS;
}
