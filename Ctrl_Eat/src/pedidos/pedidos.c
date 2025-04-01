#include "pedidos.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprimirPedido(Pedido pedi){
	char fechaPedidoStr[11], fechaEntregaStr[11];

	sscanf("2025-03-01", "%d-%d-%d", &pedi.fchPedido.tm_year, &pedi.fchPedido.tm_mon, &pedi.fchPedido.tm_mday);
	pedi.fchPedido.tm_year -= 1900; // Ajuste necesario
	pedi.fchPedido.tm_mon -= 1;     // Mes en struct tm va de 0 a 11

	printf("| %04d | $%-6.2f | %-2s | %s | %s |\n",
		   pedi.id, pedi.total, pedi.domic, fechaPedidoStr, fechaEntregaStr);
	/*int i;
	for(i=0;i<poli.numVertices;i++){
		printf("Vertice %d = ",i);
		fflush(stdout);
		imprimirPunto(poli.vertices[i]);
	}*/
}
void liberarPedido(Pedido *pedi){
	/*free(poli->vertices);
	poli->numVertices = 0;
	poli->vertices = NULL;*/
}
