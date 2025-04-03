#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../data/db/db.h"
#include "../../utils/csv_utils.h"

#define MAX_LENGTH 100
int crearProductos() {
	char str[MAX_LENGTH];
	float precio;
	char *nombre;
	char *tipo;

	printf("CREAR PRODUCTO\n");
	printf("Nombre: ");
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
	precio = round(precio * 100) / 100;
	printf("%s, %f, %s ", nombre, precio, tipo);
	int id = 0;
	obtenerUltimoIdProductos(&id);
	id++;
	printf("ID_Obtenido = %i", id);
	guardar_productos(id++, nombre, tipo, precio);
}

int main(int argc, char **argv) {
	crearProductos();
}

