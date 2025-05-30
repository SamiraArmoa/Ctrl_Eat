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
	char *tamanio=NULL;
	char *alergenos=NULL;

	printf("CREAR PRODUCTO\n");
	printf("Nombre: ");
	fflush(stdin);
	fgets(str, MAX_LENGTH, stdin);

	str[strcspn(str, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	nombre = malloc((strlen(str) + 1) * sizeof(char));
	if (nombre == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(nombre, str);  // Copiar la cadena le�da en nombre

	printf("\nPrecio: ");
	fgets(str, MAX_LENGTH, stdin);
	sscanf(str, "%f", &precio);

	printf("\nTipo(Bebida o Plato): ");
	fgets(str, MAX_LENGTH, stdin);
	str[strcspn(str, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	tipo = malloc((strlen(str) + 1) * sizeof(char));
	if (tipo == NULL) {
		printf("Error al asignar memoria para el tipo.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(tipo, str);  // Copiar la cadena le�da en nombre


	// LÓGICA SEGÚN EL TIPO
	if (strcmp(tipo, "Bebida") == 0) {
		// TAMAÑO
		printf("\nTamanio: ");
		fflush(stdin);
		fgets(str, MAX_LENGTH, stdin);
		str[strcspn(str, "\n")] = '\0';

		tamanio = malloc((strlen(str) + 1) * sizeof(char));
		if (tamanio == NULL) {
			printf("Error al asignar memoria para el tamaño.\n");
			free(nombre); free(tipo);
			return -1;
		}
		strcpy(tamanio, str);

		// ALÉRGENOS = ""
		alergenos = malloc(1);
		strcpy(alergenos, "");
	}
	else if (strcmp(tipo, "Plato") == 0) {
		// ALÉRGENOS
		printf("\nAlergenos: ");
		fflush(stdin);
		fgets(str, MAX_LENGTH, stdin);
		str[strcspn(str, "\n")] = '\0';

		alergenos = malloc((strlen(str) + 1) * sizeof(char));
		if (alergenos == NULL) {
			printf("Error al asignar memoria para los alérgenos.\n");
			free(nombre); free(tipo);
			return -1;
		}
		strcpy(alergenos, str);

		// TAMAÑO = ""
		tamanio = malloc(1);
		strcpy(tamanio, "");
	}
	else {
		printf("Tipo inválido. Debe ser 'Bebida' o 'Plato'.\n");
		free(nombre); free(tipo);
		return -1;
	}

	precio = roundf(precio * 100) / 100.0f;
	printf("%s, %f, %s ", nombre, precio, tipo);
	int id = 0;
	obtenerUltimoIdProductos(&id);
	id++;
	printf("ID_Obtenido = %i", id);
	guardar_productos(id, nombre, tipo, precio, tamanio,alergenos);
	asignarIngredientesProductos(id);

	free(nombre);
	free(tipo);
	free(tamanio);
	free(alergenos);
	return 0;
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
	printf("�Quieres eliminar este producto?\n");
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

	char *tamanio=NULL;
	char *alergenos=NULL;
	char tam[25];
	char ale[100];

	verProductos();

	printf("Inserta el id del producto que quieres actualizar: ");
	fflush(stdin);
	scanf("%i", &id_pr);

	printf("Nombre: ");
	fflush(stdin);
	fgets(nom, 100, stdin);
	nom[strcspn(nom, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	nombre = malloc((strlen(nom) + 1) * sizeof(char));
	if (nombre == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(nombre, nom);  // Copiar la cadena le�da en nombre

	printf("Precio: ");
	fflush(stdin);
	scanf("%f", &precio);

	// TIPO
	printf("Tipo (Bebida o Plato): ");
	fgets(tip, 25, stdin);
	tip[strcspn(tip, "\n")] = '\0';
	tipo = malloc((strlen(tip) + 1) * sizeof(char));
	if (tipo == NULL) {
		printf("Error al asignar memoria para el tipo.\n");
		free(nombre);
		return -1;
	}
	strcpy(tipo, tip);

	// Si es Bebida, pedir TAMAÑO
	if (strcmp(tipo, "Bebida") == 0) {
		printf("Tamaño: ");
		fgets(tam, 25, stdin);
		tam[strcspn(tam, "\n")] = '\0';
		tamanio = malloc((strlen(tam) + 1) * sizeof(char));
		if (tamanio == NULL) {
			printf("Error al asignar memoria para el tamaño.\n");
			free(nombre);
			free(tipo);
			return -1;
		}
		strcpy(tamanio, tam);

		// Si es Bebida, alergenos se guarda como cadena vacía
		alergenos = malloc(1);
		strcpy(alergenos, "");
	}
	// Si es Plato, pedir ALÉRGENOS
	else if (strcmp(tipo, "Plato") == 0) {
		printf("Alérgenos: ");
		fgets(ale, 100, stdin);
		ale[strcspn(ale, "\n")] = '\0';
		alergenos = malloc((strlen(ale) + 1) * sizeof(char));
		if (alergenos == NULL) {
			printf("Error al asignar memoria para los alérgenos.\n");
			free(nombre);
			free(tipo);
			return -1;
		}
		strcpy(alergenos, ale);

		// Si es Plato, tamanio se guarda como cadena vacía
		tamanio = malloc(1);
		strcpy(tamanio, "");
	}
	else {
		printf("Tipo inválido. Debe ser 'Bebida' o 'Plato'.\n");
		free(nombre);
		free(tipo);
		return -1;
	}
	updateProductos(id_pr, nombre, precio, tipo,tamanio,alergenos);
	return 0;
}
