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

Restaurante::Restaurante(){
	this->id = 0;
	this->nombre = "";
	this->ciudad = "";
}

Restaurante::Restaurante(int id, const char* nombre, const char* ciudad){
	this-> id = id;

	this->nombre = new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);

	this->ciudad = new char[strlen(ciudad)+1];
	strcpy(this->ciudad, ciudad);
}

Restaurante::~Restaurante(){
	delete[] this->ciudad;

	delete[] this->nombre;
}

int Restaurante::getId(){
	return this->id;
}

const char* Restaurante::getNombre(){
	return this->nombre;
}

const char* Restaurante::getCiudad(){
	return this->ciudad;
}

void Restaurante::setId(int id){
	this->id;
}

void Restaurante::setNombre(const char* nombre){
	delete[] this-> nombre;
	this->nombre = new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);

}

void Restaurante::setCiudad(const char* ciudad){
	delete[] this->ciudad;
	this->ciudad = new char[strlen(ciudad)+1];
	strcpy(this->ciudad, ciudad);
}
