/*
 * Restaurante.h
 *
 *  Created on: 29 may 2025
 *      Author: s.armoa
 */

#ifndef REMOTE_SRC_RESTAURANTES_RESTAURANTE_H_
#define REMOTE_SRC_RESTAURANTES_RESTAURANTE_H_
#include <string>

class Restaurante {
private:
	int id;
	const char* nombre;
	const char* ciudad;
public:
	Restaurante();
	Restaurante(int id, const char* nombre, const char* ciudad);
	virtual ~Restaurante();


	int getId();
	const char* getNombre();
	const char* getCiudad();

	void setId(int id);
	void setNombre(const char* nombre);
	void setCiudad(const char* ciudad);


};

#endif /* REMOTE_SRC_RESTAURANTES_RESTAURANTE_H_ */
