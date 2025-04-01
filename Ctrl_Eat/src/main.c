#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedidos/pedidos.h"
#include <time.h>
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
	if (cargar_csv() != 0) {
			fprintf(stderr, "Error al cargar los comandos\n");
			return 1;
		}
	return 0;
}

