#include "ingredientes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"ingredientes.h"
#include "../../lib/sqlite3/sqlite3.h"
#include "../../data/db/db.h"

#define MAX_LENGTH 100

int crearIngrediente() {
	char nombre[MAX_LENGTH];
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	printf("Introduce el nombre del ingrediente: ");
	fflush(stdin);
	fgets(nombre, MAX_LENGTH, stdin);
	nombre[strcspn(nombre, "\n")] = '\0';

	rc = sqlite3_open(DB_PATH, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		return rc;
	}

	const char *sql = "INSERT INTO Ingrediente (NOMBRE) VALUES (?);";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		fprintf(stderr, "Error al insertar ingrediente: %s\n",
				sqlite3_errmsg(db));
	} else {
		printf("Ingrediente creado correctamente.\n");
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return SQLITE_OK;
}

int verIngredientes() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	rc = sqlite3_open(DB_PATH, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		return rc;
	}

	const char *sql = "SELECT ID_IN, NOMBRE FROM Ingrediente;";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	printf("Lista de ingredientes:\n");
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		const char *nombre = (const char*) sqlite3_column_text(stmt, 1);
		printf("ID: %d | Nombre: %s\n", id, nombre);
	}

	if (rc != SQLITE_DONE) {
		fprintf(stderr, "Error al obtener ingredientes: %s\n",
				sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return SQLITE_OK;
}

int eliminarIngredientes() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int id_in = 0;
	int rc;

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

	rc = sqlite3_open(DB_PATH, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		return rc;
	}

	const char *sql = "DELETE FROM Ingrediente WHERE ID_IN = ?;";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	sqlite3_bind_int(stmt, 1, id_in);

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		fprintf(stderr, "Error al eliminar ingrediente: %s\n",
				sqlite3_errmsg(db));
	} else {
		printf("Ingrediente eliminado correctamente.\n");
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return SQLITE_OK;
}
