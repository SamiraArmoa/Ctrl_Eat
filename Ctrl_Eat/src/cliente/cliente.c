#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/sqlite3/sqlite3.h"
#include "../../data/db/db.h"

int crearCliente(Cliente *cliente) {
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

    // Preparar la consulta SQL para insertar un nuevo cliente
    char *sql = "INSERT INTO Cliente (ID_CL, NOMBRE, EMAIL, TELEFONO, CONTRASENA) VALUES (?, ?, ?, ?, ?)";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    // Bind the values to the SQL statement
    sqlite3_bind_int(stmt, 1, cliente->id);
    sqlite3_bind_text(stmt, 2, cliente->nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, cliente->email, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, cliente->telefono);
    sqlite3_bind_text(stmt, 5, cliente->contrasena, -1, SQLITE_STATIC);

    // Ejecutar la consulta
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Cliente creado exitosamente\n");
    }

    // Finalizar la consulta y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return SQLITE_OK;
}

int imprimirClientes() {
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
    char *sql = "SELECT * FROM Cliente";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    // Ejecutar la consulta y procesar los resultados
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nombre = sqlite3_column_text(stmt, 1);
        const unsigned char *email = sqlite3_column_text(stmt, 2);
        int telefono = sqlite3_column_int(stmt, 3);
        const unsigned char *contrasena = sqlite3_column_text(stmt, 4);

        printf("ID: %d, Nombre: %s, Email: %s, Telefono: %d, Contraseña: %s\n",
               id, nombre, email, telefono, contrasena);
    }

    // Finalizar la consulta y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return SQLITE_OK;
}
