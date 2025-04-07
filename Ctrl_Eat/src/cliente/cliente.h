#ifndef CLIENTES_H_
#define CLIENTES_H_


#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;
    char nombre[100];
    char email[100];
    int telefono;
    char contrasena[100];
} Cliente;


int crearCliente(Cliente *cliente);
int imprimirClientes();


#endif



