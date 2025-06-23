/*
 * controlador.h
 *
 *  Created on: 20 jun 2025
 *      Author: aroa.i.m
 */

#include <iostream>

#include "pedido/Pedido.h"
#include "usuario/Usuario.h"
#include "producto/Producto.h"
#include "restaurantes/Restaurante.h"

class controlador
{
public:
	void datosPedido();
	int pagarPedido(Pedido &pedido);
	int hacerPedido(Pedido &pedido);

	int pedido();

	static int editarPerfilControlador(Usuario &u);
	static int registrarseControlador(Usuario &u);
	static int iniciarSesionControlador(Usuario &u);
	static Restaurante **obtenerListaRestaurantesControlador(int &numRestaurantes);
	static Restaurante obtenerRestaurantePorId(int id);
	static Pedido** obtenerHistorialPedidosControlador(int idUsuario, int &numPedidos);
	static int** obtenerIdsProductosPedido(int idPedido, int &numIdsProducto);
	static Producto** obtenerListaProductosControlador(int &numProductos);
	static Producto obtenerProductoPorId(int id);
};
