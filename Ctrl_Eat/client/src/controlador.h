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
	void historialDePedido();

	int pedido();

	static int editarPerfilControlador(Usuario &u);
	static int registrarseControlador(Usuario &u);
	static int iniciarSesionControlador(Usuario &u);
	static const char *obtenerRestaurantesControlador();
	static Restaurante **obtenerListaRestaurantesControlador(int &numRestaurantes);
	static Restaurante obtenerRestaurantePorId(int id);
};
