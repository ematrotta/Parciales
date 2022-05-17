/*
 * Trakking.h
 *
 *  Created on: 15 may. 2022
 *      Author: Emanuel
 */

#ifndef TRAKKING_H_
#define TRAKKING_H_
#include <string.h>
#include "Inputs.h"
#include "Outputs.h"
#include <time.h>
#define TAM_AUXILIAR_ESTADO 15
#define TRUE 0
#define FALSE 1 //EN VIAJE
#define LOW 2 //CANCELADO
#define ENTREGADO 3 //ENTREGADO


typedef struct
{
	int idTrakking;
	short int isEmpty;
	int cantidad;
	int distanciaKm;
	long int horaLlegada;
	int FK_idProducto;
	int FK_idComprador;
	int FK_idVendedor;

}sTrakking;

int sTrakking_findTrakkingById(sTrakking * list,int len,int id);
int sTrakking_KmCodigoPostal(int codigoPostal);
int sTrakking_initTrakking(sTrakking * list, int len);
int sTrakking_findFreeSpace(sTrakking * list, int len);
int sTrakking_addTrakking(sTrakking* listTrakking, int lenTrakking, int distancia,int cantidad,int FK_IdProducto ,int FK_IdVendedor,int FK_IdComprador);
//void sTrakking_printOne(sTrakking trakking); A modo de Debbuger
int sTrakking_printTrakkings(sTrakking* list,int len);
int sTrakking_sortTrakkings(sTrakking* list, int len, int order);
int sTrakking_ActualizarEstadosTrakking(sTrakking trakkings[],int lenTrakkings);
int sTrakking_BajaTrakking(sTrakking trakkings[],int lenTrakkings, int idTrakkingBaja);
void sTrakking_printOneForAdmin(sTrakking trakking);
int sTrakking_printTrakkingsForAdmin(sTrakking* list,int len);


#endif /* TRAKKING_H_ */
