#ifndef VEICULOCRUD_H_INCLUDED
#define VEICULOCRUD_H_INCLUDED

typedef struct veiculo Veiculo;
typedef struct noVeiculo NoVeiculo;

struct veiculo {
  int tipoVeiculo;
  char nome[40];
  char descricao[40];
  float precoLocacao;
  char placa[12];
  int kmRodadosVeiculo;
  int alugado;
  char status;
};

struct noVeiculo {
  int tipoVeiculo;
  char nome[40];
  char descricao[40];
  float precoLocacao;
  char placa[11];
  int kmRodadosVeiculo;
  int alugado;
  char status;
  NoVeiculo* proximo;
};


void menuPVeiculo(void);
void cadastraVeiculo(void);
void buscaVeiculo(void);
void editaVeiculo(void);
void excluiVeiculo(void);
void listaVeiculos(void);
void exibeVeiculo(Veiculo*);
void sobre(void);
void gravaVeiculo(Veiculo*);
NoVeiculo* listaKmRodados(void);
NoVeiculo* listaKmRodadosInvertida(void);
NoVeiculo* listaPreco(void);
NoVeiculo* listaPrecoBaixo(void);
NoVeiculo* listaAlugado(void);
NoVeiculo* listaMenosAlugado(void);
void exibeLista(NoVeiculo* lista);
int existVeiculo(char placa_procurado[11]);

#endif