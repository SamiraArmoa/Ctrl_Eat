/*
 * User.cpp
 *
 *  Created on: 29 may 2025
 *      Author: s.armoa
 */

#include "Restaurante.h"
#include <iostream>
using namespace std;
#include "string.h"

Restaurante::Restaurante() {
	id = 12345;
	nombre = "Ctrl_Murcia";
	ciudad = "Murcia";
}

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

