/*
 * Producto.cpp
 *
 *  Created on: 30 may 2025
 *      Author: oier.artabe
 */

#include "Producto.h"
#include <iostream>
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
int Producto::getId(){
return id;
}

// Setters
void Producto::setId(int id) { this->id = id; }
void Producto::setNombre(const std::string& nombre) { this->nombre = nombre; }
void Producto::setPrecio(int precio) { this->precio = precio; }
void Producto::setTipo(const std::string& tipo) { this->tipo = tipo; }

// Método para mostrar la información del producto
void Producto::mostrar() const {
    std::cout << "ID: " << id << ", Nombre: " << nombre
              << ", Precio: " << precio << ", Tipo: " << tipo << std::endl;
}

/*
Restaurante::Restaurante(int id, const char *nombre, const char *ciudad) {
this->id = id;
setNombre(nombre);
setCiudad(ciudad);
}

virtual Restaurante::~Restaurante() {
delete[] nombre;
delete[] ciudad;
}

// Getters
int Restaurante::getId() {
return id;
}

const char* Restaurante::getNombre() {
return nombre;
}

const char* Restaurante::getCiudad() {
return ciudad;
}

// Setters
void Restaurante::setId(int id) {
this->id = id;
}

void Restaurante::setNombre(const char *nombre) {
delete[] this->nombre;

this->nombre = new char[strlen(nombre) + 1];
strcpy((char*)this->nombre, nombre);
}

void Restaurante::setCiudad(const char *ciudad) {
delete[] this->ciudad;

this->ciudad = new char[strlen(ciudad) + 1];
strcpy((char*)this->ciudad, ciudad);
}
*/
