#ifndef DATA_DB_DB_H_
#define DATA_DB_DB_H_
#define DB_PATH "../data/db/restaurante.db"


int obtenerUltimoIdEmpleados(int *id);
int insertarEmpleado(char* nombre, char* cargo, char* cuentaBancaria);
int deleteEmpleado(int id_em);
int imprimirEmpleados();
int updateEmpleados(int id_em, char* nombre, char* cargo, char* cuentaBancaria);

int guardar_productoIngrediente(int id_pr, int id_in);
int guardar_productos(int id, char *nombre, char *tipo, float precio);
int obtenerUltimoIdProductos(int* id);
int imprimirProductos();
int obtenerIngredientes();
int deleteProductos(int id_pr);
int updateProductos(int id_pr, char* nombre, float precio, char* tipo);

int insertarClientes(char* nombre, char* email, int telefono, char* contrasena);
int verClientes();
int deleteClientes(int id_cl);
int updateClientes(int id_cl, char* nombre, char* email, int telefono, char* contrasena);

int guardar_ingredientes(int id, char *nombre);
int insertarIngredientes(char* nombre);
int imprimirIngredientes();
int deleteIngredientes(int id_in);

int guardar_restaurantes(char *id, char *nombre, char *ciudad);
int obtenerUltimoIdRestaurante(int* id);
int updateRestaurante(int id, char* nombre, char* ciudad);
int insertarRestaurante(char* nombre, char* ciudad);
int imprimirRestaurante();

int obtenerProductos();
int guardarPedidos(int domic,char *fchEntrega, char *fchPedido);
int guardar_productoPedido(int id_ped, int id_pr);
int obtenerUltimoIdPedido(int *id);
int getPedidos();

int esUsuarioValido(char* nombre, char* contrasena);
#endif /* DATA_DB_DB_H_ */
