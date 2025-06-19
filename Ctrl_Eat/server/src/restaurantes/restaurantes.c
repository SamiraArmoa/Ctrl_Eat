#include "restaurantes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../data/db/db.h"
#include "../../config.h"

int actualizarRestaurante() {
	int id;
	char *nombre;
	char *ciudad;
	char nom[100];
	char ciu[100];

	verRestaurantes();
	printf("Ingrese el ID del restaurante a actualizar: ");
	fflush(stdin);
	scanf("%d", &id);

	printf("Ingrese el nuevo nombre del restaurante: ");
	fflush(stdin);
	fgets(nom, 100, stdin);
	nom[strcspn(nom, "\n")] = '\0';
	nombre = (char *)malloc((strlen(nom) + 1) * sizeof(char));
	if (nombre == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(nombre, nom);

	printf("Ingrese la nueva ciudad del restaurante: ");
	fflush(stdin);
	fgets(ciu, 100, stdin);
	ciu[strcspn(ciu, "\n")] = '\0';
	ciudad = (char *)malloc((strlen(ciu) + 1) * sizeof(char));
	if (nombre == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(ciudad, ciu);

	updateRestaurante(id, nombre, ciudad, CLIENT_DB_PATH);
	return 0;
}

int crearRestaurante() {
	char *nombre;
	char *ciudad;
	char nom[100];
	char ciu[100];

	printf("Ingrese el nuevo nombre del restaurante: ");
	fflush(stdin);
	fgets(nom, 100, stdin);
	nom[strcspn(nom, "\n")] = '\0';
	nombre = (char *)malloc((strlen(nom) + 1) * sizeof(char));
	if (nombre == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(nombre, nom);

	printf("Ingrese la nueva ciudad del restaurante: ");
	fflush(stdin);
	fgets(ciu, 100, stdin);
	ciu[strcspn(ciu, "\n")] = '\0';
	ciudad = (char *)malloc((strlen(ciu) + 1) * sizeof(char));
	if (nombre == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(ciudad, ciu);
	insertarRestaurante(nombre,ciudad, CLIENT_DB_PATH);

	return 0;
}

int verRestaurantes() {
	imprimirRestaurante(CLIENT_DB_PATH);
	return 0;
}
