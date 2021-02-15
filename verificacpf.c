#include "verificacpf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define CPF 11
#define TRUE 1
#define FALSE 0

  
int verificaCpf(char num_cpf[40]){
    fflush(stdin);
    int i_cpf[11], i,somador=0, resultado,sum, verificador_1, verificador_2, peso; 
    
    if (num_cpf == NULL){
        return TRUE;
    } 
    if (strlen(num_cpf)!= CPF){
        return TRUE;
    }

    if (isAlpha(num_cpf)){
        return TRUE;
    }
    
    for(i=0; i < 11;i++){  
        i_cpf[i] = num_cpf[i]-48;
        
    }
       

    for(i=0;i<9;i++){  
        sum += i_cpf[i]*(10-i);  
    }  
    
    resultado = (sum % 11);
    
    if  (resultado == 1 || resultado == 0){
        verificador_1 = 0;
    }else {
        verificador_1 = resultado - 11;
    }
    for(i=0;i<10;i++){  
        sum += i_cpf[i]*(11-i);  
    }  
    

    resultado = (sum % 11);
    
    if  (resultado == 1 || resultado == 0){
        verificador_2 = 0;
    }else {
        verificador_2 = resultado - 11;
    }
    
    if ((verificador_1 == i_cpf[9]) && (verificador_2 == i_cpf[10])){
        return FALSE;
    }else{
        return TRUE;
    }
    

}


int isAlpha(const char *cpf){
    do {
        if (! isdigit(*cpf)) {
        return 1;
        }
    } while(*(++cpf));
    return 0;
}

