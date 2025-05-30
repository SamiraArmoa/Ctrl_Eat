/*
* Pedidos.cpp
*
*  Created on: 30 may 2025
*      Author: s.armoa
*/

#include "Pedidos.h"
#include "string.h"
Pedidos::Pedidos() {
	id = 0;
	fechaEntrega = "00/00/0000";
	fechaPedido = "00/00/0000";
	domicilio = "Desconocido";
	idCliente = 0;
	idRestaurante = 0;

}
Pedidos::Pedidos(int id, const char* fechaEntrega, const char* fechaPedido, const char* domicilio, int idCliente, int idRestaurante) {
	this->id = id;
	this->idCliente = idCliente;
	this->idRestaurante = idRestaurante;
	setFechaEntrega(fechaEntrega);
	setFechaPedido(fechaPedido);
	setDomicilio(domicilio);
}

Pedidos::~Pedidos() {
	delete[] fechaEntrega;
	delete[] fechaPedido;
	delete[] domicilio;
}
// Getters
int Pedidos::getId() {
	return id;
}

const char* Pedidos::getFechaEntrega() {
	return fechaEntrega;
}

const char* Pedidos::getFechaPedido() {
	return fechaPedido;
}

const char* Pedidos::getDomicilio() {
	return domicilio;
}

int Pedidos::getIdCliente() {
	return idCliente;
}

int Pedidos::getIdRestaurante() {
	return idRestaurante;
}

// Setters
void Pedidos::setId(int id) {
	this->id = id;
}

void Pedidos::setFechaEntrega(const char* fechaEntrega) {
	delete[] this->fechaEntrega;
	this->fechaEntrega = new char[strlen(fechaEntrega) + 1];
	strcpy((char*)this->fechaEntrega, fechaEntrega);
}

void Pedidos::setFechaPedido(const char* fechaPedido) {
	delete[] this->fechaPedido;
	this->fechaPedido = new char[strlen(fechaPedido) + 1];
	strcpy((char*)this->fechaPedido, fechaPedido);
}

void Pedidos::setDomicilio(const char* domicilio) {
	delete[] this->domicilio;
	this->domicilio = new char[strlen(domicilio) + 1];
	strcpy((char*)this->domicilio, domicilio);
}

void Pedidos::setIdCliente(int idCliente) {
	this->idCliente = idCliente;
}

void Pedidos::setIdRestaurante(int idRestaurante) {
	this->idRestaurante = idRestaurante;
}
