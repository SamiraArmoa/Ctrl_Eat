#include "serverSocket.h"
#include <iostream>
#include <winsock2.h>
#include <cstring>
#include "../../server/data/db/db.h"
#include <stdlib.h>
#include "../../server/config.h"
#include "../../server/data/db/db.h"

int receive_login(char *response) {
	std::strtok(response, " ");
	char *username = std::strtok(nullptr, " ");
	char *password = std::strtok(nullptr, " ");
	return esUsuarioValido(username, password, CLIENT_DB_PATH);
}

int receive_register(char *response) {
	std::strtok(response, " ");
	char *username = std::strtok(nullptr, " ");
	char *password = std::strtok(nullptr, " ");
	char *email = std::strtok(nullptr, " ");
	char *telefono = std::strtok(nullptr, " ");
	int tlf = atoi((const char*) telefono);

	return insertarClientes(username, email, tlf, password, CLIENT_DB_PATH);
}

int receive_pedidos(char *response) {
	// printf(response);
	std::strtok(response, " ");
	char *restaurante = std::strtok(nullptr, " ");
	char *cliente = std::strtok(nullptr, " ");
	int id_res = atoi(restaurante);
	int id_cl = atoi(cliente);
	guardarPedidos(1, id_cl, id_res, CLIENT_DB_PATH);
	int id_p = 0;
	obtenerUltimoIdPedido(&id_p, CLIENT_DB_PATH);
	char *id_producto = std::strtok(nullptr, " ");
	while (id_producto != nullptr) {
		int id_pro = atoi(id_producto);
		printf("%i\n", id_pro);
		id_producto = std::strtok(nullptr, " ");

		guardar_productoPedido(id_p, id_pro, CLIENT_DB_PATH);
	}
	return 0;
}

int receive_usuario_actualizado(char *response) {
	std::strtok(response, " ");
	char *idUsuario = std::strtok(nullptr, " ");
	int id = atoi((const char*) idUsuario);
	char *username = std::strtok(nullptr, " ");
	char *password = std::strtok(nullptr, " ");
	char *email = std::strtok(nullptr, " ");
	char *telefono = std::strtok(nullptr, " ");
	int tlf = atoi((const char*) telefono);

	return updateClientes(id, username, email, tlf, password, CLIENT_DB_PATH);
}

const char* receive_historial_pedido(char *response) {
	std::strtok(response, " ");
	char *idUsuario = std::strtok(nullptr, " ");
	int id = atoi((const char*) idUsuario);

	return historialPedidosUsuario(id, CLIENT_DB_PATH);
}

const char* receive_productos_pedido(char* response){
	std::strtok(response, " ");
	char *idPedido = std::strtok(nullptr, " ");
	int id = atoi((const char*) idPedido);

	return obtenerProductosPedido(id, CLIENT_DB_PATH);
}

int escuchar() {
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);

	if (wsaerr != 0) {
		return 0;
	}

	// Create a socket
	SOCKET serverSocket;
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (serverSocket == INVALID_SOCKET) {
		std::cout << "Ha habido un error en los sockets " << WSAGetLastError()
				<< std::endl;
		WSACleanup();
		return 0;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(5050);

	if (bind(serverSocket, reinterpret_cast<SOCKADDR*>(&service),
			sizeof(service)) == SOCKET_ERROR) {
		std::cout << "bind() ha fallado: " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}

	if (listen(serverSocket, 1) == SOCKET_ERROR) {
		std::cout << "listen(): Error listening on socket: "
				<< WSAGetLastError() << std::endl;
		return 0;
	}

	std::cout << "Esperando conexiones..." << std::endl;

	// Inicio del bucle infinito
	while (true) {
		SOCKET acceptSocket;
		acceptSocket = accept(serverSocket, nullptr, nullptr);

		if (acceptSocket == INVALID_SOCKET) {
			std::cout << "accept failed: " << WSAGetLastError() << std::endl;
			continue; // Continuar esperando la siguiente conexión
		}

		std::cout << "Conexión aceptada" << std::endl;

		char receiveBuffer[200];
		int rbyteCount = recv(acceptSocket, receiveBuffer, 200, 0);
		if (rbyteCount < 0) {
			std::cout << "Error al recibir datos: " << WSAGetLastError()
					<< std::endl;
			closesocket(acceptSocket);
			continue;
		}

		// std::cout << "Datos recibidos: " << receiveBuffer << std::endl;

		int result;
		const char *productos;
		const char *restaurantes;
		const char *pedidos;
		switch (receiveBuffer[0]) {
		case '0':
			result = receive_login(receiveBuffer);
			break;
		case '1':
			result = receive_register(receiveBuffer);
			break;
		case '2':
			result = receive_pedidos(receiveBuffer);
			break;
		case '3':
			result = 2;
			productos = imprimirProductos(CLIENT_DB_PATH);
			break;
		case '4':
			result = 3;
			restaurantes = imprimirRestaurante(CLIENT_DB_PATH);
			break;
		case '5':
			result = receive_usuario_actualizado(receiveBuffer);
			break;
		case '6':
			result = 4;
			pedidos = receive_historial_pedido(receiveBuffer);
			break;
		case '7':
			result = 5;
			productos = receive_productos_pedido(receiveBuffer);
			break;
		default:
			result = -1;
			break;
		}

		char buffer[8000] = { 0 }; // Buffer para enviar la respuesta
		if (result == 0)
			strcpy(buffer, "1"); // Éxito
		else if (result == 1) {
			strcpy(buffer, "0"); // Error
		} else if (result == 2) {
			strcpy(buffer, productos); // Productos
		} else if (result == 3) {
			strcpy(buffer, restaurantes); // Restaurantes
		} else if (result == 4) {
			strcpy(buffer, pedidos); // Pedidos
		}else if (result == 5) {
			strcpy(buffer, productos); // idProductos
		}else if (result < 0) {
			sprintf(buffer, "%d", result);
		} else {

		}

		send(acceptSocket, buffer, strlen(buffer), 0);
		closesocket(acceptSocket); // Cerrar la conexión actual
	}

	// Este código nunca se alcanzará a menos que haya un break
	closesocket(serverSocket);
	WSACleanup();
	return 0;
}
