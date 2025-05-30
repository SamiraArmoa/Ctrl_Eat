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
    int idUsuario;
    const char* nombre;
    const char* email;
    int telefono;
    const char* contrasena;
public:
	Usuario();
	Usuario(int idUsuario, const char* nombre, const char* email, int telefono, const char* contrasena);
	virtual ~Usuario();


	int getIdUsuario();
	const char* getNombre();
	const char* getEmail();
	int getTelefono();
	const char* getContrasena();


	void setIdUsuario(int idUsuario);
	void setNombre(const char* nombre);
	void setEmail(const char* email);
	void setTelefono(int telefono);
	void setContrasena(const char* contrasena);
};

#endif /* REMOTE_SRC_USUARIO_USUARIO_H_ */
