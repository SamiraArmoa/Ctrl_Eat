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

int asignarProductoPedido(int id_ped) {
	int opcion = -1;
	while (opcion != 0) {
		obtenerProductos();
		printf("Introduce el id del producto: ");
		scanf("%d", &opcion);
		if (opcion != 0) {
			guardar_productoPedido(id_ped, opcion);
		}
	}
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
    int rc = getPedidos();
    return rc;

}
