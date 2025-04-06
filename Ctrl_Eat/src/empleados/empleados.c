#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "empleados.h"
#include "../../lib/sqlite3/sqlite3.h"
#include "../../data/db/db.h"

int obtenerUltimoIdEmpleados(int *id) {
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
	char *sql = "SELECT MAX(ID_EM) FROM Empleado";
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
int crearEmpleado() {
	int id;
	char *nombre;
	char *cargo;
	char *cuentaBancaria;
	char nom[50];
	char car[30];
	char cuenBan[35];

	obtenerUltimoIdEmpleados(&id);
	id++;
	printf("CREAR EMPLEADO\n");
	printf("Nombre: ");
	fflush(stdin);
	fgets(nom, 50, stdin);
	nom[strcspn(nom, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	nombre = malloc((strlen(nom) + 1) * sizeof(char));
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
	cargo = malloc((strlen(car) + 1) * sizeof(char));
	if (nombre == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(cargo, car);  // Copiar la cadena le�da en nombre

	printf("\nCuenta Bancaria: ");
	fgets(cuenBan, 35, stdin);
	cuenBan[strcspn(cuenBan, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	cuentaBancaria = malloc((strlen(cuenBan) + 1) * sizeof(char));
	if (cuentaBancaria == NULL) {
		printf("Error al asignar memoria para el tipo.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(cuentaBancaria, cuenBan);  // Copiar la cadena le�da en nombre

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found = sqlite3_open(DB_PATH, &db);

	if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char *insert_sql =
			"INSERT INTO Empleado(ID_EM, NOMBRE,CARGO,CUENTA_BAN,ID_RES) VALUES (?, ?, ?, ?,1)";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id);
	sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, cargo, strlen(cargo), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, cuentaBancaria, strlen(cuentaBancaria),
	SQLITE_STATIC);

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
int eliminarEmpleado() {
	int id_em = 0;
	int rc;
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

	sqlite3 *db;
	sqlite3_stmt *stmt;
	rc = sqlite3_open(DB_PATH, &db);

	printf("Empleado: %i\n", id_em);

	if (rc != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char *insert_sql = "DELETE FROM Empleado WHERE ID_EM = ?";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	// Vincular el par�metro de la consulta (nombre de comando) al marcador de posici�n `?`
	rc = sqlite3_bind_int(stmt, 1, id_em); // 1 es el �ndice del primer `?`
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
int verEmpleados() {
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
	char *sql = "SELECT ID_EM,NOMBRE,CARGO,CUENTA_BAN FROM Empleado";
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
		int id_em = (int) sqlite3_column_int(stmt, 0);
		char *nombre = (char*) sqlite3_column_text(stmt, 1);
		char *cargo = (char*) sqlite3_column_text(stmt, 2);
		char *cuentaBancaria = (char*) sqlite3_column_text(stmt, 3);

		printf("%i. Nombre:%s Cargo:%s Cuenta bancaria:%s \n", id_em, nombre,
				cargo, cuentaBancaria);
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
int actualizarEmpleado() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;
	int id_em = 0;
	char *nombre;
	char *cargo;
	char *cuentaBancaria;
	char nom[100];
	char car[25];
	char cuenBan[75];

	verEmpleados();
	printf("Inserta el id del empleado que quieres actualizar: ");
	fflush(stdin);
	scanf("%i", &id_em);

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

	printf("Cargo: ");
	fflush(stdin);
	fgets(car, 25, stdin);
	car[strcspn(car, "\n")] = '\0';  // Fix: changed from cargo to car
	// Asignar memoria din�mica para el cargo seg�n la longitud
	cargo = malloc((strlen(car) + 1) * sizeof(char));
	if (cargo == NULL) {
		free(nombre);  // Free previously allocated memory
		printf("Error al asignar memoria para el cargo.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(cargo, car);  // Copiar la cadena le�da en cargo

	printf("Cuenta bancaria: ");
	fflush(stdin);
	fgets(cuenBan, 75, stdin);
	cuenBan[strcspn(cuenBan, "\n")] = '\0';  // Fix: changed from cuentaBancaria to cuenBan
	// Asignar memoria din�mica para la cuenta bancaria seg�n la longitud
	cuentaBancaria = malloc((strlen(cuenBan) + 1) * sizeof(char));
	if (cuentaBancaria == NULL) {
		free(nombre);  // Free previously allocated memory
		free(cargo);   // Free previously allocated memory
		printf("Error al asignar memoria para la cuenta bancaria.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(cuentaBancaria, cuenBan); // Copiar la cadena le�da en cuenta bancaria

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
			"UPDATE Empleado SET NOMBRE = ?, CARGO = ?, CUENTA_BAN = ? WHERE ID_EM = ?";
	sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	rc += sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	rc += sqlite3_bind_text(stmt, 2, cargo, strlen(cargo), SQLITE_STATIC);
	rc += sqlite3_bind_text(stmt, 3, cuentaBancaria, strlen(cuentaBancaria),
			SQLITE_STATIC);
	rc += sqlite3_bind_int(stmt, 4, id_em);

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
