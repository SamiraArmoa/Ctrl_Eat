#ifndef DATA_DB_DB_H_
#define DATA_DB_DB_H_
#ifdef __cplusplus
extern "C"
{
#endif

    int obtenerUltimoIdEmpleados(int *id, const char *path);
    int insertarEmpleado(char *nombre, char *cargo, char *cuentaBancaria, const char *path);
    int deleteEmpleado(int id_em, const char *path);
    int imprimirEmpleados(const char *path);
    int updateEmpleados(int id_em, char *nombre, char *cargo, char *cuentaBancaria, const char *path);

    int guardar_productoIngrediente(int id_pr, int id_in, const char *path);
    int guardar_productos(int id, char *nombre, char *tipo, float precio, char *tamanio, char *alergenos, const char *path);
    int obtenerUltimoIdProductos(int *id, const char *path);
    int imprimirProductos(const char *path);
    int obtenerIngredientes(const char *path);
    int deleteProductos(int id_pr, const char *path);
    int updateProductos(int id_pr, char *nombre, float precio, char *tipo, char *tamanio, char *alergenos, const char *path);

    int insertarClientes(char *nombre, char *email, int telefono, char *contrasena, const char *path);
    int verClientes(const char *path);
    int deleteClientes(int id_cl, const char *path);
    int updateClientes(int id_cl, char *nombre, char *email, int telefono, char *contrasena, const char *path);

    int guardar_ingredientes(int id, char *nombre, const char *path);
    int insertarIngredientes(char *nombre, const char *path);
    int imprimirIngredientes(const char *path);
    int deleteIngredientes(int id_in, const char *path);

    int guardar_restaurantes(char *id, char *nombre, char *ciudad, const char *path);
    int obtenerUltimoIdRestaurante(int *id, const char *path);
    int updateRestaurante(int id, char *nombre, char *ciudad, const char *path);
    int insertarRestaurante(char *nombre, char *ciudad, const char *path);
    int imprimirRestaurante(const char *path);

    int obtenerProductos(const char *path);
    int guardarPedidos(int domic, const char *path);
    int guardar_productoPedido(int id_ped, int id_pr, const char *path);
    int obtenerUltimoIdPedido(int *id, const char *path);
    int getPedidos(const char *path);

    int esUsuarioValido(char *nombre, char *contrasena, const char *path);

#ifdef __cplusplus
}
#endif
#endif /* DATA_DB_DB_H_ */
