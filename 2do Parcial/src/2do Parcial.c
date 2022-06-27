/*
 ============================================================================
 Name        : 2do.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "controller.h"
#define ARCHIVO_SALON "src/Salones.bin"
#define ARCHIVO_JUEGO "src/Juegos.bin"
#define ARCHIVO_ARCADE "src/Arcades.bin"


int main(void) {
	setbuf(stdout,NULL);
	int opcion;
	int retornoControllerEditarArcade;
	int retornoControllerRemoveArcade;
	char opSalir;
	LinkedList* pArraySalones = ll_newLinkedList();
	LinkedList* pArrayJuegos = ll_newLinkedList();
	LinkedList* pArrayArcades = ll_newLinkedList();

	controller_SalonloadFromBinary(ARCHIVO_SALON, pArraySalones); //IF TODOS -2, FLAG 0
	controller_JuegoloadFromBinary(ARCHIVO_JUEGO, pArrayJuegos);
	controller_ArcadeloadFromBinary(ARCHIVO_ARCADE, pArrayArcades); //HACER CONTROLLERS


	do
	{
		if(!Utn_GetNumeroInt(&opcion,"BIENVENDIO AL PROGRAMA\n\nIngrese una opcion:\n"
				"Salon\n"
				"\t1. Alta de Salon\n"
				"\t2. Eliminar Salon\n"
				"\t3. Listar Salones\n"
				"Arcade\n"
				"\t4. Incorporar Arcade\n"
				"\t5. Modificar Arcade\n"
				"\t6. Eliminar Arcade\n"
				"\t7. Listar Arcades\n"
				"Juego\n"
				"\t8. Agregar Juego\n"
				"\t9. Imprimir Juego\n"
				"10. Informes\n"
				"11. Salir\n"
				"\tA) Listar los salones con más de 4 arcade. Indicando ID de salón, nombre, dirección y tipo de salón.\n"
				"\tB) Listar  los  arcade  para  más  de  2  jugadores,  indicando  ID  de  arcade,  cantidad  de  jugadores,  nombre  del juego,  "
				"su género y nombre del salón al que pertenece.\n"
				"\tC) Listar toda la información de un salón en específico ingresado por el usuario. Imprimir ID de salón, nombre, tipo y "
				"dirección.\n"
				"\tD) Un salón se encuentra completo si posee al menos 4 juegos del género plataforma, 3 del género laberinto y 5 del "
				"género Aventura. Listar los salones que cumplan con este mínimo de requisito.\n"
				"\tE) Listar todos los arcades de un salón determinado ingresando su ID. Informar nombre y tipo de salón, listar todos los "
				"arcade con sus datos junto con el nombre del juego que lo compone. \n"
				"\tF) Imprimir el salón con más cantidad de arcade, indicando todos los datos del salón y la cantidad de arcade que posee. "
				"Ordenado de manera ascendente.\n"
				"\tG) Listar los arcades que cumplan con sonido MONO y el género de su juego sea PLATAFORMA, informando nombre "
				"de juego, género y cantidad de jugadores que soporta el arcade. El listado deberá estar ordenado por nombre de juego.\n"
				"\nOPCION", "ERROR La opcion debe ser entre ", 11, 1, 3))
		{
			switch(opcion)
			{
			case 1:
				//ALTA SALON
				controller_addSalon(pArraySalones);
				break;
			case 2:
				//ELIMINAR SALON Y ARCADES QUE LO TIENEN
				if(!controller_ListSalon(pArraySalones))
				{
					if(!controller_removeSalon(pArraySalones, pArrayArcades))
					{
						puts("\nSalon eliminado exitosamente\n");
					}
					else
					{
						puts("\nERROR. Algo salio mal\n");
					}
				}

				break;
			case 3:
				//LISTAR SALONES
				controller_ListSalon(pArraySalones);
				break;
			case 4:
				//INCORPORAR ARCADE
				if(controller_addArcade(pArrayArcades, pArrayJuegos, pArraySalones) != 0)
				{
					puts("\nNo se pudo dar de alta. Verifique haber cargado al menos 1 juego y 1 salon primero\n");
				}
				break;
			case 5:
				//MODIFICAR ARCADE
				retornoControllerEditarArcade = controller_editArcade(pArrayArcades, pArrayJuegos, pArraySalones);
				if( retornoControllerEditarArcade != 0)
				{
					puts("\nError. No se pudo modificar correctamete\n");
					if(retornoControllerEditarArcade == -2)
					{
						puts("\nDebe cargar al menos 1 salon y un juego\n");
					}
				}
				else
				{
					puts("\nModificacion Exitosa\n");
				}
				break;
			case 6:
				//ELIMINAR ARCADE
				retornoControllerRemoveArcade = controller_removeArcade(pArrayArcades);
				if(retornoControllerRemoveArcade != 0)
				{
					puts("\nError. No se pudo eliminar correctamete\n");
					if(retornoControllerRemoveArcade == -2)
					{
						puts("\nDebe cargar al menos un Arcade\n");
					}
				}
				else
				{
					puts("\nBaja exitosa\n");
				}
				break;
			case 7:
				//LISTAR ARCADE
				controller_ListArcade(pArrayArcades, pArraySalones, pArrayJuegos);
				break;
			case 8:
				//AGREGAR JUEGO
				controller_addJuego(pArrayJuegos);
				break;
			case 9:
				//IMPRIMIR JUEGOS
				controller_ListJuego(pArrayJuegos);
				break;
			case 10:
				//INFORMES
				break;
			case 11:
				//SALIR
				if(!GetCharacter2Options(&opSalir, "Desea salir? S/N", "ERROR. S (Si) o N (No)", 'S', 'N', 3))
				{
					//Guardar en los archivos Binarios
					controller_SalonsaveAsBinary(ARCHIVO_SALON, pArraySalones);
					controller_JuegosaveAsBinary(ARCHIVO_JUEGO, pArrayJuegos);
					//Eliminar las LinkedList
					ll_deleteLinkedList(pArraySalones);
					ll_deleteLinkedList(pArrayJuegos);
				}

				break;
			}

		}

	}while(opSalir != 'S' || opSalir != 's');


	return EXIT_SUCCESS;
}
