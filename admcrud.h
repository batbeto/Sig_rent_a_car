#ifndef ADMCRUD_H_INCLUDED
#define ADMCRUD_H_INCLUDED
#include "login.h"

typedef struct administrador Administrador;

struct administrador {
  char username[40];
  char email[40];
  char nome[40];
  char cpf[12];
  char idade[11];
  char telefone[40];
  char status;
};


void cadastraAdministrador(void);
void cadastraAdministradorInicial(Usuario* user);
void buscaAdministrador(void);
void editaAdministrador(void);
void excluiAdministrador(void);
void listaAdministradores(void);
void exibeAdministrador(Administrador*);
void gravaAdministrador(Administrador*);
int existAdm(char cpf_procurado[11]);

#endif