#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/sqlite3/sqlite3.h"
#include "db.h"
#include "../../config.h"

int obtenerUltimoIdEmpleados(int *id, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT MAX(ID_EM) FROM Empleado";
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
	} else {
		printf("El comando no existe\n");
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return SQLITE_OK;
}

int insertarEmpleado(char *nombre, char *cargo, char *cuentaBancaria,
		int id_res, const char *path) {
	int id;
	obtenerUltimoIdEmpleados(&id, path);
	id++;

	sqlite3 *db;
	sqlite3_stmt *stmt;

	int db_found = sqlite3_open(path, &db);
	if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	const char *insert_sql =
			"INSERT INTO Empleado(ID_EM, NOMBRE,CARGO,CUENTA_BAN,ID_RES) VALUES (?, ?, ?, ?, ?)";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id);
	sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, cargo, strlen(cargo), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, cuentaBancaria, strlen(cuentaBancaria),
	SQLITE_STATIC);
	sqlite3_bind_int(stmt, 5, id_res);

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

int deleteEmpleado(int id_em, const char *path) {
	int rc;
	sqlite3 *db;
	sqlite3_stmt *stmt;
	rc = sqlite3_open(path, &db);

	if (rc != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	const char *insert_sql = "DELETE FROM Empleado WHERE ID_EM = ?";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	// Vincular el par�metro de la consulta (nombre de comando) al marcador de posici�n `?`
	rc = sqlite3_bind_int(stmt, 1, id_em); // 1 es el �ndice del primer `?`
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al vincular el parametro: %s\n",
				sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return rc;
	}
	int result = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	if (result != SQLITE_DONE) {
		printf("Delete error: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	} else {
		printf("Delete successful\n");
	}
	sqlite3_close(db);
	return 0;
}

int imprimirEmpleados(const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT * FROM Empleado";
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
		char *id_res = (char*) sqlite3_column_text(stmt, 4);

		printf(
				"%i. Nombre: %s Cargo: %s Cuenta bancaria: %s ID del restaurante: %s\n",
				id_em, nombre, cargo, cuentaBancaria, id_res);
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

int updateEmpleados(int id_em, char *nombre, char *cargo, char *cuentaBancaria,
		int id_res, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql =
			"UPDATE Empleado SET NOMBRE = ?, CARGO = ?, CUENTA_BAN = ?, ID_RES = ? WHERE ID_EM = ?";
	sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	rc += sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	rc += sqlite3_bind_text(stmt, 2, cargo, strlen(cargo), SQLITE_STATIC);
	rc += sqlite3_bind_text(stmt, 3, cuentaBancaria, strlen(cuentaBancaria),
	SQLITE_STATIC);
	rc += sqlite3_bind_int(stmt, 4, id_res);
	rc += sqlite3_bind_int(stmt, 5, id_em);

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
		printf("Update error: %s\n", sqlite3_errmsg(db));
	} else {
		printf("Update successful\n");
	}
	sqlite3_close(db);
	return 0;
}

int guardar_productoIngrediente(int id_pr, int id_in, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found = sqlite3_open(path, &db);

	printf("Producto: %i Ingrediente: %i\n", id_pr, id_in);

	if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	const char *insert_sql =
			"INSERT INTO PRODUCTO_INGREDIENTE(id_pr, id_in) VALUES (?, ?)";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id_pr);
	sqlite3_bind_int(stmt, 2, id_in);

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

int guardar_productos(int id, char *nombre, char *tipo, float precio,
		char *tamanio, char *alergenos, const char *path) {
	printf("%s\n", tamanio);
	printf("%s\n", alergenos);

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found = sqlite3_open(path, &db);

	if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	const char *insert_sql =
			"INSERT INTO Producto(ID_PR, NOMBRE,PRECIO,TIPO, TAMANIO, ALERGENOS) VALUES (?, ?, ?, ?, ?, ?)";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id);
	sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
	sqlite3_bind_double(stmt, 3, precio);
	sqlite3_bind_text(stmt, 4, tipo, strlen(tipo), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, tamanio, strlen(tamanio), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 6, alergenos, strlen(alergenos), SQLITE_STATIC);

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

int obtenerUltimoIdProductos(int *id, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT MAX(ID_PR) FROM Producto";
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
		printf("Id calculado: %i", *id);
	} else {
		printf("El comando no existe\n");
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return SQLITE_OK;
}

int guardar_ingredientes(int id, char *nombre, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found = sqlite3_open(path, &db);

	if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	const char *insert_sql =
			"INSERT INTO Ingrediente(ID_IN, NOMBRE) VALUES (?, ?)";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id);
	sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);

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

int obtenerIngredientes(const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT ID_IN, NOMBRE FROM Ingrediente";
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
		int id_in = (int) sqlite3_column_int(stmt, 0);
		char *nombre = (char*) sqlite3_column_text(stmt, 1);

		printf("%i. %s\n", id_in, nombre);
	}

	// Verificar si ocurri� alg�n error durante la consulta
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

const char* imprimirProductos(const char *path) {
	char *result = (char*) malloc(8000 * sizeof(char));

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return "";
	}

	// Preparar la consulta SQL
	const char *sql =
			"SELECT ID_PR,NOMBRE,PRECIO,TIPO,TAMANIO,ALERGENOS FROM Producto";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return "";
	}

	// Ejecutar la consulta y procesar los resultados
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		// Obtener los valores de cada columna (con comprobaci�n de NULL)
		int id_pr = (int) sqlite3_column_int(stmt, 0);
		char *nombre = (char*) sqlite3_column_text(stmt, 1);
		float precio = (float) sqlite3_column_double(stmt, 2);
		char *tipo = (char*) sqlite3_column_text(stmt, 3);
		char *tamanio = (char*) sqlite3_column_text(stmt, 4);
		char *alergenos = (char*) sqlite3_column_text(stmt, 5);

		char buffer[256];
		sprintf(buffer,
				"%i. Nombre:%s Precio:%.2f Tipo:%s Tamanio:%s Alergenos:%s\n",
				id_pr, nombre, precio, tipo, tamanio, alergenos);

		printf("%s", buffer);
		strcat(result, buffer);
	}

	// Verificar si ocurri� alg�n error durante la consulta
	if (rc != SQLITE_DONE) {
		fprintf(stderr, "Error al ejecutar la consulta: %s\n",
				sqlite3_errmsg(db));
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	printf("Introduce 0 para terminar de anadir ingredientes\n");
	fflush(stdout);
	return result;
}

int deleteProductos(int id_pr, const char *path) {
	int rc;
	sqlite3 *db;
	sqlite3_stmt *stmt;
	rc = sqlite3_open(path, &db);

	printf("Producto: %i\n", id_pr);

	if (rc != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	const char *insert_sql = "DELETE FROM Producto WHERE ID_PR = ?";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	// Vincular el parametro de la consulta (nombre de comando) al marcador de posici�n `?`
	rc = sqlite3_bind_int(stmt, 1, id_pr); // 1 es el indice del primer `?`
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al vincular el parametro: %s\n",
				sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return rc;
	}
	int result = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	if (result != SQLITE_DONE) {
		printf("Delete error: %s\n", sqlite3_errmsg(db));
	} else {
		printf("Delete successful\n");
	}

	sqlite3_stmt *stmt2;
	const char *insert_sql2 = "DELETE FROM PRODUCTO_INGREDIENTE WHERE id_pr = ?";
	sqlite3_prepare_v2(db, insert_sql2, strlen(insert_sql2) + 1, &stmt2, NULL);
	// Vincular el parametro de la consulta (nombre de comando) al marcador de posici�n `?`
	rc = sqlite3_bind_int(stmt2, 1, id_pr); // 1 es el indice del primer `?`
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al vincular el parametro: %s\n",
				sqlite3_errmsg(db));
		sqlite3_finalize(stmt2);
		sqlite3_close(db);
		return rc;
	}
	result = sqlite3_step(stmt2);
	sqlite3_finalize(stmt2);

	if (result != SQLITE_DONE) {
		printf("Delete error: %s\n", sqlite3_errmsg(db));
	} else {
		printf("Delete successful\n");
	}

	sqlite3_close(db);
	return 0;
}

int updateProductos(int id_pr, char *nombre, float precio, char *tipo,
		char *tamanio, char *alergenos, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql =
			"UPDATE Producto SET NOMBRE = ?, PRECIO = ?, TIPO = ?, TAMANIO=?, ALERGENOS=? WHERE ID_PR = ?";
	sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	rc += sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	rc += sqlite3_bind_double(stmt, 2, precio);
	rc += sqlite3_bind_text(stmt, 3, tipo, strlen(tipo), SQLITE_STATIC);
	rc += sqlite3_bind_text(stmt, 4, tamanio, strlen(tamanio), SQLITE_STATIC);
	rc += sqlite3_bind_text(stmt, 5, alergenos, strlen(alergenos),
	SQLITE_STATIC);
	rc += sqlite3_bind_int(stmt, 6, id_pr);

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
		printf("Update error: %s\n", sqlite3_errmsg(db));
	} else {
		printf("Update successful\n");
	}
	sqlite3_close(db);
	return 0;
}

int obtenerUltimoIdClientes(int *id, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT MAX(ID_CL) FROM Cliente";
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
		printf("El comando no existe\n");
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return SQLITE_OK;
}

int insertarClientes(char *nombre, char *email, int telefono, char *contrasena,
		const char *path) {
	int id;
	obtenerUltimoIdClientes(&id, path);
	id++;

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc = sqlite3_open(path, &db);

	if (rc != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	const char *insert_sql =
			"INSERT INTO Cliente(ID_CL, NOMBRE,EMAIL,TLF,CONTRASENA) VALUES (?, ?, ?, ?, ?)";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id);
	sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, email, strlen(email), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, telefono);
	sqlite3_bind_text(stmt, 5, contrasena, strlen(contrasena), SQLITE_STATIC);

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

int deleteClientes(int id_cl, const char *path) {
	int rc;
	sqlite3 *db;
	sqlite3_stmt *stmt;
	rc = sqlite3_open(path, &db);

	printf("Cliente: %i\n", id_cl);

	if (rc != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	const char *insert_sql = "DELETE FROM Cliente WHERE ID_CL = ?";
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
		printf("Delete error: %s\n", sqlite3_errmsg(db));
	} else {
		printf("Delete successful\n");
	}
	sqlite3_close(db);
	return 0;
}

int verClientes(const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT ID_CL,NOMBRE,EMAIL,TLF, CONTRASENA FROM Cliente";
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

		printf("%i. Nombre:%s Email:%s Telefono:%i Contrasena:%s \n", id_cl,
				nombre, email, telefono, contrasena);
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

int updateClientes(int id_cl, char *nombre, char *email, int telefono,
		char *contrasena, const char *path) {
	printf("%d,  %s, %s, %d, %s\n", id_cl, nombre, email, telefono, contrasena);
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql =
			"UPDATE CLIENTE SET NOMBRE = ?, EMAIL = ?, TLF = ?, CONTRASENA=? WHERE ID_CL = ?";
	sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	rc += sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	rc += sqlite3_bind_text(stmt, 2, email, strlen(email), SQLITE_STATIC);
	rc += sqlite3_bind_int(stmt, 3, telefono);
	rc += sqlite3_bind_text(stmt, 4, contrasena, strlen(contrasena),
	SQLITE_STATIC);
	rc += sqlite3_bind_int(stmt, 5, id_cl);

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
		printf("Update error: %s\n", sqlite3_errmsg(db));
	} else {
		printf("Update successful\n");
	}
	sqlite3_close(db);
	return 0;
}

int obtenerIDCliente(char *nombre, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;
	int id;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT ID_CL FROM Cliente WHERE NOMBRE = ?";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Vincular el nombre del cliente a la consulta
	sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);

	// Ejecutar la consulta y obtener el ID
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		id = sqlite3_column_int(stmt, 0);
	} else {
		printf("El client '%s' no existe.\n", nombre);
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return id;
}

int insertarIngredientes(char *nombre, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
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

int imprimirIngredientes(const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	rc = sqlite3_open(path, &db);
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

int deleteIngredientes(int id_in, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	rc = sqlite3_open(path, &db);
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

int guardar_restaurantes(char *id, char *nombre, char *ciudad, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found = sqlite3_open(path, &db);

	if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	const char *insert_sql =
			"INSERT INTO Restaurante(ID_RES, NOMBRE, CIUDAD) VALUES (?, ?, ?)";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, id, strlen(id), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, ciudad, strlen(ciudad), SQLITE_STATIC);

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

int obtenerUltimoIdRestaurante(int *id, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT MAX(ID_RES) FROM Restaurante";
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
	} else {
		printf("El comando no existe\n");
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return SQLITE_OK;
}

int updateRestaurante(int id, char *nombre, char *ciudad, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;
	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL para actualizar el restaurante
	const char *sql =
			"UPDATE Restaurante SET NOMBRE = ?, CIUDAD = ? WHERE ID_RES = ?";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}
	// Bind the values to the SQL statement
	sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, ciudad, strlen(ciudad), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 3, id);
	// Ejecutar la consulta
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		fprintf(stderr, "Error al ejecutar la consulta: %s\n",
				sqlite3_errmsg(db));
	} else {
		printf("Restaurante actualizado exitosamente\n");
	}
	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return SQLITE_OK;
}

int insertarRestaurante(char *nombre, char *ciudad, const char *path) {
	int id;
	obtenerUltimoIdRestaurante(&id, path);
	id++;

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL para insertar un nuevo restaurante
	const char *sql =
			"INSERT INTO Restaurante (ID_RES,NOMBRE, CIUDAD) VALUES (?, ?, ?)";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}
	// Bind the values to the SQL statement
	sqlite3_bind_int(stmt, 1, id);
	sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, ciudad, strlen(ciudad), SQLITE_STATIC);
	// Ejecutar la consulta
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		fprintf(stderr, "Error al ejecutar la consulta: %s\n",
				sqlite3_errmsg(db));
	} else {
		printf("Restaurante creado exitosamente\n");
	}
	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return SQLITE_OK;
}

const char* imprimirRestaurante(const char *path) {
	char *result = (char*) malloc(8000 * sizeof(char));

	if (result == NULL) {
		fprintf(stderr, "Error asignando memoria\n");
		return "";
	}

	result[0] = '\0';

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return "";
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT ID_RES,NOMBRE,CIUDAD FROM Restaurante";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return "";
	}
	// Ejecutar la consulta y procesar los resultados
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		// Obtener los valores de cada columna (con comprobaci�n de NULL)
		int id_res = (int) sqlite3_column_int(stmt, 0);
		char *nombre = (char*) sqlite3_column_text(stmt, 1);
		char *ciudad = (char*) sqlite3_column_text(stmt, 2);

		char buffer[300];
		sprintf(buffer, "%i. Nombre:%s Ciudad:%s\n", id_res, nombre, ciudad);

		printf("%s", buffer);
		strcat(result, buffer);
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
	return result;
}

int obtenerIDRestaurante(char *nombre, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;
	int id;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT ID_RES FROM Restaurante WHERE NOMBRE = ?";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Vincular el nombre del restaurante a la consulta
	sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);

	// Ejecutar la consulta y obtener el ID
	if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		id = sqlite3_column_int(stmt, 0);
	} else {
		printf("El restaurante '%s' no existe.\n", nombre);
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return id;
}

int obtenerProductos(const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql =
			"SELECT ID_PR, NOMBRE,PRECIO,TIPO,TAMANIO,ALERGENOS FROM Producto";
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
		int id_pr = (int) sqlite3_column_int(stmt, 0);
		char *nombre = (char*) sqlite3_column_text(stmt, 1);
		float precio = (int) sqlite3_column_int(stmt, 2);
		char *tipo = (char*) sqlite3_column_text(stmt, 3);
		char *tamanio = (char*) sqlite3_column_text(stmt, 4);
		char *alergenos = (char*) sqlite3_column_text(stmt, 5);

		printf("%i.%s.%f.%s.%s.%s\n", id_pr, nombre, precio, tipo, tamanio,
				alergenos);
	}

	// Verificar si ocurri� alg�n error durante la consulta
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

int guardarPedidos(int domic, int id_cl, int id_res, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL para insertar un nuevo pedido
	const char *sql =
			"INSERT INTO Pedido (DOMICILIO, ID_CL, ID_RES) VALUES (?, ?, ?)";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Convertir domic (0 o 1) a cadena
	const char *domic_str = domic ? "Si" : "No";

	// Bind de los valores a la consulta
	sqlite3_bind_text(stmt, 1, domic_str, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, id_cl);
	sqlite3_bind_int(stmt, 3, id_res);

	// Ejecutar la consulta
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		fprintf(stderr, "Error al ejecutar la consulta: %s\n",
				sqlite3_errmsg(db));
	} else {
		printf("Pedido creado exitosamente\n");
	}

	// Finalizar y cerrar
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return SQLITE_OK;
}

int guardar_productoPedido(int id_ped, int id_pr, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found = sqlite3_open(path, &db);

	if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	const char *insert_sql =
			"INSERT INTO PRODUCTO_PEDIDO(id_ped, id_producto) VALUES (?, ?)";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id_ped);
	sqlite3_bind_int(stmt, 2, id_pr);

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

int obtenerUltimoIdPedido(int *id, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT MAX(ID_PED) FROM Pedido";
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
		printf("Id calculado: %i", *id);
	} else {
		printf("El comando no existe\n");
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return SQLITE_OK;
}

int getPedidos(const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT ID_PED, DOMICILIO, ID_CL, ID_RES FROM Pedido";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Ejecutar la consulta y procesar los resultados
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		int id_ped = sqlite3_column_int(stmt, 0);
		const unsigned char *domic = sqlite3_column_text(stmt, 1);
		int id_cl = sqlite3_column_int(stmt, 2);
		int id_res = sqlite3_column_int(stmt, 3);

		printf(
				"ID Pedido: %d\nDomicilio: %s\nID Cliente: %d\nID Restaurante: %d\n\n",
				id_ped, domic, id_cl, id_res);
	}

	// Verificar si ocurrió algún error durante la consulta
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

const char* historialPedidosUsuario(int id_cl, const char *path) {
	char *result = (char*) malloc(8000 * sizeof(char));

	if (result == NULL) {
		fprintf(stderr, "Error asignando memoria\n");
		return "";
	}

	result[0] = '\0';

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return "";
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT ID_PED,domicilio,ID_RES FROM Pedido where ID_CL = ?";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id_cl);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return "";
	}
	// Ejecutar la consulta y procesar los resultados
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		// Obtener los valores de cada columna (con comprobaci�n de NULL)
		int id_ped = (int) sqlite3_column_int(stmt, 0);
		char *domicilio = (char*) sqlite3_column_text(stmt, 1);
		int id_res = (int) sqlite3_column_int(stmt, 2);

		char buffer[300];
		sprintf(buffer, "%i;%s;%i\n", id_ped, domicilio, id_res);

		printf("%s", buffer);
		strcat(result, buffer);
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
	return result;
}

const char* obtenerProductosPedido(int id_ped, const char *path) {
	char *result = (char*) malloc(8000 * sizeof(char));

	if (result == NULL) {
		fprintf(stderr, "Error asignando memoria\n");
		return "";
	}

	result[0] = '\0';

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return "";
	}

	// Preparar la consulta SQL
	const char *sql = "SELECT ID_producto from PRODUCTO_PEDIDO where id_ped=?";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id_ped);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return "";
	}
	// Ejecutar la consulta y procesar los resultados
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		// Obtener los valores de cada columna (con comprobaci�n de NULL)
		int id_producto = (int) sqlite3_column_int(stmt, 0);

		char buffer[300];
		sprintf(buffer, "%i\n", id_producto);

		printf("%s", buffer);
		strcat(result, buffer);
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
	return result;
}

int esUsuarioValido(char *email, char *contrasena, const char *path) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;
	int id = 0;

	// Abrir la base de datos
	rc = sqlite3_open(path, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	// Preparar la consulta SQL
	const char *sql =
			"SELECT ID_CL FROM Cliente where EMAIL = ? and CONTRASENA = ? ";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, email, strlen(email), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, contrasena, strlen(contrasena), SQLITE_STATIC);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error al preparar la consulta: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return rc;
	}

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		id = sqlite3_column_int(stmt, 0);
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	fflush(stdout);
	if (id == 0) {
		return 1; // false
	}
	return id * (-1); // true
}
