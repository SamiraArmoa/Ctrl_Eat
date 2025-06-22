#include <iostream>
#include <winsock2.h>

char* loginSocket(const char *username, const char *password) {
	char *message = new char[512];
	strcpy(message, "0");
	strcat(message, " ");
	strcat(message, username);
	strcat(message, " ");
	strcat(message, password);
	strcat(message, "\0");
	printf(message);
	printf("\n");
	return message;
}

char* registerSocket(const char *username, const char *password, const char *email, int tlf) {
	char telefono[10];
	sprintf(telefono, "%d", tlf);
	char *message = new char[512];
	strcpy(message, "1");
	strcat(message, " ");
	strcat(message, username);
	strcat(message, " ");
	strcat(message, password);
	strcat(message, " ");
	strcat(message, email);
	strcat(message, " ");
	strcat(message, telefono);
	strcat(message, "\0");
	printf(message);
	printf("\n");
	return message;
}

char* updateUsuarioSocket(int id, const char *username, const char *password, const char *email, int tlf) {
	char telefono[10];
	sprintf(telefono, "%d", tlf);
	char idUsuario[3];
	sprintf(idUsuario, "%d", id);

	char *message = new char[512];
	strcpy(message, "5");
	strcat(message, " ");
	strcat(message, idUsuario);
	strcat(message, " ");
	strcat(message, username);
	strcat(message, " ");
	strcat(message, password);
	strcat(message, " ");
	strcat(message, email);
	strcat(message, " ");
	strcat(message, telefono);
	strcat(message, "\0");
	printf(message);
	printf("\n");
	return message;
}

char* pedidoSocket(int id_r, int id_c, int *id_productos) {
	char restaurante[10];
	sprintf(restaurante, "%d", id_r);
	char cliente[10];
	sprintf(cliente, "%d", id_c);
	printf("%s\n", cliente);
	char productos[512] = { 0 };
	int i = 0;
	while (id_productos[i] != 0) {
		char id_producto[10] = { 0 };
		sprintf(id_producto, "%d", id_productos[i]);
		strcat(productos, id_producto);
		strcat(productos, " ");
		i++;
	}
	strcat(productos, "\0");

	char *message = new char[512];
	strcpy(message, "2");
	strcat(message, " ");
	strcat(message, restaurante);
	strcat(message, " ");
	strcat(message, cliente);
	strcat(message, " ");
	strcat(message, productos);
	strcat(message, "\0");
	return message;
}

char* menuSocket() {
	char *message = new char[512];
	strcpy(message, "3");
	return message;
}

char* restaurantesSocket() {
	char *message = new char[512];
	strcpy(message, "4");
	return message;
}

const char* enviarSocket(const char *message) {
	WSADATA wsaData;
	int wserr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wserr = WSAStartup(wVersionRequested, &wsaData);

	if (wserr != 0) {
		return "0";
	}

	SOCKET clientSocket;
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientSocket == INVALID_SOCKET) {
		std::cout << "Error con el socket" << std::endl;
		WSACleanup();
		return "0";
	}

	// Connect to the server
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with the server's IP address
	clientService.sin_port = htons(5050);     // Use the same port as the server

	// Use the connect function
	if (connect(clientSocket, reinterpret_cast<SOCKADDR*>(&clientService),
			sizeof(clientService)) == SOCKET_ERROR) {
		std::cout << "Conexión fallida" << WSAGetLastError() << std::endl;
		WSACleanup();
		return "0";
	}

	int sbyteCount = send(clientSocket, message, 200, 0);
	if (sbyteCount == SOCKET_ERROR) {
		std::cout << "Error al enviar: " << WSAGetLastError() << std::endl;
		return "-1";
	} else {
		std::cout << "Mensaje enviado: " << message << std::endl;
	}

	// Receiving data from the server
	static char receiveBuffer[8000];
	memset(receiveBuffer, 0, sizeof(receiveBuffer));

	int rbyteCount = recv(clientSocket, receiveBuffer,
			sizeof(receiveBuffer) - 1, 0);
	if (rbyteCount < 0) {
		std::cout << "Error al recibir datos: " << WSAGetLastError()
				<< std::endl;
		return "0";
	}

	receiveBuffer[rbyteCount] = '\0';

//        std::cout << "Datos recibidos: " << receiveBuffer << std::endl;

	return receiveBuffer;
}

void hacerPedido(int id_usuario_actual) {
	// Pide los prodductos
	char *menu = menuSocket();
	enviarSocket(menu);
	delete (menu);

	int productos[100];
	int id_escogida = -1;
	int i = 0;
	while (id_escogida != 0) {
		printf(
				"Introduce el id del producto que quieres pedir (0 para terminar): ");
		scanf("%d", &id_escogida);
		productos[i] = id_escogida;
		i++;
	}

	char *restaurantes = restaurantesSocket();
	enviarSocket(restaurantes);
	delete (restaurantes);

	int restaurante_escogido = 0;
	printf("Introduce el id del restaurante: ");
	scanf("%d", &restaurante_escogido);

	char *mensage = pedidoSocket(restaurante_escogido, id_usuario_actual,
			productos);
	enviarSocket(mensage);
}
