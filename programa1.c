/* Programa 1. Convierte de entero a ipv4 */

#include <stdio.h>
#include <stdint.h>


void main(){

 uint32_t x;
 uint32_t y=0xFF;

 printf("Enter a number: ");
 scanf("%d", &x);

 printf("The address is: ");
 printf("%d", (x>>24)&y);
 printf(".%d", (x>>16)&y);
 printf(".%d", (x>>8)&y);
 printf(".%d\n", x&y);
}
