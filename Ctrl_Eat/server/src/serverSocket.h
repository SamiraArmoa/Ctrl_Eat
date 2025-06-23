#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

int receive_login(char *response);
int receive_register(char *response);
int receive_pedidos(char *response);
int receive_usuario_actualizado(char *response);
const char* receive_historial_pedido(char* response);
const char* receive_productos_pedido(char* response);
int escuchar();

#endif
