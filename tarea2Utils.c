#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "tarea2Utils.h" 

static const char *errorArgumentos = "Formatos aceptados son los siguientes:\n\t1->num bits\n\t2->num/bits\n";

/*
 * Imprime un mensaje indicando cuál es el formato esperado para la entrada
 * del programa2 de la tarea
 */
void imprimirArgumentosEsperadosP2(){
  terminarConMensaje(errorArgumentos);
}

/*
 * Termina la ejecución del programa mostŕando un mensaje
 * en la salida de error standar 
 */
void terminarConMensaje(const char *err){
  fprintf(stderr,"[Error]: %s\n",err);
  exit(1);
}

/*
 * Termina la ejecución del programa mostrando un mensaje 
 * y la información del último error. 
 */
void terminarConError(const char *err){
  perror(err);
  exit(1);
}

/*
 * Imprime un mensaje de validación de la entrada de datos, seguido de una descripción de la entrada esperada
 * y termina la ejecución del programa
 */
void mensajeValidacionEntrada(const char *msg){
  fprintf(stderr, "[Error]: %s\n", msg);
  fprintf(stderr, "%s", errorArgumentos); 
  exit(1);
}

/*
 * Hace el Parsing de un string sin signo comenzando en la posición (posicion)
 * retorna 0 si termina el parsing correctamente y 1 si ocurrió algún error.
 * La variable posición retorna la última posición procesada
 */
int parsearEntero(const char *arg, int *posicion){
  /* Inicializar el procesamiento en el estado inicial */
  int estado = 0;

  if (arg != NULL){
    /* 
     * Consumir caracteres hasta llegar al estado de aceptación (2).
     * Si se encuentra un caracter inválido se sale de la función
     * dejando la posición apuntando al caracter inválido.
     */
    while(estado != 2){
      /* Discriminar el estado actual en el parsing*/
      switch (estado){
        /* Inicio del parsing de la cadena*/
        case 0: 
          switch(arg[*posicion]){
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
              /* Mover el puntero para consumir el siguiente caracter y pasar al estado 1*/
              (*posicion)++;
              estado = 1;
              break;
            default:
              return 1;
              break;
          }
          break;
        /* Reconociendo el entero, después del primer valor */
        case 1: 
          switch(arg[*posicion]){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
              /* Mover el puntero para consumir el siguiente caracter y pasar al estado 1*/
              (*posicion)++;
              break;
            default:
              return 1;
              break; 
          }
          break;
      }
    }
  } else{
    return 1; 
  }

  return 0;
}
