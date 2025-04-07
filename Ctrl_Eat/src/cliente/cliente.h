#ifndef CLIENTES_H_
#define CLIENTES_H_

typedef struct {
    int id;
    char nombre[100];
    char email[100];
    int telefono;
    char contrasena[100];
} Cliente;

int crearCliente();
int eliminarCliente();
int actualizarCliente();
int imprimirClientes();

#endif



