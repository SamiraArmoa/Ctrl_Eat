#include "ingredientes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"ingredientes.h"
#include "../../data/db/db.h"

#define MAX_LENGTH 100

int crearIngrediente() {
	char nombre[MAX_LENGTH];

	printf("Introduce el nombre del ingrediente: ");
	fflush(stdin);
	fgets(nombre, MAX_LENGTH, stdin);
	nombre[strcspn(nombre, "\n")] = '\0';

	insertarIngredientes(nombre);
	return 0;
}

int verIngredientes() {
	int rc = imprimirIngredientes();
	return rc;
}

int eliminarIngredientes() {
	int id_in = 0;
	verIngredientes();

	printf("Inserta el id del ingrediente que quieres eliminar: ");
	fflush(stdin);
	scanf("%i", &id_in);

	int confirmacion = 0;
	//	printf("\nELIMINAR PRODUCTO\n");
	printf("¿Quieres eliminar este producto?\n");
	printf("1. SI\n");
	printf("2. NO\n");
	printf("Opcion: ");
	scanf("%d", &confirmacion);

	if (confirmacion != 1) {
		printf("Eliminacion cancelada.\n");
		return 0; // Salimos sin hacer nada
	}

	deleteIngredientes(id_in);
	return 0;
}
