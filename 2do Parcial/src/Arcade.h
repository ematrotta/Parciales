/*
 * Arcade.h
 *
 *  Created on: 23 jun. 2022
 *      Author: Emanuel
 */

#ifndef ARCADE_H_
#define ARCADE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Inputs.h"
#include "Outputs.h"
#include "LinkedList.h"

#define LEN_NAC 50
#define LEN_TIPOSONIDO 50
#define LIMITE_JUGADORES 4
#define LIMITE_FICHAS 10
#define TIPE_MONO 1
#define TIPO_ESTE 2
#define ARCHIVO_ULTID_ARCADE "src/UltimoIdArcade.bin"



typedef struct
{

	char nacionalidad[LEN_NAC];
	int cantidadJugadores;
	int cantidadMaxFichas;
	int tipoSonido;
	int idArcade;
	int idJuego;
	int idSalon;

}Arcade;

int Arcade_IdGenerator();
Arcade* Arcade_new();
Arcade* Arcade_newParametros(int idArcade,int idJuego,int idSalon,int tipoSonido,int cantJugadores,int maxFichas,char* nacionalidad);

int Arcade_setIdArcade(Arcade* this,int id);
int Arcade_getIdArcade(Arcade* this,int* id);
int Arcade_setIdJuego(Arcade* this,int id);
int Arcade_getIdJuego(Arcade* this,int* id);
int Arcade_setIdSalon(Arcade* this,int id);
int Arcade_getIdSalon(Arcade* this,int* id);
int Arcade_setJugadores(Arcade* this,int cantidadJugadores);
int Arcade_getJugadores(Arcade* this,int* cantidadJugadores);
int Arcade_setMaxFichas(Arcade* this,int cantidadMaxFichas);
int Arcade_getMaxFichas(Arcade* this,int* cantidadMaxFichas);
int Arcade_setTipoSonido(Arcade* this,int tipo);
int Arcade_getTipoSonido(Arcade* this,int* tipo);
int Arcade_setNacionalidad(Arcade* this,char* nacionalidad);
int Arcade_getNacionalidad(Arcade* this,char* nacionalidad);
int Arcade_SetLastId(int* pId, char* path);
int Arcade_GetIdArcadeFromBinary(int* pId, char* path);


//int Arcade_InputsData(LinkedList* this,char mensajeError[]);
int Arcade_sortById(void* this1, void* this2);
int Arcade_findById(LinkedList* this, int id);
int Arcade_findByIdSalon(LinkedList* this, int id);




#endif /* ARCADE_H_ */
