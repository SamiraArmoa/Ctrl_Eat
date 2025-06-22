/*
 * controlador.cpp
 *
 *  Created on: 20 jun 2025
 *      Author: aroa.i.m
 */

#include "controlador.h"
#include "clientSocket.h"
#include <string.h>
#include <sstream>
using namespace std;

int controlador::registrarseControlador(Usuario &u)
{
	char *registrar;
	registrar = registerSocket(u.getNombre(), u.getContrasena(), u.getEmail(),
							   u.getTelefono());
	int res = atoi(enviarSocket(registrar));

	cout << "Respuesta desde el controlador: " << res << endl;

	//	Devuelvo el id
	int id = iniciarSesionControlador(u);
	return id;
}

int controlador::iniciarSesionControlador(Usuario &u)
{
	char *login;
	login = loginSocket(u.getEmail(), u.getContrasena());
	int res = atoi(enviarSocket(login));

	cout << "Respuesta desde el controladora: " << res << endl;
	return (res * -1); // Si no es 0, existe
}

int controlador::editarPerfilControlador(Usuario &u){
	char* update;
	update = updateUsuarioSocket(u.getId(),u.getNombre(), u.getContrasena(), u.getEmail(), u.getTelefono());
	int res = atoi(enviarSocket(update));

	cout<< "Respuesta desde el controlador" << res << endl;
	return res; // Si res == 1, actualizado correctamente
}

const char *controlador::obtenerRestaurantesControlador()
{
	char *restaurantes = restaurantesSocket();	  // "4"
	const char *res = enviarSocket(restaurantes); // respuesta del servidor
	delete[] restaurantes;						  // liberar memoria

	if (res == nullptr || strlen(res) == 0)
	{
		std::cerr << "No se recibieron datos de restaurantes." << std::endl;
		return "";
	}

	// La respuesta del servidor ya viene formateada correctamente
	// Solo necesitamos imprimirla directamente
	std::cout << res << std::endl;

	return res;
}

Restaurante **controlador::obtenerListaRestaurantesControlador(int &numRestaurantes)
{
//	std::cout << "DEBUG: Iniciando obtenerListaRestaurantesControlador()" << std::endl;
	numRestaurantes = 0;

	char *restaurantes = restaurantesSocket(); // "4"
//	std::cout << "DEBUG: Mensaje a enviar: " << restaurantes << std::endl;
	const char *res = enviarSocket(restaurantes); // respuesta del servidor
	delete[] restaurantes;						  // liberar memoria

//	std::cout << "DEBUG: Respuesta recibida: [" << (res ? res : "NULL") << "]" << std::endl;

	if (res == nullptr || strlen(res) == 0)
	{
		std::cerr << "No se recibieron datos de restaurantes." << std::endl;
		return nullptr; // devolver null
	}

	// Primero contar cuántos restaurantes hay
	std::string respuesta(res);
	std::istringstream stream(respuesta);
	std::string linea;
	int contador = 0;

	while (std::getline(stream, linea))
	{
		if (!linea.empty() && linea.find('.') != std::string::npos &&
			linea.find("Nombre:") != std::string::npos &&
			linea.find("Ciudad:") != std::string::npos)
		{
			contador++;
		}
	}

//	std::cout << "DEBUG: Total de restaurantes encontrados: " << contador << std::endl;

	if (contador == 0)
	{
		return nullptr;
	}

	// Crear el array dinámico
	Restaurante **listaRestaurantes = new Restaurante *[contador];
	numRestaurantes = contador;
	int indice = 0;

	// Reiniciar el stream para parsear
	std::istringstream stream2(respuesta);

	while (std::getline(stream2, linea) && indice < contador)
	{
//		std::cout << "DEBUG: Procesando línea: [" << linea << "]" << std::endl;

		if (linea.empty())
			continue; // saltar líneas vacías

		// Buscar el patrón de ID, nombre y ciudad
		size_t puntoPos = linea.find('.');
		size_t nombrePos = linea.find("Nombre:");
		size_t ciudadPos = linea.find("Ciudad:");

//		std::cout << "DEBUG: Posiciones - Punto: " << puntoPos << ", Nombre: " << nombrePos << ", Ciudad: " << ciudadPos << std::endl;

		if (puntoPos != std::string::npos && nombrePos != std::string::npos && ciudadPos != std::string::npos)
		{
			// Extraer el ID
			std::string idStr = linea.substr(0, puntoPos);
			int id = std::stoi(idStr);

			// Extraer el nombre (entre "Nombre:" y "Ciudad:")
			std::string nombre = linea.substr(nombrePos + 7, ciudadPos - nombrePos - 8);

			// Limpiar espacios al final del nombre
			while (!nombre.empty() && nombre.back() == ' ')
			{
				nombre.pop_back();
			}

			// Extraer la ciudad (después de "Ciudad:")
			std::string ciudad = linea.substr(ciudadPos + 7);

			// Limpiar espacios al inicio de la ciudad
			while (!ciudad.empty() && ciudad.front() == ' ')
			{
				ciudad.erase(0, 1);
			}

//			std::cout << "DEBUG: Parseando - ID: " << id << ", Nombre: [" << nombre << "], Ciudad: [" << ciudad << "]" << std::endl;

			// Crear objeto Restaurante y añadirlo al array
//			std::cout << "DEBUG: Creando objeto Restaurante..." << std::endl;
			listaRestaurantes[indice] = new Restaurante(id, nombre.c_str(), ciudad.c_str());
//			std::cout << "DEBUG: Objeto creado y añadido en índice: " << indice << std::endl;
			indice++;
		}
	}

//	std::cout << "DEBUG: Fin del bucle de parsing. Total de restaurantes creados: " << indice << std::endl;

	// Imprimir la lista de restaurantes creada
//	std::cout << "Lista de restaurantes creada:" << std::endl;
//	for (int i = 0; i < numRestaurantes; i++)
//	{
//		std::cout << listaRestaurantes[i]->getId() << ". Nombre: " << listaRestaurantes[i]->getNombre()
//				  << " Ciudad: " << listaRestaurantes[i]->getCiudad() << std::endl;
//	}

	return listaRestaurantes;
}

Restaurante controlador::obtenerRestaurantePorId(int id)
{
	int numRestaurantes = 0;
	Restaurante **listaRestaurantes = controlador::obtenerListaRestaurantesControlador(numRestaurantes);

	if (listaRestaurantes == nullptr)
	{
		return Restaurante(); // devolver un restaurante vacío
	}

	for (int i = 0; i < numRestaurantes; i++)
	{
		if (listaRestaurantes[i]->getId() == id)
		{
			Restaurante resultado = *listaRestaurantes[i]; // copia del restaurante encontrado

			// Liberar memoria del array
			for (int j = 0; j < numRestaurantes; j++)
			{
				delete listaRestaurantes[j];
			}
			delete[] listaRestaurantes;

			return resultado;
		}
	}

	// Liberar memoria del array
	for (int i = 0; i < numRestaurantes; i++)
	{
		delete listaRestaurantes[i];
	}
	delete[] listaRestaurantes;

	// Si no se encuentra, devolver un restaurante vacío
	return Restaurante();
}
