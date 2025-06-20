/*
 * controlador.cpp
 *
 *  Created on: 20 jun 2025
 *      Author: aroa.i.m
 */

#include "controlador.h"
#include "clientSocket.h"
using namespace std;

void controlador::registrarseControlador(Usuario &u) {
	char *registrar;
	registrar = registerSocket(u.getNombre(),u.getContrasena(),u.getEmail(),u.getTelefono());
	enviarSocket(registrar);

	cout<<"Respuesta desde el controlador: " << registrar <<endl;
}

int controlador::iniciarSesionControlador(Usuario &u){
	char *login;
	login = loginSocket(u.getNombre(), u.getContrasena());
	int res = enviarSocket(login);

	cout<<"Respuesta desde el controlador: " << login <<endl;
	return res;
}


