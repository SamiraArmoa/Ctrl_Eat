/*
 * Producto.h
 *
 *  Created on: 30 may 2025
 *      Author: oier.artabe
 */

#ifndef CTRL_EAT_REMOTE_SRC_PRODUCTO_PRODUCTO_H_
#define CTRL_EAT_REMOTE_SRC_PRODUCTO_PRODUCTO_H_

class Producto {
private:
	int id;
	const char* nombre;
	int precio;
	const char* tipo;

public:

	Producto();

	Producto(int id, const const char*& nombre, int precio, const const char*& tipo);

	~Producto();

	int getId() const;
	const char* getNombre() const;
	int getPrecio() const;
	const char* getTipo() const;

	void setId(int id);
	void setNombre(const char*& nombre);
	void setPrecio(int precio);
	void setTipo(const char*& tipo);

	void mostrar() const;
};

#endif /* CTRL_EAT_REMOTE_SRC_PRODUCTO_PRODUCTO_H_ */
