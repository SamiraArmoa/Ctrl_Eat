#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "../../lib/sqlite3/sqlite3.h"
#include "../../data/db/db.h"
#define MAX_LENGTH 100

int obtenerUltimoIdClientes(int *id) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(DB_PATH, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	char *sql = "SELECT MAX(ID_CL) FROM Cliente";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Ejecutar la consulta y procesar los resultados
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		// Obtener los valores de cada columna (con comprobaci�n de NULL)
		*id = sqlite3_column_int(stmt, 0);
		printf("Id calculado: %i\n", *id);
	} else {
		printf("El comando: %s no existe\n");
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return SQLITE_OK;
}

// Crear un nuevo empleado
int crearCliente() {
	char str[MAX_LENGTH];
	int id;
	char *nombre;
	char *email;
	int telefono;
	char *contrasena;
	char nom[100];
	char em[100];
	char con[100];

	obtenerUltimoIdClientes(&id);
	id++;
	printf("CREAR CLIENTE\n");
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

	printf("Email: ");
	fflush(stdin);
	fgets(em, 100, stdin);
	nom[strcspn(em, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	email = malloc((strlen(em) + 1) * sizeof(char));
	if (email == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(email, em);  // Copiar la cadena le�da en nombre

	printf("Telefono: ");
	fflush(stdin);
	fgets(str, MAX_LENGTH, stdin);
	sscanf(str, "%i", &telefono);

	printf("\nContrasena: ");
	fgets(con, 100, stdin);
	con[strcspn(con, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	contrasena = malloc((strlen(con) + 1) * sizeof(char));
	if (contrasena == NULL) {
		printf("Error al asignar memoria para el tipo.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(contrasena, con);  // Copiar la cadena le�da en nombre

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found = sqlite3_open(DB_PATH, &db);

	if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char *insert_sql =
			"INSERT INTO Cliente(ID_CL, NOMBRE,EMAIL,TLF,CONTRASENA) VALUES (?, ?, ?, ?, ?)";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id);
	sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, email, strlen(email), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, telefono);
	sqlite3_bind_text(stmt, 5, contrasena,strlen(contrasena), SQLITE_STATIC);

	int result = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	if (result != SQLITE_DONE) {
		printf("Insert error: %s\n", sqlite3_errmsg(db));
	} else {
		printf("Insert successful\n");
	}

	sqlite3_close(db);
	fflush(stdout);
	return 0;
}

// Eliminar empleado por nombre
int eliminarCliente() {
	int id_cl = 0;
	int rc;
	imprimirClientes();
	printf("Inserta el id del cliente que quieres eliminar: ");
	scanf("%d", &id_cl);

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

	sqlite3 *db;
	sqlite3_stmt *stmt;
	rc = sqlite3_open(DB_PATH, &db);

	printf("Cliente: %i\n", id_cl);

	if (rc != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char *insert_sql = "DELETE FROM Cliente WHERE ID_CL = ?";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	// Vincular el par�metro de la consulta (nombre de comando) al marcador de posici�n `?`
	rc = sqlite3_bind_int(stmt, 1, id_cl); // 1 es el �ndice del primer `?`
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al vincular el par�metro: %s\n",
				sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return rc;
	}
	int result = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	if (result != SQLITE_DONE) {
		printf("Insert error: %s\n", sqlite3_errmsg(db));
	} else {
		printf("Insert successful\n");
	}
	sqlite3_close(db);
	return 0;
}

// Mostrar todos los empleados
int imprimirClientes() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(DB_PATH, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	char *sql = "SELECT ID_CL,NOMBRE,EMAIL,TLF, CONTRASENA FROM Cliente";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Ejecutar la consulta y procesar los resultados
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		// Obtener los valores de cada columna (con comprobaci�n de NULL)
		int id_cl = (int) sqlite3_column_int(stmt, 0);
		char *nombre = (char*) sqlite3_column_text(stmt, 1);
		char *email = (char*) sqlite3_column_text(stmt, 2);
		int telefono = (int) sqlite3_column_int(stmt, 3);
		char *contrasena = (char*) sqlite3_column_text(stmt, 4);

		printf("%i. Nombre:%s Email:%s Telefono:%i Contrasena:%s \n", id_cl, nombre,
				email,telefono, contrasena);
	}

	// Verificar si ocurri� alg�n error durante la consulta
	if (rc != SQLITE_DONE) {
		fprintf(stderr, "Error al ejecutar la consulta: %s\n",
				sqlite3_errmsg(db));
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	fflush(stdout);
	return SQLITE_OK;
}

// Actualizar por ID
int actualizarCliente() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;
	int id_cl = 0;
	char *nombre;
	char *email;
	int telefono;
	char *contrasena;
	char nom[100];
	char em[100];
	char con[100];

	imprimirClientes();
	printf("Inserta el id del empleado que quieres actualizar: ");
	fflush(stdin);
	scanf("%i", &id_cl);

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

	printf("Email: ");
	fflush(stdin);
	fgets(em, 25, stdin);
	em[strcspn(em, "\n")] = '\0';  // Fix: changed from cargo to car
	// Asignar memoria din�mica para el cargo seg�n la longitud
	email = malloc((strlen(em) + 1) * sizeof(char));
	if (email == NULL) {
		free(nombre);  // Free previously allocated memory
		printf("Error al asignar memoria para el cargo.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(email, em);  // Copiar la cadena le�da en cargo

	printf("Telefono: ");
	fflush(stdin);
	scanf("%i", &telefono);

	printf("Contrasena: ");
	fflush(stdin);
	fgets(con, 75, stdin);
	con[strcspn(con, "\n")] = '\0';  // Fix: changed from cuentaBancaria to cuenBan
	// Asignar memoria din�mica para la cuenta bancaria seg�n la longitud
	contrasena= malloc((strlen(con) + 1) * sizeof(char));
	if (contrasena == NULL) {
		free(nombre);  // Free previously allocated memory
		free(email); // Free previously allocated memory
		printf("Error al asignar memoria para la cuenta bancaria.\n");
		return -1;  // Error si no se pudo asignar memoria
	}

	strcpy(contrasena, con); // Copiar la cadena le�da en cuenta bancaria

	// Abrir la base de datos
	rc = sqlite3_open(DB_PATH, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	char *sql =
			"UPDATE CLIENTE SET NOMBRE = ?, EMAIL = ?, TLF = ?, CONTRASENA=? WHERE ID_CL = ?";
	sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	rc += sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	rc += sqlite3_bind_text(stmt, 2, email, strlen(email), SQLITE_STATIC);
	rc += sqlite3_bind_int(stmt, 4, telefono);
	rc += sqlite3_bind_text(stmt, 3, contrasena, strlen(contrasena),
			SQLITE_STATIC);
	rc += sqlite3_bind_int(stmt, 4, id_cl);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al vincular el par�metro: %s\n",
				sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return rc;
	}
	int result = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	if (result != SQLITE_DONE) {
		printf("Insert error: %s\n", sqlite3_errmsg(db));
	} else {
		printf("Insert successful\n");
	}
	sqlite3_close(db);
	return 0;
}
