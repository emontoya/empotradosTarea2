/*
 * Dado un valor entero sin signo y la cantidad de bits correspondientes a máscarada de red
 * calcula la ip de la subred y mostrándola en formato IPv4 al igual que la máscara.
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
          mensajeValidacionEntrada("Máscara de red inválida");
        }
      }
      else {
        mensajeValidacionEntrada("Separador de red/máscara incorrecto");
      }
    } else {
      mensajeValidacionEntrada("Argumentos inválidos");
    }
  } else {
    /* Hacer el parsing del primer entero*/
    if(parsearEntero(argv[1], &final, &red, &validarEntero32SinSigno) != 0){
      mensajeValidacionEntrada("Valor de red inválido");
    }

    /* Indicar que se comienza en el primer caracter para el segundo numero*/
    final = 0;

    /* Hacer el parsing del segundo entero*/
    if(parsearEntero(argv[2],&final, &bits, &validarEntero31Bits) != 0){
      mensajeValidacionEntrada("Máscara de red inválida");
    }
  }

  /* Para almacenar la máscara de red*/
  uint32_t mascara;
  uint32_t subred;

  /* Obtener la máscara de red*/
  mascara = 0xFFFFFFFF<< (32 - bits);

  /* Obtener la subred */
  subred = red & mascara;

  /* 
   * Conversión a IPv4 de la subred y de la máscara
   */
  printf("Network is %s, Mask is %s\n", EnteroToIPv4(subred), EnteroToIPv4(mascara));

  return 0;
}
