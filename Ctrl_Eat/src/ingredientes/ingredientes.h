#ifndef INGREDIENTES_H
#define INGREDIENTES_C

typedef struct{
	int id;
	char* nombre;
}Ingrediente;

void crearIngrediente(Ingrediente ingredientes[], int *count);

void eliminarIngrediente(Ingrediente ingredientes[], int *count);

void actualizarIngrediente(Ingrediente ingredientes[], int count);

void listarIngredientes(Ingrediente ingredientes[], int count);

#endif
