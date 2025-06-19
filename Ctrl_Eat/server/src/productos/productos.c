#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../data/db/db.h"
#include "../../utils/csv_utils.h"
#include "productos.h"
#include "../../config.h"

#define MAX_LENGTH 100
int asignarIngredientesProductos(int id_pr)
{
	int error = - 1;
	int opcion = -1;
	while (opcion != 0)
	{
		obtenerIngredientes(CLIENT_DB_PATH);
		printf("Introduce el id del ingrediente: ");
		scanf("%d", &opcion);
		if (opcion != 0)
		{
			error = guardar_productoIngrediente(id_pr, opcion, CLIENT_DB_PATH);
		}
	}
	return error;
}

int crearProductos()
{
	char str[MAX_LENGTH];
	float precio;
	char *nombre;
	char *tipo;
	char *tamanyo = "";
	char *alergenos = "";

	printf("CREAR PRODUCTO\n");
	printf("Nombre: ");
	fflush(stdin);
	fgets(str, MAX_LENGTH, stdin);

	str[strcspn(str, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	nombre = (char *)malloc((strlen(str) + 1) * sizeof(char));
	if (nombre == NULL)
	{
		printf("Error al asignar memoria para el nombre.\n");
		return -1; // Error si no se pudo asignar memoria
	}
	strcpy(nombre, str); // Copiar la cadena le�da en nombre

	printf("\nPrecio: ");
	fgets(str, MAX_LENGTH, stdin);
	sscanf(str, "%f", &precio);

	printf("\nTipo: ");
	fgets(str, MAX_LENGTH, stdin);

	str[strcspn(str, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	tipo = (char *)malloc((strlen(str) + 1) * sizeof(char));
	if (tipo == NULL)
	{
		printf("Error al asignar memoria para el tipo.\n");
		return -1; // Error si no se pudo asignar memoria
	}
	strcpy(tipo, str); // Copiar la cadena le�da en nombre

	if (strcmp(tipo, "Bebida\n"))
	{
		printf("\nTamaño: ");
		fgets(str, MAX_LENGTH, stdin);
		str[strcspn(str, "\n")] = '\0';
		tamanyo = (char *)malloc((strlen(str) + 1) * sizeof(char));
		strcpy(tamanyo, str);
		alergenos = "null";
	}
	else
	{
		printf("\nAlergenos: ");
		fgets(str, MAX_LENGTH, stdin);
		str[strcspn(str, "\n")] = '\0';
		alergenos = (char *)malloc((strlen(str) + 1) * sizeof(char));
		strcpy(alergenos, str);
		tamanyo = "null";
	}

	printf("%s, %f, %s ", nombre, precio, tipo);
	int id = 0;
	obtenerUltimoIdProductos(&id, CLIENT_DB_PATH);
	id++;
	printf("ID_Obtenido = %i", id);
	guardar_productos(id, nombre, tipo, precio, tamanyo, alergenos, CLIENT_DB_PATH);
	asignarIngredientesProductos(id);
	return 0;
}

int verProductos()
{
	imprimirProductos(CLIENT_DB_PATH);
	return 0;
}

int eliminarProductos()
{
	int id_pr = 0;
	verProductos();
	printf("Inserta el id del producto que quieres eliminar: ");
	fflush(stdin);
	scanf("%d", &id_pr);

	int confirmacion = 0;
	//	printf("\nELIMINAR PRODUCTO\n");
	printf("�Quieres eliminar este producto?\n");
	printf("1. SI\n");
	printf("2. NO\n");
	printf("Opcion: ");
	scanf("%d", &confirmacion);

	if (confirmacion != 1)
	{
		printf("Eliminacion cancelada.\n");
		return 0; // Salimos sin hacer nada
	}
	deleteProductos(id_pr, CLIENT_DB_PATH);
	return 0;
}

int actualizarProductos()
{
	int id_pr = 0;
	char *nombre;
	float precio;
	char *tipo;
	char *tamanyo = "";
	char *alergenos = "";

	char nom[100];
	char tip[25];
	char tam[25];
	char alg[100];

	verProductos();

	printf("Inserta el id del producto que quieres actualizar: ");
	fflush(stdin);
	scanf("%i", &id_pr);

	printf("Nombre: ");
	fflush(stdin);
	fgets(nom, 100, stdin);
	nom[strcspn(nom, "\n")] = '\0';
	// Asignar memoria din�mica para el nombre seg�n la longitud
	nombre = (char *)malloc((strlen(nom) + 1) * sizeof(char));
	if (nombre == NULL)
	{
		printf("Error al asignar memoria para el nombre.\n");
		return -1; // Error si no se pudo asignar memoria
	}
	strcpy(nombre, nom); // Copiar la cadena le�da en nombre

	printf("Precio: ");
	fflush(stdin);
	scanf("%f", &precio);

	printf("Tipo: ");
	fflush(stdin);
	fgets(tip, 25, stdin);
	tip[strcspn(tip, "\n")] = '\0';
	// Asignar memoria din�mica para el tipo seg�n la longitud
	tipo = (char *)malloc((strlen(tip) + 1) * sizeof(char));
	if (tipo == NULL)
	{
		printf("Error al asignar memoria para el tipo.\n");
		return -1; // Error si no se pudo asignar memoria
	}
	strcpy(tipo, tip); // Copiar la cadena le�da en tipo

	if (strcmp(tipo, "Bebida\n"))
	{
		printf("\nTamaño: ");
		fgets(tam, MAX_LENGTH, stdin);
		tamanyo = (char *)malloc((strlen(tam) + 1) * sizeof(char));
		tam[strcspn(tam, "\n")] = '\0';
		strcpy(tamanyo, tam);
	}
	else
	{
		printf("\nAlergenos: ");
		fgets(alg, MAX_LENGTH, stdin);
		alergenos = (char *)malloc((strlen(alg) + 1) * sizeof(char));
		alg[strcspn(alg, "\n")] = '\0';
		strcpy(alergenos, alg);
	}

	updateProductos(id_pr, nombre, precio, tipo, tamanyo, alergenos, CLIENT_DB_PATH);
	return 0;
}
