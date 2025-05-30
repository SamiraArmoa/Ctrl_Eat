#include <iostream>
#include <winsock2.h>
#include <cstring>
#include "../../local/data/db/db.h"
#include <stdlib.h>
#include "../../local/config.h"

int receive_login(char *response)
{
    std::strtok(response, " ");
    char *username = std::strtok(nullptr, " ");
    char *password = std::strtok(nullptr, " ");
    return esUsuarioValido(username, password, SERVER_DB_PATH);
}

int receive_register(char *response)
{
    std::strtok(response, " ");
    char *username = std::strtok(nullptr, " ");
    char *password = std::strtok(nullptr, " ");
    char *email = std::strtok(nullptr, " ");
    char *telefono = std::strtok(nullptr, " ");
    int tlf = atoi((const char *)telefono);

    return insertarClientes(username, email, tlf, password, SERVER_DB_PATH);
}

int receive_pedidos(char *response)
{
    // printf(response);
    std::strtok(response, " ");
    char *restaurante = std::strtok(nullptr, " ");
    char *cliente = std::strtok(nullptr, " ");
    guardarPedidos(1, SERVER_DB_PATH);
    int id_p = 0;
    obtenerUltimoIdPedido(&id_p, SERVER_DB_PATH);
    char *id_producto = std::strtok(nullptr, " ");
    while (id_producto != nullptr)
    {
        int id_pro = atoi(id_producto);
        printf("%i\n", id_pro);
        id_producto = std::strtok(nullptr, " ");
        // aquí tienes que parsear cada string con los ids, y añadirlos a un array de ints. No
        // te olvides de añadir un 0 al final del array. Luego, por cada número en el array,
        // llamas a guardar_producto_pedido y metetes cada id del producto en id_p. Luego devuelves un 0
        guardar_productoPedido(id_p, id_pro, SERVER_DB_PATH);
    }
    return 0;
}

int main()
{
    // Initialize WSA variables
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);

    // Check for initialization success
    if (wsaerr != 0)
    {
        std::cout << "The Winsock dll not found!" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "The Winsock dll found" << std::endl;
        std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
    }

    // Create a socket
    SOCKET serverSocket;
    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Check for socket creation success
    if (serverSocket == INVALID_SOCKET)
    {
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }
    else
    {
        std::cout << "Socket is OK!" << std::endl;
    }

    // Bind the socket to an IP address and port number
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with your desired IP address
    service.sin_port = htons(5050);                   // Choose a port number

    // Use the bind function
    if (bind(serverSocket, reinterpret_cast<SOCKADDR *>(&service), sizeof(service)) == SOCKET_ERROR)
    {
        std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else
    {
        std::cout << "bind() is OK!" << std::endl;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 1) == SOCKET_ERROR)
    {
        std::cout << "listen(): Error listening on socket: " << WSAGetLastError() << std::endl;
    }
    else
    {
        std::cout << "listen() is OK! I'm waiting for new connections..." << std::endl;
    }

    // Accept incoming connections
    SOCKET acceptSocket;
    acceptSocket = accept(serverSocket, nullptr, nullptr);

    // Check for successful connection
    if (acceptSocket == INVALID_SOCKET)
    {
        std::cout << "accept failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }
    else
    {
        std::cout << "accept() is OK!" << std::endl;
    }

    // Receive data from the client
    char receiveBuffer[200];
    int rbyteCount = recv(acceptSocket, receiveBuffer, 200, 0);
    if (rbyteCount < 0)
    {
        std::cout << "Server recv error: " << WSAGetLastError() << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Received data: " << receiveBuffer << std::endl;
    }

    int result;
    switch (receiveBuffer[0])
    {
    case '0':
        result = receive_login(receiveBuffer);
        break;
    case '1':
        result = receive_register(receiveBuffer);
        break;

    case '2':
        result = receive_pedidos(receiveBuffer);
        break;

    default:
        break;
    }

    char buffer[200];
    if (result == 0)
        strcpy(buffer, "1"); // Éxito
    else
        strcpy(buffer, "0"); // Error

    send(acceptSocket, buffer, strlen(buffer), 0);
    // Send a response to the client
    // char buffer[200];
    // std::cout << "Enter the message: ";
    // std::cin.getline(buffer, 200);
    // int sbyteCount = send(acceptSocket, buffer, 200, 0);
    // if (sbyteCount == SOCKET_ERROR)
    // {
    //     std::cout << "Server send error: " << WSAGetLastError() << std::endl;
    //     return -1;
    // }
    // else
    // {
    //     std::cout << "Server: Sent " << sbyteCount << " bytes" << std::endl;
    // }

    // return 0;
}