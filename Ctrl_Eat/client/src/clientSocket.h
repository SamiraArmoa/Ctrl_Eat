#ifndef CTRL_EAT_CLIENT_H_
#define CTRL_EAT_CLIENT_H_

char *loginSocket(const char *username, const char *password);
char *registerSocket(const char *username, const char *password, const char *email, int tlf);
char *updateUsuarioSocket(int id, const char *username, const char *password, const char *email, int tlf);
char* pedidoSocket(int id_r, int id_c, int *id_productos);
char* historialPedidoSocket(int id_c);
char* obtenerProductosPedidoSocket(int id_ped);
char* menuSocket();
char* restaurantesSocket();
const char *enviarSocket(const char *message);
void hacerPedido(int id_usuario_actual);

#endif
