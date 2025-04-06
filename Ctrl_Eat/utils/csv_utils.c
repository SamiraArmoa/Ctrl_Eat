#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_utils.h"
#include "../lib/sqlite3/sqlite3.h"
#include "../data/db/db.h"

#define MAX_LINE 2048

int guardar_productoIngrediente(int id_pr, int id_in) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found = sqlite3_open(DB_PATH, &db);

	printf("Producto: %i Ingrediente: %i\n", id_pr, id_in);

	if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char *insert_sql =
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
	printf("%s\n", id_in);
}

int guardar_productoIngredientes(int id_pr, char *ingredientes_ids) {
	printf("Cadena original: %s\n", ingredientes_ids);

	// Primera llamada a strtok para obtener el primer token
	char *id_ingrediente = strtok(ingredientes_ids, ";");

	// Mientras haya tokens para procesar
	while (id_ingrediente != NULL) {
		int id_casteado = atoi(id_ingrediente);
		printf("Procesando ingrediente ID: %d\n", id_casteado);
		guardar_productoIngrediente(id_pr, id_casteado);

		// Obtener el siguiente token
		id_ingrediente = strtok(NULL, ";");
	}

	return 0;
}

int guardar_ingredientes(int id, char *nombre) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found = sqlite3_open(DB_PATH, &db);

	if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char *insert_sql = "INSERT INTO Ingrediente(ID_IN, NOMBRE) VALUES (?, ?)";
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

int guardar_productos(int id, char *nombre, char *tipo, float precio) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found = sqlite3_open(DB_PATH, &db);

	if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char *insert_sql =
			"INSERT INTO Producto(ID_PR, NOMBRE,PRECIO,TIPO) VALUES (?, ?, ?, ?)";
	sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id);
	sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
	sqlite3_bind_double(stmt, 3, precio);
	sqlite3_bind_text(stmt, 4, tipo, strlen(tipo), SQLITE_STATIC);

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

int guardar_restaurantes(char *id, char *nombre, char *ciudad) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found = sqlite3_open(DB_PATH, &db);

	if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char *insert_sql =
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

int guardar_productoPedido(int id_ped, int id_pr) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found = sqlite3_open(DB_PATH, &db);

	if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char *insert_sql =
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
int guardarPedidos(int domic,char *fchEntrega, char *fchPedido){
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

    // Preparar la consulta SQL para insertar un nuevo pedido
    char *sql = "INSERT INTO Pedido (FCHA_ENTREGA, FCHA_PEDIDO, DOMICILIO, ID_CL, ID_RES) VALUES (?, ?, ?, ?, ?)";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    // Convertir domic (0 o 1) a cadena
    const char *domic_str = domic ? "Sí" : "No";

    // Bind de los valores a la consulta
    sqlite3_bind_text(stmt, 1, fchEntrega, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, fchPedido, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, domic_str, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, 1); // TODO id_cl valor
    sqlite3_bind_int(stmt, 5, 1); // TODO id_res calor

    // Ejecutar la consulta
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Pedido creado exitosamente\n");
    }

    // Finalizar y cerrar
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return SQLITE_OK;
}



int cargar_ingredientes() {
	FILE *file = fopen("../data/csv/ingredientes.csv", "r");
	if (!file) {
		perror("Error al abrir el archivo");
		return 1;
	}
	char line[MAX_LINE];
	//descartar el encabezado
	fgets(line, sizeof(line), file);

	while (fgets(line, sizeof(line), file)) {
		char *id, *nombre; //puntero para cada apartado

		id = strtok(line, ",");
		nombre = strtok(NULL, "\n");

		if (id && nombre) {
			//eliminar espacion en blanco al inicio o al final del nombre
			char *trimmed_nombre = nombre;
			while (*trimmed_nombre == ' ')
				trimmed_nombre++;

			//eliminar cualquier caracter de nueva linea o retorno de carro al final
			size_t len = strlen(trimmed_nombre);
			while (len > 0
					&& (trimmed_nombre[len - 1] == '\n'
							|| trimmed_nombre[len - 1] == '\r')) {
				trimmed_nombre[len - 1] = '\0';
				len--;
			}

			int id_casteado = atoi(id);
			guardar_ingredientes(id_casteado, trimmed_nombre);
//			printf("%s,%s\n", id, nombre);
		} else {
			fprintf(stderr, "ERROR EN LA LINEA: %s\n", line);
		}
	}
	fclose(file);
	return 0;
}

int cargar_productos() {
	FILE *file = fopen("../data/csv/productos.csv", "r");
	if (!file) {
		perror("Error al abrir el archivo");
		return 1;
	}
	char line[MAX_LINE];
	//descartar el encabezado
	fgets(line, sizeof(line), file);

	while (fgets(line, sizeof(line), file)) {
		char *id, *nombre, *ingredientes, *tipo, *precio; //puntero para cada apartado

		id = strtok(line, ",");
		nombre = strtok(NULL, ",");
		ingredientes = strtok(NULL, ",");
		tipo = strtok(NULL, ",");
		precio = strtok(NULL, "\n");

		if (id && nombre && ingredientes && tipo && precio) {
			//eliminar espacion en blanco al inicio o al final del nombre
			char *trimmed_precio = precio;
			while (*trimmed_precio == ' ')
				trimmed_precio++;

			//eliminar cualquier caracter de nueva linea o retorno de carro al final
			size_t len = strlen(trimmed_precio);
			while (len > 0
					&& (trimmed_precio[len - 1] == '\n'
							|| trimmed_precio[len - 1] == '\r')) {
				trimmed_precio[len - 1] = '\0';
				len--;
			}

			float precio_parseado = atof(trimmed_precio);
			int id_casteado = atoi(id);
			guardar_productos(id_casteado, nombre, tipo,
					precio_parseado);
			guardar_productoIngredientes(id_casteado, ingredientes);
//			printf("%s,%s,%s,%s \n", id, nombre, ingredientes, tipo);
		} else {
			fprintf(stderr, "ERROR EN LA LINEA: %s\n", line);
		}
	}
	fclose(file);
	return 0;
}
int cargar_restaurantes() {
	FILE *file = fopen("../data/csv/restaurantes.csv", "r");
	if (!file) {
		perror("Error al abrir el archivo");
		return 1;
	}
	char line[MAX_LINE];
	//descartar el encabezado
	fgets(line, sizeof(line), file);

	while (fgets(line, sizeof(line), file)) {
		char *id, *nombre, *ciudad; //puntero para cada apartado

		id = strtok(line, ";");
		nombre = strtok(NULL, ";");
		ciudad = strtok(NULL, "\n");

		if (id && nombre && ciudad) {
			//eliminar espacion en blanco al inicio o al final del nombre
			char *trimmed_ciudad = ciudad;
			while (*trimmed_ciudad == ' ')
				trimmed_ciudad++;

			//eliminar cualquier caracter de nueva linea o retorno de carro al final
			size_t len = strlen(trimmed_ciudad);
			while (len > 0
					&& (trimmed_ciudad[len - 1] == '\n'
							|| trimmed_ciudad[len - 1] == '\r')) {
				trimmed_ciudad[len - 1] = '\0';
				len--;
			}
			guardar_restaurantes(id, nombre, trimmed_ciudad);
//			printf("%s, %s, %s\n", id, nombre, ciudad);
		} else {
			fprintf(stderr, "ERROR EN LA LINEA: %s\n", line);
		}
	}
	fclose(file);
	return 0;
}

int cargar_csvs() {
	int ce1 = cargar_ingredientes();
	int ce2 = cargar_productos();
	int ce3 = cargar_restaurantes();
	if (ce1 == 0 && ce2 == 0 && ce3 == 0) {
		return 0;
	}
	return 1;
}

