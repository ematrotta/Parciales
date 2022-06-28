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
#include "Informes.h"
#define ARCHIVO_SALON "src/Salones.bin"
#define ARCHIVO_JUEGO "src/Juegos.bin"
#define ARCHIVO_ARCADE "src/Arcades.bin"


int main(void) {
	setbuf(stdout,NULL);
	int opcion;
	int flagModificacion;
	int retornoMenu;
	int retornoControllerEditarArcade;
	int retornoControllerRemoveArcade;
	char opSalir;
	char opSubmenu;
	LinkedList* pArraySalones = ll_newLinkedList();
	LinkedList* pArrayJuegos = ll_newLinkedList();
	LinkedList* pArrayArcades = ll_newLinkedList();

	//SE UTILIZA PARA CONSULTAR SI DESEA GUARDAR CAMBIOS EFECTUADOS EN LA LISTA.
	flagModificacion = 0;


	//CARGO ENTIDADES DESDE LOS ARCHIVOS SI ES QUE EXISTEN
	controller_SalonloadFromBinary(ARCHIVO_SALON, pArraySalones); //OK
	controller_JuegoloadFromBinary(ARCHIVO_JUEGO, pArrayJuegos); //OK
	controller_ArcadeloadFromBinary(ARCHIVO_ARCADE, pArrayArcades); //OK


	do
	{
		retornoMenu = -1;
		if(!Utn_GetNumeroInt(&opcion,"\n\nIngrese una opcion:\n"
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
				"\n10. Informes\n"
				"11. Salir\n\nOPCION", "ERROR La opcion debe ser entre ", 11, 1, 3))
		{
			retornoMenu = -2;
			switch(opcion)
			{
			case 1:
				//ALTA SALON
				if(!controller_addSalon(pArraySalones))
				{
					flagModificacion = 1;
				}
				break;
			case 2:
				//ELIMINAR SALON Y ARCADES QUE LO TIENEN
				if(!controller_ListSalon(pArraySalones))
				{
					if(!controller_removeSalon(pArraySalones, pArrayArcades))
					{
						puts("\nSalon eliminado exitosamente\n");
						flagModificacion = 1;
					}
					else
					{
						puts("\nERROR. Algo salio mal. Verifique haber ingresado el ID Correcto\n");
					}
				}

				break;
			case 3:
				//LISTAR SALONES
				controller_ListSalon(pArraySalones);
				break;
			case 4:
				//INCORPORAR ARCADE
				if(!controller_addArcade(pArrayArcades, pArrayJuegos, pArraySalones))
				{
					flagModificacion = 1;
				}
				else
				{
					puts("\nNo se pudo dar de alta. Verifique haber cargado al menos 1 juego y 1 salon primero\n");
				}
				break;
			case 5:
				//MODIFICAR ARCADE
				retornoControllerEditarArcade = controller_editArcade(pArrayArcades, pArrayJuegos, pArraySalones);
				if(retornoControllerEditarArcade != 0)
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
					flagModificacion = 1;
				}
				break;
			case 6:
				//ELIMINAR ARCADE
				controller_ListArcade(pArrayArcades, pArraySalones, pArrayJuegos);
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
					flagModificacion = 1;
				}
				break;
			case 7:
				//LISTAR ARCADE
				controller_ListArcade(pArrayArcades, pArraySalones, pArrayJuegos);
				break;
			case 8:
				//AGREGAR JUEGO
				if(!controller_addJuego(pArrayJuegos))
				{
					flagModificacion = 1;
				}
				break;
			case 9:
				//IMPRIMIR JUEGOS
				controller_ListJuego(pArrayJuegos);
				break;
			case 10:
				//INFORMES
				if(!Utn_GetChar(&opSubmenu, "\tA) Listar los salones con más de 4 arcade.\n"
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
						"\tH) Imprimir arcades segun ID de salon\n"
						"\nOPCION", "La opción debe ser entre A y G", 'H', 'A', 3))
				{
					switch(opSubmenu)
					{
					case 'A':
						//LISTAR SALONES CON MÁS DE 4 ARCADE
						if(Informes_listarSalonesConMas4Arcades(pArraySalones, pArrayArcades))
						{
							puts("\nNo hay Salones con más de 4 Arcades\n");
						}
					break;
					case 'B':
						//IMPRIMIR ARCADE PARA MAS 2 2 JUGADORES
						if(Informes_printAcadeParaMas2Jugadores(pArrayArcades, pArrayJuegos, pArraySalones))
						{
							puts("\nNo hay Salones para más de 2 jugadores\n");
						}
					break;
					case 'C':
						//IMPRIMIR DATOS DE UN SALON ESPECIFICO
						if(Informes_printOneSalon(pArraySalones))
						{
							puts("\nERROR. No se pudo listar, asegurate de haber cargado al menos un salon o verifica el id\n");
						}
					break;
					case 'D':
						//IMPRIMIR SALONES COMPLETOS
						if(Informes_printSalonCompleto(pArraySalones, pArrayArcades, pArrayJuegos))
						{
							puts("\nNo hay salones completos\n");
						}
					break;
					case 'E':
						//IMPRIMIR SALON CON ARCADES Y NOMBRE DE JUEGOS
						if(Informes_printSalonConArcadesYJuegos(pArraySalones, pArrayArcades, pArrayJuegos) == -3)
						{
							puts("\nVerifique haber ingresado el id de salon correcto\n");
						}
					break;
					case 'F':
						//IMPRIMIR SALON Y ARCADES CON MAYOR CANTIDAD DE ARCADES
						if(Informes_printSalonConMasArcades(Arcade_sortById,1,pArraySalones, pArrayArcades, pArrayJuegos) == -4)
						{
							puts("\nNo hay Arcades para mostrar\n");
						}
					break;
					case 'G':
						//IMPRIMIR ARCADES POR ORDEN ASENDENTE DE NOMBRE DE JUEGO SEGUN GENERO PLATAFORMA Y TIPO DE SONIDO MONO
						if(Informes_ImprimirJuegoPorNombreYCondiciones(Juego_sortByName, 1, pArrayJuegos, pArrayArcades, TIPO_PLAT, TIPE_MONO))
						{
							puts("\nNo hay Arcades Con las caracteristicas indicadas\n");
						}
					break;
					case 'H':
						if(Informes_ImprimirArcadesByIdSalon(pArrayArcades, pArrayJuegos, pArraySalones))
						{
							puts("\nNo se encontraron Arcades con ese ID\n");
						}
						break;
					}
				}
				break;
			case 11:
				//SALIR
				if(!GetCharacter2Options(&opSalir, "Desea salir? S/N", "ERROR. S (Si) o N (No)", 'S', 'N', 3))
				{
					//SI COLOCA QUE SI, EL RETORNO ES 0 Y PREGUNTA SI DESEA ADEMAS GUARDAR LOS CAMBIOS (SI HUBO)
					if(opSalir == 'S' || opSalir == 's')
					{
						retornoMenu = 0;
						//SI HUBO ALGUNA MODIFICACION PREGUNTO SI QUIERE GUARDAR LOS CABIOS
						if(flagModificacion == 1)
						{
							if(!GetCharacter2Options(&opSalir, "Desea gurdar Los cambios? S/N", "ERROR. S (Si) o N (No)", 'S', 'N', 3))
							{
								if(opSalir == 'S' || opSalir == 's')
								{
									//Guardar en los archivos Binarios
									controller_SalonsaveAsBinary(ARCHIVO_SALON, pArraySalones);
									controller_JuegosaveAsBinary(ARCHIVO_JUEGO, pArrayJuegos);
									controller_ArcadesaveAsBinary(ARCHIVO_ARCADE, pArrayArcades);
								}
							}
						}

						//Eliminar las LinkedList
						ll_deleteLinkedList(pArraySalones);
						ll_deleteLinkedList(pArrayJuegos);
						ll_deleteLinkedList(pArrayArcades);

					}


				}

				break;
			}

		}

		//SI ES -2 SIGO DENTRO DEL BUCLE. SI ES -1 SALGO CON EL RETORNO PORQUE INGRESO EL USUARIO MAL LA OPCION
		// MAS DE 3 VECES, Y SI ES 0  ES PORQUE QUISO SALIR
	}while(retornoMenu == -2);


	return retornoMenu;
}
