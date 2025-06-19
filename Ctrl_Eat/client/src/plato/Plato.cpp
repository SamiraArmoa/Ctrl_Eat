/*
 * Bebida.cpp
 *
 *  Created on: 30 may 2025
 *      Author: oihanb
 */

#include "Plato.h"
#include <cstring>
#include <iostream>
using namesapce std;

Plato::Plato() : Producto(), alergenos(nullptr) {}

Plato::Plato(int id, const char*& nombre, int precio, const char* alergenos)
    : Producto(id, nombre, precio),alergenos(alergenos) {}

Plato::~Plato() {}

const char* Plato::getAlergenos() const {
    return alergenos;
}

void Plato::setAlergenos(const char* alergenos) {
    this-> alergenos= alergenos;
}



