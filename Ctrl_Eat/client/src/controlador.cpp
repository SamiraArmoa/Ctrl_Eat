/*
 * controlador.cpp
 *
 *  Created on: 20 jun 2025
 *      Author: aroa.i.m
 */

#include "controlador.h"
#include "clientSocket.h"
using namespace std;

int controlador::registrarseControlador(Usuario &u) {
	char *registrar;
	registrar = registerSocket(u.getNombre(), u.getContrasena(), u.getEmail(),
			u.getTelefono());
	int res = atoi(enviarSocket(registrar));

	cout << "Respuesta desde el controlador: " << res << endl;

//	Devuelvo el id
	int id = iniciarSesionControlador(u);
	return id;
}

int controlador::iniciarSesionControlador(Usuario &u) {
	char *login;
	login = loginSocket(u.getNombre(), u.getContrasena());
	int res = atoi(enviarSocket(login));

	cout << "Respuesta desde el controladora: " << res << endl;
	return (res * -1); // Si no es 0, existe
}

const char* controlador::obtenerRestauranteControlador() {
	char *restaurantes;
	restaurantes = restaurantesSocket();
	const char* res = enviarSocket(restaurantes);
	cout << res <<endl;

	return "";

}

