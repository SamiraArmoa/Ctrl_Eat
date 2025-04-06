#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedidos/pedidos.h"
#include "productos/productos.h"
#include "empleados/empleados.h"
#include "../utils/csv_utils.h"
#include "productos/productos.h"
#include "restaurantes/restaurantes.h"
#include "cliente/cliente.h"
#include <time.h>
int imprimirMenu(int *opcion) {
	int num;

	printf("Bienvenido Administrados\n");
	printf("Elige una opcion:\n");
	printf("1. Cargar ingredientes, restaurantes y productos desde el .csv\n");
	printf("2. Crear empleados\n");
	printf("3. Eliminar empleados\n");
	printf("4. Actualizar empleados\n");
	printf("5. Ver empleados\n");
	printf("6. Actualizar restaurantes\n");
	printf("7. Crear restaurantes\n");
	printf("8. Ver clientes\n");
	printf("9. Ver pedidos\n");
	printf("10. Crear productos\n");
	printf("11. Eliminar productos\n");
	printf("12. Actualizar productos\n");
	printf("13. Ver productos\n");
	printf("14. Crear ingredientes\n");
	printf("15. Eliminar ingredientes\n");
	printf("16. Ver ingredientes\n");
	printf("17. Crear pedidos\n");
	printf("18. Salir\n");

	scanf("%d", &num);
	*opcion = num;
	return 0;
}

int escogerOpcion(int *opcion) {
	int ce = 5;
	Restaurante restaurante;
	switch (*opcion) {
	case 1:
		ce = cargar_csvs();
		if (ce == 0) {
			printf("Archivos cargados en la base de datos\n");
		}
		break;
	case 2:
		crearEmpleado();
		break;
	case 3:
		eliminarEmpleado();
		break;
	case 4:
		actualizarEmpleado();
		break;
	case 5:
		verEmpleados();
		break;
	case 6:
		actualizarRestaurante();
		break;
	case 7:
		crearRestaurante();
		break;
	case 8:
		imprimirClientes();
		break;
	case 9:
		//imprimirPedido();
		break;
	case 10:
		crearProductos();
		break;
	case 11:
		eliminarProductos();
		break;
	case 12:
		actualizarProductos();
		break;
	case 13:
		verProductos();
		break;
	case 17:
		crearPedido();
		break;

	default:
		printf("No existe esa opcion\n");
		break;
	}
}

int main(int argc, char **argv) {

	int opcion = 0;
	while (opcion != 18) {
		imprimirMenu(&opcion);
		escogerOpcion(&opcion);
	}
	return 0;
}

