/*
 * Juego.h
 *
 *  Created on: 23 jun. 2022
 *      Author: Emanuel
 */

#ifndef JUEGO_H_
#define JUEGO_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Inputs.h"
#include "Outputs.h"
#include "LinkedList.h"
#define LEN_NAME_JUEGO 50
#define LEN_EMP_JUEGO 50
#define TIPO_PLAT 1
#define TIPO_LAB 2
#define TIPO_AVEN 3
#define TIPO_OTRO 4
#define ARCHIVO_ULTID_JUEGO "src/UltimoIdJuego.bin"


typedef struct
{

	char nombreJuego[LEN_NAME_JUEGO];
	char empresaJuego[LEN_EMP_JUEGO];
	int tipoJuego;
	int idJuego;

}Juego;

Juego* Juego_new();
Juego* Juego_newParametros(int idJuego,int tipoJuego,char* nombreJuego,char* empresaJuego);

int Juego_setId(Juego* this,int id);
int Juego_getId(Juego* this,int* id);
int Juego_setTipo(Juego* this,int tipo);
int Juego_getTipo(Juego* this,int* tipo);
int Juego_setNombre(Juego* this,char* nombreJuego);
int Juego_getNombre(Juego* this,char* nombreJuego);
int Juego_setEmpresa(Juego* this,char* empresaJuego);
int Juego_getEmpresa(Juego* this,char* empresaJuego);

int Juego_printOne(Juego* this);
int Juego_SetLastId(int* pId, char* path);
int Juego_GetIdJuegoFromBinary(int* pId, char* path);
int Juego_InputsData(LinkedList* this,char mensajeError[]);
int Juego_sortById(void* this1, void* this2);
int Juego_findById(LinkedList* this, int id);





#endif /* JUEGO_H_ */
