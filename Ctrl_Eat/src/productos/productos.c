#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../data/db/db.h"
#include "../../utils/csv_utils.h"
#include "productos.h"
#include "../../lib/sqlite3/sqlite3.h"

#define MAX_LENGTH 100
int obtenerIngredientes() {
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
	char *sql = "SELECT ID_IN, NOMBRE FROM Ingrediente";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Ejecutar la consulta y procesar los resultados
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		// Obtener los valores de cada columna (con comprobación de NULL)
		int id_in = (int) sqlite3_column_int(stmt, 0);
		char *nombre = (char*) sqlite3_column_text(stmt, 1);

		printf("%i. %s\n", id_in, nombre);
	}

	// Verificar si ocurrió algún error durante la consulta
	if (rc != SQLITE_DONE) {
		fprintf(stderr, "Error al ejecutar la consulta: %s\n",
				sqlite3_errmsg(db));
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	printf("Introduce 0 para terminar de anadir ingredientes\n");
	return SQLITE_OK;
}
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
	char *sql = "SELECT ID_PR,NOMBRE,PRECIO,TIPO FROM Producto";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Ejecutar la consulta y procesar los resultados
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		// Obtener los valores de cada columna (con comprobación de NULL)
		int id_pr = (int) sqlite3_column_int(stmt, 0);
		char *nombre = (char*) sqlite3_column_text(stmt, 1);
		float precio = (float) sqlite3_column_double(stmt, 2);
		char *tipo = (char*) sqlite3_column_text(stmt, 3);

		printf("%i. Nombre:%s Precio:%.2f Tipo:%s\n", id_pr, nombre, precio,
				tipo);
	}

	// Verificar si ocurrió algún error durante la consulta
	if (rc != SQLITE_DONE) {
		fprintf(stderr, "Error al ejecutar la consulta: %s\n",
				sqlite3_errmsg(db));
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	printf("Introduce 0 para terminar de anadir ingredientes\n");
	return SQLITE_OK;
}
int eliminarProductos() {
	int id_pr = 0;
	int rc;
	verProductos();
	printf("Inserta el id del producto que quieres eliminar: ");
	scanf("%d", &id_pr);
	sqlite3 *db;
	sqlite3_stmt *stmt;
	rc = sqlite3_open(DB_PATH, &db);

	printf("Producto: %i\n", id_pr);

	if (rc != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char *insert_sql = "DELETE FROM Producto WHERE ID_PR = ?";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	// Vincular el parámetro de la consulta (nombre de comando) al marcador de posición `?`
	rc = sqlite3_bind_int(stmt, 1, id_pr); // 1 es el índice del primer `?`
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al vincular el parámetro: %s\n",
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
