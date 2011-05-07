/*
 * Dado un valor entero sin signo y la cantidad de bits correspondientes a la clase de red
 * calcula la ip de red y la máscara de subred.
 * El programa permitirá dos posibles formatos de entrada:
 * 1 -> num bits (la solicitada en la tarea)
 * 2 -> num/bits (Esta la vamos a agregar porque es la parecida a la representación habitual)
 */
#include <stdio.h>
#include "tarea2Utils.h"

int main(int argc, const char *argv[]){

  uint32_t  red;
  uint8_t   bits;

  red = 10;
  bits = 2;
  
  int inicio = 0;
  int final = 0;

  if (argc <2 || argc > 3){
    mensajeValidacionEntrada("Argumentos inválidos");
  } else if (argc == 2){
	if(parsearEntero(argv[1], &final) != 0){
		if (argv[1][final] == '/'){
		  final++;
		  parsearEntero(argv[1],&final);
		}
		else {
		  mensajeValidacionEntrada("Argumentos invládos");
		}
	} else {
		mensajeValidacionEntrada("Argumentos inválidos(Arg 2 parse 1 fail)");
	}
  } else {
    parsearEntero(argv[1], &final);

    // TODO: procesar el primer entero

    final = 0;
    parsearEntero(argv[2],&final);

    // TODO: procesar el segundo entero
  }

  return 0;
}
