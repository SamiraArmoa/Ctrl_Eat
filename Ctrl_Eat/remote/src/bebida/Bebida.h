/*
 * Bebida.h
 *
 *  Created on: 30 may 2025
 *      Author: oier.artabe
 */

#ifndef REMOTE_SRC_BEBIDA_BEBIDA_H_
#define REMOTE_SRC_BEBIDA_BEBIDA_H_

#include "../producto/Producto.h"  // Asegúrate de que esta ruta sea correcta

class Bebida : public Producto {
private:
    const char* tamanio;

public:
    Bebida();  // Constructor por defecto
    Bebida(int id, const char*& nombre, int precio, const char* tamanio);  // Constructor con herencia
    ~Bebida();

    const char* getTamanio() const;
    void setTamanio(const char*& tamanio);
};

#endif /* REMOTE_SRC_BEBIDA_BEBIDA_H_ */
