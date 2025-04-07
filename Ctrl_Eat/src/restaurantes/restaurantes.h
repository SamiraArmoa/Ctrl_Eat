#ifndef RESTAURANTES_H_
#define RESTAURANTES_H_
#include <stdio.h>
#include <stdlib.h>
typedef struct {
   int id;
   char nombre[100];
   char ciudad[100];
} Restaurante;
int actualizarRestaurante();
int crearRestaurante();
#endif
