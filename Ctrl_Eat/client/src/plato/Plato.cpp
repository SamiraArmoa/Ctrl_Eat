/*
 * Bebida.cpp
 *
 *  Created on: 30 may 2025
 *      Author: oihanb
 */

#include "Plato.h"
#include <string.h>
#include <iostream>
#include "../producto/Producto.h"
using namespace std;

Plato::Plato():Producto(){
	this->alergenos = "";
}

Plato::Plato(int id, const char* nombre, int precio, const char* alergenos):Producto(id, nombre, precio){
	this->alergenos = new char[strlen(alergenos)+1];
	strcpy(this->alergenos, alergenos);
}

Plato::~Plato(){
	delete[] this->alergenos;
}

const char* Plato::getAlergenos() const{
	return this->alergenos;
}

void Plato::setAlergenos(const char* alergenos){
	delete[] this->alergenos;
	this->alergenos = new char[strlen(alergenos)+1];
	strcpy(this->alergenos, alergenos);
}


