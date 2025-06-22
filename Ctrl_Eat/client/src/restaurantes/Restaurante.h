/*
 * Restaurante.h
 *
 *  Created on: 29 may 2025
 *      Author: s.armoa
 */

#ifndef REMOTE_SRC_RESTAURANTES_RESTAURANTE_H_
#define REMOTE_SRC_RESTAURANTES_RESTAURANTE_H_
#include <string>

class Restaurante
{
private:
	int id;
	char *nombre;
	char *ciudad;

public:
	Restaurante();
	Restaurante(int id, const char *nombre, const char *ciudad);
	Restaurante(const Restaurante &other);			  // Constructor de copia
	Restaurante &operator=(const Restaurante &other); // Operador de asignación
	~Restaurante();

	int getId() const;
	const char *getNombre() const;
	const char *getCiudad() const;

	void setId(int id);
	void setNombre(const char *nombre);
	void setCiudad(const char *ciudad);
};

#endif /* REMOTE_SRC_RESTAURANTES_RESTAURANTE_H_ */
