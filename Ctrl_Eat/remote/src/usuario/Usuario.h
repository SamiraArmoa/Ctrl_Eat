/*
 * Usuario.h
 *
 *  Created on: 30 may 2025
 *      Author: s.armoa
 */

#ifndef REMOTE_SRC_USUARIO_USUARIO_H_
#define REMOTE_SRC_USUARIO_USUARIO_H_

class Usuario {
private:
    int id;
    const char* nombre;
    const char* email;
    int telefono;
    int contrasena;
public:
	Usuario();
	Usuario(int id, const char* nombre, const char* email, int telefono, int contrasena);
	virtual ~Usuario();


	int getId();
	const char* getNombre();
	const char* getEmail();
	int getTelefono();
	int getContrasena();


	void setId(int id);
	void setNombre(const char* nombre);
	void setEmail(const char* email);
	void setTelefono(int telefono);
	void setContrasena(int contrasena);
};

#endif /* REMOTE_SRC_USUARIO_USUARIO_H_ */
