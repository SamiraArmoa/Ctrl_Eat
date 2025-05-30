/*
 * Bebida.cpp
 *
 *  Created on: 30 may 2025
 *      Author: oier.artabe
 */

#include "Bebida.h"
#include <iostream>
#include <cstring>
using namespace std;


// Constructor por defecto
Bebida::Bebida() : Producto(), tamanio(nullptr) {}

Bebida::Bebida(int id, const char*& nombre, int precio, const char* tamanio)
    : Producto(id, nombre, precio), tamanio(tamanio) {}

Bebida::~Bebida() {}Usuario::~Usuario() {
    delete[] tamanio;
}
const char* Bebida::getTamanio() const {
    return tamanio;
}

void Bebida::setTamanio(const char*& tamanio) {
    this->tamanio = tamanio;
}


