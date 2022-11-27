#ifndef  cliente_h
#define cliente_h

typedef enum classe {
  NULO = 0,
  Premium = 1,
  Ouro = 2,
  Prata = 3,
  Bronze = 4,
  Leezu = 5
} Classe;

typedef struct _cliente {
    int conta;
    Classe classe; 
    int ops;
} Cliente;

#endif
