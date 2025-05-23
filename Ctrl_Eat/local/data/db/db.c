#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/sqlite3/sqlite3.h"
#include "db.h"

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
	} else {
		printf("El comando: %s no existe\n");
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return SQLITE_OK;
}

int insertarEmpleado(char *nombre, char *cargo, char *cuentaBancaria) {
	int id;
	obtenerUltimoIdEmpleados(&id);
	id++;

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
	return 0;
}

int deleteEmpleado(int id_em) {
	int rc;
	sqlite3 *db;
	sqlite3_stmt *stmt;
	rc = sqlite3_open(DB_PATH, &db);

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

int imprimirEmpleados() {
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

int updateEmpleados(int id_em, char *nombre, char *cargo, char *cuentaBancaria) {
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
		printf("Update error: %s\n", sqlite3_errmsg(db));
	} else {
		printf("Update successful\n");
	}
	sqlite3_close(db);
	return 0;
}

int obtenerUltimoIdProductos(int *id) {
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
	char *sql = "SELECT MAX(ID_PR) FROM Producto";
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
		printf("El comando: %s no existe\n");
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return SQLITE_OK;
}

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

int imprimirProductos() {
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
		// Obtener los valores de cada columna (con comprobaci�n de NULL)
		int id_pr = (int) sqlite3_column_int(stmt, 0);
		char *nombre = (char*) sqlite3_column_text(stmt, 1);
		float precio = (float) sqlite3_column_double(stmt, 2);
		char *tipo = (char*) sqlite3_column_text(stmt, 3);

		printf("%i. Nombre:%s Precio:%.2f Tipo:%s\n", id_pr, nombre, precio,
				tipo);
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
	return SQLITE_OK;
}

int deleteProductos(int id_pr) {
	int rc;
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
	// Vincular el par�metro de la consulta (nombre de comando) al marcador de posici�n `?`
	rc = sqlite3_bind_int(stmt, 1, id_pr); // 1 es el �ndice del primer `?`
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

int updateProductos(int id_pr, char *nombre, float precio, char *tipo) {
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
	char *sql =
			"UPDATE Producto SET NOMBRE = ?, PRECIO = ?, TIPO = ? WHERE ID_PR = ?";
	sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	rc += sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	rc += sqlite3_bind_double(stmt, 2, precio);
	rc += sqlite3_bind_text(stmt, 3, tipo, strlen(tipo), SQLITE_STATIC);
	rc += sqlite3_bind_int(stmt, 4, id_pr);

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

int insertarClientes(char *nombre, char *email, int telefono, char *contrasena) {
	int id;
	obtenerUltimoIdClientes(&id);
	id++;

	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc = sqlite3_open(DB_PATH, &db);

	if (rc != SQLITE_OK) {
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

int deleteClientes(int id_cl) {
	int rc;
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

int verClientes() {
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
		char *contrasena) {
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

int insertarIngredientes(char *nombre) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

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

int imprimirIngredientes() {
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

int deleteIngredientes(int id_in) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;

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

int obtenerUltimoIdRestaurante(int *id) {
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
	char *sql = "SELECT MAX(ID_RES) FROM Restaurante";
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
		printf("El comando: %s no existe\n");
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return SQLITE_OK;
}

int updateRestaurante(int id, char *nombre, char *ciudad) {
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

	// Preparar la consulta SQL para actualizar el restaurante
	char *sql = "UPDATE Restaurante SET NOMBRE = ?, CIUDAD = ? WHERE ID_RES = ?";
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

int insertarRestaurante(char *nombre, char *ciudad) {
	int id;
	obtenerUltimoIdRestaurante(&id);
	id++;

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

	// Preparar la consulta SQL para insertar un nuevo restaurante
	char *sql =
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

int imprimirRestaurante() {
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
	char *sql = "SELECT ID_RES,NOMBRE,CIUDAD FROM Restaurante";
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
		int id_res = (int) sqlite3_column_int(stmt, 0);
		char *nombre = (char*) sqlite3_column_text(stmt, 1);
		char *ciudad = (char*) sqlite3_column_text(stmt, 2);

		printf("%i. Nombre:%s Ciudad:%s \n", id_res, nombre,
				ciudad);
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

int obtenerProductos() {
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
	char *sql = "SELECT ID_PR, NOMBRE,PRECIO,TIPO FROM Producto";
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

		printf("%i.%s.%f.%s\n", id_pr, nombre, precio, tipo);
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

int obtenerUltimoIdPedido(int *id) {
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
	char *sql = "SELECT MAX(ID_PED) FROM Pedido";
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
		printf("El comando: %s no existe\n");
	}

	// Finalizar la consulta y cerrar la base de datos
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return SQLITE_OK;
}

int getrPedidos() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Abrir la base de datos
    rc = sqlite3_open(DB_PATH, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    // Preparar la consulta SQL
    char *sql = "SELECT ID_PED, FCHA_ENTREGA, FCHA_PEDIDO, DOMICILIO, ID_CL, ID_RES FROM Pedido";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    // Ejecutar la consulta y procesar los resultados
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id_ped = sqlite3_column_int(stmt, 0);
        char *fchEntrega = (char*) sqlite3_column_text(stmt, 1);
		char *fchPedido = (char*) sqlite3_column_text(stmt, 2);
        int domic = sqlite3_column_int(stmt, 3);
        int id_cl = sqlite3_column_int(stmt, 4);
        int id_res = sqlite3_column_int(stmt, 5);

        printf("ID Pedido: %d\nFecha Entrerga: %s\nFecha Pedido: %s\nDomicilio: %d\nID Cliente: %d\nID Restaurante: %d\n\n",
               id_ped, fchEntrega, fchPedido, domic,  id_cl, id_res);
    }

    // Verificar si ocurrió algún error durante la consulta
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
    }

    // Finalizar la consulta y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    fflush(stdout);
    return SQLITE_OK;
}


