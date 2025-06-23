/*
 * controlador.cpp
 *
 *  Created on: 20 jun 2025
 *      Author: aroa.i.m
 */

#include "controlador.h"
#include "clientSocket.h"
#include "bebida/Bebida.h"
#include "plato/Plato.h"
#include <string.h>
#include <iostream>
#include <sstream>
//#include <cstring>
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
	login = loginSocket(u.getEmail(), u.getContrasena());
	int res = atoi(enviarSocket(login));

	cout << "Respuesta desde el controladora: " << res << endl;
	return (res * -1); // Si no es 0, existe
}

int controlador::editarPerfilControlador(Usuario &u) {
	char *update;
	update = updateUsuarioSocket(u.getId(), u.getNombre(), u.getContrasena(),
			u.getEmail(), u.getTelefono());
	int res = atoi(enviarSocket(update));

	cout << "Respuesta desde el controlador" << res << endl;
	return res; // Si res == 1, actualizado correctamente
}

Restaurante** controlador::obtenerListaRestaurantesControlador(
		int &numRestaurantes) {
//	std::cout << "DEBUG: Iniciando obtenerListaRestaurantesControlador()" << std::endl;
	numRestaurantes = 0;

	char *restaurantes = restaurantesSocket(); // "4"
//	std::cout << "DEBUG: Mensaje a enviar: " << restaurantes << std::endl;
	const char *res = enviarSocket(restaurantes); // respuesta del servidor
	delete[] restaurantes;						  // liberar memoria

//	std::cout << "DEBUG: Respuesta recibida: [" << (res ? res : "NULL") << "]" << std::endl;

	if (res == nullptr || strlen(res) == 0) {
		cerr << "No se recibieron datos de restaurantes." << endl;
		return nullptr; // devolver null
	}

	// Primero contar cuántos restaurantes hay
	std::string respuesta(res);
	std::istringstream stream(respuesta);
	std::string linea;
	int contador = 0;

	while (std::getline(stream, linea)) {
		if (!linea.empty() && linea.find('.') != std::string::npos
				&& linea.find("Nombre:") != std::string::npos
				&& linea.find("Ciudad:") != std::string::npos) {
			contador++;
		}
	}

//	std::cout << "DEBUG: Total de restaurantes encontrados: " << contador << std::endl;

	if (contador == 0) {
		return nullptr;
	}

	// Crear el array dinámico
	Restaurante **listaRestaurantes = new Restaurante*[contador];
	numRestaurantes = contador;
	int indice = 0;

	// Reiniciar el stream para parsear
	std::istringstream stream2(respuesta);

	while (std::getline(stream2, linea) && indice < contador) {
//		std::cout << "DEBUG: Procesando línea: [" << linea << "]" << std::endl;

		if (linea.empty())
			continue; // saltar líneas vacías

		// Buscar el patrón de ID, nombre y ciudad
		size_t puntoPos = linea.find('.');
		size_t nombrePos = linea.find("Nombre:");
		size_t ciudadPos = linea.find("Ciudad:");

//		std::cout << "DEBUG: Posiciones - Punto: " << puntoPos << ", Nombre: " << nombrePos << ", Ciudad: " << ciudadPos << std::endl;

		if (puntoPos != std::string::npos && nombrePos != std::string::npos
				&& ciudadPos != std::string::npos) {
			// Extraer el ID
			std::string idStr = linea.substr(0, puntoPos);
			int id = std::stoi(idStr);

			// Extraer el nombre (entre "Nombre:" y "Ciudad:")
			std::string nombre = linea.substr(nombrePos + 7,
					ciudadPos - nombrePos - 8);

			// Limpiar espacios al final del nombre
			while (!nombre.empty() && nombre.back() == ' ') {
				nombre.pop_back();
			}

			// Extraer la ciudad (después de "Ciudad:")
			std::string ciudad = linea.substr(ciudadPos + 7);

			// Limpiar espacios al inicio de la ciudad
			while (!ciudad.empty() && ciudad.front() == ' ') {
				ciudad.erase(0, 1);
			}

//			std::cout << "DEBUG: Parseando - ID: " << id << ", Nombre: [" << nombre << "], Ciudad: [" << ciudad << "]" << std::endl;

			// Crear objeto Restaurante y añadirlo al array
//			std::cout << "DEBUG: Creando objeto Restaurante..." << std::endl;
			listaRestaurantes[indice] = new Restaurante(id, nombre.c_str(),
					ciudad.c_str());
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

Restaurante controlador::obtenerRestaurantePorId(int id) {
	int numRestaurantes = 0;
	Restaurante **listaRestaurantes =
			controlador::obtenerListaRestaurantesControlador(numRestaurantes);

	if (listaRestaurantes == nullptr) {
		return Restaurante(); // devolver un restaurante vacío
	}

	for (int i = 0; i < numRestaurantes; i++) {
		if (listaRestaurantes[i]->getId() == id) {
			Restaurante resultado = *listaRestaurantes[i]; // copia del restaurante encontrado

			// Liberar memoria del array
			for (int j = 0; j < numRestaurantes; j++) {
				delete listaRestaurantes[j];
			}
			delete[] listaRestaurantes;

			return resultado;
		}
	}

	// Liberar memoria del array
	for (int i = 0; i < numRestaurantes; i++) {
		delete listaRestaurantes[i];
	}
	delete[] listaRestaurantes;

	// Si no se encuentra, devolver un restaurante vacío
	return Restaurante();
}

Producto** controlador::obtenerListaProductosControlador(int &numProductos) {
    numProductos = 0;
    char *productos = menuSocket();
    const char *res = enviarSocket(productos);
    delete[] productos;

    if (res == nullptr || strlen(res) == 0) {
        std::cerr << "No se recibieron productos." << std::endl;
        return nullptr;
    }

    // Copiar la respuesta para no modificar la original
    char *respuesta = new char[strlen(res) + 1];
    strcpy(respuesta, res);

    // Contar cuántos productos hay
    int contador = 0;
    char *linea = strtok(respuesta, "\n");
    while (linea != nullptr) {
        if (strchr(linea, '.') && strstr(linea, "Nombre:") && strstr(linea, "Precio:")
            && strstr(linea, "Tipo:") && strstr(linea, "Tamanio:") && strstr(linea, "Alergenos:")) {
            contador++;
        }
        linea = strtok(nullptr, "\n");
    }

    if (contador == 0) {
        delete[] respuesta;
        return nullptr;
    }

    Producto **lista = new Producto*[contador];
    numProductos = contador;
    int indice = 0;

    // Volver a copiar la respuesta para el segundo recorrido
    char *respuesta2 = new char[strlen(res) + 1];
    strcpy(respuesta2, res);
    linea = strtok(respuesta2, "\n");

    while (linea != nullptr && indice < contador) {
        if (strlen(linea) == 0) {
            linea = strtok(nullptr, "\n");
            continue;
        }

        // Buscar posiciones de cada campo
        char *puntoPos = strchr(linea, '.');
        char *nombrePos = strstr(linea, "Nombre:");
        char *precioPos = strstr(linea, "Precio:");
        char *tipoPos = strstr(linea, "Tipo:");
        char *tamanioPos = strstr(linea, "Tamanio:");
        char *alergenosPos = strstr(linea, "Alergenos:");

        if (puntoPos && nombrePos && precioPos && tipoPos && tamanioPos && alergenosPos) {
            // ID
            char idStr[10] = {0};
            strncpy(idStr, linea, puntoPos - linea);
            int id = atoi(idStr);

            // Nombre
            int lenNombre = precioPos - nombrePos - 8;
            char *nombre = new char[lenNombre + 1];
            strncpy(nombre, nombrePos + 7, lenNombre);
            nombre[lenNombre] = '\0';

            // Precio
            int lenPrecio = tipoPos - precioPos - 8;
            char precioStr[20] = {0};
            strncpy(precioStr, precioPos + 7, lenPrecio);
            int precio = static_cast<int>(atof(precioStr));

            // Tipo
            int lenTipo = tamanioPos - tipoPos - 6;
            char *tipo = new char[lenTipo + 1];
            strncpy(tipo, tipoPos + 5, lenTipo);
            tipo[lenTipo] = '\0';

            // Tamanio
            int lenTamanio = alergenosPos - tamanioPos - 9;
            char *tamanio = new char[lenTamanio + 1];
            strncpy(tamanio, tamanioPos + 8, lenTamanio);
            tamanio[lenTamanio] = '\0';

            // Alergenos
            char *alergenos = new char[strlen(alergenosPos + 10) + 1];
            strcpy(alergenos, alergenosPos + 10);

            // Crear producto
            if (strcmp(tipo, "bebida") == 0 || strcmp(tipo, "Bebida") == 0) {
                lista[indice] = new Bebida(id, nombre, precio, tamanio);
            } else {
                lista[indice] = new Plato(id, nombre, precio, alergenos);
            }
            indice++;

            delete[] nombre;
            delete[] tipo;
            delete[] tamanio;
            delete[] alergenos;
        }

        linea = strtok(nullptr, "\n");
    }

    delete[] respuesta;
    delete[] respuesta2;
    return lista;
}


Pedido** controlador::obtenerHistorialPedidosControlador(int idUsuario,
		int &numPedidos) {
	cout << "DEBUG: Iniciando obtenerHistorialPedidosControlador()" << endl;
	numPedidos = 0;

	char *pedidos = historialPedidoSocket(idUsuario); // "6"
	//	std::cout << "DEBUG: Mensaje a enviar: " << restaurantes << std::endl;
	const char *res = enviarSocket(pedidos);

	cout << "DEBUG: Respuesta recibida: [" << (res ? res : "NULL") << "]"<< endl;

	if (res == nullptr || strlen(res) == 0) {
		cerr << "No se recibieron datos del historial de pedidos." << endl;
		return nullptr;
	}

	// Contar la cantidad de pedidos
	std::string respuesta(res);
	std::istringstream stream(respuesta);
	std::string linea;
	int contador = 0;

	while (std::getline(stream, linea)) {
		if (!linea.empty()) {
			contador++;
		}
	}

	cout << "DEBUG: Total de pedidos encontrados: " << contador << endl;

	if (contador == 0) {
		return nullptr;
	}

	Pedido **listaPedidos = new Pedido*[contador];
	numPedidos = contador;
	int indice = 0;

	std::istringstream stream2(respuesta);
	while (std::getline(stream2, linea) && indice < contador) {
		std::cout << "DEBUG: Procesando línea: [" << linea << "]" << std::endl;

		if (linea.empty())
			continue;

		size_t pos1 = linea.find(';');
		size_t pos2 = linea.rfind(';');

		std::cout << "DEBUG: Posiciones - Primer ';': " << pos1
				<< ", Segundo ';': " << pos2 << std::endl;

		if (pos1 == std::string::npos || pos2 == std::string::npos
				|| pos1 == pos2) {
			std::cout << "DEBUG: Línea con formato inválido, se omite."
					<< std::endl;
			continue;
		}

		// Parsear campos
		std::string idStr = linea.substr(0, pos1);
		std::string domicilioStr = linea.substr(pos1 + 1, pos2 - pos1 - 1);
		std::string idResStr = linea.substr(pos2 + 1);

		int idPedido = std::stoi(idStr);
		int idRestaurante = std::stoi(idResStr);

		std::cout << "DEBUG: Parseando - ID: " << idPedido << ", Domicilio: ["
				<< domicilioStr << "], ID Restaurante: " << idRestaurante
				<< std::endl;

		// Crear objeto Pedido
		std::cout << "DEBUG: Creando objeto Pedido..." << std::endl;
		listaPedidos[indice] = new Pedido(idPedido, domicilioStr.c_str(),
				idUsuario, idRestaurante);
		std::cout << "DEBUG: Objeto creado y añadido en índice: " << indice
				<< std::endl;

		indice++;
	}

	std::cout << "DEBUG: Fin del bucle de parsing. Total de pedidos creados: "
			<< indice << std::endl;

	// Imprimir lista de pedidos (opcional)
	/*
	 std::cout << "Lista de pedidos creada:" << std::endl;
	 for (int i = 0; i < numPedidos; i++) {
	 std::cout << listaPedidos[i]->getId() << ". Domicilio: " << listaPedidos[i]->getDomicilio()
	 << " Restaurante: " << listaPedidos[i]->getIdRestaurante() << std::endl;
	 }
	 */

	return listaPedidos;
}

int** controlador::obtenerIdsProductosPedido(int idPedido,
		int &numIdsProducto) {
	std::cout << "DEBUG: Iniciando obtenerIdsProductosPedido()" << std::endl;
	numIdsProducto = 0;

	char *idsProducto = obtenerProductosPedidoSocket(idPedido); // "7"
	//	std::cout << "DEBUG: Mensaje a enviar: " << restaurantes << std::endl;
	const char *res = enviarSocket(idsProducto);

	std::cout << "DEBUG: Respuesta recibida: [" << (res ? res : "NULL") << "]"
			<< std::endl;

	if (res == nullptr || strlen(res) == 0) {
		std::cerr << "No se recibieron datos de productos para el pedido."
				<< std::endl;
		return nullptr;
	}

	std::string respuesta(res);
	std::istringstream stream(respuesta);
	std::string linea;
	int contador = 0;

	// Contar productos
	while (std::getline(stream, linea)) {
		if (!linea.empty()) {
			contador++;
		}
	}

	std::cout << "DEBUG: Total de productos encontrados: " << contador
			<< std::endl;

	if (contador == 0) {
		return nullptr;
	}

	// Crear array dinámico de punteros a int
	int **listaIds = new int*[contador];
	numIdsProducto = contador;
	int indice = 0;

	std::istringstream stream2(respuesta);
	while (std::getline(stream2, linea) && indice < contador) {
		std::cout << "DEBUG: Procesando línea: [" << linea << "]" << std::endl;

		if (linea.empty())
			continue;

		int id = std::stoi(linea);
		std::cout << "DEBUG: Parseando ID Producto: " << id << std::endl;

		listaIds[indice] = new int(id);
		std::cout << "DEBUG: ID añadido en índice " << indice << std::endl;

		indice++;
	}

	std::cout << "DEBUG: Fin del bucle de parsing. Total de IDs creados: "
			<< indice << std::endl;

	return listaIds;
}

