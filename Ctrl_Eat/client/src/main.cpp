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

static Usuario usuario_actual;
int id_usuario_actual = 0;
Producto** productos = nullptr;
int num_productos = 0;

void elegirRestaurante(int &idRes);
void editarPerfil();
void historialDePedido();
void registrarse();
int bienvenida();
void cerrarSesion();
int pantallaInicio();
int pagarPedido(Producto** productosRecibidos, int num_productos);
void cargarProductos ();

void anadirProductos(Producto **&productos, int &numElementos, Producto &p) {
	Producto **nuevosProductos = new Producto*[numElementos + 1];
	for (int i = 0; i < numElementos; ++i) {
		nuevosProductos[i] = productos[i];
	}
	nuevosProductos[numElementos] = new Producto(p); // Copia del producto
	numElementos++;
	delete[] productos; // Liberar memoria del array antiguo
	productos = nuevosProductos; // Asignar el nuevo array
	cout << "Producto añadido: " << p.getNombre() << endl;
}

int hacerPedido() {
//	cout << "DEBUG: Iniciando hacerPedido()" << endl;
	int idRes = 0;
	elegirRestaurante(idRes);
	cargarProductos();
	Producto** listaProductos = nullptr;
	int numProductos = 0;

	cout << "Imprimiendo productos" << endl;
	int idProducto = 0;
	while (idProducto != -1) {
		for (int i = 0; i < num_productos; ++i) {
		productos[i]->mostrar();
	}
		cout << "Selecciona un producto (0 para salir): ";
		cin >> idProducto;

		if (idProducto == 0) {
			break;
		}
		Producto p = controlador::obtenerProductoPorId(idProducto);
		// cout << "DEBUG: Producto obtenido con ID " << p.getId() << ", " << p.getNombre() << endl;
		if (p.getId() != 0) { // Si el producto existe
			anadirProductos(listaProductos, numProductos, p);
		} else {
			cout << "Producto no encontrado." << endl;
		}
	}
	// Productos seleccionados
	cout << "\nProductos seleccionados:" << endl;
	for (int i = 0; i < numProductos; ++i) {
		listaProductos[i]->mostrar();
		cout << endl;
	}

	int respuesta = pagarPedido(listaProductos, numProductos);
	if (respuesta == 1) {
		cout << "Pedido pagado correctamente." << endl;
		Pedido pedido = Pedido(0, "Domicilio de prueba", id_usuario_actual, idRes);
		controlador::hacerPedidoControlador(pedido, listaProductos, numProductos);
		// Aquí se podría guardar el pedido en la base de datos
	} else if (respuesta == 2) {
		cout << "Pedido cancelado." << endl;
	} else {
		cout << "Opción no válida." << endl;
	}
	pantallaInicio(); // Volver a la pantalla de inicio
}


void elegirRestaurante(int &idRes) {
//	cout << "DEBUG: Iniciando elegirRestaurante()" << endl;
	// Obtener lista de restaurantes como array dinámico
	int numRestaurantes = 0;
	Restaurante **listaRestaurantes =
			controlador::obtenerListaRestaurantesControlador(numRestaurantes);
//	cout << "DEBUG: Lista obtenida, tamaño: " << numRestaurantes << endl;

	if (listaRestaurantes == nullptr || numRestaurantes == 0) {
		cout << "No hay restaurantes disponibles." << endl;
		return;
	}

	// Mostrar los restaurantes
	cout << "\nRestaurantes disponibles:" << endl;
	for (int i = 0; i < numRestaurantes; i++) {
		cout << listaRestaurantes[i]->getId() << ". "
				<< listaRestaurantes[i]->getNombre() << " - "
				<< listaRestaurantes[i]->getCiudad() << endl;
	}

	//  Pedir id y asignarselo al parámetro por referencia
	cout << "\nIntroduce el id del restaurante: ";
	cin >> idRes;

	// Liberar memoria del array
	for (int i = 0; i < numRestaurantes; i++) {
		delete listaRestaurantes[i];
	}
	delete[] listaRestaurantes;
}

void cargarProductos () {
	productos = controlador::obtenerListaProductosControlador(num_productos);
}

void editarPerfil() {
	char nombre[30];
	char email[30];
	char contrasena[30];
	unsigned int telefono;

	cout << "Editar perfil" << endl;
	cout << "Nombre: ";
	cin >> nombre;
	cout << "Email: ";
	cin >> email;
	cout << "Contrasena: ";
	cin >> contrasena;
	cout << "Telefono: ";
	cin >> telefono;
	cout << "Pulsa enter para continuar";

	Usuario u = Usuario(id_usuario_actual, nombre, email, telefono, contrasena);
	int codigo = controlador::editarPerfilControlador(u);

	if (codigo == 0) {
		cout << "Error al actualizar el usuario" << endl;
		editarPerfil();
	} else {
		cout << "El usuario se ha actualizado correctamente" << endl;
		usuario_actual = u;
		pantallaInicio();
	}

}

void iniciarSesion() {
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

	if (id != 0) {
		id_usuario_actual = id;
		usuario_actual = u;
		pantallaInicio();
	} else {
		cout << "Usuario/Password no es valido" << endl;
		iniciarSesion();
	}
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

	while (strcmp(contrasena, confirmacionContrasena) != 0) {
		cout << "La contrasena no es la misma, vuelve a intentarlo" << endl;
		cout << "Confirmar contrasena: ";
		cin >> confirmacionContrasena;
	}

	cout << "Telefono: ";
	cin >> telefono;

	Usuario u = Usuario(1, nombre, email, telefono, contrasena);

	int id = controlador::registrarseControlador(u);
//	cout << "Id Main: " << id << endl;
	if (id == 0) {
		cout << "Error al crear el usuario" << endl;
		registrarse();
	} else {
		id_usuario_actual = id;
		usuario_actual = Usuario(email, contrasena);
		pantallaInicio();
	}
}

int bienvenida() {
	int opcion;
	cout << "BIENVENIDO" << endl;
	cout << "Elije una opcion: " << endl;
	cout << "1. Iniciar Sesion" << endl;
	cout << "2. Registrarse" << endl;
	cout << "3. Salir" << endl;
	cin >> opcion;

	switch (opcion) {
	case 1:
		iniciarSesion();
		break;
	case 2:
		registrarse();
		break;
	default:
		cout << "Saliendo del programa..." << endl;
		id_usuario_actual = 0;
		break;
	}

	return 0;
}

void cerrarSesion() {
	id_usuario_actual = 0;
	bienvenida();
}

int pantallaInicio() {
	int opcion;
	cout << "Hola " << usuario_actual.getEmail() << endl;
	cout << "Elige una opcion: " << endl;
	cout << "1. Hacer pedido" << endl;
	cout << "2. Editar perfil" << endl;
	cout << "3. Ver historial de pedidos" << endl;
	cout << "4. Cerrar sesion" << endl;
	cin >> opcion;

	switch (opcion) {
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

int pagarPedido(Producto** productosRecibidos, int num_productos) {
//	cout << "DEBUG: Iniciando pagarPedido()" << endl;
	// Calcular el importe total
	int total = 0;
	for (int i = 0; i < num_productos; ++i) {
		total += productosRecibidos[i]->getPrecio();
	}

	int opcion;
	cout << "El importe total es de : " << total << "$" << endl;
	cout << "Elige una opcion:" << endl;
	cout << "1. Pagar" << endl;
	cout << "2. Cancelar" << endl;
	cin >> opcion;
	// cout << "Respuesta" << opcion << endl;

	if (opcion == 1) {
		cout << "Pedido pagado correctamente." << endl;
		return 1; // Pedido pagado
	} else if (opcion == 2) {
		cout << "Pedido cancelado." << endl;
	}	

	return 0;
}

void historialDePedido() {
	Pedido **listaPedidos = nullptr;
	int numPedidos = 0;
	listaPedidos = controlador::obtenerHistorialPedidosControlador(id_usuario_actual, numPedidos);
	if (listaPedidos == nullptr || numPedidos == 0) {
		cout << "No hay pedidos en el historial." << endl;
		return;
	}
	cout << "Historial de pedidos:" << endl;
	for (int i = 0; i < numPedidos; i++) {
		cout << "Pedido " << listaPedidos[i]->getId() << ": Domicilio: " << listaPedidos[i]->getDomicilio()
				<< ", Restaurante: " << controlador::obtenerRestaurantePorId(listaPedidos[i]->getIdRestaurante()).getNombre() << endl;

		int numIdsProducto = 0;
		int **idsProductos = controlador::obtenerIdsProductosPedido(listaPedidos[i]->getId(), numIdsProducto);

		if (idsProductos == nullptr || numIdsProducto == 0) {
			cout << "No hay productos en este pedido." << endl;
			continue;
		}

		cout << "\t- Productos en el pedido:" << endl;
		for (int j = 0; j < numIdsProducto; j++) {
			Producto p = controlador::obtenerProductoPorId(*idsProductos[j]);
			if (p.getId() != 0) { // Si el producto existe
				cout << "\t\t- "  << p.getNombre() << ", Precio: " << p.getPrecio() << "$" << endl;
			} else {
				cout << "Producto con ID " << *idsProductos[j] << " no encontrado." << endl;
			}
		}
		// Liberar memoria de los ids de productos
		for (int j = 0; j < numIdsProducto; j++) {
			delete idsProductos[j];
		}
		delete[] idsProductos;
		cout << endl;
	}
	// Liberar memoria del array
	for (int i = 0; i < numPedidos; i++) {
		delete listaPedidos[i];
	}
	delete[] listaPedidos;
}

int main() {
	bienvenida();
}
