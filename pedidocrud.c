#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedidocrud.h"
#include "verificacpf.h"
#include "veiculocrud.h"
#include "clientecrud.h"


void cadastraPedido(void) {
  system("clear");
  fflush(stdin);
  Pedido* ped;
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU  CADASTRO PEDIDO ######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("= = = = = = = = = = = \n");
  ped = (Pedido*) malloc(sizeof(Pedido));
  do{
  printf("Informe o id do Pedido: \n>>> ");
  scanf(" %14[^\n]", ped->id);
  getchar();
  }while(existPedido(ped->id));
  fflush(stdin);
  do{
  printf("Informe o CPF do cliente: \n>>> ");
  scanf(" %14[^\n]", ped->cpf_cliente);
  getchar();
  }while(!clienPed(ped->cpf_cliente));
  fflush(stdin);
  do{
  printf("Informe a placa do veiculo: \n>>> ");
  scanf(" %14[^\n]", ped->placa_veiculo);
  getchar();
  }while(!existVeiculo(ped->placa_veiculo));

  printf("Informe data inicial: \n>>> ");
  scanf(" %14[^\n]", ped->data_inicio);
  getchar();
  ped->km_rodados_pedido = 0;
  ped->status = '1';
  printf("###############################\n");
  exibePedido(ped);
  printf("###############################\n");
  gravaPedido(ped);
  fflush(stdin);
  free(ped);
}

void gravaPedido(Pedido* ped) {
  FILE* fp;
  fp = fopen("pedido.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  fwrite(ped, sizeof(Pedido), 1, fp);
  fclose(fp);
}

void exibePedido(Pedido* ped) {
  printf("id: %s\n", ped->id);
  printf("CPF Cliente:  %s\n", ped->cpf_cliente);
  printf("PLACA do veiculo:  %s\n", ped->placa_veiculo);
  printf("Data do inicio:  %s\n", ped->data_inicio);
  printf("Status:  %c\n", ped->status);
  if(ped->km_rodados_pedido == 0){
    printf("O PEDIDO ESTÁ EM TRÂMITE.\n");
  }else{
    printf("O PEDIDO FOI DEVOLVIDO.\n");
  }
  getchar();
  printf("\n");
}

void editaPedido(void) {
  system("clear");
  FILE* fp;
  Pedido* ped;
  int achou = 0;
  char resp;
  char procurado[15];
  fp = fopen("pedido.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU  EDITAR PEDIDO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o id do Pedido a ser alterado: ");
  scanf(" %14[^\n]", procurado);
  ped = (Pedido*) malloc(sizeof(Pedido));

  while((!achou) && (fread(ped, sizeof(Pedido), 1, fp))) {
   if ((strcmp(ped->id, procurado) == 0) && (ped->status == '1')) {
     achou = 1;
   }
  }
  if (achou) {
    exibePedido(ped);
    getchar();
    printf("Deseja realmente editar este Pedido (s/n)? ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {
      do{
      printf("Informe o id do Pedido: ");
      scanf(" %14[^\n]", ped->id);
      getchar();
      }while(existPedido(ped->id));
      printf("Informe CPF do cliente: ");
      scanf(" %14[^\n]", ped->cpf_cliente);
      printf("Informe a data inicial do Pedido: ");
      scanf(" %10[^\n]", ped->data_inicio);
      getchar();
      printf("Informe a placa do veiculo: \n>>> ");
      scanf(" %14[^\n]", ped->placa_veiculo);
      getchar();
      ped->status = '1';
      fseek(fp, -1*sizeof(Pedido), SEEK_CUR);
      fwrite(ped, sizeof(Pedido), 1, fp);
      printf("\nPedido editado com sucesso!!!\n");
    } else {
      printf("\nOk, os dados não foram alterados\n");
    }
  } else {
    printf("O Pedido com id %s não foi encontrado...\n", procurado);
  }
  free(ped);
  fclose(fp);
}

void buscaPedido(void) {
  system("clear");
  FILE* fp;
  Pedido* ped;
  int achou = 0;
  char procurado[15];
  fp = fopen("pedido.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU  BUSCAR PEDIDO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o id do Pedido a ser buscado:\n ");
  scanf(" %14[^\n]", procurado);
  getchar();
  ped = (Pedido*) malloc(sizeof(Pedido));

  while((!achou) && (fread(ped, sizeof(Pedido), 1, fp))) {
   if ((strcmp(ped->id, procurado) == 0) && (ped->status == '1')) {
     achou = 1;
   }
  }
 
  if (achou) {
    exibePedido(ped);
  } else {
    printf("O pedido com id %s não foi encontrado...\n", procurado);
  }
  free(ped);
  fclose(fp);
}

void listaPedido(void) {
  system("clear");
  FILE* fp;
  Pedido* ped;
  fp = fopen("pedido.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU  EXIBIR PEDIDO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  ped = (Pedido*) malloc(sizeof(Pedido));
  while(fread(ped, sizeof(Pedido), 1, fp)) {
    if (ped->status == '1') {
      exibePedido(ped);
    }
  }
  fclose(fp);
  free(ped);
}

void excluiPedido(void) {
  system("clear");
  FILE* fp;
  Pedido* ped;
  int achou = 0;
  char resp;
  char procurado[15];
  fp = fopen("pedido.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU DELETAR PEDIDO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o ID do Pedido a ser apagado: ");
  scanf(" %14[^\n]", procurado);
  getchar();
  ped = (Pedido*) malloc(sizeof(Pedido));
  achou = 0;
  while((!achou) && (fread(ped, sizeof(Pedido), 1, fp))) {
   if ((strcmp(ped->id, procurado) == 0) && (ped->status == '1')) {
     achou = 1;
   }
  }
  
  if (achou) {
    exibePedido(ped);
    printf("Deseja realmente apagar este Pedido (s/n)? ");
    scanf("%c", &resp);
    if (resp == 's' || resp == 'S') {
      ped->status = '0';
      fseek(fp, -1*sizeof(Pedido), SEEK_CUR);
      fwrite(ped, sizeof(Pedido), 1, fp);
      printf("\nPedido excluído com sucesso!!!\n");
     } else {
       printf("\nOk, os dados não foram alterados\n");
     }
  } else {
    printf("O Pedido com %s não foi encontrado...\n", procurado);
  }
  fclose(fp);
  free(ped);
}


int existPedido(char id_procurado[10]){
  FILE* fp;
  Pedido* ped;
  fp = fopen("pedido.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  ped = (Pedido*) malloc(sizeof(Pedido));
  while((fread(ped, sizeof(Pedido), 1, fp))) {
   if ((strcmp(ped->id, id_procurado) == 0) && (ped->status == '1')) {
     free(ped);
     fclose(fp);
     return 1;
   }
  }
  free(ped);
  fclose(fp);
  return 0;
}


void devolverPedido(void){
  system("clear");
  FILE* fp;
  Pedido* ped;
  int achou = 0;
  char resp;
  char procurado[15];
  fp = fopen("pedido.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU  DEVOLVER PEDIDO ######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o id do pedido a ser devolvido:\n>>> ");
  scanf(" %14[^\n]", procurado);
  ped = (Pedido*) malloc(sizeof(Pedido));

  while((!achou) && (fread(ped, sizeof(Pedido), 1, fp))) {
   if ((strcmp(ped->id, procurado) == 0) && (ped->status == '1')) {
     achou = 1;
   }
  }
  if (achou) {
    if(ped->km_rodados_pedido == 0){
    exibePedido(ped);
    getchar();
    printf("Deseja realmente entregar o veiculo (s/n)? ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {      
      printf("Informe a data final do Pedido: ");
      scanf(" %10[^\n]", ped->data_final);      
      getchar();

      printf("Informe os kilometros rodados: ");
      scanf(" %d", &ped->km_rodados_pedido);      
      getchar();




      FILE* fp2;
      fp2 = fopen("veiculo.dat", "r+b");

      Veiculo* veiculo;
      veiculo = (Veiculo*) malloc(sizeof(Veiculo));
      int achou1 = 0;

      while((!achou1) && (fread(veiculo, sizeof(Veiculo), 1, fp2))) {
        if ((strcmp(veiculo->placa, ped->placa_veiculo) == 0) && (veiculo->status == '1')) {
          veiculo->kmRodadosVeiculo += ped->km_rodados_pedido;
          veiculo->alugado += 1;
          fseek(fp2, (-1)*sizeof(Veiculo), SEEK_CUR);
          fwrite(veiculo, sizeof(Veiculo), 1, fp2);
          achou1 = 1;
        }
      }
      free(veiculo);
      fclose(fp2);
      
           
      ped->status = '1';
      fseek(fp, -1*sizeof(Pedido), SEEK_CUR);
      fwrite(ped, sizeof(Pedido), 1, fp);
      printf("\nPedido devolvido com sucesso!!!\n");
    } else {
      printf("\nOk, os dados não foram alterados\n");
    }
}else{
  printf("Pedido já está devolvido!.");
}

  } else {
    printf("O Pedido com id %s não foi encontrado...\n", procurado);
  }
  free(ped);
  fclose(fp);
}