/*
* Pedidos.cpp
*
*  Created on: 30 may 2025
*      Author: s.armoa
*/

#include "Pedido.h"
#include "string.h"

Pedido::Pedido() {
	this->id = 0;
	this->domicilio = "";
	this->idCliente = 0;
	this->idRestaurante = 0;
}

Pedido::Pedido(int id, const char* domicilio, int idCliente, int idRestaurante) {
	this->id = id;
	this->idCliente = idCliente;
	this->idRestaurante = idRestaurante;

	this->domicilio = new char[strlen(domicilio) + 1];
	strcpy(this->domicilio, domicilio);
}

Pedido::~Pedido() {
	delete[] domicilio;
}
// Getters
int Pedido::getId() {
	return this->id;
}

const char* Pedido::getDomicilio() {
	return this->domicilio;
}

int Pedido::getIdCliente() {
	return this->idCliente;
}

int Pedido::getIdRestaurante() {
	return this->idRestaurante;
}

// Setters
void Pedido::setId(int id) {
	this->id = id;
}

void Pedido::setDomicilio(const char* domicilio) {
	delete[] this->domicilio;
	this->domicilio = new char[strlen(domicilio) + 1];
	strcpy(this->domicilio, domicilio);
}

void Pedido::setIdCliente(int idCliente) {
	this->idCliente = idCliente;
}

void Pedido::setIdRestaurante(int idRestaurante) {
	this->idRestaurante = idRestaurante;
}
