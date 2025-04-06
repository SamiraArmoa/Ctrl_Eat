#include "ingredientes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



	void generarID(int numero, char *id) {
		sprintf(id, "I%03d", numero);
		fflush(stdout);
		fflush(stdin);
	}

	void crearIngrediente(Ingrediente ingredientes[], int *count) {
	    if (*count >= 300) {
	        printf("No se pueden agregar más ingredientes.\n");
	        fflush(stdout);
	        fflush(stdin);
	        return;
	    }

	    printf("Ingrese el nombre del ingrediente: ");
	    fflush(stdout);
	    fflush(stdin);
	    scanf(" %[^\n]", ingredientes[*count].nombre);
	    generarID(*count + 1, ingredientes[*count].id);

	    printf("Ingrediente creado: %s - ID: %s\n", ingredientes[*count].nombre, ingredientes[*count].id);
	    fflush(stdout);
	    fflush(stdin);

	    (*count)++;
	}


	void eliminarIngrediente(Ingrediente ingredientes[], int *count) {
	    char nombre[50];
	    printf("Ingrese el nombre del ingrediente a eliminar: ");
	    fflush(stdout);
	    fflush(stdin);
	    scanf(" %[^\n]", nombre);

	    for (int i = 0; i < *count; i++) {
	        if (strcmp(ingredientes[i].nombre, nombre) == 0) {
	            printf("Ingrediente %s eliminado.\n", ingredientes[i].nombre);
	            fflush(stdout);
	            fflush(stdin);

	            // Mover los elementos restantes
	            for (int j = i; j < *count - 1; j++) {
	                ingredientes[j] = ingredientes[j + 1];
	            }

	            (*count)--;
	            return;
	        }
	    }
	    printf("No se encontró el ingrediente.\n");
	    fflush(stdout);
	    fflush(stdin);
	}

	// Actualiza el nombre de un ingrediente dado su ID
	void actualizarIngrediente(Ingrediente ingredientes[], int count) {
	    char id[5];
	    printf("Ingrese el ID del ingrediente a actualizar: ");
	    fflush(stdout);
	    fflush(stdin);
	    scanf("%s", id);

	    for (int i = 0; i < count; i++) {
	        if (strcmp(ingredientes[i].id, id) == 0) {
	            printf("Ingrese el nuevo nombre: ");
	            fflush(stdout);
	            fflush(stdin);
	            scanf(" %[^\n]", ingredientes[i].nombre);
	            printf("Ingrediente actualizado: %s - ID: %s\n", ingredientes[i].nombre, ingredientes[i].id);
	            fflush(stdout);
	            fflush(stdin);
	            return;
	        }
	    }
	    printf("No se encontró el ingrediente con ese ID.\n");
	    fflush(stdout);
	    fflush(stdin);
	}

	// Lista todos los ingredientes
	void listarIngredientes(Ingrediente ingredientes[], int count) {
	    printf("\nLista de Ingredientes:\n");
	    fflush(stdout);
	    fflush(stdin);
	    for (int i = 0; i < count; i++) {
	        printf("ID: %s - Nombre: %s\n", ingredientes[i].id, ingredientes[i].nombre);
	        fflush(stdout);
	        fflush(stdin);
	    }

	}

