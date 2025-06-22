/*
 * main.cpp
 *
 *  Created on: 29 may 2025
 *      Author: aroa.i.m
 */
#include <iostream>
#include "usuario/Usuario.h"
#include "clientSocket.h"
#include "../src/producto/producto.h"
#include "../src/restaurantes/Restaurante.h"
#include "clientSocket.h"
#include "controlador.h"
#include <string.h>

#include "../src/pedido/Pedido.h"
using namespace std;

static Usuario usuario;
int id_usuario_actual = 0;

void datosPedido();
int pagarPedido(Pedido &pedido);
int hacerPedido(Pedido &pedido);
void elegirRestaurante(int &idRes);
void elegirProductos();
void editarPerfil();
void historialDePedido();
void registrarse();
int bienvenida();
void cerrarSesion();
int pantallaInicio();
int pedido();
int pagarPedido();

int pagarPedido(Pedido &pedido)
{
	int opcion;
	cout << "El importe total es de : " << endl;
	cout << "Elige una opcion:" << endl;
	cout << "1. Pagar" << endl;
	cout << "2. Cancelar" << endl;
	cin >> opcion;

	return opcion;
}

void anadirProductos(int nuevoID, const char* nombre, int precio, Producto**& productos, int& numElementos) {
    Producto** productosCopia = new Producto*[numElementos + 1];

    for (int i = 0; i < numElementos; ++i) {
        productosCopia[i] = productos[i];
    }

    productosCopia[numElementos] = new Producto(nuevoID, nombre, precio);
    numElementos++;

    delete[] productos;
    productos = productosCopia;
}

int hacerPedido()
{
//	cout << "DEBUG: Iniciando hacerPedido()" << endl;
	int idRes = 0;
	elegirRestaurante(idRes);
	// elegirProductos();

	//	pagarPedido(pedido);
}

void elegirRestaurante(int &idRes)
{
//	cout << "DEBUG: Iniciando elegirRestaurante()" << endl;
	// Obtener lista de restaurantes como array dinámico
	int numRestaurantes = 0;
	Restaurante **listaRestaurantes = controlador::obtenerListaRestaurantesControlador(numRestaurantes);
//	cout << "DEBUG: Lista obtenida, tamaño: " << numRestaurantes << endl;

	if (listaRestaurantes == nullptr || numRestaurantes == 0)
	{
		cout << "No hay restaurantes disponibles." << endl;
		return;
	}

	// Mostrar los restaurantes
	cout << "\nRestaurantes disponibles:" << endl;
	for (int i = 0; i < numRestaurantes; i++)
	{
		cout << listaRestaurantes[i]->getId() << ". " << listaRestaurantes[i]->getNombre()
			 << " - " << listaRestaurantes[i]->getCiudad() << endl;
	}

	//  Pedir id y asignarselo al parámetro por referencia
	cout << "\nIntroduce el id del restaurante: ";
	cin >> idRes;

	// Liberar memoria del array
	for (int i = 0; i < numRestaurantes; i++)
	{
		delete listaRestaurantes[i];
	}
	delete[] listaRestaurantes;
}

void elegirProductos()
{
	int *idProductos;
	cout << "Selecciona un producto:" << endl;
	cout << "Introduce el id del producto: ";
	// cin >> idProductos;
}

void editarPerfil()
{
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

void iniciarSesion()
{
	char usuario[30];
	char contrasena[30];

	cout << "Iniciar Sesion" << endl;
	cout << "Email: ";
	cin >> usuario;
	cout << "Contrasena: ";
	cin >> contrasena;

	Usuario u = Usuario(usuario, contrasena);
	int id = controlador::iniciarSesionControlador(u);
	cout << "Id: " << id << endl;

	if (id != 0)
	{
		id_usuario_actual = id;
		pantallaInicio();
	}
	else
	{
		cout << "Usuario/Password no es valido" << endl;
		iniciarSesion();
	}
}

void registrarse()
{
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

	while (strcmp(contrasena, confirmacionContrasena) != 0)
	{
		cout << "La contrasena no es la misma, vuelve a intentarlo" << endl;
		cout << "Confirmar contrasena: ";
		cin >> confirmacionContrasena;
	}

	cout << "Telefono: ";
	cin >> telefono;

	Usuario u = Usuario(1, nombre, email, telefono, contrasena);

	int id = controlador::registrarseControlador(u);
	cout << "Id Main: " << id << endl;
	if (id == 0)
	{
		cout << "Error al crear el usuario" << endl;
		registrarse();
	}
	else
	{
		id_usuario_actual = id;
		pantallaInicio();
	}
}

int bienvenida()
{
	int opcion;
	cout << "BIENVENIDO" << endl;
	cout << "Elije una opcion: " << endl;
	cout << "1. Iniciar Sesion" << endl;
	cout << "2. Registrarse" << endl;
	cout << "3. Salir" << endl;
	cin >> opcion;

	switch (opcion)
	{
	case 1:
		iniciarSesion();
		break;
	case 2:
		registrarse();
		break;
	default:
		id_usuario_actual = 0;
		break;
	}

	return 0;
}

void cerrarSesion()
{
	id_usuario_actual = 0;
	bienvenida();
}

int pantallaInicio()
{
	int opcion;
	cout << "Elige una opcion: " << endl;
	cout << "1. Hacer pedido" << endl;
	cout << "2. Editar perfil" << endl;
	cout << "3. Ver historial de pedidos" << endl;
	cout << "4. Cerrar sesion" << endl;
	cin >> opcion;

	switch (opcion)
	{
	case 1:
		hacerPedido();
		break;
	case 2:
		editarPerfil();
		break;
	case 3:
		historialDePedido();
		break;
	case 4:
		cerrarSesion();
		break;
	default:
		break;
	}

	return 0;
}

int pedido()
{
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

int pagarPedido()
{
	int opcion;
	cout << "El importe total es de : " << endl;
	cout << "Elige una opcion:" << endl;
	cout << "1. Pagar" << endl;
	cout << "2. Cancelar" << endl;
	cin >> opcion;
	cout << "Respuesta" << opcion;

	return 0;
}

void datosPedido()
{
	// TODO:
}

void historialDePedido()
{
	// TODO:
}

int main()
{
	id_usuario_actual = 0;
	bienvenida();
}
