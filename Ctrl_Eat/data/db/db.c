#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/sqlite3/sqlite3.h"
#include "db.h"

int obtenerUltimoIdProductos(int* id) {
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
    char *sql = "SELECT MAX(ID_PR) FROM Producto";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    // Ejecutar la consulta y procesar los resultados
    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        // Obtener los valores de cada columna (con comprobación de NULL)
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
