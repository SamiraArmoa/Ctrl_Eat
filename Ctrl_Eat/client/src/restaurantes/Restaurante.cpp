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

Restaurante::Restaurante()
{
	this->id = 0;
	this->nombre = new char[1];
	this->nombre[0] = '\0';
	this->ciudad = new char[1];
	this->ciudad[0] = '\0';
}

Restaurante::Restaurante(int id, const char *nombre, const char *ciudad)
{
	this->id = id;

	this->nombre = new char[strlen(nombre) + 1];
	strcpy(this->nombre, nombre);

	this->ciudad = new char[strlen(ciudad) + 1];
	strcpy(this->ciudad, ciudad);
}

// Constructor de copia
Restaurante::Restaurante(const Restaurante &other)
{
	this->id = other.id;

	this->nombre = new char[strlen(other.nombre) + 1];
	strcpy(this->nombre, other.nombre);

	this->ciudad = new char[strlen(other.ciudad) + 1];
	strcpy(this->ciudad, other.ciudad);
}

// Operador de asignación
Restaurante &Restaurante::operator=(const Restaurante &other)
{
	if (this != &other)
	{ // Evitar auto-asignación
		// Liberar memoria existente
		delete[] this->nombre;
		delete[] this->ciudad;

		// Copiar datos
		this->id = other.id;

		this->nombre = new char[strlen(other.nombre) + 1];
		strcpy(this->nombre, other.nombre);

		this->ciudad = new char[strlen(other.ciudad) + 1];
		strcpy(this->ciudad, other.ciudad);
	}
	return *this;
}

Restaurante::~Restaurante()
{
	delete[] this->ciudad;
	delete[] this->nombre;
}

int Restaurante::getId() const
{
	return this->id;
}

const char *Restaurante::getNombre() const
{
	return this->nombre;
}

const char *Restaurante::getCiudad() const
{
	return this->ciudad;
}

void Restaurante::setId(int id)
{
	this->id = id;
}

void Restaurante::setNombre(const char *nombre)
{
	delete[] this->nombre;
	this->nombre = new char[strlen(nombre) + 1];
	strcpy(this->nombre, nombre);
}

void Restaurante::setCiudad(const char *ciudad)
{
	delete[] this->ciudad;
	this->ciudad = new char[strlen(ciudad) + 1];
	strcpy(this->ciudad, ciudad);
}
