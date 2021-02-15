#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientecrud.h"
#include "verificacpf.h"
#include "verificaemail.h"
#include "verificatelefone.h"
#include "verificanome.h"

void cadastraCliente(void) {
  system("clear");
  fflush(stdin);
  Cliente* clien;
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO CLIENTE ######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  clien = (Cliente*) malloc(sizeof(Cliente));
  do{
  printf("Informe o nome do Cliente: \n>>> ");
  scanf(" %39[^\n]", clien->nome);
  getchar();
  }while(verificaNome(clien->nome));
  do{
  printf("Informe o email do cliente: \n>>> ");
  scanf(" %39[^\n]", clien->email);
  getchar();
  }while(verificaEmail(clien->email));
  do{
  printf("Informe o telefone do cliente: \n>>> ");
  scanf(" %14[^\n]", clien->telefone);
  getchar();
  }while(verificaTelefone(clien->telefone));
  do{
  printf("Informe o cpf do cliente: \n>>> ");
  scanf(" %14[^\n]", clien->cpf);
  getchar();
  }while(existClient(clien->cpf));
  clien->status = '1';
  printf("###############################\n");
  exibeCliente(clien);
  printf("###############################\n");
  gravaCliente(clien);

  fflush(stdin);
  free(clien);
}

void gravaCliente(Cliente* clien) {
  FILE* fp;
  fp = fopen("cliente.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  } 
  fwrite(clien, sizeof(Cliente), 1, fp);
  fclose(fp);
}

void editaCliente(void) {
  system("clear");
  FILE* fp;
  Cliente* clien;
  int achou = 0;
  char resp;
  char procurado[11];
  fp = fopen("cliente.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EDITAR CLIENTE ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o CPF do Cliente a ser alterado: ");
  scanf(" %14[^\n]", procurado);
  getchar();
  clien = (Cliente*) malloc(sizeof(Cliente));

  while((!achou) && (fread(clien, sizeof(Cliente), 1, fp))) {
   if ((strcmp(clien->cpf, procurado) == 0) && (clien->status == '1')) {
     achou = 1;
   }
  if (achou) {
    exibeCliente(clien);
    printf("Deseja realmente editar este Cliente (s/n)?\n>>> ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {
      printf("O que você deseja editar?. \n(1) nome\n(2) email\n(3) telefone\n(4) cpf\n>>> ");
      scanf(" %c", &resp);
      getchar();

      switch(resp){
        case '1':
        do{
        printf("Informe o nome do cliente:\n>>> ");
        scanf(" %39[^\n]", clien->nome);
        getchar();
        }while(verificaNome(clien->nome));
        break;
        case '2':
        do{
        printf("Informe o email do cliente: \n>>> ");
        scanf(" %39[^\n]", clien->email);
        getchar();
        }while(verificaEmail(clien->email));
        break;
        case '3':
        do{
        printf("Informe o telefone do cliente: \n>>> ");
        scanf(" %14[^\n]", clien->telefone);
        getchar();
        }while(verificaTelefone(clien->telefone));
        break;
        case '4':
        do{
        printf("Informe o cpf do cliente: \n>>> ");
        scanf(" %14[^\n]", clien->cpf); 
        getchar();
        }while(existClient(clien->cpf));
        break;
        
        default:
        do{
        printf("Informe o nome do cliente: \n>>>");
        scanf(" %39[^\n]", clien->nome);
        getchar();
        }while(verificaNome(clien->nome));
        do{
        printf("Informe o email do cliente: \n>>> ");
        scanf(" %39[^\n]", clien->email);
        getchar();
        }while(verificaEmail(clien->email));
        do{
        printf("Informe o telefone do cliente: \n>>> ");
        scanf(" %14[^\n]", clien->telefone);
        getchar();
        }while(verificaTelefone(clien->telefone));
        do{
        printf("Informe o cpf do cliente: \n>>> ");
        scanf(" %14[^\n]", clien->cpf); 
        getchar();
        }while(existClient(clien->cpf));
        break;
      }

      
      clien->status = '1';
      fseek(fp, -1*sizeof(Cliente), SEEK_CUR);
      fwrite(clien, sizeof(Cliente), 1, fp);
      printf("\nCliente editado com sucesso!!!\n");
      } else {
      printf("\nOk, os dados não foram alterados\n");
      }    
    }else {
      printf("O cliente com cpf %s não foi encontrado...\n", procurado);
    }  
  }
  free(clien);
  fclose(fp);
}


void exibeCliente(Cliente* clien){
  printf("Nome: %s\n", clien->nome);
  printf("Email: %s\n", clien->email);
  printf("Telefone: %s\n", clien->telefone);
  printf("Cpf: %s\n", clien->cpf);
  printf("Status: %c\n", clien->status);
  getchar();
  printf("\n");
}

void buscaCliente(void) {
  system("clear");
  FILE* fp;
  Cliente* clien;
  int achou = 0;
  char procurado[15];
  fp = fopen("cliente.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU BUSCAR CLIENTE ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o cpf do Cliente a ser buscado:\n>>> ");
  scanf(" %14[^\n]", procurado);
  getchar();
  clien = (Cliente*) malloc(sizeof(Cliente));

  while((!achou) && (fread(clien, sizeof(Cliente), 1, fp))) {
   if ((strcmp(clien->cpf, procurado) == 0) && (clien->status == '1')) {
     achou = 1;
   }
  }  
  if (achou) {
    exibeCliente(clien);
  } else {
    printf("O cliente como cpf %s não foi encontrado...\n", procurado);
  }  
  
  free(clien);
  fclose(fp);
}


void listaClientes(void) {
  system("clear");
  FILE* fp;
  Cliente* clien;
  fp = fopen("cliente.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EXIBIR CLIENTE ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  clien = (Cliente*) malloc(sizeof(Cliente));
  int op;
  printf("LISTAR:\n1) TODOS \n2) POR INICIAL DO NOME\n>>> ");
  scanf(" %d", &op);
  getchar();

  if(op == 1){
  while(fread(clien, sizeof(Cliente), 1, fp)) {
    if (clien->status == '1') {
      exibeCliente(clien);
    }
  }
  }
  else if(op == 2){
    char nuser[40];
    printf("INSIRA AS INICIAIS DO NOME:\n");
    scanf(" %39[^\n]", nuser);
    getchar();
    while(fread(clien, sizeof(Cliente), 1, fp)) {
    if (clien->status == '1' && strncmp(nuser, clien->nome, strlen(nuser)) == 0) {
      exibeCliente(clien);
    }
  }
  }

  getchar();
  fclose(fp);
  free(clien);
}

void excluiCliente(void) {
  system("clear");
  FILE* fp;
  Cliente* clien;
  int achou = 0;
  char resp;
  char procurado[15];
  fp = fopen("cliente.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU DELETAR CLIENTE #######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o cpf do Cliente a ser apagado:\n>>> ");
  scanf(" %14[^\n]", procurado);
  getchar();
  clien = (Cliente*) malloc(sizeof(Cliente));

  while((!achou) && (fread(clien, sizeof(Cliente), 1, fp))) {
   if ((strcmp(clien->cpf, procurado) == 0) && (clien->status == '1')) {
     achou = 1;
   }
  }
  
  if (achou) {
    exibeCliente(clien);
    printf("Deseja realmente apagar este Cliente (s/n)?\n>>> ");
    scanf("%c", &resp);
    getchar();
    if (resp == 's' || resp == 'S') {
      clien->status = '0';
      fseek(fp, -1*sizeof(Cliente), SEEK_CUR);
      fwrite(clien, sizeof(Cliente), 1, fp);
      printf("\nCliente excluído com sucesso!!!\n");
     } else {
       printf("\nOk, os dados não foram alterados\n");
     }
  } else {
    printf("O cliente com cpf %s não foi encontrado...\n", procurado);
  }
  fclose(fp);
  free(clien);
}

int existClient(char cpf_procurado[11]){
  FILE* fp;
  Cliente* clien;
  fp = fopen("cliente.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  clien = (Cliente*) malloc(sizeof(Cliente));
  while((fread(clien, sizeof(Cliente), 1, fp))) {
   if ((strcmp(clien->cpf, cpf_procurado) == 0) && (clien->status == '1')) {
      free(clien);
      fclose(fp);
      printf("CPF já existe.");
      getchar();
      return 1;     
     }
   }
   if (verificaCpf(cpf_procurado)){
    free(clien);
    fclose(fp);
    return 0;
  }else{
    free(clien);
    fclose(fp);
    printf("CPF inválido!");
    getchar();
    return 1;
  }
}


int clienPed(char cpf_procurado[11]){
    FILE* fp;
  Cliente* clien;
  fp = fopen("cliente.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  clien = (Cliente*) malloc(sizeof(Cliente));
  while((fread(clien, sizeof(Cliente), 1, fp))) {
   if ((strcmp(clien->cpf, cpf_procurado) == 0) && (clien->status == '1')) {
      free(clien);
      fclose(fp);      
      getchar();
      return 1;     
     }
   }
   free(clien);
   fclose(fp);  
   return 0;   
}