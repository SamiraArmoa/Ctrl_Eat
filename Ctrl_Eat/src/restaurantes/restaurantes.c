#include "restaurantes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/sqlite3/sqlite3.h"
#include "../../data/db/db.h"

int obtenerUltimoIdRestaurante(int* id) {
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
    char *sql = "SELECT MAX(ID_RES) FROM Restaurante";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    // Ejecutar la consulta y procesar los resultados
    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        // Obtener los valores de cada columna (con comprobaci�n de NULL)
        *id = sqlite3_column_int(stmt, 0);
        printf("Id calculado: %i",*id);
    } else {
        printf("El comando: %s no existe\n");
    }

    // Finalizar la consulta y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return SQLITE_OK;
}
int actualizarRestaurante() {
   sqlite3 *db;
   sqlite3_stmt *stmt;
   int rc;
   int id;
   char* nombre;
   char* ciudad;
   char nom[100];
   char ciu[100];

   // Abrir la base de datos
   rc = sqlite3_open(DB_PATH, &db);
   if (rc != SQLITE_OK) {
       fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
       sqlite3_close(db);
       return rc;
   }
   printf("Ingrese el ID del restaurante a actualizar: ");
   fflush(stdin);
	scanf("%d", &id);

	printf("Ingrese el nuevo nombre del restaurante: ");
	fflush(stdin);
	fgets(nom,100,stdin);
	nom[strcspn(nom, "\n")]='\0';
	nombre = malloc((strlen(nom) + 1) * sizeof(char));
	if (nombre == NULL) {
			printf("Error al asignar memoria para el nombre.\n");
			return -1;  // Error si no se pudo asignar memoria
		}
	strcpy(nombre, nom);


	printf("Ingrese la nueva ciudad del restaurante: ");
	fflush(stdin);
	fgets(ciu,100,stdin);
	ciu[strcspn(ciu, "\n")]='\0';
	ciudad = malloc((strlen(ciu) + 1) * sizeof(char));
	if (nombre == NULL) {
			printf("Error al asignar memoria para el nombre.\n");
			return -1;  // Error si no se pudo asignar memoria
		}
	strcpy(ciudad, ciu);

   // Preparar la consulta SQL para actualizar el restaurante
   char *sql = "UPDATE Restaurante SET NOMBRE = ?, CIUDAD = ? WHERE ID_RES = ?";
   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
   if (rc != SQLITE_OK) {
       fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
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
       fprintf(stderr, "Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
   } else {
       printf("Restaurante actualizado exitosamente\n");
   }
   // Finalizar la consulta y cerrar la base de datos
   sqlite3_finalize(stmt);
   sqlite3_close(db);
   return SQLITE_OK;
}
int crearRestaurante() {
   sqlite3 *db;
   sqlite3_stmt *stmt;
   int rc;
   int id;
	char* nombre;
	char* ciudad;
	char nom[100];
	char ciu[100];
	obtenerUltimoIdRestaurante(&id);
	id++;
   // Abrir la base de datos
   rc = sqlite3_open(DB_PATH, &db);
   if (rc != SQLITE_OK) {
       fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
       sqlite3_close(db);
       return rc;
   }

   	printf("Ingrese el nuevo nombre del restaurante: ");
   	fflush(stdin);
   	fgets(nom,100,stdin);
   	nom[strcspn(nom, "\n")]='\0';
   	nombre = malloc((strlen(nom) + 1) * sizeof(char));
   	if (nombre == NULL) {
   			printf("Error al asignar memoria para el nombre.\n");
   			return -1;  // Error si no se pudo asignar memoria
   		}
   	strcpy(nombre, nom);


   	printf("Ingrese la nueva ciudad del restaurante: ");
   	fflush(stdin);
   	fgets(ciu,100,stdin);
   	ciu[strcspn(ciu, "\n")]='\0';
   	ciudad = malloc((strlen(ciu) + 1) * sizeof(char));
   	if (nombre == NULL) {
   			printf("Error al asignar memoria para el nombre.\n");
   			return -1;  // Error si no se pudo asignar memoria
   		}
   	strcpy(ciudad, ciu);

   // Preparar la consulta SQL para insertar un nuevo restaurante
   char *sql = "INSERT INTO Restaurante (ID_RES,NOMBRE, CIUDAD) VALUES (?, ?, ?)";
   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
   if (rc != SQLITE_OK) {
       fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
       sqlite3_close(db);
       return rc;
   }
   // Bind the values to the SQL statement
   sqlite3_bind_int(stmt,1,id);
   sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
   sqlite3_bind_text(stmt, 3, ciudad, strlen(ciudad), SQLITE_STATIC);
   // Ejecutar la consulta
   rc = sqlite3_step(stmt);
   if (rc != SQLITE_DONE) {
       fprintf(stderr, "Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
   } else {
       printf("Restaurante creado exitosamente\n");
   }
   // Finalizar la consulta y cerrar la base de datos
   sqlite3_finalize(stmt);
   sqlite3_close(db);
   return SQLITE_OK;
}
