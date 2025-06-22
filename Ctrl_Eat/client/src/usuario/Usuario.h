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
    char* nombre;
    char* email;
    int telefono;
    char* contrasena;
public:
	Usuario();
	Usuario(int id, const char* nombre, const char* email, int telefono, const char* contrasena);
	Usuario(const char* email, const char* contrasena);
	~Usuario();


	int getId();
	const char* getNombre();
	const char* getEmail();
	int getTelefono();
	const char* getContrasena();


	void setId(int id);
	void setNombre(const char* nombre);
	void setEmail(const char* email);
	void setTelefono(int telefono);
	void setContrasena(const char* contrasena);


	const char* verUsuario();

	int iniciarSesion(char* email, char* contrasena);
	int registrarse();

};

#endif /* REMOTE_SRC_USUARIO_USUARIO_H_ */
