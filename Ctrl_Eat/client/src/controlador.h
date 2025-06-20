/*
 * controlador.h
 *
 *  Created on: 20 jun 2025
 *      Author: aroa.i.m
 */

#include <iostream>
#include "pedidos/Pedidos.h"
#include "usuario/Usuario.h"
#include "producto/Producto.h"
#include "restaurantes/Restaurante.h"

class controlador {
public:
	void datosPedido();
	int pagarPedido(Pedidos &pedido);
	int hacerPedido(Pedidos &pedido);
	void historialDePedido();
	int elegirRestaurante();
	int pedido();

	void editarPerfil();
	static void registrarseControlador(Usuario &u);
	static int iniciarSesionControlador(Usuario &u);

};




