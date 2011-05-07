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
 * Retorna el entero reconocido:
 * Esta función es temporal, solo para verificar
 * que se estén reconociendo bien los valores
 * (No se hace ninguna validación, se asume que
 * los parámetros son válidos)
 *
 * Se entiende la sobrecarga de ejecutar esta función
 * por el recorrido que hace del string, por eso solo se utilizará
 * como herramienta de debug
 */
char * obtenerValor(const char *arg, int inicio, int final){
  char *result;
  int length = final - inicio;

  if ((result = (char *)malloc(sizeof(char)*(length) + 1)) == NULL){
    terminarConError("No hay espacio en memoria\n");
  } 
  
  result[length] = '\0';

  int i;
  for(i = 0; i <= length; i++){
    result[i] = arg[inicio + i];
  }

  return result;
}

/*
 *
 */
int convertirEntero(const char *arg, int inicio, int final, uint32_t *entero){
  return 0;
}

/*
 * Validador para un entero de 32 bits sin signo
 */
int validarEntero32SinSigno(char actual, int inicio, int posicion, int estado){
  return 0;
}

/*
 * Validador para un entero menor o igual a 31
 */
int validarEntero31Bits(char actual, int inicio, int posicion, int estado){
  return 0;
}

/*
 * Hace el Parsing de un string sin signo comenzando en la posición (posicion)
 * retorna 0 si termina el parsing correctamente y 1 si ocurrió algún error.
 * La variable posición retorna la última posición procesada
 * - Esta función no valida que se reciba una cadena nula, ni tampoco que
 *   la cadena en la posición sea correcta. (Esto se hace para evitar
 *   solicitar la longitud de la cadena)
 */
int parsearEntero(const char *arg, int *posicion, uint32_t *result, validadorEntero validador){
  /* Inicializar el procesamiento en el estado inicial */
  int estado = 0;

  /* Inicializar el entero a construir*/
  *result = 0;

  /* 
   * Ciclo infinito para consumir los caracteres
   * cada estado final esresponsable de retornar
   * con un valor adecuado
   */
  while(1){
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
            /* Construir la sección del número reconocido*/
            *result = *result * 10 + ((int)arg[*posicion] - 48);

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
            /* Construir la sección del número reconocido*/
            *result = *result * 10 + ((int)arg[*posicion] - 48);

            /* Mover el puntero para consumir el siguiente caracter*/
            (*posicion)++;
            break;
          case '\0':
            /* Retornar indicando que se concluyó bien el procesamiento*/ 
            return 0;
            break; 
          default:
            return 1;
            break; 
        }
        break;
    }
  }

  return 0;
}
