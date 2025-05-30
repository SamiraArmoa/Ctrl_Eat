#include <iostream>
#include <winsock2.h>

char *loginSocket(const char *username, const char *password)
{
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

char *registerSocket(const char *username, const char *password, const char *email, int tlf)
{
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

char *pedidoSocket(int id_r, int id_c, int *id_productos)
{
    char restaurante[10];
    sprintf(restaurante, "%d", id_r);
    char cliente[10];
    sprintf(cliente, "%d", id_c);
    printf("%s\n", cliente);
    char productos[512] = {0};
    int i = 0;
    while (id_productos[i] != 0)
    {
        char id_producto[10] = {0};
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

int enviarSocket(const char *message)
{
    // Initialize WSA variables
    WSADATA wsaData;
    int wserr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wserr = WSAStartup(wVersionRequested, &wsaData);

    // Check for initialization success
    if (wserr != 0)
    {
        std::cout << "The winsock dll not found" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "The Winsock dll found" << std::endl;
        std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
    }

    // Create a socket
    SOCKET clientSocket;
    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Check for socket creation success
    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }
    else
    {
        std::cout << "Socket is OK!" << std::endl;
    }

    // Connect to the server
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with the server's IP address
    clientService.sin_port = htons(5050);                   // Use the same port as the server

    // Use the connect function
    if (connect(clientSocket, reinterpret_cast<SOCKADDR *>(&clientService), sizeof(clientService)) == SOCKET_ERROR)
    {
        std::cout << "Client: connect() - Failed to connect: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }
    else
    {
        std::cout << "Client: Connect() is OK!" << std::endl;
        std::cout << "Client: Can start sending and receiving data..." << std::endl;
    }

    int sbyteCount = send(clientSocket, message, 200, 0);
    if (sbyteCount == SOCKET_ERROR)
    {
        std::cout << "Client send error: " << WSAGetLastError() << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Client: Sent " << sbyteCount << " bytes" << std::endl;
    }

    // Receiving data from the server
    char receiveBuffer[200];
    int rbyteCount = recv(clientSocket, receiveBuffer, 200, 0);
    if (rbyteCount < 0)
    {
        std::cout << "Client recv error: " << WSAGetLastError() << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Client: Received data: " << receiveBuffer << std::endl;
    }

    // Continue with the client setup...
}

int main()
{
    char *mensage = loginSocket("bob", "holi");

    // int productos[] = {2, 3, 4, 5, 0};
    // char *mensage = pedidoSocket(4, 3, productos);
    // printf("Holaaaaa: %s", mensage);
    enviarSocket(mensage);
    delete (mensage);
}