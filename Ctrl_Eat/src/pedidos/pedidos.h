#ifndef PEDIDOS_H_
#define PEDIDOS_H_
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;
    float total;
    int domic; // 0 = No, 1 = Sí
    char* fchPedido;   // "YYYY-MM-DD"
    char* fchEntrega;
    int id_cl;
    int id_res;
} Pedido;

// New method declarations
int imprimirPedido();
int crearPedido();


#endif
