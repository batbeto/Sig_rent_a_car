#include <stdlib.h>
#include <stdio.h>
#include "admcrud.h"
#include "clientecrud.h"
#include "operadorcrud.h"
#include "veiculocrud.h"
#include "pedidocrud.h"
#include "login.h"
#include <string.h>
#include "index.h"

void menuInicial(void){
  system("clear");
  int op;
  FILE* user;
  user = fopen("usuario.dat", "r+b");
  if (user == NULL) {
    cadastraUsuarioInicial();
  }
  do{
        system("clear");
        fflush(stdin);
        printf("##############################################\n");
        printf("########  MENU  INICIAL ######################\n");
        printf("##############################################\n");
        printf("######### SIG RENT A CAR #####################\n");
        printf("########### BEM VINDO ########################\n");
        printf("##############################################\n");    
        printf("####### 1 - LOGIN ############################\n");
        printf("####### 2 - SOBRE ############################\n");
        printf("####### 3 - SAIR #############################\n");
        printf("##############################################\n>>> ");
        scanf("%d", &op);
        getchar();
        switch(op){
          case 1:
            system("clear");
            menuLogin();
            break;
          case 2:
            system("clear");
            sobre();
            break;
          default:
            system("clear");
            break; 
        }
    }while(op != 3);
    fclose(user);
}

void menuLogin(){
  system("clear");
  FILE* fp;
  Usuario* user;
  int achou = 0;
  char procurado[40];
  char password[40];
  fp = fopen("usuario.dat", "rb");
  if (fp == NULL){
    printf("Ops! Ocorreu um erro na abertura do arquivo!\n");
    printf("Não é possível continuar o programa...\n");
    exit(1);
  }
  printf("\n\n");
  printf("####################################\n");
  printf("######  MENU LOGIN #################\n");
  printf("####################################\n");
  printf("######### SIG RENT A CAR ###########\n");
  printf("####################################\n");
  printf("Informe o username:\n>>> ");
  scanf(" %39[^\n]", procurado);
  getchar();
  printf("Informe a senha:\n>>> ");
  scanf(" %39[^\n]", password);
  getchar();
  user = (Usuario*) malloc(sizeof(Usuario));
  achou = 0;

  while((!achou) && (fread(user, sizeof(Usuario), 1, fp))) {
    if ((strcmp(user->username, procurado) == 0) && (strcmp(user->senha, password) == 0) && (user->status == '1')) {
      achou = 1;
    }
  }
  
  if (achou) {
    if(user->cadastroFisico == '1'){
      if(user->tipoUsuario == '1'){
      menuAdministrativo();
    }else {
      menuOperativo();        
    }
    }
  else {
    if(user->tipoUsuario == '1'){
        cadastraAdministradorInicial(user);
    }else {
        cadastraOperadorInicial(user);     
    }
  }
        
  } else{
    printf("O usuario %s não foi encontrado...\n", user->username);
  }
  free(user);
  fclose(fp);
}


void menuOperativo(void){
  system("clear");
  int op;
    do{
        system("clear");
        fflush(stdin);
        printf("##############################################\n");
        printf("########  MENU  OPERADOR #####################\n");
        printf("##############################################\n");
        printf("######### SIG RENT A CAR #####################\n");
        printf("########### BEM VINDO ########################\n");
        printf("##############################################\n");        
        printf("####### 1 - CLIENTE ##########################\n");
        printf("####### 2 - PEDIDO ###########################\n");
        printf("####### 3 - RELATORIO ########################\n");
        printf("####### 4 - SAIR #############################\n");
        printf("##############################################\n>>> ");
        scanf("%d", &op);
        getchar();
        switch (op)
        {
        case 1:
            system("clear");
            menuOperativoUsuario();
            break;
        
        case 2:
            system("clear");
            menuOperativoPedido();
            break;
        case 3:
            system("clear");
            menuRelatorio();
            break;
        default:
            system("clear");
            break;
        }
    }while(op != 4);
}


void menuOperativoPedido(void){
  system("clear");
  int op;
    do{
        system("clear");
        fflush(stdin);
        printf("##############################################\n");
        printf("########  MENU  OPERADOR #####################\n");
        printf("##############################################\n");
        printf("######### SIG RENT A CAR #####################\n");
        printf("########### BEM VINDO ########################\n");
        printf("##############################################\n");        
        printf("####### 1 - CADASTRAR PEDIDO ###################\n");
        printf("####### 2 - ACESSAR PEDIDO #####################\n");
        printf("####### 3 - ALTERAR PEDIDO #####################\n");
        printf("####### 4 - LISTAR PEDIDO ######################\n");
        printf("####### 5 - DEVOLVER PEDIDO ####################\n");
        printf("####### 6 - SAIR     #########################\n");
        printf("##############################################\n>>> ");
        scanf("%d", &op);
        getchar();
        switch (op)
        {
        case 1:
            system("clear");
            cadastraPedido();
            break;
        
        case 2:
            system("clear");
            buscaPedido();
            break;
        
        case 3:
            system("clear");
            editaPedido();
            break;
        
        case 4:
            system("clear");
            listaPedido();
            break;
        case 5:
            system("clear");
            devolverPedido();
            break;
        default:
            system("clear");
            break;
        }
    }while(op != 6);
}

void menuOperativoUsuario(void){
  system("clear");
  int op;
    do{
        system("clear");
        fflush(stdin);
        printf("##############################################\n");
        printf("########  MENU  OPERADOR #####################\n");
        printf("##############################################\n");
        printf("######### SIG RENT A CAR #####################\n");
        printf("########### BEM VINDO ########################\n");
        printf("##############################################\n");        
        printf("####### 1 - CADASTRAR CLIENTE ###################\n");
        printf("####### 2 - ACESSAR CLIENTE #####################\n");
        printf("####### 3 - ALTERAR CLIENTE #####################\n");
        printf("####### 4 - LISTAR CLIENTE ######################\n");
        printf("####### 5 - SAIR     #########################\n");
        printf("##############################################\n>>> ");
        scanf("%d", &op);
        getchar();
        switch (op) {
        case 1:
            system("clear");
            cadastraCliente();
            break;
        
        case 2:
            system("clear");
            buscaCliente();
            break;
        
        case 3:
            system("clear");
            editaCliente();
            break;
        
        case 4:
            system("clear");
            listaClientes();
            break;
        default:
            system("clear");
            break;
        }
    }while(op != 5);
}

void menuAdministrativo(void){
  system("clear");
  int op;
    do{
        system("clear");
        fflush(stdin);
        printf("##############################################\n");
        printf("########  MENU  PRINCIPAL ####################\n");
        printf("##############################################\n");
        printf("######### SIG RENT A CAR #####################\n");
        printf("########### BEM VINDO ########################\n");
        printf("##############################################\n");        
        printf("####### 1 - CADASTRAR DADO ###################\n");
        printf("####### 2 - ACESSAR DADO #####################\n");
        printf("####### 3 - ALTERAR DADO #####################\n");
        printf("####### 4 - LISTAR DADO ######################\n");
        printf("####### 5 - DELETAR DADO #####################\n");
        printf("####### 6 - RELATORIO ########################\n");
        printf("####### 7 - SAIR     #########################\n");
        printf("##############################################\n>>> ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            system("clear");
            menuCadastrarDado();
            break;
        
        case 2:
            system("clear");
            menuAcessarDado();
            break;
        
        case 3:
            system("clear");
            menuAlterarDado();
            break;
        
        case 4:
            system("clear");
            menuListarDado();
            break;
        case 5:
            system("clear");
            menuDeletarDado();
            break;
        case 6:
            system("clear");
            menuRelatorio();
            break;
        default:
            system("clear");
            break;
        }
    }while(op != 7);
}


void menuCadastrarDado(void){
    system("clear");
    fflush(stdin);
    int op;
    printf("##########################################\n");
    printf("######  MENU  CADASTRO DADO ##############\n");
    printf("##########################################\n");
    printf("######### SIG RENT A CAR #################\n");
    printf("##########################################\n");
    printf("VOCE DESEJA CADASTRAR O QUE? \n1) ADMINISTRADOR \n2) CLIENTE \n3) OPERADOR\n4) VEICULO\n5) USUARIO \n6) PEDIDO\n7) SAIR\n>>> ");
    scanf("%d", &op);
    switch (op)    {
    case 1:
        system("clear");
        cadastraAdministrador();
        break;

    case 2:
        system("clear");
        cadastraCliente();
        break;

    case 3:
        system("clear");
        cadastraOperador();
        break;

    case 4:
        system("clear");
        cadastraVeiculo();
        break;
    case 5:
        system("clear");
        cadastraUsuario();
        break;
    case 6:
        system("clear");
        cadastraPedido();
        break;
    default:
        system("clear");
        break;
    }
}

void menuAcessarDado(void){
    system("clear");
    fflush(stdin);    
    int op;
    printf("##########################################\n");
    printf("######  MENU  ACESSAR DADO ###############\n");
    printf("##########################################\n");
    printf("######### SIG RENT A CAR #################\n");
    printf("##########################################\n");
    printf("VOCE DESEJA ACESSAR O QUE? \n1) ADMINISTRADOR \n2) CLIENTE \n3) OPERADOR\n4) VEICULO \n5) USUARIO \n6) PEDIDO \n7) DEVOLVER PEDIDO\n8) SAIR\n>>> ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        system("clear");
        buscaAdministrador();
        break;
    case 2:
        system("clear");
        buscaCliente();
        break;
    case 3:
        system("clear");
        buscaOperador();
        break;
    case 4:
        system("clear");
        buscaVeiculo();
        break;
    case 5:
        system("clear");
        buscaUsuario();
        break;
    case 6:
        system("clear");
        buscaPedido();
    case 7:
        system("clear");
        devolverPedido();
        break;
    default:
        system("clear");
        break;
    }
}

void menuAlterarDado(void){
    system("clear");
    fflush(stdin);
    int op;
    printf("##########################################\n");
    printf("######  MENU  EDITAR DADO ################\n");
    printf("##########################################\n");
    printf("######### SIG RENT A CAR #################\n");
    printf("##########################################\n");
    printf("VOCE DESEJA ALTERAR O QUE? \n1) ADMINISTRADOR \n2) CLIENTE \n3) OPERADOR\n4) VEICULO\n5) USUARIO \n6) PEDIDO\n7) SAIR\n>>> ");
    scanf("%d", &op);
    getchar();
    switch (op)
    {
    case 1:
        system("clear");
        editaAdministrador();
        break;
    case 2:
        system("clear");
        editaCliente();
        break;
    case 3:
        system("clear");
        editaOperador();
        break;
    case 4:
        system("clear");
        editaVeiculo();
        break;
    case 5:
        system("clear");
        editaUsuario();
        break;
    case 6:
        system("clear");
        editaPedido();
        break;
    default:
        system("clear");
        break;
    }
}


void menuDeletarDado(void){
    system("clear");
    int op;
    int id;
    char cpf[11];
    system("clear");
    printf("##########################################\n");
    printf("######  MENU DELETAR DADO ################\n");
    printf("##########################################\n");
    printf("######### SIG RENT A CAR #################\n");
    printf("##########################################\n");
    printf("INSIRA O TIPO DE DADO QUE DESEJA DELETAR \n1) ADMINISTRADOR \n2) CLIENTE \n3) OPERADOR \n4) VEICULO\n5) USUARIO \n6 PEDIDO\n7) SAIR\n>>> ");
    scanf("%d", &op);
    getchar();
    switch (op){
    case 1:
        system("clear");
        excluiAdministrador();       
        printf("ADMINISTRADOR DELETADO COM SUCESSO !.");
        getchar();
        break;
    
    case 2:
        system("clear");
        excluiCliente();
        printf("CLIENTE DELETADO COM SUCESSO !.");
        getchar();
        break;
    case 3:
        system("clear");
        excluiOperador();
        printf("OPERADOR DELETADO COM SUCESSO !.");
        getchar();
        break;
    case 4:
        system("clear");
        excluiVeiculo();
        printf("VEICULO DELETADO COM SUCESSO !.");
        getchar();
        break;
    case 5:
        system("clear");
        excluiUsuario();
        printf("USUARIO DELETADO COM SUCESSO !.");
        getchar();
        break;
    case 6:
        system("clear");
        excluiPedido();
        printf("PEDIDO DELETADO COM SUCESSO !.");
        getchar();
        break;
    default:
        system("clear");
        break;
    }
}

void menuListarDado(void){
    system("clear");
    int op;
    int id;
    char cpf[11];
    printf("##########################################\n");
    printf("######  MENU DELETAR DADO ################\n");
    printf("##########################################\n");
    printf("######### SIG RENT A CAR #################\n");
    printf("##########################################\n");
    printf("INSIRA O TIPO DE DADO QUE DESEJA LISTAR \n1) ADMINISTRADOR \n2) CLIENTE \n3) OPERADOR \n4) VEICULO\n5) USUARIO\n6) PEDIDO\n7) SAIR\n>>> ");
    scanf("%d", &op);
    getchar();
    switch (op){
    case 1:
        system("clear");
        listaAdministradores();  
        getchar();     
        break;    
    case 2:
        system("clear");
        listaClientes(); 
        getchar();      
        break;
    case 3:
        system("clear");
        listaOperador();
        getchar();
        break;
    case 4:
        system("clear");
        listaVeiculos();
        getchar();
        break;
    case 5:
        system("clear");
        listaUsuario();
        getchar();
        break;
    case 6:
        system("clear");
        listaPedido();
        getchar();
        break;
    default:
        system("clear");
        break;
    }
}

void menuRelatorio(void){
    system("clear");
    int op;
    int id;
    char cpf[11];
    NoVeiculo* lista;
    printf("##########################################\n");
    printf("#########  MENU RELATORIO ################\n");
    printf("##########################################\n");
    printf("######### SIG RENT A CAR #################\n");
    printf("##########################################\n");
    printf("ESCOLHA O RELATORIO: \n1) KM VEICULO(+RODADO) \n2) KM VEICULO(-RODADO) \n3) PREÇO ALUGUEL(+ALTO) \n4) PREÇO ALUGUEL(+BAIXO) \n5) FREQUENCIA ALUGUEL(+FREQUENTE)\n6) FREQUENCIA ALUGUEL(-FREQUENTE)\n7) SAIR \n>>> ");
    scanf("%d", &op);
    getchar();
    switch (op){
    case 1:
        system("clear");
        lista = listaKmRodados();
        exibeLista(lista);
        getchar();       
        break;    
    case 2:
        system("clear");
        lista = listaKmRodadosInvertida();
        exibeLista(lista);
        getchar();     
        break;
    case 3:
        system("clear");
        lista = listaPreco();
        exibeLista(lista);
        getchar();
        break;
    case 4:
        system("clear");
        lista = listaPrecoBaixo();
        exibeLista(lista);
        getchar();
        break;
    case 5:
        system("clear");
        lista = listaAlugado();
        exibeLista(lista);
        getchar();
        break;
    case 6:
        system("clear");
        lista = listaMenosAlugado();
        exibeLista(lista);
        getchar();
        break;
    default:
        system("clear");
        break;
    }
}

void sobre(void){
  printf("##########################################\n");
  printf("######### SIG RENT A CAR #################\n");
  printf("##########################################\n");
  printf("UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE(UFRN)\n");
  printf("Professor: Flavius Gorgonio\n");
  printf("Programa produzido por Arthur Anthony e Adalberto Maia, alunos de BSI \n");
  printf("Numero para contato: (84)99709-6080 e (84)99610-2812\n");
  printf("Emails para contato: arthuranthony2000@gmail.com e btowmaia@gmail.com\n");
  getchar();
}