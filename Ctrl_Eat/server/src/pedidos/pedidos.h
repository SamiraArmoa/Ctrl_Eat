#ifndef PEDIDOS_H_
#define PEDIDOS_H_
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;
    float total;
    int domic; // 0 = No, 1 = Sí
    int id_cl;
    int id_res;
} Pedido;

// New method declarations
int imprimirPedidos();
int crearPedido();


#endif
