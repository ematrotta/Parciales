
#ifndef PARSER_H_
#define PARSER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Inputs.h"
#include "Outputs.h"
#include "LinkedList.h"
#include "Salon.h"
#include "Juego.h"
#include "Arcade.h"

int parser_SalonFromBinary(FILE* pFile , LinkedList* this);
int parser_JuegoFromBinary(FILE* pFile , LinkedList* this);
int parser_ArcadeFromBinary(FILE* pFile , LinkedList* this);




#endif /* PARSER_H_ */




