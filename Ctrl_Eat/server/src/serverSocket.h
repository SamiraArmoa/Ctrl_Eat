#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

int receive_login(char *response);
int receive_register(char *response);
int receive_pedidos(char *response);
int receive_usuario_actualizado(char *response);
int escuchar();

#endif
