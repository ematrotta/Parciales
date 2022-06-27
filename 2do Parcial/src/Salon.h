/*
 * Salon.h
 *
 *  Created on: 23 jun. 2022
 *      Author: Emanuel
 */

#ifndef SALON_H_
#define SALON_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Inputs.h"
#include "Outputs.h"
#include "LinkedList.h"
#define LEN_NAME_SALON 50
#define LEN_DIR_SALON 50
#define TIPE_SHOP 1
#define TIPO_LOC 2
#define ARCHIVO_ULTID_SALON "src/UltimoIdSalon.bin"


typedef struct
{

	char nombreSalon[LEN_NAME_SALON];
	char direccionSalon[LEN_DIR_SALON];
	int tipoSalon;
	int idSalon;

}Salon;

Salon* Salon_new();
Salon* Salon_newParametros(int idSalon,int tipoSalon,char* nombreSalon,char* direccionSalon);

int Salon_setId(Salon* this,int id);
int Salon_getId(Salon* this,int* id);
int Salon_setTipo(Salon* this,int tipo);
int Salon_getTipo(Salon* this,int* tipo);
int Salon_setNombre(Salon* this,char* nombreSalon);
int Salon_getNombre(Salon* this,char* nombre);
int Salon_setDireccion(Salon* this,char* direccionSalon);
int Salon_getDireccion(Salon* this,char* direccion);

int Salon_printOne(Salon* this);
int Salon_SetLastId(int* pId, char* path);
int Salon_GetIdSalonFromBinary(int* pId, char* path);
int Salon_InputsData(LinkedList* this,char mensajeError[]);
int Salon_sortById(void* this1, void* this2);
int Salon_findById(LinkedList* this, int id);





#endif /* SALON_H_ */
