#include "verificanome.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#define FALSE 0
#define TRUE 1

int verificaNome(char name[40]){
  int i = 0;
  if(strlen(name) >= 3){
    for (i = 0; i < strlen(name); i++) {
            if ((isalpha(name[i]) == 0)){
                printf("Nome inválido!, informe um nome válido!\n");
                return TRUE;
            }
        }
        return FALSE;
  }
  else{
    return TRUE;
  }
}