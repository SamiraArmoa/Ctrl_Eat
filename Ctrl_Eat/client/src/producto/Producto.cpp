/*
 * Producto.cpp
 *
 *  Created on: 20 jun 2025
 *      Author: aroa.i.m
 */

#include "Producto.h"
#include <iostream>
#include <string.h>
using namespace std;

Producto::Producto(){
	this->id = 0;
	this->nombre = "";
	this->precio = 0;
}

Producto::Producto(int id, const char* nombre, int precio){
	this->id = id;
	this->nombre = new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);
	this -> precio = precio;
}

Producto::~Producto(){
	delete[] this->nombre;
}

int Producto::getId() const{
	return this->id;
}

const char* Producto::getNombre() const{
	return this->nombre;
}

int Producto::getPrecio() const{
	return this->precio;
}

void Producto::setId(int id){
	this->id = id;
}

void Producto::setNombre(const char* nombre){
	delete [] this-> nombre;
	this->nombre = new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);
}

void Producto::setPrecio(int precio){
	this->precio = precio;
}

void Producto::mostrar() const{
	cout<< "ID: " << this-> id << ", Nombre: " << this->nombre << ", Precio: " << this->precio << "$";
}