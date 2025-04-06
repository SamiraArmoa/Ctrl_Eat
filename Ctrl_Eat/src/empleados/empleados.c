#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/sqlite3/sqlite3.h"
#include "empleados.h"

// Generar ID tipo "EMP001"
void generarIDEmpleado(int numero, char *id) {
    sprintf(id, "EMP%03d", numero);
}

// Crear un nuevo empleado
void crearEmpleado(Empleado empleados[], int *count) {
    if (*count >= 300) {
        printf("No se pueden agregar más empleados.\n");
        return;
    }

    printf("Ingresa el nombre del empleado: ");
    fflush(stdin);
    scanf(" %[^\n]", empleados[*count].nombre);

    printf("Ingresa el cargo: ");
    fflush(stdin);
    scanf(" %[^\n]", empleados[*count].cargo);

    printf("Ingresa la cuenta bancaria: ");
    fflush(stdin);
    scanf(" %[^\n]", empleados[*count].cuentaBancaria);

    generarIDEmpleado(*count + 1, empleados[*count].id);
    printf("Empleado creado: %s - ID: %s\n", empleados[*count].nombre, empleados[*count].id);

    (*count)++;
}

// Eliminar empleado por nombre
void eliminarEmpleado(Empleado empleados[], int *count) {
    char nombre[50];
    printf("Ingresa el nombre del empleado a eliminar: ");
    fflush(stdin);
    scanf(" %[^\n]", nombre);

    for (int i = 0; i < *count; i++) {
        if (strcmp(empleados[i].nombre, nombre) == 0) {
            printf("Empleado %s eliminado.\n", empleados[i].nombre);

            // Mover los demás
            for (int j = i; j < *count - 1; j++) {
                empleados[j] = empleados[j + 1];
            }
            (*count)--;
            return;
        }
    }
    printf("No se encontró el empleado.\n");
}

// Actualizar por ID
void actualizarEmpleado(Empleado empleados[], int count) {
    char idBuscado[10];

    printf("Ingrese el ID del empleado a actualizar (ej. EMP001): ");
    fflush(stdout);
    fflush(stdin);
    scanf(" %[^\n]", idBuscado);

    int encontrado = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(empleados[i].id, idBuscado) == 0) {
            printf("Empleado encontrado: %s - Cargo actual: %s - Cuenta actual: %s\n",
                   empleados[i].nombre, empleados[i].cargo, empleados[i].cuentaBancaria);

            printf("Nuevo nombre: ");
            scanf(" %[^\n]", empleados[i].nombre);

            printf("Nuevo cargo: ");
            scanf(" %[^\n]", empleados[i].cargo);

            printf("Nueva cuenta bancaria: ");
            scanf(" %[^\n]", empleados[i].cuentaBancaria);

            printf("Empleado actualizado correctamente.\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se ha encontrado ningún empleado con el ID %s\n", idBuscado);
    }
}

// Mostrar todos los empleados
void verEmpleados(Empleado empleados[], int count) {
    printf("\nLista de Empleados:\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %s - Nombre: %s - Cargo: %s - Cuenta Bancaria: %s\n",
               empleados[i].id,
               empleados[i].nombre,
               empleados[i].cargo,
               empleados[i].cuentaBancaria);
    }
}
