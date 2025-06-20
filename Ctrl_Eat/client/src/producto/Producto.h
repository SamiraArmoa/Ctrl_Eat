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
    char* nombre;
    int precio;

public:
    Producto();
    Producto(int id, const char* nombre, int precio);
    ~Producto();

    int getId() const;
    const char* getNombre() const;
    int getPrecio() const;

    void setId(int id);
    void setNombre(const char* nombre);
    void setPrecio(int precio);
    void mostrar() const;
};

#endif /* CTRL_EAT_REMOTE_SRC_PRODUCTO_PRODUCTO_H_ */
