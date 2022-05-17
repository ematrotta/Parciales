/*
 * Usuario.h
 *
 *  Created on: 11 may. 2022
 *      Author: Emanuel
 */

#ifndef USUARIO_H_
#define USUARIO_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Inputs.h"
#include "Outputs.h"
#define TAM_CORREO 25
#define TAM_PASSWORD 10
#define TAM_DOMICILIO 50
#define TAM_TIPO_USUARIO 10
#define TIPO_USUARIO_ADMIN 1
#define TIPO_USUARIO_COMUN 2
#define TRUE 0 //LIBRE
#define FALSE 1 //OCUPADO
#define LOW 2 //DADO DE BAJA

typedef struct{
	int idUsuario;
	short int isEmpty;
	short int tipoUsuario;
	char correo[TAM_CORREO];
	char password[TAM_PASSWORD];
	char domicilio[TAM_DOMICILIO];
	int codigoPostal;

}sUsuario;

int sUsuario_initUsuario(sUsuario * list, int len);
int sUsuario_findFreeSpace(sUsuario * list, int len);
int sUsuario_InputsDataUsuario(sUsuario * usuario, char mensajeError[]);
int sUsuario_addUsuario(sUsuario* list, int len, char direccion[],char mail[],char password[],short int tipoUsuario,int codigoPostal);
void sUsuario_printOne(sUsuario usuario);
int sUsuario_printUsuarios(sUsuario* list,int len);
int sUsuario_printAllIdByInit(sUsuario* list,int len,int init);
void sUsuario_printOneForAdmin(sUsuario usuario);
int sUsuario_printUsuariosForAdmin(sUsuario* list,int len);
int sUsuario_printUsuariosForAdminActives(sUsuario* list,int len);


int sUsuario_findUsuarioById(sUsuario * list,int len,int id);
int sUsuario_findUsuarioByMail(sUsuario * list,int len,char mail[]);
int sUsuario_ValidarMailyPassword(sUsuario * list,int len,char mail[],char password[]);


#endif /* USUARIO_H_ */
