/*
 * Pedidos.h
 *
 *  Created on: 30 may 2025
 *      Author: s.armoa
 */

#ifndef REMOTE_SRC_PEDIDOS_PEDIDOS_H_
#define REMOTE_SRC_PEDIDOS_PEDIDOS_H_

class Pedidos {
private:
	int id;
	const char* fechaEntrega;
	const char* fechaPedido;
	const char* domicilio;
	int idCliente;
	int idRestaurante;
public:
	Pedidos();
	Pedidos(int id, const char* fechaEntrega, const char* fechaPedido, const char* domicilio, int idCliente, int idRestaurante);
	virtual ~Pedidos();

	int getId();
	const char* getFechaEntrega();
	const char* getFechaPedido();
	const char* getDomicilio();
	int getIdCliente();
	int getIdRestaurante();

	void setId(int id);
	void setFechaEntrega(const char* fechaEntrega);
	void setFechaPedido(const char* fechaPedido);
	void setDomicilio(const char* domicilio);
	void setIdCliente(int idCliente);
	void setIdRestaurante(int idRestaurante);
};

#endif /* REMOTE_SRC_PEDIDOS_PEDIDOS_H_ */
