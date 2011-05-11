/* Programa 1. Convierte de entero a ipv4 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "tarea2Utils.h"


int main(int argc, char *argv[]){



 validProgram1(argc);

 unsigned int  x=strtoul(argv[1],NULL,0);
 
 
 
 
 printf("The address is: %s", EnteroToIPv4(x));

 



 return 0;



}
