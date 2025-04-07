#ifndef INGREDIENTES_H
#define INGREDIENTES_H


typedef struct{
	int id;
	char* nombre;
}Ingrediente;

int crearIngrediente();

int eliminarIngredientes(int id);

int verIngredientes() ;

#endif
