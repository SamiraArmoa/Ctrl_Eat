#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_utils.h"
#include "../lib/sqlite3/sqlite3.h"
#include "../data/db/db.h"

#define MAX_LINE 2048

int guardar_productoIngredientes(int id_pr, char *ingredientes_ids){
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
		char *id, *nombre, *ingredientes, *tipo, *precio,*extra;//puntero para cada apartado
		char *tamanio=NULL, *alergenos=NULL;

		id = strtok(line, ",");
		nombre = strtok(NULL, ",");
		ingredientes = strtok(NULL, ",");
		tipo = strtok(NULL, ",");
		precio = strtok(NULL, ",");

		extra=strtok(NULL,"\n");


		if (id && nombre && ingredientes && tipo && precio && extra) {
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

			if (strcmp(tipo, "Bebida") == 0) {
				tamanio = extra;
				alergenos = NULL;
			} else if (strcmp(tipo, "Plato") == 0) {
				alergenos = extra;
				tamanio = NULL;
			}

			guardar_productos(id_casteado, nombre, tipo,
					precio_parseado,tamanio,alergenos);
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

