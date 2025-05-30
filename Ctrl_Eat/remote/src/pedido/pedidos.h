/*
 * pedido.h
 *
 *  Created on: 30 may 2025
 *      Author: oihan.bilbao
 */

#ifndef CTRL_EAT_REMOTE_SRC_PEDIDO_PEDIDOS_H_
#define CTRL_EAT_REMOTE_SRC_PEDIDO_PEDIDOS_H_



class Pedido {

private:
	int id;
	int idR;
	int idCl;
	int productos[100];

public:
	Pedido();
	Pedido(int id, int idR, int idCl, int productos[100]);
	virtual ~Pedido();

	int getId() const
	{
		return id;
	}

	void setId(int id)
	{
		this->id = id;
	}

	int getIdCl() const
	{
		return idCl;
	}

	void setIdCl(int idCl)
	{
		this->idCl = idCl;
	}

	int getIdR() const
	{
		return idR;
	}

	void setIdR(int idR)
	{
		this->idR = idR;
	}

	const int* getProductos() const
	{
		return productos;
	}
};
#endif /* CTRL_EAT_REMOTE_SRC_PEDIDO_PEDIDOS_H_ */
