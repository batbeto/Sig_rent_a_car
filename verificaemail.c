#include "verificaemail.h"
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0


int verificaEmail(char email[40]){ 
   if (strlen(email) > 5){
   int arroba = 0, ponto = 0, antesPonto = 0, depoisPonto = 0, i;
   for (i = 0; i < strlen(email); i++) {
      char c = email[i];
      if(c == '@') {
         if (arroba)
         break; 
         arroba = 1;
         if (i < 3)
         break; 
      }
      else if (arroba) { 
         if (ponto) { 
         depoisPonto++;
         }
         else if(c == '.') {
         ponto = 1;
         if (antesPonto < 3) {
            break; 
         }
         }
         else {
         antesPonto++;
         }
      }
   } 
   
   if (i == strlen(email) && depoisPonto > 1){
      
      return FALSE;
   }
   }
  printf("Email invalido!\n"); 
  return TRUE;
}
