/*
 * Usuario.cpp
 *
 *  Created on: 30 may 2025
 *      Author: s.armoa
 */

#include "Usuario.h"
#include <iostream>
using namespace std;
#include "string.h"

Usuario::Usuario() {
	id = 0;
	nombre = "Anonimo";
	email = "sin_email@ejemplo.com";
	telefono = 0;
	contrasena = "";
}

Usuario::Usuario(int id, const char* nombre, const char* email, int telefono, const char*contrasena){
	this->id = id;
	this->telefono = telefono;
	setContrasena(contrasena);
	setNombre(nombre);
	setEmail(email);
}
Usuario::~Usuario() {
    delete[] nombre;
    delete[] email;
    delete[] contrasena;
}

int Usuario::getId() {
    return id;
}

const char* Usuario::getNombre() {
    return nombre;
}

const char* Usuario::getEmail() {
    return email;
}

int Usuario::getTelefono() {
    return telefono;
}

const char* Usuario::getContrasena() {
    return contrasena;
}


void Usuario::setId(int id) {
    this->id = id;
}

void Usuario::setNombre(const char* nombre) {
    delete[] this->nombre;
    this->nombre = new char[strlen(nombre) + 1];
    strcpy((char*)this->nombre, nombre);
}

void Usuario::setEmail(const char* email) {
    delete[] this->email;
    this->email = new char[strlen(email) + 1];
    strcpy((char*)this->email, email);
}

void Usuario::setTelefono(int telefono) {
    this->telefono = telefono;
}

void Usuario::setContrasena(const char* contrasena) {
	delete[] this->contrasena;
	this->contrasena = new char[strlen(contrasena) + 1];
	strcpy((char*)this->contrasena,contrasena);
}
