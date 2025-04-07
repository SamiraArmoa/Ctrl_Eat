#include "pedidos.h"
#include "../restaurantes/restaurantes.h"
#include "../cliente/cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/sqlite3/sqlite3.h"
#include "../../data/db/db.h"
#include "../../utils/csv_utils.h"

#define MAX_LENGTH 100
int obtenerProducto() {
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
int asignarProductoPedido(int id_ped) {
	int opcion = -1;
	while (opcion != 0) {
		obtenerProducto();
		printf("Introduce el id del producto: ");
		scanf("%d", &opcion);
		if (opcion != 0) {
			guardar_productoPedido(id_ped, opcion);
		}
	}
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

int crearPedido() {
	char str[MAX_LENGTH];
	int domic; // 0 = No, 1 = Sí
	char *fchPedido;
	char *fchEntrega;

	printf("CREAR PEDIDO\n");
	printf("a domicilio 1-> si 0->no: ");
	fflush(stdin);
	fgets(str, MAX_LENGTH, stdin);
	sscanf(str, "%i", &domic);

	printf("\nFecha Pedido: ");
	fflush(stdin);
	fgets(str, MAX_LENGTH, stdin);

	str[strcspn(str, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	fchPedido = malloc((strlen(str) + 1) * sizeof(char));
	if (fchPedido == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(fchPedido, str);  // Copiar la cadena le�da en nombre
	printf("\nFecha Entrega: ");
	fflush(stdin);
	fgets(str, MAX_LENGTH, stdin);

	str[strcspn(str, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	fchEntrega = malloc((strlen(str) + 1) * sizeof(char));
	if (fchEntrega == NULL) {
		printf("Error al asignar memoria para el nombre.\n");
		return -1;  // Error si no se pudo asignar memoria
	}
	strcpy(fchEntrega, str);  // Copiar la cadena le�da en nombre

	printf("%i, %s, %s ", domic, fchPedido, fchEntrega);
	int id = 0;
	obtenerUltimoIdPedido(&id);
	id++;
	printf("ID_Obtenido = %i", id);
	guardarPedidos(domic, fchEntrega, fchPedido);
	asignarProductoPedido(id);
	return 0;
}

// Nueva función para imprimir pedidos
int imprimirPedidos() {
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
    char *sql = "SELECT ID_PED, FCH_PEDIDO, FCH_ENTREGA, DOMICILIO, ID_CL, ID_RES FROM Pedido";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    // Ejecutar la consulta y procesar los resultados
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id_ped = sqlite3_column_int(stmt, 0);
        char *fchPedido = (char*) sqlite3_column_text(stmt, 1);
        char *fchEntrega = (char*) sqlite3_column_text(stmt, 2);
        int domic = sqlite3_column_int(stmt, 3);
        int id_cl = sqlite3_column_int(stmt, 4);
        int id_res = sqlite3_column_int(stmt, 5);

        printf("ID Pedido: %d\nFecha Pedido: %s\nFecha Entrega: %s\nDomicilio: %d\nID Cliente: %d\nID Restaurante: %d\n\n",
               id_ped,fchPedido, fchEntrega, domic,  id_cl, id_res);
    }

    // Verificar si ocurrió algún error durante la consulta
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
    }

    // Finalizar la consulta y cerrar la base de datos
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    printf("LOL\n");
    fflush(stdout);
    return SQLITE_OK;
}
