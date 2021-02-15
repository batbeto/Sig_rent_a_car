#ifndef CLIENTECRUD_H_INCLUDED
#define CLIENTECRUD_H_INCLUDED

typedef struct cliente Cliente;

struct cliente {
  char email[40];
  char nome[40];
  char cpf[12];
  char idade[11];
  char telefone[40];
  char status;
};


void cadastraCliente(void);
void buscaCliente(void);
void editaCliente(void);
void excluiCliente(void);
void listaClientes(void);
void exibeCliente(Cliente*);
void gravaCliente(Cliente*);
int existClient(char cpf_procurado[11]);
int clienPed(char cpf_procurado[11]);

#endif