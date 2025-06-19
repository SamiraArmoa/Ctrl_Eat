#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "empleados.h"
#include "../restaurantes/restaurantes.h"
#include "../../data/db/db.h"
#include "../../config.h"

// Crear un nuevo empleado
int crearEmpleado() {
	int id;
	char *nombre;
	char *cargo;
	char *cuentaBancaria;
	int id_res;
	char nom[50];
	char car[30];
	char cuenBan[35];
	char id_res_str[3];

	obtenerUltimoIdEmpleados(&id, CLIENT_DB_PATH);
	id++;
	printf("CREAR EMPLEADO\n");
	printf("Nombre: ");
	fflush(stdin);
	fgets(nom, 50, stdin);
	nom[strcspn(nom, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	nombre = (char *)malloc((strlen(nom) + 1) * sizeof(char));
	if (nombre == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(nombre, nom);  // Copiar la cadena le�da en nombre

	printf("Cargo: ");
	fflush(stdin);
	fgets(car, 30, stdin);
	nom[strcspn(car, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	cargo = (char *)malloc((strlen(car) + 1) * sizeof(char));
	if (cargo == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(cargo, car);  // Copiar la cadena le�da en nombre

	printf("\nCuenta Bancaria: ");
	fgets(cuenBan, 35, stdin);
	cuenBan[strcspn(cuenBan, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	cuentaBancaria = (char *)malloc((strlen(cuenBan) + 1) * sizeof(char));
	if (cuentaBancaria == NULL) {
		printf("Error al asignar memoria para el tipo.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(cuentaBancaria, cuenBan);  // Copiar la cadena le�da en nombre
	fflush(stdout);

	verRestaurantes();
	printf("\nID Restaurante: ");
	fgets(id_res_str, 3, stdin);
	id_res_str[strcspn(id_res_str, "\n")] = '\0';
	id_res = atoi(id_res_str);
	fflush(stdout);

	int error = insertarEmpleado(nombre, cargo, cuenBan, id_res, CLIENT_DB_PATH);
	if (error != 0) {
		return error;
	}
	return 0;
}

// Eliminar empleado por nombre
int eliminarEmpleado() {
	int id_em = 0;
	verEmpleados();
	printf("Inserta el id del empleado que quieres eliminar: ");
	scanf("%d", &id_em);

	int confirmacion = 0;
	//	printf("\nELIMINAR EMPLEADO\n");
	printf("�Quieres eliminar este empleado?\n");
	printf("1. SI\n");
	printf("2. NO\n");
	printf("Opcion: ");
	scanf("%d", &confirmacion);

	if (confirmacion != 1) {
		printf("Eliminacion cancelada.\n");
		return 0; // Salimos sin hacer nada
	}

	printf("Empleado: %i\n", id_em);
	deleteEmpleado(id_em, CLIENT_DB_PATH);
	return 0;
}

// Mostrar todos los empleados
int verEmpleados() {
	int rc = imprimirEmpleados(CLIENT_DB_PATH);
	return rc;
}

// Actualizar por ID
int actualizarEmpleado() {
	int id_em = 0;
	char *nombre;
	char *cargo;
	char *cuentaBancaria;
	char nom[100];
	char car[25];
	char cuenBan[75];
	char id_res_str[3];
 	int id_res;

	verEmpleados();
	printf("Inserta el id del empleado que quieres actualizar: ");
	fflush(stdin);
	scanf("%i", &id_em);

	printf("Nombre: ");
	fflush(stdin);
	fgets(nom, 100, stdin);
	nom[strcspn(nom, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	nombre = (char *)malloc((strlen(nom) + 1) * sizeof(char));
	if (nombre == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(nombre, nom);  // Copiar la cadena le�da en nombre

	printf("Cargo: ");
	fflush(stdin);
	fgets(car, 25, stdin);
	car[strcspn(car, "\n")] = '\0';  // Fix: changed from cargo to car
	// Asignar memoria din�mica para el cargo seg�n la longitud
	cargo = (char *)malloc((strlen(car) + 1) * sizeof(char));
	if (cargo == NULL) {
		free(nombre);  // Free previously allocated memory
		printf("Error al asignar memoria para el cargo.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(cargo, car);  // Copiar la cadena le�da en cargo


	printf("Cuenta bancaria: ");
	fflush(stdin);
	fgets(cuenBan, 75, stdin);
	cuenBan[strcspn(cuenBan, "\n")] = '\0'; // Fix: changed from cuentaBancaria to cuenBan
	// Asignar memoria din�mica para la cuenta bancaria seg�n la longitud
	cuentaBancaria = (char *)malloc((strlen(cuenBan) + 1) * sizeof(char));
	if (cuentaBancaria == NULL) {
		free(nombre);  // Free previously allocated memory
		free(cargo);   // Free previously allocated memory
		printf("Error al asignar memoria para la cuenta bancaria.\n");
		fflush(stdin);
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(cuentaBancaria, cuenBan); // Copiar la cadena le�da en cuenta bancaria

	verRestaurantes();
	printf("\nID Restaurante: ");
	fgets(id_res_str, 3, stdin);
	id_res_str[strcspn(id_res_str, "\n")] = '\0';
	id_res = atoi(id_res_str);
	fflush(stdout);


	updateEmpleados(id_em, nombre, cargo, cuenBan, id_res, CLIENT_DB_PATH);
	fflush(stdin);
	return 0;
}
