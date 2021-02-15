#include "verificatelefone.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0


int verificaTelefone(char num_telefone[40]){
    if (strlen(num_telefone) > 7){
        int i;    
        for (i = 0; i < strlen(num_telefone); i++) {
            if ((isdigit(num_telefone[i])== FALSE)){
                return TRUE;
            }
        }
        return FALSE;
    }
    return TRUE; 
}