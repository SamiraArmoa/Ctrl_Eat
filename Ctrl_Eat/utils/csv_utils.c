#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_utils.h"
//#include <sqlite3.h>
#include "../lib/sqlite3/sqlite3.h"

#define MAX_LINE 2048

int guardar_ingredientes(char *id, char *nombre){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int db_found = sqlite3_open("./db/local.db", &db);

    if (db_found != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char *insert_sql = "INSERT INTO Ingrediente(ID_IN, NOMBRE) VALUES (?, ?)";
    sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, id, strlen(id), SQLITE_STATIC);
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

int guardar_productos(char *id, char *nombre, char *ingredientes, char* tipo, float precio ){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int db_found = sqlite3_open("./db/local.db", &db);

    if (db_found != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char *insert_sql = "INSERT INTO Producto(ID_PR, NOMBRE,PRECIO,TIPO) VALUES (?, ?, ?, ?)";
    sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, id, strlen(id), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
    sqlite3_bind_double(stmt,3,precio);
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

int guardar_restaurantes(char *id, char *nombre, char* ciudad){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int db_found = sqlite3_open("./db/local.db", &db);

    if (db_found != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char *insert_sql = "INSERT INTO Restaurante(ID_RES, NOMBRE, CIUDAD) VALUES (?, ?, ?)";
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
			guardar_ingredientes(id, trimmed_nombre);
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
			guardar_productos(id, nombre, ingredientes, tipo, precio_parseado);
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

int main() {
	cargar_ingredientes();
	cargar_productos();
	cargar_restaurantes();
	return 0;
}

