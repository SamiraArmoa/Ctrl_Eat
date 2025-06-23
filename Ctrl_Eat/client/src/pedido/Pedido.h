/*
 * Pedidos.h
 *
 *  Created on: 30 may 2025
 *      Author: s.armoa
 */

#ifndef REMOTE_SRC_PEDIDO_PEDIDOS_H_
#define REMOTE_SRC_PEDIDO_PEDIDOS_H_

class Pedido {
private:
	int id;
	char* domicilio;
	int idCliente;
	int idRestaurante;
public:
	Pedido();
	Pedido(int id, const char* domicilio, int idCliente, int idRestaurante);
	~Pedido();

	int getId();
	const char* getDomicilio();
	int getIdCliente();
	int getIdRestaurante();

	void setId(int id);
	void setDomicilio(const char* domicilio);
	void setIdCliente(int idCliente);
	void setIdRestaurante(int idRestaurante);
	void mostrar() const;
};

#endif /* REMOTE_SRC_PEDIDO_PEDIDOS_H_ */
