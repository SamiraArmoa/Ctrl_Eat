#ifndef PRODUCTOS_H
#define PRODUCTOS_C

typedef struct{
	int id;
	char* nombre;
	char* tipo;
	float precio;
}Producto;

int crearProductos();
int verProductos();
int eliminarProductos();
int actualizarProductos();
#endif
