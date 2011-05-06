#ifndef TAREA2UTILS_H
#define TAREA2UTILS_H

#include <stdint.h>

void imprimirArgumentosEsperadosP2();

void terminarConError(const char *err);

void terminarConMensaje(const char *err);

void mensajeValidacionEntrada(const char *msg);

int parsearEntero(const char *arg, int *posicion);
#endif
