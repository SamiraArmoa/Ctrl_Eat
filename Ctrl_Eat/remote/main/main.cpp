/*
 * main.cpp
 *
 *  Created on: 29 may 2025
 *      Author: aroa.i.m
 */
#include <iostream>
using namespace std;

int bienvenida() {
	int opcion;
	cout << "BIENVENIDO";
	cout << "Elije una opcion: " << endl;
	cout << "1. Iniciar Sesion" << endl;
	cout << "2. Registrarse" << endl;
	cout << "3. Salir" << endl;
	cin >> opcion;
	cout << "Respuesta: " << opcion;

	return 0;
}

void iniciarSesion() {
	char email[30];
	char contrasena[30];

	cout << "Iniciar Sesion" << endl;
	cout << "Email: ";
	cin >> email;
	cout << "Contrasena: ";
	cin >> contrasena;
	cout << "Pulsa enter para continuar";
}

void registrarse() {
	char nombre[30];
	char email[30];
	char contrasena[30];
	char confirmacionContrasena[30];
	unsigned int telefono;

	cout << "Registrarse" << endl;
	cout << "Nombre: ";
	cin >> nombre;
	cout << "Email: ";
	cin >> email;
	cout << "Contrasena: ";
	cin >> contrasena;
	cout << "Confirmar contrasena: ";
	cin >> confirmacionContrasena;
	cout << "Telefono: ";
	cin >> telefono;
	cout << "Pulsa enter para continuar";
}

int pantallaInicio() {
	int opcion;
	cout << "Hola";
	cout << "Elije una opcion: " << endl;
	cout << "1. Hacer pedido" << endl;
	cout << "2. Editar perfil" << endl;
	cout << "3. Ver historial de pedidos" << endl;
	cout << "4. Cerrar sesion" << endl;
	cin >> opcion;
	cout << "Respuesta: " << opcion;

	return 0;
}

int elegirRestaurante(){
	int opcion;
	cout << "Selecciona un restaurante: " << endl;
	cout << "1. Ctrl + Madrid" << endl;
	cout << "2. Ctrl + Barcelona" << endl;
	cout << "3. Ctrl + Bilbao" << endl;
	cout << "4. Ctrl + Malaga" << endl;
	cout << "5. Ctrl + Sevilla" << endl;
	cout << "6. Ctrl + Zaragoza" << endl;
	cout << "7. Ctrl + Granada" << endl;
	cout << "8. Ctrl + Murcia" << endl;
	cout << "9. Ctrl + Alicante" << endl;
	cin >> opcion;
	cout << "Respuesta: " << opcion;

	return 0;
}

int pedido(){
	int opcion;
	cout << "Pedido" << endl;
	cout << "1. Ensalada cesar" << endl;
	cout << "2. Pollo a la brasa" << endl;
	cout << "3. Tacos al paston" << endl;
	cout << "4. Jugo natural" << endl;
	cout << "5. Sopa de cebolla" << endl;
	cout << "6. Continuar" << endl;
	cin >> opcion;
	cout << "Respuesta: " << opcion;

	return 0;
}

int pagarPedido(){
	int opcion;
	cout << "El importe total es de : " << endl;
	cout << "Elige una opcion:" << endl;
	cout << "1. Pagar" << endl;
	cout << "2. Cancelar" << endl;
	cin >> opcion;
	cout << "Respuesta" << opcion;

	return 0;
}

void editarPerfil() {
	char nombre[30];
	char email[30];
	char contrasena[30];
	unsigned int telefono;

	cout << "Editar perfil";
	cout << "Nombre: ";
	cin >> nombre;
	cout << "Email: ";
	cin >> email;
	cout << "Contrasena: ";
	cin >> contrasena;
	cout << "Telefono: ";
	cin >> telefono;
	cout << "Pulsa enter para continuar";
}

void datosPedido(){
//TODO:
}

void historialDePedido(){
//TODO:
}



int main() {
	int status = 0;
//	status = bienvenida();
//	iniciarSesion();
//	registrarse();
//	status = pantallaInicio();
//	editarPerfil();
//	historialDePedido();
//	status = elegirRestaurante();
//	status = pedido();
	status = pagarPedido();
}
