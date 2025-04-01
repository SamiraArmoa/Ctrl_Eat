#ifndef INGREDIENTES_H
#define INGREDIENTES_C

typedef struct{
	int id;
	char* nombre;
}Ingrediente;

int guardarIngredientes(int id, char* nombre);
#endif
