/*
 * Pedidos.h
 *
 *  Created on: 30 may 2025
 *      Author: s.armoa
 */

#ifndef REMOTE_SRC_PEDIDOS_PEDIDOS_H_
#define REMOTE_SRC_PEDIDOS_PEDIDOS_H_

#include <vector>  // necesario
using namespace std;

class Pedidos {
private:
	int id;
	const char* domicilio;
	int idCliente;
	int idRestaurante;
public:
	Pedidos();
	Pedidos(int id, const char* domicilio, int idCliente, int idRestaurante);
	virtual ~Pedidos();

	int getId();
	const char* getDomicilio();
	int getIdCliente();
	int getIdRestaurante();

	void setId(int id);
	void setDomicilio(const char* domicilio);
	void setIdCliente(int idCliente);
	void setIdRestaurante(int idRestaurante);
	static vector<Pedidos> verPedidos(const vector<Pedidos>& todos, int idCliente);
};

#endif /* REMOTE_SRC_PEDIDOS_PEDIDOS_H_ */
