/*
 * Informes.c
 *
 *  Created on: 27 jun. 2022
 *      Author: Emanuel
 */

#include "Informes.h"

//A) LISTAR TODOS LOS SALONES CON MÁS DE 4 ARCADES

/// @fn int Informes_listarSalonesConMas4Arcades(LinkedList*, LinkedList*)
/// @brief Listar salanes con más de 4 Arcades
///
/// @pre
/// @post
/// @param thisSalones Array de salones
/// @param thisArcade Array de arcades
/// @return -1 si alguno de los parámetros es NULL, -2 si no hay salones o la cantidad de arcades es menor que 4,
/// -3 si no encontró ningún salon con los requisitos, 0 si salio todo bien
int Informes_listarSalonesConMas4Arcades(LinkedList* thisSalones,LinkedList* thisArcade)
{
	int retorno;
	int i;
	int flagSalonesMayor4;
	int idSalon;
	int contadorArcades;
	int cantidadSalones;
	int cantidadArcades;
	retorno = -1;
	contadorArcades = 0;
	flagSalonesMayor4 = 1;
	Salon* pAuxSalon;
	if(thisSalones != NULL && thisArcade != NULL)
	{
		retorno = -2;
		cantidadSalones = ll_len(thisSalones);
		cantidadArcades = ll_len(thisArcade);
		//CONSULTO QUE AL MENOS HAYA ALGUN SALON Y AL MENOS 4 ARCADES,
		if(cantidadSalones>0 && cantidadArcades>=4)
		{
			for(i = 0;i<cantidadSalones;i++)
			{
				pAuxSalon = ll_get(thisSalones, i);
				if(pAuxSalon != NULL)
				{
					Salon_getId(pAuxSalon, &idSalon);
					if(idSalon>0)
					{
						contadorArcades = Arcade_CuantitySalonByIdSalon(thisArcade, idSalon);
						if(contadorArcades >= 4)
						{
							if(flagSalonesMayor4 == 1)
							{
								printf("%10s | %25s | %25s | %11s\n","ID","NOMBRE","DIRECCION","TIPO");
								flagSalonesMayor4 = 0;
							}
							Salon_printOne(pAuxSalon);
						}
					}

				}

			}
			//SI NUNCA ENCONTRO SALONES CON MÁS DE 4 ARCADES
			if(flagSalonesMayor4 == 1)
			{
				retorno = -3;
			}
			else
			{
				//SI PUDO LISTAR ALGUNO, EL RETORNO ES 0
				retorno = 0;
			}

		}
	}


	return retorno;
}


//B) LISTAR LOS ARCADE PARA MÁS DE 4 JUGADORES
/// @fn int Informes_printAcadeParaMas2Jugadores(LinkedList*, LinkedList*, LinkedList*)
/// @brief Imprimir los Arcades para más de 2 Jugadores
///
/// @pre
/// @post
/// @param thisArcades Array Arcades
/// @param thisJuegos Array Juegos
/// @param thisSalones Array Salones
/// @return -1 si se ingresaron mal los parámetros, -2 si la cantidad de arcades es 0, -3 si no se encontro
/// ningun arcade para más de 2 jugadores, 0 si salio todo bien
int Informes_printAcadeParaMas2Jugadores(LinkedList* thisArcades, LinkedList* thisJuegos, LinkedList* thisSalones)
{
	int retorno;
	int i;
	int flagArcadesParaMas2Jugadores;
	int cantidadArcades;
	int cantidadJugadores;
	Arcade* pAuxArcade;
	retorno = -1;
	flagArcadesParaMas2Jugadores = 1;
	if(thisArcades != NULL && thisJuegos != NULL && thisSalones != NULL)
	{
		cantidadArcades = ll_len(thisArcades);
		retorno = -2;
		if(cantidadArcades>0)
		{
			for(i = 0;i<cantidadArcades;i++)
			{
				pAuxArcade = ll_get(thisArcades, i);
				Arcade_getJugadores(pAuxArcade, &cantidadJugadores);
				if(cantidadJugadores>2)
				{
					if(flagArcadesParaMas2Jugadores == 1)
					{
						printf("%10s | %25s | %10s | %10s | %25s| %25s| %25s| %25s\n","ID ARCADE","NACIONALIDAD","JUGADORES","FICHAS","JUEGO","GENERO","SALON","SONIDO");
						flagArcadesParaMas2Jugadores = 0;
					}
					Arcade_printOne(pAuxArcade, thisSalones, thisJuegos);
				}
			}
			if(flagArcadesParaMas2Jugadores == 1)
			{
				retorno = -3;
			}
			else
			{
				retorno = 0;
			}

		}

	}

	return retorno;
}

//C)
/// @fn int Informes_printOneSalon(LinkedList*)
/// @brief Imprimir información de un salón específico
///
/// @pre
/// @post
/// @param thisSalon
/// @return -1 si los parámetros son NULL, -2 si ingresa mal el rango del id, -3 si no se pudo encontrar el id,
/// 0 si salio todo bien
int Informes_printOneSalon(LinkedList* thisSalon)
{
	int retorno;
	int opSalon;
	int indexSalon;
	Salon* pAuxSalon;
	pAuxSalon = NULL;
	retorno = -1;
	if(thisSalon != NULL)
	{
		retorno = -2;
		if(!Utn_GetNumeroInt(&opSalon, "Ingrese un id de salón que desea ver su info", "ERROR. debe ser entre 1 y 10000", 10000, 1, 3))
		{
			indexSalon = Salon_findById(thisSalon, opSalon);
			retorno = -3;
			if(indexSalon>=0)
			{
				pAuxSalon = ll_get(thisSalon, indexSalon);
				printf("%10s | %25s | %25s | %11s\n","ID","NOMBRE","DIRECCION","TIPO");
				Salon_printOne(pAuxSalon);
				retorno = 0;

			}
		}
	}

	return retorno;
}

/// @fn int Informes_printSalonCompleto(LinkedList*, LinkedList*, LinkedList*)
/// @brief Imprimir salones completos: Que tengan con juegos:
/// 4 de genero plataforma, 3 del genero laberinto y 5 del genero aventura
///
/// @pre
/// @post
/// @param thisSalon
/// @param thisArcade
/// @param thisJuego
/// @return -1 si alguno de los parámetros es NULL, -2 si la cantidad de salones es menor a 1, -3 si no se
/// encontraron salones completos, 0 si se encontraron salones completos.
int Informes_printSalonCompleto(LinkedList* thisSalon, LinkedList* thisArcade, LinkedList* thisJuego)
{
	int retorno;
	int cantidadSalones;
	int i;
	int idAuxSalon;
	int flagSalonesCompletos;
	Salon* pAuxSalon;
	pAuxSalon = NULL;
	flagSalonesCompletos = 1;
	retorno = -1;
	if(thisArcade != NULL && thisJuego != NULL && thisSalon != NULL)
	{
		cantidadSalones = ll_len(thisSalon);
		retorno = -2;
		if(cantidadSalones>0)
		{
			for(i = 0;i<cantidadSalones;i++)
			{
				pAuxSalon = ll_get(thisSalon, i);
				if(pAuxSalon != NULL)
				{
					if(!Salon_getId(pAuxSalon, &idAuxSalon))
					{
						if(Arcade_CountByGeneroGameInSalon(thisArcade, thisJuego, TIPO_PLAT, idAuxSalon)>=4 &&
								Arcade_CountByGeneroGameInSalon(thisArcade, thisJuego, TIPO_LAB, idAuxSalon)>=3	&&
								Arcade_CountByGeneroGameInSalon(thisArcade, thisJuego, TIPO_AVEN, idAuxSalon)>=5)
						{
							if(flagSalonesCompletos == 1)
							{
								printf("%10s | %25s | %25s | %11s\n","ID","NOMBRE","DIRECCION","TIPO");
								flagSalonesCompletos = 0;
							}
							Salon_printOne(pAuxSalon);
						}
					}

				}


			}
			if(flagSalonesCompletos == 1)
			{
				retorno = -3;
			}
			else
			{
				retorno = 0;
			}

		}

	}


	return retorno;
}

/// @fn int Informes_printSalonConArcadesYJuegos(LinkedList*, LinkedList*, LinkedList*)
/// @brief Imprimir Salon especifico con sus arcades indicando nombre de juego que contiene
///
/// @pre
/// @post
/// @param thisSalon
/// @param thisArcade
/// @param thisJuego
/// @return -1 si alguno de los parámetros es NULL, -2 si no selecciona un ID dentro del rango, -3 si no ecuentra salon,
/// -4 si hay error en la funcion porque no puede mostrar Arcades, 0 si salio todo bien
int Informes_printSalonConArcadesYJuegos(LinkedList* thisSalon, LinkedList* thisArcade, LinkedList* thisJuego)
{
	int retorno;
	int opSalon;
	int indexSalon;
	Salon* pAuxSalon;
	pAuxSalon = NULL;
	retorno = -1;
	if(thisSalon != NULL)
	{
		retorno = -2;
		if(!Utn_GetNumeroInt(&opSalon, "Ingrese un id de salón que desea ver su info", "ERROR. debe ser entre 1 y 10000", 10000, 1, 3))
		{
			indexSalon = Salon_findById(thisSalon, opSalon);
			retorno = -3;
			if(indexSalon>=0)
			{
				pAuxSalon = ll_get(thisSalon, indexSalon);
				if(pAuxSalon != NULL)
				{
					puts("\nDATOS DEL SALON\n\n");
					printf("%10s | %25s | %25s | %11s\n","ID","NOMBRE","DIRECCION","TIPO");
					Salon_printOne(pAuxSalon);
					//SI NO SE ENCONTRO NINGUNO
					retorno = -4;
					if(!Arcade_printByIDSalon(thisArcade, thisJuego, opSalon,Arcade_printOneSpecial1,Arcade_sortById,1))
					{
						retorno = 0;
					}


				}


			}
		}
	}

	return retorno;
}

/// @fn int Informes_printSalonConMasArcades(int(*pFuncOrderArcades)(void*,void*),int,LinkedList*, LinkedList*, LinkedList*)
/// @brief Imprimir Salon especifico con sus arcades indicando nombre de juego que contiene
///
/// @pre
/// @post
/// @param pFuncOrderArcades
/// @param order
/// @param thisSalon
/// @param thisArcade
/// @param thisJuego
/// @return -1 si alguno de los parámetros es NULL o el order es distinto de 1 y 0, -2 si no selecciona un ID dentro del rango, -3 si no pudo imprimir ninguno,
///  0 si salio todo bien
int Informes_printSalonConMasArcades(int(*pFuncOrderArcades)(void*,void*),int orderArcade,LinkedList* thisSalon, LinkedList* thisArcade, LinkedList* thisJuego)
{
	int retorno;
	int auxIdSalon;
	int cantidadSalones;
	int i;
	int idSalonMaxArcades;
	int cantidadArcades;
	int cantidadMaximaArcades;
	int flagMaxCantidadArcade;
	flagMaxCantidadArcade = 0;
	Salon* pAuxSalon;
	Salon* SalonMaxArcades;
	pAuxSalon = NULL;
	retorno = -1;
	if(thisSalon != NULL && thisJuego != NULL && thisArcade != NULL && pFuncOrderArcades != NULL && (orderArcade == 1 || orderArcade == 0))
	{

		cantidadSalones = ll_len(thisSalon);
		retorno = -2;
		if(cantidadSalones>0)
		{
			for(i = 0;i<cantidadSalones;i++)
			{
				pAuxSalon = ll_get(thisSalon, i);
				if(pAuxSalon != NULL)
				{
					Salon_getId(pAuxSalon, &auxIdSalon);
					cantidadArcades = Arcade_CuantitySalonByIdSalon(thisArcade, auxIdSalon);
					if(cantidadArcades>cantidadMaximaArcades || flagMaxCantidadArcade == 0)
					{
						idSalonMaxArcades = auxIdSalon;
						SalonMaxArcades = pAuxSalon;
						cantidadMaximaArcades = cantidadArcades;
						flagMaxCantidadArcade = 1;
					}

				}

			}
			printf("\nDATOS DEL SALON:\nCantidad de Arcades %d\n",cantidadMaximaArcades);
			printf("%10s | %25s | %25s | %11s\n","ID","NOMBRE","DIRECCION","TIPO");
			Salon_printOne(SalonMaxArcades);
			//SI NO SE ENCONTRO NINGUNO
			retorno = -3;
			//IMPRIMO LOS ARCADES SEGUN ID DE SALON
			if(!Arcade_printByIDSalon(thisArcade, thisJuego, idSalonMaxArcades,Arcade_printOneSpecial1,pFuncOrderArcades,orderArcade))
			{
				//VUELVO A ORDENAR LOS ARCADE
				controller_sortArcadeById(thisArcade);
				retorno = 0;
			}
		}

	}

	return retorno;
}

/// @fn int Informes_ImprimirJuegoPorNombreYCondiciones(int(*)(void*, void*), int, LinkedList*, LinkedList*, int, int)
/// @brief Ordenar los nombres de los juegos e imprimir los arcades que tienen un sonido determinado y son un juego de determinado genero
///
/// @pre
/// @post
/// @param pFuncOrderGames Funcion de ordenamiento de Juegos
/// @param orderGames 1 o 0
/// @param thisJuegos Array de Juegos
/// @param thisArcades Array de Arcades
/// @param genero
/// @param tipoSonido
/// @return -1 si alguno de los parametros es NULL o el orden es distinto de 1 o 0, -2 si no hay juegos ni arcades, -3 si no se encontró ninguno
/// con las condiciones, 0 si salio todo bien
int Informes_ImprimirJuegoPorNombreYCondiciones(int(*pFuncOrderGames)(void*,void*),int orderGames,LinkedList* thisJuegos, LinkedList* thisArcades, int genero, int tipoSonido)
{
	int retorno;
	int cantidadJuegos;
	int cantidadArcades;
	char nombreJuego[LEN_NAME_JUEGO];
	char cAuxGeneroJuego[LEN_NAME_JUEGO];
	int idJuego;
	int idArcade;
	int idJuegoArcade;
	int auxTipoSonido;
	int jugadores;
	int generoJuego;
	int i;
	int j;
	int flagArcadeCondiciones;
	flagArcadeCondiciones = 1;
	Juego* pAuxJuego;
	Arcade* pAuxArcade;
	retorno = -1;
	if(pFuncOrderGames != NULL && (orderGames == 1 || orderGames == 0) && thisJuegos != NULL && thisArcades != NULL)
	{
		cantidadArcades = ll_len(thisArcades);
		cantidadJuegos = ll_len(thisJuegos);
		retorno = -2;
		if(cantidadArcades>0 && cantidadJuegos>0)
		{
			//ORDENO LOS JUEGOS
			ll_sort(thisJuegos, pFuncOrderGames, orderGames);
			//RECORRO LOS JUEGOS
			for(i = 0;i<cantidadJuegos;i++)
			{
				pAuxJuego = ll_get(thisJuegos, i);
				//OBTENGO SU NOMBRE, SU ID Y SU TIPO/GENERO
				if(pAuxJuego != NULL)
				{
					Juego_getNombre(pAuxJuego, nombreJuego);
					Juego_getId(pAuxJuego, &idJuego);
					Juego_getTipo(pAuxJuego, &generoJuego);
					//RECORRO LOS ARCADE
					for(j = 0;j<cantidadArcades;j++)
					{
						pAuxArcade = ll_get(thisArcades, j);
						if(pAuxArcade != NULL)
						{
							//OBTENGO DEL ARCADE EL ID DEL JUEGO, ID DEL ARCADE, CANTIDAD DE JUGADORES Y SU TIPO DE SONIDO
							Arcade_getIdJuego(pAuxArcade, &idJuegoArcade);
							Arcade_getTipoSonido(pAuxArcade, &auxTipoSonido);
							Arcade_getJugadores(pAuxArcade, &jugadores);
							Arcade_getIdArcade(pAuxArcade, &idArcade);
							//SI SU ID DE JUEGO, ES IGUAL AL ID DEL JUEGO RECORRIDO Y EL GENERO DEL JUEGO ES IGUAL AL PASADO POR
							//PARAMETRO Y EL TIPO DE SONIDO DEL ARCADE ES IGUAL AL PASADO POR PARÁMETRO
							if(idJuegoArcade == idJuego && generoJuego == genero && auxTipoSonido == tipoSonido)
							{
								switch(generoJuego)
								{
								case TIPO_PLAT:
									strncpy(cAuxGeneroJuego,"Plataforma",LEN_NAME_JUEGO);
									break;
								case TIPO_LAB:
									strncpy(cAuxGeneroJuego,"Laberinto",LEN_NAME_JUEGO);
									break;
								case TIPO_AVEN:
									strncpy(cAuxGeneroJuego,"Aventura",LEN_NAME_JUEGO);
									break;
								case TIPO_OTRO:
									strncpy(cAuxGeneroJuego,"Otro",LEN_NAME_JUEGO);
									break;
								}
								if(flagArcadeCondiciones == 1)
								{
									printf("| %10s | %25s | %25s | %10s |\n","ID ARCADE","NOMBRE JUEGO","GENERO","JUGADORES");
									flagArcadeCondiciones = 0;
								}
								printf("| %10d | %25s | %25s | %10d |\n",idArcade,nombreJuego,cAuxGeneroJuego,jugadores);
							}
						}
					}
				}
			}
			//SI NO SE ENCONTRÓ NINGUNO CON LA CONDICION
			if(flagArcadeCondiciones == 1)
			{
				retorno = -3;
			}
			else
			{
				retorno = 0;
			}
			//VUELVO A ORDENAR LOS JUEGOS POR ID
			controller_sortJuegoById(thisJuegos);
		}
	}


	return retorno;

}

//H) IMPRIMIR ARCADES SEGUN ID DE SALON
int Informes_ImprimirArcadesByIdSalon(LinkedList* thisArcades, LinkedList* thisJuegos,LinkedList* thisSalones)
{
	int retorno;
	int opSalon;
	int indexSalon;
	Salon* pAuxSalon;
	pAuxSalon = NULL;
	retorno = -1;
	if(thisArcades != NULL && thisJuegos != NULL && thisSalones != NULL)
	{
		retorno = -2;
		if(!Utn_GetNumeroInt(&opSalon, "Ingrese un id de un Salon", "ERROR. debe ser entre 1 y 10000", 10000, 1, 3))
		{
			indexSalon = Salon_findById(thisSalones, opSalon);
			retorno = -3;
			if(indexSalon>=0)
			{
				pAuxSalon = ll_get(thisSalones, indexSalon);
				if(pAuxSalon != NULL)
				{

					if(!Arcade_printAcadeByIdSalon(thisArcades, thisJuegos, thisSalones, opSalon))
					{
						retorno = 0;
					}


				}


			}
		}
	}

	return retorno;
}

