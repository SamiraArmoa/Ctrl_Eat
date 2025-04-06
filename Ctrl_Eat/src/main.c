#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedidos/pedidos.h"
#include "../utils/csv_utils.h"
#include "productos/productos.h"
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
	printf("17. Salir\n");

	scanf("%d", &num);
	*opcion = num;
	return 0;
}

int escogerOpcion(int *opcion) {
	int ce = 5;

	switch (*opcion) {
	case 1:
		ce = cargar_csvs();
		if (ce == 0) {
			printf("Archivos cargados en la base de datos\n");
		}
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

	default:
		printf("No existe esa opcion\n");
		break;
	}
}

int main(int argc, char **argv) {
	/*pedido prueba
	 Pedido p1 = {1, 25.50, "Si"};
	 struct tm temp1 = {0}, temp2 = {0};
	 strptime("2025-03-01", "%Y-%m-%d", &temp1);
	 strptime("2025-03-02", "%Y-%m-%d", &temp2);
	 p1.fchPedido = temp1;
	 p1.fchEntrega = temp2;
	 imprimirPedido(p1);
	 */
//	if (cargar_csv() != 0) {
//			fprintf(stderr, "Error al cargar los comandos\n\n");
//			return 1;
//		}
	int opcion = 0;
	while (opcion != 17) {
		imprimirMenu(&opcion);
		escogerOpcion(&opcion);
	}

//	printf("%d", opcion);
}

