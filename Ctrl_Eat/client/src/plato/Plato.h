/*
 * Plato.h
 *
 *  Created on: 30 may 2025
 *      Author: oihan.bilbao
 */

#ifndef CTRL_EAT_REMOTE_SRC_PLATO_PLATO_H_
#define CTRL_EAT_REMOTE_SRC_PLATO_PLATO_H_

#include "../producto/Producto.h"

class Plato : public Producto {
private:
    char* alergenos;

public:
    Plato();
    Plato(int id, const char* nombre, int precio, const char* alergenos);
    ~Plato();

    const char* getAlergenos() const;
    void setAlergenos(const char* alergenos);

};

#endif
