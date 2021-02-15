#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

typedef struct usuario Usuario;

struct usuario {  
  char username[40];
  char senha[40];
  char tipoUsuario;
  char status;
  char cadastroFisico;
};

void cadastraUsuarioInicial(void);
void cadastraUsuario(void);
void buscaUsuario(void);
void editaUsuario(void);
void excluiUsuario(void);
void listaUsuario(void);
void exibeUsuario(Usuario*);
void gravaUsuario(Usuario*);
void logarUsuario(void);
int existUser(char username_procurado[40]);

#endif