/*
 * Producto.cpp
 *
 *  Created on: 30 may 2025
 *      Author: oier.artabe
 */

#include "Producto.h"
#include <iostream>
#include <cstring>
using namespace std;


// Constructor por defecto
Producto::Producto() : id(0), nombre(""), precio(0), tipo("") {}

// Constructor con parámetros
Producto::Producto(int id, const const char*& nombre, int precio, const const char*& tipo){
this->id = id;
setNombre(nombre);
setPrecio(precio);
setTipo(tipo);
}

virtual Producto::~Producto() {
delete[] nombre;
delete[] precio;
delete[] tipo;
}

// Destructor
Producto::~Producto() {}

// Getters
int Producto::getId(){ // @suppress("Member declaration not found")
return id;
}
const char* Producto::getNombre(){ // @suppress("No return") // @suppress("Member declaration not found")
delete[] this->nombre;
}
int Producto::getPrecio(){ // @suppress("Member declaration not found")
return precio;
}
const char* Producto::getTipo(){ // @suppress("Member declaration not found")
return tipo;
}

// Setters
void Producto::setId(int id) {
this->id = id;
}
void Producto::setNombre(const char* nombre) { // @suppress("Member declaration not found")
delete[] this->nombre;
this->nombre = new char[strlen(nombre) + 1];
strcpy((char*)this->nombre, nombre);
}
void Producto::setPrecio(int precio) {
this->precio = precio;
}
void Producto::setTipo(const char* nombre) { // @suppress("Member declaration not found")
	delete[] this->tipo;
	this->tipo = new char[strlen((char*) tipo) + 1];
	strcpy((char*)this->tipo, (char*) tipo);
}

// Método para mostrar la información del producto
void Producto::mostrar() const {
    std::cout << "ID: " << id << ", Nombre: " << nombre
              << ", Precio: " << precio << ", Tipo: " << tipo << std::endl;
}

