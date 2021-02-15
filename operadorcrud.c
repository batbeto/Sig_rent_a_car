#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operadorcrud.h"
#include "index.h"
#include "verificacpf.h"
#include "verificaemail.h"
#include "verificatelefone.h"
#include "verificanome.h"

void cadastraOperador(void) {
  system("clear");
  fflush(stdin);
  Operador* ope;
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO OPERADOR #####\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  ope = (Operador*) malloc(sizeof(Operador));
  printf("Informe o nome do operador: \n>>> ");
  scanf(" %39[^\n]", ope->nome);
  getchar();
  do{
  printf("Informe o email do operador: \n>>> ");
  scanf(" %39[^\n]", ope->email);
  getchar();
  }while(verificaEmail(ope->email));
  do{
  printf("Informe o telefone do operador: \n>>> ");
  scanf(" %39[^\n]", ope->telefone);
  getchar();
  }while(verificaTelefone(ope->telefone));
  do{
  printf("Informe o cpf do operador: \n>>> ");
  scanf(" %14[^\n]", ope->cpf);
  getchar();
  }while(existOperador(ope->cpf));

  ope->status = '1';
  printf("###############################\n");
  exibeOperador(ope);
  printf("###############################\n");
  gravaOperador(ope);
  fflush(stdin);
  free(ope);
}

void cadastraOperadorInicial(Usuario* user){
  system("clear");
  fflush(stdin);
  int achou = 0;
  Operador* ope;
  FILE* fp;  
  
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO OPERADOR #####\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  ope = (Operador*) malloc(sizeof(Operador));
  do{
  printf("Informe o nome do Operador: \n>>> ");
  scanf(" %39[^\n]", ope->nome);
  getchar();
  }while(verificaNome(ope->nome));
  do{
  printf("Informe o email do Operador: \n>>> ");
  scanf(" %39[^\n]", ope->email);
  getchar();
  }while(verificaEmail(ope->email));
  do{
  printf("Informe o telefone do Operador: \n>>> ");
  scanf(" %14[^\n]", ope->telefone);
  getchar();
  }while(verificaTelefone(ope->telefone));
  do{
  printf("Informe o cpf do Operador: \n>>> ");
  scanf(" %14[^\n]", ope->cpf);
  getchar();
  }while(existOperador(ope->cpf));  
  ope->status = '1';
  strcpy(ope->username , user->username);

  fp = fopen("usuario.dat", "r+b");

  while((!achou) && (fread(user, sizeof(Usuario), 1, fp))) {    
    if ((strcmp(user->username, ope->username) == 0) && (ope->status == '1')) {
      user->cadastroFisico = '1';
      fseek(fp, -1*sizeof(Usuario), SEEK_CUR);
      fwrite(user, sizeof(Usuario), 1, fp);      
      achou = 1;
    }
  }
  
  
  printf("###############################\n");
  exibeOperador(ope);
  printf("###############################\n");
  gravaOperador(ope);   
  fflush(stdin);
  fclose(fp);
}


void gravaOperador(Operador* ope) {
  FILE* fp;
  fp = fopen("operador.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  fwrite(ope, sizeof(Operador), 1, fp);
  fclose(fp);
}

void exibeOperador(Operador* ope) {
  printf("Nome: %s\n", ope->nome);
  printf("Email: %s\n", ope->email);
  printf("Telefone: %s\n", ope->telefone);
  printf("Cpf: %s\n", ope->cpf);
  printf("Status: %c\n", ope->status);
  printf("\n");
}

void editaOperador(void) {
  system("clear");
  FILE* fp;
  Operador* ope;
  int achou = 0;
  char resp;
  char procurado[15];
  fp = fopen("operador.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EDITAR OPERADOR #######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o CPF do Operador a ser alterado:\n>>> ");
  scanf(" %14[^\n]", procurado);
  ope = (Operador*) malloc(sizeof(Operador));
 
  while((!achou) && (fread(ope, sizeof(Operador), 1, fp))) {
   if ((strcmp(ope->cpf, procurado) == 0) && (ope->status == '1')) {
     achou = 1;
   }
  if (achou) {
    exibeOperador(ope);
    getchar();
    printf("Deseja realmente editar este Operador (s/n)?\n>>> ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {
      do{
      printf("Informe o nome do Operador: \n>>> ");
      scanf(" %14[^\n]", ope->nome);
      }while(verificaNome(ope->nome));
      do{
      printf("Informe o email do operador: \n>>> ");
      scanf(" %39[^\n]", ope->email);
      getchar();
      }while(verificaEmail(ope->email)); 
      do{
      printf("Informe o telefone do operador: \n>>> ");
      scanf(" %39[^\n]", ope->telefone);
      getchar();
      }while(verificaTelefone(ope->telefone));
      
      do{
      printf("Informe o cpf do operador: \n>>> ");
      scanf(" %14[^\n]", ope->cpf);
      getchar();
      }while(existOperador(ope->cpf));

      ope->status = '1';
      fseek(fp, -1*sizeof(Operador), SEEK_CUR);
      fwrite(ope, sizeof(Operador), 1, fp);
      printf("\nOperador editado com sucesso!!!\n");
      }else {
      printf("\nOk, os dados não foram alterados\n");
      }
    }else {
      printf("O operador com cpf %s não foi encontrado...\n", procurado);
    }  
  }
  free(ope);
  fclose(fp);
}

void buscaOperador(void){
  system("clear");
  FILE* fp;
  Operador* ope;
  int achou = 0;
  char procurado[15];
  fp = fopen("operador.dat", "rb");
  if (fp == NULL){
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU BUSCAR OPERADOR #######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o cpf do operador a ser buscado:\n>>> ");
  scanf(" %14[^\n]", procurado);
  getchar();
  ope = (Operador*) malloc(sizeof(Operador));


  while((!achou) && (fread(ope, sizeof(Operador), 1, fp))) {
    if ((strcmp(ope->cpf, procurado) == 0) && (ope->status == '1')) {
      achou = 1;
    }
  }
  
  if (achou) {
    exibeOperador(ope);
  } else {
    printf("O operador %s não foi encontrado...\n", procurado);
  }
  free(ope);
  fclose(fp);
}

void listaOperador(void) {
  system("clear");
  FILE* fp;
  Operador* ope;
  fp = fopen("operador.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU LISTAR OPERADOR #######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  ope = (Operador*) malloc(sizeof(Operador));

  int op;
  printf("LISTAR:\n1) TODOS \n2) POR INICIAL DO NOME\n>>> ");
  scanf(" %d", &op);
  getchar();

  if(op == 1){
  while(fread(ope, sizeof(Operador), 1, fp)) {
    if (ope->status == '1') {
      exibeOperador(ope);
    }
  }
  }
  else if(op == 2){
    char nuser[40];
    printf("INSIRA AS INICIAIS DO NOME:\n");
    scanf(" %39[^\n]", nuser);
    getchar();
    while(fread(ope, sizeof(Operador), 1, fp)) {
    if (ope->status == '1' && strncmp(nuser, ope->nome, strlen(nuser)) == 0) {
      exibeOperador(ope);
    }
  }
  }
  
  fclose(fp);
  free(ope);
}

void excluiOperador(void) {
  system("clear");
  FILE* fp;
  Operador* ope;
  int achou = 0;
  char resp;
  char procurado[15];
  fp = fopen("operador.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU DELETAR OPERADOR ######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o cpf do operador a ser apagado:\n>>> ");
  scanf(" %14[^\n]", procurado);
  getchar();
  ope = (Operador*) malloc(sizeof(Operador));

  while((!achou) && (fread(ope, sizeof(Operador), 1, fp))) {
   if ((strcmp(ope->cpf, procurado) == 0) && (ope->status == '1')) {
     achou = 1;
   }
  }
  
  if (achou) {
    exibeOperador(ope);
    printf("Deseja realmente apagar este operador (s/n)?\n>>> ");
    scanf("%c", &resp);
    if (resp == 's' || resp == 'S') {
      ope->status = '0';
      fseek(fp, -1*sizeof(Operador), SEEK_CUR);
      fwrite(ope, sizeof(Operador), 1, fp);
      printf("\nOperador excluído com sucesso!!!\n");
     } else {
       printf("\nOk, os dados não foram alterados\n");
     }
  } else {
    printf("O operador com cpf %s não foi encontrado...\n", procurado);
  }
  fclose(fp);
  free(ope);
}

int existOperador(char cpf_procurado[11]){
  FILE* fp;
  Operador* ope;
  fp = fopen("operador.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  ope = (Operador*) malloc(sizeof(Operador));
  while((fread(ope, sizeof(Operador), 1, fp))) {
   if ((strcmp(ope->cpf, cpf_procurado) == 0) && (ope->status == '1')) {
      free(ope);
      fclose(fp);
      printf("CPF já existe.");
      getchar();
      return 1;     
     }
  }
  if (verificaCpf(cpf_procurado)){
    free(ope);
    fclose(fp);
    return 0;
  }else{
    free(ope);
    fclose(fp);
    printf("CPF inválido!");
    getchar();
    return 1;
  }       
}



