#ifndef TAREA2UTILS_H
#define TAREA2UTILS_H

#include <stdint.h>

void validProgram1(int);

void imprimirArgumentosEsperadosP2();

void terminarConError(const char *err);

void terminarConMensaje(const char *err);

void mensajeValidacionEntrada(const char *msg);



/* Estados para la validación*/
#define VAL_INICIO 0
#define VAL_MENOR 1
#define VAL_MAYOR 2
#define VAL_ERROR 3
/*
 * Puntero a función empleado para la validación del entero
 * - Todo se hace con la idea de lograr hacer la validación
 * en la misma pasada del parsing. Se podría pensar en incluir
 * estos estados en la lógica general del parsing del entero
 * pero se tendría que manejar parámetros adicionales haciendo
 * menos legible el código.
 *
 * La idea general es sacar el autómata que valida los números
 * de la sección del autómata que reconoce los números.
 */
typedef int (*validadorEntero)(char actual, int posicion, int *estado);

int validarEntero32SinSigno(char actual, int posicion, int *estado);

int validarEntero31Bits(char actual, int posicion, int *estado);

/* Estados para el reconocimiento de los enteros */
#define REC_INICIO 0
#define REC_RECONOCIENDO 1

int parsearEntero(const char *arg, int *posicion, uint32_t *result, validadorEntero validador);

char * EnteroToIPv4(uint32_t entero);
#endif
