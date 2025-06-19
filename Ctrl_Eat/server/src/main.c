#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedidos/pedidos.h"
#include "productos/productos.h"
#include "empleados/empleados.h"
#include "../utils/csv_utils.h"
#include "restaurantes/restaurantes.h"
#include "ingredientes/ingredientes.h"
#include "cliente/cliente.h"
#include <time.h>
#include "serverSocket.h"

int imprimirMenu(int *opcion) {
	int num;

	printf("Bienvenido Administrador\n");
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
	printf("18. Crear cliente\n");
	printf("19. Eliminar cliente\n");
	printf("20. Actualizar cliente\n");
	printf("21. Salir\n");

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
		printf("Ha terminado");
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
		imprimirPedidos();
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
	case 14:
		crearIngrediente();
		break;
	case 15:
		eliminarIngredientes();
		break;
	case 16:
		verIngredientes();
		break;
	case 17:
		crearPedido();
		break;
	case 18:
		crearCliente();
		break;
	case 19:
		eliminarCliente();
		break;
	case 20:
		actualizarCliente();
		break;

	default:
		printf("No existe esa opcion\n");
		break;
	}
}

int main(int argc, char **argv) {


	int opcion = 0;
	printf("Que quieres hacer?\n");
 	printf("0. Entrar como administrador\n");
	printf("1. Escuchar conexiones de clientes\n");
	
	scanf("%d", &opcion);

	if (opcion == 0) {
		int opcionAdmin = 0;
	while (opcionAdmin != 21) {
		imprimirMenu(&opcion);
		escogerOpcion(&opcion);
	}
	} else if (opcion == 1) {
		printf("Escuchando...\n");
		for(;;) {
			escuchar();
		}
	} else {
		printf("Opción inválida\n");
	}

	
	return 0;
}

