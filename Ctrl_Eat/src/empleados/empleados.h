#ifndef EMPLEADOS_H
#define EMPLEADOS_H

typedef struct {
    char id[10];
    char nombre[50];
    char cargo[50];
    char cuentaBancaria[30];
} Empleado;

int crearEmpleado();
int eliminarEmpleado();
int actualizarEmpleado();
int verEmpleados();
#endif

