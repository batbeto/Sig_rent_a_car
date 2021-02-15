#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veiculocrud.h"
#include "verificanome.h"

void cadastraVeiculo(void) {
  system("clear");
  fflush(stdin);
  Veiculo* veiculo;
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU CADASTRO VEICULO ######\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  veiculo = (Veiculo*) malloc(sizeof(Veiculo));
  do{
  printf("Informe o nome do veiculo: \n>>> ");
  scanf(" %39[^\n]", veiculo->nome);
  getchar();
  }while(verificaNome(veiculo->nome));
  printf("Informe uma descrição breve do veiculo: \n>>> ");
  scanf(" %39[^\n]", veiculo->descricao);
  getchar();
  printf("Informe o preço de locação do veiculo: \n>>> ");
  scanf(" %f", &veiculo->precoLocacao);
  getchar();
  do{
  printf("Informe a placa de locação do veiculo: \n>>> ");
  scanf(" %14[^\n]", veiculo->placa);
  getchar();
  }while(existVeiculo(veiculo->placa));
  veiculo->status = '1';
  veiculo->kmRodadosVeiculo = 0;
  veiculo->alugado = 0;
  printf("Digite o tipo de veiculo: \n0) CARRO\n1) MOTO\n>>> ");
  scanf(" %d", &veiculo->tipoVeiculo);
  getchar();  
  printf("###############################\n");
  exibeVeiculo(veiculo);
  printf("###############################\n");
  gravaVeiculo(veiculo);
  fflush(stdin);
  free(veiculo);
}

void gravaVeiculo(Veiculo* veiculo) {
  FILE* fp;
  fp = fopen("veiculo.dat", "ab");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  fwrite(veiculo, sizeof(Veiculo), 1, fp);
  fclose(fp);
}

void editaVeiculo(void) {
  system("clear");
  FILE* fp;
  Veiculo* veiculo;
  int achou = 0;
  char resp;
  char procurado[15];
  fp = fopen("veiculo.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EDITAR VEICULO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe a placa do veiculo a ser alterado:\n>>> ");
  scanf(" %14[^\n]", procurado);
  veiculo = (Veiculo*) malloc(sizeof(Veiculo));

  while((!achou) && (fread(veiculo, sizeof(Veiculo), 1, fp))) {
   if ((strcmp(veiculo->placa, procurado) == 0) && (veiculo->status == '1')){
     achou = 1;
   }
  if (achou) {
    exibeVeiculo(veiculo);
    getchar();
    printf("Deseja realmente editar este veiculo (s/n)?\n>>> ");
    scanf("%c", &resp);
    if (resp == 's' || resp == 'S') {
      veiculo = (Veiculo*) malloc(sizeof(Veiculo));
      do{
      printf("Informe o nome do veiculo: \n>>> ");
      scanf(" %39[^\n]", veiculo->nome);
      getchar();
      }while(verificaNome(veiculo->nome));
      printf("Informe uma descrição breve do veiculo: \n>>> ");
      scanf(" %39[^\n]", veiculo->descricao);
      getchar();
      printf("Informe o preço de locação do veiculo: \n>>> ");
      scanf(" %f", &veiculo->precoLocacao);
      getchar();
      do{
      printf("Informe a placa do veiculo: \n>>> ");
      scanf(" %14[^\n]", veiculo->placa);
      getchar();
      }while(existVeiculo(veiculo->placa));
      veiculo->status = '1';
      printf("Digite o tipo de veiculo: \n0) CARRO\n1) MOTO\n>>> ");
      scanf(" %d",&veiculo->tipoVeiculo);
      getchar();
      fseek(fp, (-1)*sizeof(Veiculo), SEEK_CUR);
      fwrite(veiculo, sizeof(Veiculo), 1, fp);
      printf("\nVeiculo editado com sucesso!!!\n");
      } else {
      printf("\nOk, os dados não foram alterados\n");
      }    
    }else {
      printf("O veiculo com a placa %s não foi encontrado...\n", procurado);
    }  
  }
  free(veiculo);
  fclose(fp);
}


void exibeVeiculo(Veiculo* veiculo){
  printf("Nome: %s\n", veiculo->nome);
  printf("Descrição: %s\n", veiculo->descricao);
  printf("Status: %c\n", veiculo->status);
  printf("Placa: %s\n", veiculo->placa);
  printf("Km Rodados: %d\n", veiculo->kmRodadosVeiculo);
  printf("Preço Locação: %f\n", veiculo->precoLocacao);
  printf("Tipo de veiculo: %d\n", veiculo->tipoVeiculo);
  getchar();
  printf("\n");
}

void buscaVeiculo(void) {
  system("clear");
  FILE* fp;
  Veiculo* veiculo;
  int achou = 0;
  char procurado[15];
  fp = fopen("veiculo.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU BUSCAR VEICULO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe a placa do veiculo a ser buscado:\n>>> ");
  scanf(" %14[^\n]", procurado);
  getchar();
  veiculo = (Veiculo*) malloc(sizeof(Veiculo));
  achou = 0;
  while((!achou) && (fread(veiculo, sizeof(Veiculo), 1, fp))) {
   if ((strcmp(veiculo->placa, procurado) == 0) && (veiculo->status == '1')) {
     achou = 1;
   }
 }
  if (achou) {
    exibeVeiculo(veiculo);
  } else {
    printf("O veiculo com a placa %s não foi encontrado...\n", procurado);
  }  
  
  free(veiculo);
  fclose(fp);
}

void listaVeiculos(void) {
  system("clear");
  FILE* fp;
  Veiculo* veiculo;
  fp = fopen("veiculo.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU EXIBIR VEICULO ########\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  veiculo = (Veiculo*) malloc(sizeof(Veiculo));

  int op;
  printf("LISTAR:\n1) TODOS \n2) POR INICIAL DO NOME\n>>> ");
  scanf(" %d", &op);
  getchar();

  if(op == 1){
  while(fread(veiculo, sizeof(Veiculo), 1, fp)) {
    if (veiculo->status == '1') {
      exibeVeiculo(veiculo);
    }
  }
  }
  else if(op == 2){
    char nuser[40];
    printf("INSIRA AS INICIAIS DO NOME:\n");
    scanf(" %39[^\n]", nuser);
    getchar();
    while(fread(veiculo, sizeof(Veiculo), 1, fp)) {
    if (veiculo->status == '1' && strncmp(nuser, veiculo->nome, strlen(nuser)) == 0) {
      exibeVeiculo(veiculo);
    }
  }
  }
  fclose(fp);
  free(veiculo);
}

void excluiVeiculo(void) {
  system("clear");
  FILE* fp;
  Veiculo* veiculo;
  int achou = 0;
  char resp;
  char procurado[15];
  fp = fopen("veiculo.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }else{
    printf("\n\n");
    printf("####################################\n");
    printf("######  MENU DELETAR VEICULO #######\n");
    printf("####################################\n");
    printf("######### SIG RENT A CAR ###########\n");
    printf("####################################\n");
    printf("Informe a placa do veiculo a ser apagado:\n>>> ");
    scanf(" %14[^\n]", procurado);
    getchar();
    veiculo = (Veiculo*) malloc(sizeof(Veiculo));

    while((!achou) && (fread(veiculo, sizeof(Veiculo), 1, fp))) {
    if ((strcmp(veiculo->placa, procurado) == 0) && (veiculo->status == '1')) {
      achou = 1;
    }
    }
    
    if (achou) {
      exibeVeiculo(veiculo);
      printf("Deseja realmente apagar este Veiculo (s/n)?\n>>> ");
      scanf("%c", &resp);
      if (resp == 's' || resp == 'S') {
        veiculo->status = '0';
        fseek(fp, -1*sizeof(Veiculo), SEEK_CUR);
        fwrite(veiculo, sizeof(Veiculo), 1, fp);
        printf("\nVeiculo excluído com sucesso!!!\n");
      } else {
        printf("\nOk, os dados não foram alterados\n");
      }
    } else {
      printf("O Veiculo com a placa %s não foi encontrado...\n", procurado);
    }    
  }
  fclose(fp);
  free(veiculo);
}

int existVeiculo(char placa_procurado[11]){
  FILE* fp;
  Veiculo* veic;
  fp = fopen("veiculo.dat", "r+b");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  veic = (Veiculo*) malloc(sizeof(Veiculo));
  while((fread(veic, sizeof(Veiculo), 1, fp))) {
   if ((strcmp(veic->placa, placa_procurado) == 0) && (veic->status == '1')) {
     free(veic);
     fclose(fp);
     return 1;
   }
  }
  free(veic);
  fclose(fp);
  return 0;
}



NoVeiculo* listaKmRodados(void) {
  FILE* fp;
  Veiculo* veic;
  NoVeiculo* noVeiculo;
  NoVeiculo* lista;
  NoVeiculo* atual;
  NoVeiculo* anter;

  lista = NULL;
  fp = fopen("veiculo.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }

  veic = (Veiculo*) malloc(sizeof(Veiculo));
  while(fread(veic, sizeof(Veiculo), 1, fp)) {
    if (veic->status == '1') {
      noVeiculo = (NoVeiculo*) malloc(sizeof(NoVeiculo));
      noVeiculo->tipoVeiculo = veic->tipoVeiculo;
      strcpy(noVeiculo->nome, veic->nome);
      strcpy(noVeiculo->descricao, veic->descricao);
      noVeiculo->precoLocacao = veic->precoLocacao;
      strcpy(noVeiculo->placa, veic->placa);
      noVeiculo->kmRodadosVeiculo = veic->kmRodadosVeiculo;
      noVeiculo->alugado = veic->alugado;
      noVeiculo->status = veic->status;

      if (lista == NULL) {
        lista = noVeiculo;
        noVeiculo->proximo = NULL;
      } else if (noVeiculo->kmRodadosVeiculo > lista->kmRodadosVeiculo)  {
        noVeiculo->proximo = lista;
        lista = noVeiculo;
      } else {
        anter = lista;
        atual = lista->proximo;
        while ((atual != NULL) && (noVeiculo->kmRodadosVeiculo < lista->kmRodadosVeiculo)) {
          anter = atual;
          atual = atual->proximo;
        }
        anter->proximo = noVeiculo;
        noVeiculo->proximo = atual;
      }
    }
  }
  fclose(fp);
  free(veic);
  return lista;
}

NoVeiculo* listaKmRodadosInvertida(void) {
  FILE* fp;
  Veiculo* veic;
  NoVeiculo* noVeiculo;
  NoVeiculo* lista;
  NoVeiculo* atual;
  NoVeiculo* anter;
  lista = NULL;
  fp = fopen("veiculo.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }

  veic = (Veiculo*) malloc(sizeof(Veiculo));
  while(fread(veic, sizeof(Veiculo), 1, fp)) {
    if (veic->status == '1') {
      noVeiculo = (NoVeiculo*) malloc(sizeof(NoVeiculo));
      noVeiculo->tipoVeiculo = veic->tipoVeiculo;
      strcpy(noVeiculo->nome, veic->nome);
      strcpy(noVeiculo->descricao, veic->descricao);
      noVeiculo->precoLocacao = veic->precoLocacao;
      strcpy(noVeiculo->placa, veic->placa);
      noVeiculo->kmRodadosVeiculo = veic->kmRodadosVeiculo;
      noVeiculo->alugado = veic->alugado;
      noVeiculo->status = veic->status;

      if (lista == NULL) {
        lista = noVeiculo;
        noVeiculo->proximo = NULL;
      } else if (noVeiculo->kmRodadosVeiculo < lista->kmRodadosVeiculo)  {
        noVeiculo->proximo = lista;
        lista = noVeiculo;
      } else {
        anter = lista;
        atual = lista->proximo;
        while ((atual != NULL) && (noVeiculo->kmRodadosVeiculo > lista->kmRodadosVeiculo)) {
          anter = atual;
          atual = atual->proximo;
        }
        anter->proximo = noVeiculo;
        noVeiculo->proximo = atual;
      }
    }
  }
  fclose(fp);
  free(veic);
  return lista;
}

NoVeiculo* listaPreco(void) {
  FILE* fp;
  Veiculo* veic;
  NoVeiculo* noVeiculo;
  NoVeiculo* lista;
  NoVeiculo* atual;
  NoVeiculo* anter;

  lista = NULL;
  fp = fopen("veiculo.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }

  veic = (Veiculo*) malloc(sizeof(Veiculo));
  while(fread(veic, sizeof(Veiculo), 1, fp)) {
    if (veic->status == '1') {
      noVeiculo = (NoVeiculo*) malloc(sizeof(NoVeiculo));
      noVeiculo->tipoVeiculo = veic->tipoVeiculo;
      strcpy(noVeiculo->nome, veic->nome);
      strcpy(noVeiculo->descricao, veic->descricao);
      noVeiculo->precoLocacao = veic->precoLocacao;
      strcpy(noVeiculo->placa, veic->placa);
      noVeiculo->kmRodadosVeiculo = veic->kmRodadosVeiculo;
      noVeiculo->alugado = veic->alugado;
      noVeiculo->status = veic->status;

      if (lista == NULL) {
        lista = noVeiculo;
        noVeiculo->proximo = NULL;
      } else if (noVeiculo->precoLocacao > lista->precoLocacao)  {
        noVeiculo->proximo = lista;
        lista = noVeiculo;
      } else {
        anter = lista;
        atual = lista->proximo;
        while ((atual != NULL) && (noVeiculo->precoLocacao < lista->precoLocacao)) {
          anter = atual;
          atual = atual->proximo;
        }
        anter->proximo = noVeiculo;
        noVeiculo->proximo = atual;
      }
    }
  }
  fclose(fp);
  free(veic);
  return lista;
}

NoVeiculo* listaPrecoBaixo(void) {
  FILE* fp;
  Veiculo* veic;
  NoVeiculo* noVeiculo;
  NoVeiculo* lista;
  NoVeiculo* atual;
  NoVeiculo* anter;

  lista = NULL;
  fp = fopen("veiculo.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }

  veic = (Veiculo*) malloc(sizeof(Veiculo));
  while(fread(veic, sizeof(Veiculo), 1, fp)) {
    if (veic->status == '1') {
      noVeiculo = (NoVeiculo*) malloc(sizeof(NoVeiculo));
      noVeiculo->tipoVeiculo = veic->tipoVeiculo;
      strcpy(noVeiculo->nome, veic->nome);
      strcpy(noVeiculo->descricao, veic->descricao);
      noVeiculo->precoLocacao = veic->precoLocacao;
      strcpy(noVeiculo->placa, veic->placa);
      noVeiculo->kmRodadosVeiculo = veic->kmRodadosVeiculo;
      noVeiculo->alugado = veic->alugado;
      noVeiculo->status = veic->status;

      if (lista == NULL) {
        lista = noVeiculo;
        noVeiculo->proximo = NULL;
      } else if (noVeiculo->precoLocacao < lista->precoLocacao)  {
        noVeiculo->proximo = lista;
        lista = noVeiculo;
      } else {
        anter = lista;
        atual = lista->proximo;
        while ((atual != NULL) && (noVeiculo->precoLocacao > lista->precoLocacao)) {
          anter = atual;
          atual = atual->proximo;
        }
        anter->proximo = noVeiculo;
        noVeiculo->proximo = atual;
      }
    }
  }
  fclose(fp);
  free(veic);
  return lista;
}

NoVeiculo* listaAlugado(void) {
  FILE* fp;
  Veiculo* veic;
  NoVeiculo* noVeiculo;
  NoVeiculo* lista;
  NoVeiculo* atual;
  NoVeiculo* anter;

  lista = NULL;
  fp = fopen("veiculo.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }

  veic = (Veiculo*) malloc(sizeof(Veiculo));
  while(fread(veic, sizeof(Veiculo), 1, fp)) {
    if (veic->status == '1') {
      noVeiculo = (NoVeiculo*) malloc(sizeof(NoVeiculo));
      noVeiculo->tipoVeiculo = veic->tipoVeiculo;
      strcpy(noVeiculo->nome, veic->nome);
      strcpy(noVeiculo->descricao, veic->descricao);
      noVeiculo->precoLocacao = veic->precoLocacao;
      strcpy(noVeiculo->placa, veic->placa);
      noVeiculo->kmRodadosVeiculo = veic->kmRodadosVeiculo;
      noVeiculo->alugado = veic->alugado;
      noVeiculo->status = veic->status;

      if (lista == NULL) {
        lista = noVeiculo;
        noVeiculo->proximo = NULL;
      } else if (noVeiculo->alugado > lista->alugado)  {
        noVeiculo->proximo = lista;
        lista = noVeiculo;
      } else {
        anter = lista;
        atual = lista->proximo;
        while ((atual != NULL) && (noVeiculo->alugado < lista->alugado)) {
          anter = atual;
          atual = atual->proximo;
        }
        anter->proximo = noVeiculo;
        noVeiculo->proximo = atual;
      }
    }
  }
  fclose(fp);
  free(veic);
  return lista;
}


NoVeiculo* listaMenosAlugado(void) {
  FILE* fp;
  Veiculo* veic;
  NoVeiculo* noVeiculo;
  NoVeiculo* lista;
  NoVeiculo* atual;
  NoVeiculo* anter;
  
  lista = NULL;
  fp = fopen("veiculo.dat", "rb");
  if (fp == NULL) {
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }

  veic = (Veiculo*) malloc(sizeof(Veiculo));
  while(fread(veic, sizeof(Veiculo), 1, fp)) {
    if (veic->status == '1') {
      noVeiculo = (NoVeiculo*) malloc(sizeof(NoVeiculo));
      noVeiculo->tipoVeiculo = veic->tipoVeiculo;
      strcpy(noVeiculo->nome, veic->nome);
      strcpy(noVeiculo->descricao, veic->descricao);
      noVeiculo->precoLocacao = veic->precoLocacao;
      strcpy(noVeiculo->placa, veic->placa);
      noVeiculo->kmRodadosVeiculo = veic->kmRodadosVeiculo;
      noVeiculo->alugado = veic->alugado;
      noVeiculo->status = veic->status;

      if (lista == NULL) {
        lista = noVeiculo;
        noVeiculo->proximo = NULL;
      } else if (noVeiculo->alugado < lista->alugado)  {
        noVeiculo->proximo = lista;
        lista = noVeiculo;
      } else {
        anter = lista;
        atual = lista->proximo;
        while ((atual != NULL) && (noVeiculo->alugado > lista->alugado)) {
          anter = atual;
          atual = atual->proximo;
        }
        anter->proximo = noVeiculo;
        noVeiculo->proximo = atual;
      }
    }
  }
  fclose(fp);
  free(veic);
  return lista;
}

void exibeLista(NoVeiculo* lista) {
  printf("\n\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  while (lista != NULL) {
    printf("Nome: %s\n", lista->nome);
    printf("Preço da locação: %f\n", lista->precoLocacao);
    printf("Placa: %s\n", lista->placa);
    printf("KM rodados: %d\n", lista->kmRodadosVeiculo);
    printf("Numero de alugueis: %d\n", lista->alugado);
    printf("\n");
    lista = lista->proximo;
  }
}

