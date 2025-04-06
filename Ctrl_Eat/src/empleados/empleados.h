#ifndef EMPLEADOS_H
#define EMPLEADOS_H

typedef struct {
    char id[10];
    char nombre[50];
    char cargo[50];
    char cuentaBancaria[30];
} Empleado;


void crearEmpleado(Empleado empleados[], int *count);
void eliminarEmpleado(Empleado empleados[], int *count);
void actualizarEmpleado(Empleado empleados[], int count);
void verEmpleados(Empleado empleados[], int count);
void generarIDEmpleado(int numero, char *id);

#endif

