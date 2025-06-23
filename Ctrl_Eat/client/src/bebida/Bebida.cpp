/*
 * Bebida.cpp
 *
 *  Created on: 30 may 2025
 *      Author: oier.artabe
 */

#include "Bebida.h"
#include <iostream>
#include <cstring>
using namespace std;


Bebida::Bebida():Producto(){
	this->tamanio = "";
}
Bebida::Bebida(int id, const char* nombre, int precio, const char* tamanio):Producto(id, nombre, precio){
	this->tamanio = new char[strlen(tamanio)+1];
	strcpy(this->tamanio, tamanio);
}
Bebida::~Bebida(){
	delete[] this->tamanio;
}

const char* Bebida::getTamanio() const{
	return this->tamanio;
}

void Bebida::setTamanio(const char* tamanio){
	delete[] this->tamanio;
	this->tamanio = new char[strlen(tamanio)+1];
	strcpy(this->tamanio, tamanio);
}

void Bebida::mostrar() const{
	Producto::mostrar();
	cout<< ", Tamanio: " << this->tamanio <<endl;
}