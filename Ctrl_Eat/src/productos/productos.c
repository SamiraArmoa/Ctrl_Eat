#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../data/db/db.h"
#include "../../utils/csv_utils.h"
#include "productos.h"

#define MAX_LENGTH 100
int asignarIngredientesProductos(int id_pr) {
	int opcion = -1;
	while (opcion != 0) {
		obtenerIngredientes();
		printf("Introduce el id del ingrediente: ");
		scanf("%d", &opcion);
		if (opcion != 0) {
			guardar_productoIngrediente(id_pr, opcion);
		}
	}
}

int crearProductos() {
	char str[MAX_LENGTH];
	float precio;
	char *nombre;
	char *tipo;

	printf("CREAR PRODUCTO\n");
	printf("Nombre: ");
	fflush(stdin);
	fgets(str, MAX_LENGTH, stdin);

	str[strcspn(str, "\n")] = '\0';
	// Asignar memoria dinámica para el nombre según la longitud
	nombre = malloc((strlen(str) + 1) * sizeof(char));
	if (nombre == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(nombre, str);  // Copiar la cadena leída en nombre

	printf("\nPrecio: ");
	fgets(str, MAX_LENGTH, stdin);
	sscanf(str, "%f", &precio);

	printf("\nTipo: ");
	fgets(str, MAX_LENGTH, stdin);

	str[strcspn(str, "\n")] = '\0';
	// Asignar memoria dinámica para el nombre según la longitud
	tipo = malloc((strlen(str) + 1) * sizeof(char));
	if (tipo == NULL) {
		printf("Error al asignar memoria para el tipo.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(tipo, str);  // Copiar la cadena leída en nombre

	precio = roundf(precio * 100) / 100.0f;
	printf("%s, %f, %s ", nombre, precio, tipo);
	int id = 0;
	obtenerUltimoIdProductos(&id);
	id++;
	printf("ID_Obtenido = %i", id);
	guardar_productos(id, nombre, tipo, precio);
	asignarIngredientesProductos(id);

}

int verProductos() {
	int rc = imprimirProductos();
	return rc;
}

int eliminarProductos() {
	int id_pr = 0;
	verProductos();
	printf("Inserta el id del producto que quieres eliminar: ");
	fflush(stdin);
	scanf("%d", &id_pr);

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
	deleteProductos(id_pr);
	return 0;
}

int actualizarProductos() {
	int id_pr = 0;
	char *nombre;
	float precio;
	char *tipo;
	char nom[100];
	char tip[25];

	verProductos();

	printf("Inserta el id del producto que quieres actualizar: ");
	fflush(stdin);
	scanf("%i", &id_pr);

	printf("Nombre: ");
	fflush(stdin);
	fgets(nom, 100, stdin);
	nom[strcspn(nom, "\n")] = '\0';
	// Asignar memoria dinámica para el nombre según la longitud
	nombre = malloc((strlen(nom) + 1) * sizeof(char));
	if (nombre == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(nombre, nom);  // Copiar la cadena leída en nombre

	printf("Precio: ");
	fflush(stdin);
	scanf("%f", &precio);

	printf("Tipo: ");
	fflush(stdin);
	fgets(tip, 25, stdin);
	tip[strcspn(tip, "\n")] = '\0';
	// Asignar memoria dinámica para el tipo según la longitud
	tipo = malloc((strlen(tip) + 1) * sizeof(char));
	if (tipo == NULL) {
		printf("Error al asignar memoria para el tipo.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(tipo, tip);  // Copiar la cadena leída en tipo

	updateProductos(id_pr, nombre, precio, tipo);
	return 0;
}
