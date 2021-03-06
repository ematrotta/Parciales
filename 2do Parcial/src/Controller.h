#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Inputs.h"
#include "Outputs.h"
#include "LinkedList.h"
#include "Salon.h"
#include "Arcade.h"
#include "Juego.h"
#include "Parser.h"

//CONTROLLERS SALON
int controller_SalonloadFromBinary(char* path , LinkedList* this);
int controller_addSalon(LinkedList* this);
int controller_editSalon(LinkedList* this);
int controller_ListSalon(LinkedList* this);
int controller_SalonsaveAsBinary(char* path , LinkedList* this);
int controller_sortSalonById(LinkedList* this);
int controller_removeSalon(LinkedList* ThisSalones, LinkedList* ThisArcades);;

//CONTROLLERS JUEGO
int controller_JuegoloadFromBinary(char* path , LinkedList* this);
int controller_addJuego(LinkedList* this);
int controller_ListJuego(LinkedList* this);
int controller_JuegosaveAsBinary(char* path , LinkedList* this);
int controller_sortJuegoById(LinkedList* this);

//CONTROLLERS ARCADE
int controller_ArcadeloadFromBinary(char* path , LinkedList* this);
int controller_addArcade(LinkedList* thisArcades,LinkedList* thisJuegos,LinkedList* thisSalones);
int controller_ListArcade(LinkedList* thisArcades, LinkedList* thisSalones, LinkedList* thisJuegos);
int controller_ArcadesaveAsBinary(char* path , LinkedList* this);
int controller_sortArcadeById(LinkedList* this);
int controller_editArcade(LinkedList* thisArcades, LinkedList* thisJuegos, LinkedList* thisSalones);
int controller_removeArcade(LinkedList* thisArcade);


//RELACIONES ENTRE ENTIDADES
int Arcade_InputsData(LinkedList* thisArcades,LinkedList* thisJuegos,LinkedList* thisSalones,char mensajeError[]);
int Arcade_printOne(Arcade* this,LinkedList* thisSalones,LinkedList* thisJuegos);
int Arcade_printByIDSalon(LinkedList* thisArcade, LinkedList* thisJuego, int idSalon,int (*pFuncImpresion)(Arcade*,LinkedList*),int (*pFuncSort)(void* this1, void* this2),int order);
int Arcade_printOneSpecial1(Arcade* this,LinkedList* thisJuegos);
int Arcade_CountByGeneroGameInSalon(LinkedList* thisArcade, LinkedList* thisJuego, int generoGame, int idSalon);
int Arcade_printAcadeByIdSalon(LinkedList* thisArcades,LinkedList* thisJuegos,LinkedList* thisSalones ,int idSalon);

#endif /* CONTROLLER_H_ */


