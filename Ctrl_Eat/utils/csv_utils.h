#ifndef CSV_UTILS_H
#define CSV_UTILS_H

int guardar_ingredientes(int id, char *nombre);
int guardar_productos(int id, char *nombre, char *ingredientes, char* tipo, float precio );
int guardar_restaurantes(char *id, char *nombre, char* ciudad);

#endif
