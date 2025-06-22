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
	this->id = 0;
	this->nombre = "";
	this->email = "";
	this->telefono = 0;
	this->contrasena = "";
}

Usuario::Usuario(int id, const char *nombre, const char *email, int telefono, const char *contrasena) {
	this->id = id;

	this->nombre = new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);

	this->email = new char[strlen(email)+1];
	strcpy(this->email, email);

	this->telefono = telefono;

	this->contrasena = new char[strlen(contrasena)+1];
	strcpy(this->contrasena,contrasena);
}

Usuario::Usuario(const char* email, const char* contrasena){
	this->id = 0;
	this->nombre = "";
	this->telefono = 0;

	this->email = new char[strlen(email)+1];
	strcpy(this->email, email);

	this->contrasena = new char[strlen(contrasena)+1];
	strcpy(this->contrasena,contrasena);
}

Usuario::~Usuario() {
	delete[] this->nombre;
	delete[] this->email;
	delete[] this->contrasena;
}

int Usuario::getId() {
	return this->id;
}

const char* Usuario::getNombre() {
	return this->nombre;
}

const char* Usuario::getEmail() {
	return this->email;
}

int Usuario::getTelefono() {
	return this->telefono;
}

const char* Usuario::getContrasena() {
	return this->contrasena;
}

void Usuario::setId(int id) {
	this->id;
}

void Usuario::setNombre(const char *nombre) {
	delete[] this->nombre;
	this->nombre = new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);
}

void Usuario::setEmail(const char *email) {
	delete[] this->email;
	this->email = new char[strlen(email)+1];
	strcpy(this->email, email);

}

void Usuario::setTelefono(int telefono) {
	this->telefono;
}

void Usuario::setContrasena(const char *contrasena) {
	delete[] this->contrasena;
	this->contrasena = new char[strlen(contrasena)+1];
	strcpy(this->contrasena,contrasena);
}

const char* Usuario::verUsuario() {
	cout<< "ID: " << this->id <<endl;
	cout<< "Nombre: " << this-> nombre <<endl;
	cout<< "Email: " << this->email <<endl;
	cout<< "Telefono: " << this->telefono << endl;
	cout<< "Contraseña: " << this-> contrasena << endl;
}
