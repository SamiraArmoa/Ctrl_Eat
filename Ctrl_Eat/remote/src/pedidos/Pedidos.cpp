/*
* Pedidos.cpp
*
*  Created on: 30 may 2025
*      Author: s.armoa
*/

#include "Pedidos.h"
#include "string.h"
#include <vector>
using namespace std;
Pedidos::Pedidos() {
	id = 0;
	domicilio = "Desconocido";
	idCliente = 0;
	idRestaurante = 0;

}
Pedidos::Pedidos(int id, const char* domicilio, int idUsuario, int idRestaurante) {
	this->id = id;
	this->idCliente = idUsuario;
	this->idRestaurante = idRestaurante;
	setDomicilio(domicilio);
}

Pedidos::~Pedidos() {

	delete[] domicilio;
}
// Getters
int Pedidos::getId() {
	return id;
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

vector<Pedidos> Pedidos::verPedidos(const vector<Pedidos>& todos, int idCliente) {
    vector<Pedidos> resultado;

    for (const Pedidos& p : todos) {
        if (p.getIdUsuario() == idUsuario) {
            resultado.push_back(p);
        }
    }

    return resultado;
}
