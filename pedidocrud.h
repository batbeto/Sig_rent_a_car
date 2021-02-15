#ifndef PEDIDOCRUD_H_INCLUDED
#define PEDIDOCRUD_H_INCLUDED
#include "veiculocrud.h"

typedef struct pedido Pedido;

struct pedido{
    char id[10];
    char cpf_cliente[12];
    char placa_veiculo[12];
    char data_inicio[11];
    char data_final[11];    
    char status;
    int km_rodados_pedido;
};
  

void cadastraPedido(void);
void buscaPedido(void);
void editaPedido(void);
void excluiPedido(void);
void listaPedido(void);
void exibePedido(Pedido*);
void gravaPedido(Pedido*);
void devolverPedido(void);
int existPedido(char id_procurado[10]);


#endif