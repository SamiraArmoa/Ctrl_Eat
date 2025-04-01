#ifndef PEDIDOS_H_
#define PEDIDOS_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int id;
	float total;
	char domic[3]; //Si o No , no necesita malloc
	struct tm fchPedido; // no es puntero debido a que struct tm tiene un tamño fijo
	struct tm fchEntrega;
}Pedido;
void imprimirPedido(Pedido pedi);
void liberarPedido(Pedido *pedi);
#endif
