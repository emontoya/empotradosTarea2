#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "tarea2Utils.h" 


static const char *errorArgumentos = "Formatos aceptados son los siguientes:\n\t1-> num nbits\n\t2-> num/nbits\nDonde:\n\t0 < num < 4294967296\n\t0 < nbits < 32\nNOTA:\n\tNo se permiten espacios al comienzo o final de cada\n\tnúmero ni tampoco ceros al inicio de estos\n";

/*VALIDACION PROGRAMA 1*/

void validProgram1(int n){
	if (n==1|| n>2){
	
	fprintf(stderr,"Error: Argumento invalido\n");
	exit(1);
	}

}


/*FIN VALIDACION PROGRAMA 1*/


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
 * Realizar la validación
 * - No se valida que el estado pasado sea uno correcto
 *   se asume que es controlado
 */
static int validarEntero(char actual, int posicion, int *estado, const char *limite, int longitud){
  int valor;

  /*
   * Verificar que no se haya exedido el máximo de dígitos
   * o que se esté en el máximo de ellos
   */
  if(posicion < longitud){
    /* Obtener el valor para la comparación*/
    valor = (int)actual - (int)limite[posicion];

    if(*estado == VAL_INICIO){
        /* Asignar el nuevo estado (No se valida la longitud 1)*/
        *estado = valor == 0 ? VAL_INICIO : valor > 0 ? VAL_MAYOR : VAL_MENOR;

        /* Validar que si es la última posición el número no sea mayor*/
        if (posicion == longitud && *estado ==VAL_MAYOR){
          *estado = VAL_ERROR;
        }
    }
  } else if(posicion == longitud){ /* Se está en el último dígito */
    /* Verificar que no se llegue al último dígito en estado VAL_MAYOR o
     * que estando en estado VAL_IGUAL el último dígito sea mayor*/
    if ((*estado == VAL_INICIO && ((int)actual - (int)limite[posicion]) > 0) || (*estado == VAL_MAYOR)){
      *estado = VAL_ERROR;
    }
  } else {
    *estado = VAL_ERROR;
  }

  return *estado;
}

/*
 * Asume que el entero es menor o igual a 255.
 * No se hacen validaciones adicionales porque se
 * asume que los parámetros están debidamente
 * inicializados y en la posición correcta.
 * (Esta es una función de uso interno y por lo
 * tanto sus parámetros son controlados)
 */
static void ConvertirAString(uint32_t numero, char * result, int *pos){
  uint32_t digito;    // 255/100
  uint32_t potencia = 100;
  int primero = 1;

  if (numero == 0){
    result[(*pos)++] = (char)(48);
  }
  else{
    while(numero > 0){
      digito = numero / potencia;
      
      if (!primero || digito > 0){
        result[(*pos)++] = (char)(digito + 48);
        primero = 0;
      }
      
      numero = numero % potencia;
      potencia /= 10;
    }
  }
}

/*
 * Convierte un entero de 32 bits a un string en formato
 * IPv4.
 * El usuario de esta función es el responsable de liberar
 * la memoria reservada para almacenar el string; 
 */
char * EnteroToIPv4(uint32_t entero){
  char *result;

  /* Reservar la memoria para almacenar el string*/
  if ((result = malloc(sizeof(char) * 16)) == NULL){
    terminarConMensaje("No hay espacio para almacenar el string");
  }

  int pos = 0;

  ConvertirAString((entero >> 24) & 0x000000FF, result, &pos);
  result[pos++] = '.';
  ConvertirAString((entero >> 16) & 0x000000FF, result, &pos);
  result[pos++] = '.';
  ConvertirAString((entero >> 8) & 0x000000FF, result, &pos);
  result[pos++] = '.';
  ConvertirAString(entero & 0x000000FF, result, &pos);

  /* Agregar el caracter que indica el final de la cadena*/
  result[pos] = '\0';

  return result;
}

/* Definir las constantes ligadas a la validación del entero*/
static const char *MAX_32 = "4294967295";
static const int MAX_32_LENGTH = 9; 
/*
 * Validador para un entero menor o igual a
 */
int validarEntero32SinSigno(char actual, int posicion, int *estado){
  return validarEntero(actual, posicion, estado, MAX_32, MAX_32_LENGTH);
}

/* Definir las constantes ligadas a la validación de este entero*/
static const char *MAX_BITS = "31";
static const int MAX_BITS_LENGTH = 1; 
/*
 * Validador para un entero menor o igual a 31
 */
int validarEntero31Bits(char actual, int posicion, int *estado){
  return validarEntero(actual, posicion, estado, MAX_BITS, MAX_BITS_LENGTH);
}

/*
 * Hace el Parsing de un string sin signo comenzando en la posición (posicion)
 * retorna 0 si termina el parsing correctamente y 1 si ocurrió algún error.
 * La variable posición retorna la última posición procesada
 * - El método descarta reconocer un valor = 0
 * - Esta función no valida que se reciba una cadena nula, ni tampoco que
 *   la posición sea válida. (Esto se hace para evitar
 *   solicitar la longitud de la cadena)
 */
int parsearEntero(const char *arg, int *posicion, uint32_t *result, validadorEntero validador){
  /* Inicializar el iestado para el procesamiento */
  int estado = REC_INICIO;
  
  /* Inicializar el estado para la validación*/
  int vEstado = VAL_INICIO;

  /* Inicializar el entero a construir*/
  *result = 0;

  /* Guardar posición inicial del parsing */
  int inicio = *posicion;

  /* 
   * Ciclo infinito para consumir los caracteres
   * cada estado final esresponsable de retornar
   * con un valor adecuado
   */
  while(1){
    /* Discriminar el estado actual en el parsing*/
    switch (estado){
      /* Inicio del parsing de la cadena*/
      case REC_INICIO: 
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
            /* Validar el número reconocido hasta el momento */
            if(validador(arg[*posicion], *posicion - inicio, &vEstado) == VAL_ERROR){
              return 1;
            }

            /* Construir la sección del número reconocido*/
            *result = *result * 10 + ((int)arg[*posicion] - 48);

            /* 
             * Mover el puntero para consumir el siguiente caracter 
             * y pasar al estado REC_RECONOCIMIENTO
             */
            (*posicion)++;
            estado = REC_RECONOCIENDO;
            break;
          default:
            return 1;
            break;
        }
        break;
      /* Reconociendo el entero, después del primer dígito */
      case REC_RECONOCIENDO: 
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
            /* Validar el número reconocido hasta el momento */
            if(validador(arg[*posicion], *posicion - inicio, &vEstado) == VAL_ERROR){
              return 1;
            }

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
