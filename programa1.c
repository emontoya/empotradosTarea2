/* Programa 1. Convierte de entero a ipv4 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "utilsx.h"


int main(int argc, char *argv[]){

 valid1Program1(argc);

 unsigned int  x=strtoul(argv[1],NULL,0);
 
 
 uint32_t y=0xFF;
  
 
 printf("The address is: ");
 
 printf("%u", (x>>24)&y);
 printf(".%u", (x>>16)&y);
 printf(".%u", (x>>8)&y);
 printf(".%u\n", x&y);


 return 0;

}
