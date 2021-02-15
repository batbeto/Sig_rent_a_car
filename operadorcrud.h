#ifndef OPERADORCRUD_H_INCLUDED
#define OPERADORCRUD_H_INCLUDED
#include "login.h"

typedef struct operador Operador;

struct operador {
  char email[40];
  char nome[40];
  char cpf[12];
  char idade[11];
  char telefone[40];
  char username[40];
  char status;
};
void cadastraOperador(void);
void cadastraOperadorInicial(Usuario* user);
void buscaOperador(void);
void editaOperador(void);
void excluiOperador(void);
void listaOperador(void);
void exibeOperador(Operador*);
void gravaOperador(Operador*);
int existOperador(char cpf_procurado[11]);

#endif