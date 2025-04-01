#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/sqlite3/sqlite3.h"

int guardarIngredientes(int id, char* nombre){
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found = sqlite3_open("../../data/db/restaurante.db");

	if (db_found != SQLITE_OK) {
		printf("error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	char* insertSql = "INSERT INTO INGREDIENTE VALUES (?,?)";
	sqlite3_prepare_v2(db, insertSql, strlen(insertSql)+1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, id);
	sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);

	int resultado = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	if(resultado != SQLITE_DONE){
		printf("Insert error: %s\n", sqlite3_errmsg(db));
	}else{
		printf("Insert successful\n");
	}

	sqlite3_close(db);
	return 0;
}

int leerIngredientes(){
	char str[40];
	char* ingrediente;
	FILE *file = fopen("../../data/csv/ingredientes.csv", "r");
	if (!file) {
		perror("Error al abrir el archivo");
		return 1;
	}

	fgets(str,40,file);
	while(fgets(str,40,file)){
		char *id, *nombre;
		id= strtok(str,",");
		nombre= strtok(NULL,"\n");
		if (id && nombre) {
			char* trimmed_nombre = nombre;
			while(*trimmed_nombre == ' '){
				trimmed_nombre++;
			}
			size_t len = strlen(trimmed_nombre);
			while(len > 0 && (trimmed_nombre[len-1] == '\n' || trimmed_nombre[len-1] == 'r')){
				trimmed_nombre[len-1] = '\0';
				len--;
			}

			printf("%s ", id);
			printf("%s\n", nombre);
			int idParseado = atoi(id);
			guardarIngredientes(idParseado, nombre);

		}else{
			fprintf(stderr, "error al leer linea: %s\n", str);
		}
	}
}

int main(int argc, char **argv) {
	leerIngredientes();
	guardarIngredientes();
}
