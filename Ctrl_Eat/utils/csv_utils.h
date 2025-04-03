#ifndef CSV_UTILS_H
#define CSV_UTILS_H

int cargar_csvs();
int guardar_ingredientes(int id, char *nombre);
int guardar_productos(int id, char *nombre, char* tipo, float precio);
int guardar_restaurantes(char *id, char *nombre, char* ciudad);
int guardar_productoIngrediente(int id_pr, int id_in);

#endif
