#ifndef TAREA2UTILS_H
#define TAREA2UTILS_H

#include <stdint.h>

void imprimirArgumentosEsperadosP2();

void terminarConError(const char *err);

void terminarConMensaje(const char *err);

void mensajeValidacionEntrada(const char *msg);


int convertirEntero(const char *arg, int inicio, int final, uint32_t *entero);

char * obtenerValor(const char *arg, int inicio, int final);
/*
 * Puntero a función enpleado para la validación del entero
 * - Todo se hace con la idea de lograr hacer la validación
 * en la misma pasada del parsing.
 *
 * La idea general es manejar 3 estados.
 * 0- inicial
 * 1- menor que el valor máximo, pero sin llegar al final
 */
typedef int (*validadorEntero)(char actual, int inicio, int posicion, int estado);

int validarEntero32SinSigno(char actual, int inicio, int posicion, int estado);

int validarEntero31Bits(char actual, int inicio, int posicion, int estado);

int parsearEntero(const char *arg, int *posicion, uint32_t *result, validadorEntero validador);
#endif
