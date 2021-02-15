#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admcrud.h"
#include "login.h"
#include "index.h"
#include "verificacpf.h"
#include "verificaemail.h"
#include "verificatelefone.h"
#include "verificanome.h"

void cadastraAdministrador(void) {
  system("clear");
  fflush(stdin);
  Administrador* adm;
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO ADM ##########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  adm = (Administrador*) malloc(sizeof(Administrador));
  do{
  printf("Informe o nome do administrador: \n>>> ");
  scanf(" %39[^\n]", adm->nome);
  getchar();
  }while(verificaNome(adm->nome));  
  
  printf("Informe o username do administrador: \n>>> ");
  scanf(" %39[^\n]", adm->username);
  getchar();
  do{
    printf("Informe o email do administrador: \n>>> ");
    scanf(" %39[^\n]", adm->email);
    getchar();
  }while(verificaEmail(adm->email));
  do{
  printf("Informe o telefone do administrador: \n>>> ");
  scanf(" %14[^\n]", adm->telefone);
  getchar();
  }while(verificaTelefone(adm->telefone));
  do{
  printf("Informe o cpf do administrador: \n>>> ");
  
  scanf(" %14[^\n]", adm->cpf);
  getchar();
  }while(existAdm(adm->cpf));

  adm->status = '1';
  printf("###############################\n");
  exibeAdministrador(adm);
  printf("###############################\n");
  gravaAdministrador(adm);
  fflush(stdin); 
  free(adm);
} // OK

void cadastraAdministradorInicial(Usuario* user){
  system("clear");
  fflush(stdin);
  int achou = 0;
  FILE* fp;
  Administrador* adm;
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO ADM ##########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  adm = (Administrador*) malloc(sizeof(Administrador));
  do{
  printf("Informe o nome do administrador: \n>>> ");
  scanf(" %39[^\n]", adm->nome);
  getchar();
  }while(verificaNome(adm->nome));
  do{
  printf("Informe o email do administrador: \n>>> ");
  scanf(" %39[^\n]", adm->email);
  getchar();
  }while(verificaEmail(adm->email));
  do{
  printf("Informe o telefone do administrador: \n>>> ");
  scanf(" %14[^\n]", adm->telefone);
  getchar();
  }while(verificaTelefone(adm->telefone));
  do{    
    printf("Informe o cpf do administrador: \n>>> ");
    scanf(" %14[^\n]", adm->cpf);
    getchar();  
  }while(existAdm(adm->cpf));
  adm->status = '1';
  
  strcpy(adm->username, user->username);

  fp = fopen("usuario.dat", "r+b"); 



  while((!achou) && (fread(user, sizeof(Usuario), 1, fp))) {
    if ((strcmp(user->username, adm->username) == 0) && (adm->status == '1')) {
      user->cadastroFisico = '1';
      
      getchar();
      fseek(fp, -1*sizeof(Usuario), SEEK_CUR);
      fwrite(user, sizeof(Usuario), 1, fp);
      
      getchar();
      achou = 1;
    }
  } 
  

  printf("###############################\n");
  exibeAdministrador(adm);
  printf("###############################\n");
  gravaAdministrador(adm);  
  fflush(stdin);  
  fclose(fp);
}

void gravaAdministrador(Administrador* adm) {
  FILE* fp;
  fp = fopen("administrador.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  fwrite(adm, sizeof(Administrador), 1, fp);
  fclose(fp);
}

void exibeAdministrador(Administrador* adm) {
  printf("Nome: %s\n", adm->nome);
  printf("Email: %s\n", adm->email);
  printf("Username: %s\n", adm->username);
  printf("Telefone: %s\n", adm->telefone);
  printf("Cpf: %s\n", adm->cpf);
  printf("Status: %c\n", adm->status);
  getchar();
  printf("\n");
}

void editaAdministrador(void) {
  system("clear");
  FILE* fp;
  Administrador* adm;
  int achou = 0;
  char resp;
  char procurado[11];
  fp = fopen("administrador.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EDITAR ADM ############\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o CPF do administrador a ser alterado: ");
  scanf(" %14[^\n]", procurado);
  getchar();
  adm = (Administrador*) malloc(sizeof(Administrador));

  while((!achou) && (fread(adm, sizeof(Administrador), 1, fp))) {
   if ((strcmp(adm->cpf, procurado) == 0) && (adm->status == '1')) {
     achou = 1;
   }
  }
  if (achou) {
    exibeAdministrador(adm);
    getchar();
    printf("Deseja realmente editar este administrador (s/n)?\n>>> ");
    scanf(" %c", &resp);
    getchar();
    if (resp == 's' || resp == 'S') {
      printf("O que você deseja editar?. \n(1) nome\n(2) username\n(3) email\n(4) telefone\n(5) cpf\n>>> ");
      scanf(" %c", &resp);
      switch(resp){
        case '1':
        do{
        printf("Informe o nome do administrador:\n>>> ");
        scanf(" %14[^\n]", adm->nome);
        getchar();
        }while(verificaNome(adm->nome));
        break;
        case '2':
        printf("Informe o username do administrador: \n>>> ");
        scanf(" %39[^\n]", adm->username);
        getchar();
        break;
        case '3':
        do{
        printf("Informe o email do administrador: \n>>> ");
        scanf(" %39[^\n]", adm->email);
        getchar();
        }while(verificaEmail(adm->email));
        break;
        case '4':
        do{
        printf("Informe o telefone do administrador: \n>>> ");
        scanf(" %14[^\n]", adm->telefone);
        getchar();
        }while(verificaTelefone(adm->telefone));
        break;
        case '5':
        do {
        printf("Informe o cpf do administrador: \n>>> ");
        scanf(" %14[^\n]", adm->cpf);
        getchar();
        } while(existAdm(adm->cpf));
        break;
        
        default:
        do{
        printf("Informe o nome do administrador:\n>>> ");
        scanf(" %14[^\n]", adm->nome);
        getchar();
        }while(verificaNome(adm->nome));
        printf("Informe o username do administrador: \n>>> ");
        scanf(" %39[^\n]", adm->username);
        getchar();
        do{
        printf("Informe o email do administrador: \n>>> ");
        scanf(" %39[^\n]", adm->email);
        getchar();
        }while(verificaEmail(adm->email));
        do{
        printf("Informe o telefone do administrador: \n>>> ");
        scanf(" %14[^\n]", adm->telefone);
        getchar();
        }while(verificaTelefone(adm->telefone));
        do{
        printf("Informe o cpf do administrador: \n>>> ");
        scanf(" %14[^\n]", adm->cpf);
        getchar();
        }while(existAdm(adm->cpf));
        break;
      }
      fseek(fp, -1*sizeof(Administrador), SEEK_CUR);
      fwrite(adm, sizeof(Administrador), 1, fp);
      printf("\nAdministrador editado com sucesso!!!\n");
    } else {
      printf("\nOk, os dados não foram alterados\n");
    }
  } else {
    printf("O administrador com cpf %s não foi encontrado...\n", procurado);
  }
  free(adm);
  fclose(fp);
}

void buscaAdministrador(void) {
  system("clear");
  FILE* fp;
  Administrador* adm;
  int achou = 0;
  char procurado[15];
  fp = fopen("administrador.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU BUSCAR ADM ############\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o cpf do administrador a ser buscado:\n>>> ");
  scanf(" %14[^\n]", procurado);
  getchar();
  adm = (Administrador*) malloc(sizeof(Administrador));

  while((!achou) && (fread(adm, sizeof(Administrador), 1, fp))) {
   if ((strcmp(adm->cpf, procurado) == 0) && (adm->status == '1')) {
     achou = 1;
   }
  }  
  if (achou) {
    exibeAdministrador(adm);
  } else {
    printf("O administrador com cpf %s não foi encontrado...\n", procurado);
  }
  fclose(fp);
  free(adm);
}

void listaAdministradores(void) {
  system("clear");
  FILE* fp;
  Administrador* adm;
  fp = fopen("administrador.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EXIBIR ADM ############\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  adm = (Administrador*) malloc(sizeof(Administrador));
  int op;
  printf("LISTAR:\n1) TODOS \n2) POR INICIAL DO NOME\n>>> ");
  scanf(" %d", &op);
  getchar();

  if(op == 1){
  while(fread(adm, sizeof(Administrador), 1, fp)) {
    if (adm->status == '1') {
      exibeAdministrador(adm);
    }
  }
  }
  else if(op == 2){
    char nuser[40];
    printf("INSIRA AS INICIAIS DO NOME:\n");
    scanf(" %39[^\n]", nuser);
    getchar();
    while(fread(adm, sizeof(Administrador), 1, fp)) {
    if (adm->status == '1' && strncmp(nuser, adm->nome, strlen(nuser)) == 0) {
      exibeAdministrador(adm);
    }
  }
  }
  fclose(fp);
  free(adm);
}

void excluiAdministrador(void) {
  system("clear");
  FILE* fp;
  Administrador* adm;
  int achou = 0;
  char resp;
  char procurado[15];
  fp = fopen("administrador.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU DELETAR ADM ###########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o cpf do administrador a ser apagado:\n>>> ");
  scanf(" %14[^\n]", procurado);
  getchar();
  adm = (Administrador*) malloc(sizeof(Administrador));
  
  while((!achou) && (fread(adm, sizeof(Administrador), 1, fp))) {
   if ((strcmp(adm->cpf, procurado) == 0) && (adm->status == '1')) {
     achou = 1;
   }
  }
  
  if (achou) {
    exibeAdministrador(adm);
    printf("Deseja realmente apagar este administrador (s/n)?\n>>> ");
    scanf("%c", &resp);
    if (resp == 's' || resp == 'S') {
      adm->status = '0';
      fseek(fp, -1*sizeof(Administrador), SEEK_CUR);
      fwrite(adm, sizeof(Administrador), 1, fp);
      printf("\nAdministrador excluído com sucesso!!!\n");
     } else {
       printf("\nOk, os dados não foram alterados\n");
     }
  } else {
    printf("O administrador com cpf %s não foi encontrado...\n", procurado);
  }
  fclose(fp);
  free(adm);
}

int existAdm(char cpf_procurado[11]){
  FILE* fp;
  Administrador* adm;
  fp = fopen("administrador.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  adm = (Administrador*) malloc(sizeof(Administrador));
  while((fread(adm, sizeof(Administrador), 1, fp))) {
   if ((strcmp(adm->cpf, cpf_procurado) == 0) && (adm->status == '1')) {     
      free(adm);
      fclose(fp);
      printf("CPF já existe.");
      getchar();
      return 1;     
     }
  }
  if (verificaCpf(cpf_procurado)){
    free(adm);
    fclose(fp);
    return 0;
  }else{
    free(adm);
    fclose(fp);
    printf("CPF inválido!");
    getchar();
    return 1;
  }       
}
  
  

