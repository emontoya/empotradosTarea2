/*
 * Dado un valor entero sin signo y la cantidad de bits correspondientes a la clase de red
 * calcula la ip de red y la máscara de subred.
 * El programa permitirá dos posibles formatos de entrada:
 * 1 -> num bits (la solicitada en la tarea)
 * 2 -> num/bits (Esta la vamos a agregar porque es la parecida a la representación habitual)
 */
#include <stdio.h>
#include <stdlib.h>
#include "tarea2Utils.h"

int main(int argc, const char *argv[]){

  uint32_t  red;
  uint32_t   bits;

  red = 10;
  bits = 2;
  
  int inicio = 0;
  int final = 0;

  if (argc <2 || argc > 3){
    mensajeValidacionEntrada("Argumentos inválidos");
  } else if (argc == 2){
    /* 
     * Como es solo un string que incluye el separado '/' se espera que el parsing
     * falle al encontrar el separador  
     */
    if(parsearEntero(argv[1], &final, &red, &validarEntero32SinSigno) != 0){
      /* Verificar que el fallo en el parsing sea por el separador */
      if (argv[1][final] == '/'){
        /* Descartar el separador */
        final++;
        
        /* Indicar el comienzo del segundo entero*/
        inicio = final;
        /* 
         * El parsing del segundo entero si debe retornar correctamente porque encuentra
         * el final del string
         */
        if(parsearEntero(argv[1],&final, &bits, &validarEntero31Bits) != 0){
          mensajeValidacionEntrada("Argumentos inválidos (Segundo entero)");
        }
      }
      else {
        mensajeValidacionEntrada("Argumentos inválidos (Separador incorrecto)");
      }
    } else {
      mensajeValidacionEntrada("Argumentos inválidos(Arg 2 parse 1 fail)");
    }
  } else {
    /* Hacer el parsing del primer entero*/
    if(parsearEntero(argv[1], &final, &red, &validarEntero32SinSigno) != 0){
      mensajeValidacionEntrada("Argumentos inválidos(Arg 1)");
    }

    /* Indicar que se comienza en el primer caracter para el segundo numero*/
    final = 0;

    /* Hacer el parsing del segundo entero*/
    if(parsearEntero(argv[2],&final, &bits, &validarEntero31Bits) != 0){
      mensajeValidacionEntrada("Argumentos inválidos(Arg 2)");
    }
  }

  /* Para almacenar la máscara de red*/
  uint32_t mascara;
  uint32_t subred;

  uint32_t MaxInt32 = 0xFFFFFFFF;

  /* Obtener la máscara de red*/
  mascara = MaxInt32 << (32 - bits);

  /* Obtener la subred */
  subred = red & mascara;

  // TODO: Esto debería meterse en una función para reutilizarla también en programa1;
  /* Conversión a IPv4 de la subred y de la máscara*/
  printf("Network is %u.%u.%u.%u, Mask is %u.%u.%u.%u\n",(uint8_t)((subred & 0xFF000000)>>24), (uint8_t)((subred & 0x00FF0000)>>16), (uint8_t)((subred & 0x0000FF00)>>8), (uint8_t)(subred & 0x000000FF),
    (uint8_t)((mascara & 0xFF000000)>>24), (uint8_t)((mascara & 0x00FF0000)>>16), (uint8_t)((mascara & 0x0000FF00)>>8), (uint8_t)(mascara & 0x000000FF));    

  return 0;
}
