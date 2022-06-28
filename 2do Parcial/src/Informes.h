/*
 * Informes.h
 *
 *  Created on: 27 jun. 2022
 *      Author: Emanuel
 */

#ifndef SRC_INFORMES_H_
#define SRC_INFORMES_H_
#include "controller.h"

//A)
int Informes_listarSalonesConMas4Arcades(LinkedList* thisSalones,LinkedList* thisArcade);
//B)
int Informes_printAcadeParaMas2Jugadores(LinkedList* thisArcades, LinkedList* thisJuegos, LinkedList* thisSalones);
//C)
int Informes_printOneSalon(LinkedList* thisSalon);
//D)
int Informes_printSalonCompleto(LinkedList* thisSalon, LinkedList* thisArcade, LinkedList* thisJuego);
//E)
int Informes_printSalonConArcadesYJuegos(LinkedList* thisSalon, LinkedList* thisArcade, LinkedList* thisJuego);
//F)
int Informes_printSalonConMasArcades(int(*pFuncOrderArcades)(void*,void*),int orderArcade,LinkedList* thisSalon, LinkedList* thisArcade, LinkedList* thisJuego);
//G)
int Informes_ImprimirJuegoPorNombreYCondiciones(int(*pFuncOrderGames)(void*,void*),int orderGames,LinkedList* thisJuegos, LinkedList* thisArcades, int genero, int tipoSonido);



#endif /* SRC_INFORMES_H_ */
