/* Programa 1. Convierte de entero a ipv4 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "tarea2Utils.h"


int main(int argc, char *argv[]){

 validProgram1(argc);

 uint32_t x;
 int final=0;
 if(parsearEntero(argv[1],&final,&x, &validarEntero32SinSigno)==0){ 
  printf("The address is: %s\n", EnteroToIPv4(x));
 
 }
 else{
 printf("Error: Argumento No Valido-Debe ser un numero\n");
 
 }
 
 
 

 return 0;



}
