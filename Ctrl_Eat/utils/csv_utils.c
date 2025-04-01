#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_utils.h"
//#include <sqlite3.h>

#define MAX_LINE 2048
/*
int guardar_file(char *nombre){
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int db_found= sqlite3_open("./data/db/restaurante.db",&db);
   if (db_found != SQLITE_OK) {
		printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
   char *insert_sql = "INSERT INTO CMD(NONMBRE) VALUES (?)";
       sqlite3_prepare_v2(db, insert_sql, strlen(insert_sql) + 1, &stmt, NULL);
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
*/
int cargar_ingredientes(){
	FILE *file= open("./data/csv/ingredientes.csv","r");
	if(!file){
		perror("Error al abrir el archivo");
		return 1;
	}
	char line[MAX_LINE];
	//descartar el encabezado
	fgets(line,sizeof(line), file);

	while(fgets(line,sizeof(line),file)){
		char *id,*nombre; //puntero para cada apartado

		id= strok(line,",");
		nombre = strtok(NULL, "\n");

		if(id && nombre){
			//eliminar espacion en blanco al inicio o al final del nombre
			char* trimmed_nombre = nombre;
			while (*trimmed_nombre == ' ') trimmed_nombre++;

			//eliminar cualquier caracter de nueva linea o retorno de carro al final
			size_t len= strlen(trimmed_nombre);
			 while (len > 0 && (trimmed_nombre[len-1] == '\n' || trimmed_nombre[len-1] == '\r')) {
						trimmed_nombre[len-1] = '\0';
						len--;
					}
			 guardar_file(trimmed_nombre);
		} else {
			fprint(stderr,"ERROR EN LA LINEA: %s\n",line);
		}
	}
	fclose(file);
	return 0;
}

int cargar_productos(){
	FILE *file= open("./data/csv/productos_actualizados.csv","r");
	if(!file){
		perror("Error al abrir el archivo");
		return 1;
	}
	char line[MAX_LINE];
	//descartar el encabezado
	fgets(line,sizeof(line), file);

	while(fgets(line,sizeof(line),file)){
		char *id,*nombre,*ingredientes,*Tipo; //puntero para cada apartado

		id= strok(line,",");
		nombre= strtok(NULL, ",");
		ingredientes= strtok(NULL, ",");
		Tipo = strtok(NULL, "\n");

		if(id && nombre && ingredientes && Tipo){
			//eliminar espacion en blanco al inicio o al final del nombre
			char* trimmed_Tipo = Tipo;
			while (*trimmed_Tipo == ' ') trimmed_Tipo++;

			//eliminar cualquier caracter de nueva linea o retorno de carro al final
			size_t len= strlen(trimmed_Tipo);
			 while (len > 0 && (trimmed_Tipo[len-1] == '\n' || trimmed_Tipo[len-1] == '\r')) {
						trimmed_Tipo[len-1] = '\0';
						len--;
					}
			 guardar_file(trimmed_Tipo);
		} else {
			fprint(stderr,"ERROR EN LA LINEA: %s\n",line);
		}
	}
	fclose(file);
	return 0;
}
int cargar_restaurantes(){
	FILE *file= open("./data/csv/restaurantes.csv","r");
	if(!file){
		perror("Error al abrir el archivo");
		return 1;
	}
	char line[MAX_LINE];
	//descartar el encabezado
	fgets(line,sizeof(line), file);

	while(fgets(line,sizeof(line),file)){
		char *ID,*Nombre,*Ciudad; //puntero para cada apartado

		ID= strok(line,",");
		Nombre= strtok(NULL, ",");
		Ciudad= strtok(NULL, "\n");

		if(ID && Nombre && Ciudad){
			//eliminar espacion en blanco al inicio o al final del nombre
			char* trimmed_Ciudad = Ciudad;
			while (*trimmed_Ciudad == ' ') trimmed_Ciudad++;

			//eliminar cualquier caracter de nueva linea o retorno de carro al final
			size_t len= strlen(trimmed_Ciudad);
			 while (len > 0 && (trimmed_Ciudad[len-1] == '\n' || trimmed_Ciudad[len-1] == '\r')) {
						trimmed_Ciudad[len-1] = '\0';
						len--;
					}
			 guardar_file(trimmed_Ciudad);
		} else {
			fprint(stderr,"ERROR EN LA LINEA: %s\n",line);
		}
	}
	fclose(file);
	return 0;
}

int cargar_csvs(){
	cargar_ingredientes();
	cargar_productos();
	cargar_restaurantes();
	return 0;
}

