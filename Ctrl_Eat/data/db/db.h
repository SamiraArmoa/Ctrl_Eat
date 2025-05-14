#ifndef DATA_DB_DB_H_
#define DATA_DB_DB_H_
#define DB_PATH "../data/db/restaurante.db"


int obtenerUltimoIdEmpleados(int *id);
int insertarEmpleado(char* nombre, char* cargo, char* cuentaBancaria);
int deleteEmpleado(int id_em);
int imprimirEmpleados();
int updateEmpleados(int id_em, char* nombre, char* cargo, char* cuentaBancaria);

int obtenerUltimoIdProductos(int* id);
int imprimirProductos();
int obtenerIngredientes();
int deleteProductos(int id_pr);
int updateProductos(int id_pr, char* nombre, float precio, char* tipo);

int insertarClientes(char* nombre, char* email, int telefono, char* contrasena);
int verClientes();
int deleteClientes(int id_cl);
int updateClientes(int id_cl, char* nombre, char* email, int telefono, char* contrasena);

int insertarIngredientes(char* nombre);
int imprimirIngredientes();
int deleteIngredientes(int id_in);

int obtenerUltimoIdRestaurante(int* id);
int updateRestaurante(int id, char* nombre, char* ciudad);
int createRestaurante(char* nombre, char* ciudad);

int obtenerProductos();
int obtenerUltimoIdPedido(int *id);
int getPedidos();
#endif /* DATA_DB_DB_H_ */
