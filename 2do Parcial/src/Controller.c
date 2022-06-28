#include "Controller.h"


//*************SALON*************************************************************
/** \brief Carga los datos de los Salon desde el archivo binario
 *
 * \param path char*
 * \param this LinkedList*
 * \return int -1 si no se ingresó bien alguno de los parámetros, -2 si no se pudo abrir el archivo correctamente o no existe,
 * 0 si se pudo realizar más de una lectura
 *
 */
int controller_SalonloadFromBinary(char* path , LinkedList* this) //OK
{
	int retorno;
	int retornoParser;

	FILE* pArchivo;

	retorno = -1;
	if(path != NULL && this != NULL)
	{
		retorno = -2;
		pArchivo = fopen(path,"rb");
		if(pArchivo != NULL)
		{
			//CARGO LOS DATOS DEL ARCHIVO EN MEMORIA DINAMICA. SI LAS LECTURAS FUERON 0, RETORNO 1. SI SON
			//MAYORES A 0 LAS LECTURAS, RETORNO 0 Y SI EL PUNTERO AL ARCHIVO ES NULL PORQUE NO EXISTE ES -2
			retornoParser = parser_SalonFromBinary(pArchivo, this);
			if(retornoParser>0)
			{
				retorno = 0;

			}
			else
			{
				retorno = 1;
			}

		}
		fclose(pArchivo);

	}
    return retorno;
}

/** \brief Baja de Salon
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int -1 si los parametros ingresados son NULL,-2 si ingresó el usuario mal el ID,
 * -3 si no se encontró usuario con el id, 0 si salio todo bien
 *
 *
 */
int controller_removeSalon(LinkedList* thisSalones,LinkedList* thisArcade)
{
	int retorno;
	int i;
	int indexArcade;
	char confirm;
	int idSalon;
	int cantidadSalones;
	int auxId;
	Salon* auxSalon;
	retorno = -1;
	auxSalon = NULL;
	cantidadSalones = ll_len(thisSalones);

	if(thisSalones != NULL && thisArcade != NULL)
	{

		retorno = -2;
		if(cantidadSalones>0)
		{
			retorno = -3;
			if(!Utn_GetNumeroInt(&auxId, "Qué Id desea dar de baja?", "Error. Debe ser entre 1 y 10000", 10000, 1, 3))
			{
				retorno = -4;

				for(i = 0;i<cantidadSalones;i++)
				{

					auxSalon = ll_get(thisSalones, i);
					Salon_getId(auxSalon, &idSalon);
					if(idSalon == auxId)
					{
						retorno = -5;
						//SI LO ENCUENTRA, PIDE CONFIRMAR LA ELIMINACION DEL SALON
						if(!GetCharacter2Options(&confirm, "Se perderan todos los datos. Esta seguro de la baja? S/N", "Ingrese S(si) o N(no)", 'S', 'N', 3))
						{
							if(confirm == 's' || confirm == 'S')
							{
								ll_remove(thisSalones, i);
								//TENGO QUE CONSULTAR NUEVAMENTE POR EL TAMAÑO DE LA LISTA DE ARCADES
								for(i = 0;i<ll_len(thisArcade);i++)
								{
									indexArcade = Arcade_findByIdSalon(thisArcade, idSalon);
									if(indexArcade>=0)
									{
										ll_remove(thisArcade, indexArcade);

									}

								}
								retorno = 0;

							}
						}

						break;
					}
				}
			}
		}


	}

    return retorno;
}


/** \brief Alta de Salon
 *
 * \param path char*
 * \param this LinkedList*
 * \return int -1 si no se ingresó bien alguno de los parámetros, -2 si no se pudieron ingresar los datos de los salones correctamente,
 * 0 si salio todo bien
 *
 */
int controller_addSalon(LinkedList* this)
{
	//SE LE AGREGO LA LISTA DE VUELOS PARA RECONOCER LOS VUELOS DISPONIBLES

	int retorno;
	retorno = -1;

	if(this != NULL)
	{
		retorno = -2;
		if(!Salon_InputsData(this,"No se pudo cargar correctamente"))
		{
			retorno = 0;
		}

	}

	return retorno;
}


/** \brief Listar Salones
 *
 * \param this LinkedList*
 * \return int -1 si no se ingresaron correctamente los parámetros, 0 si está todo bien
 *
 */
int controller_ListSalon(LinkedList* this)
{
	int retorno;
	int i;
	int cantidadSalon;

	retorno = -1;
	Salon* pAux;

	cantidadSalon = ll_len(this);

	if(this != NULL)
	{
		if(cantidadSalon == 0)
		{
			puts("\nNo hay salones para mostrar\n");
		}
		else
		{
			printf("%10s | %25s | %25s | %11s\n","ID","NOMBRE","DIRECCION","TIPO");
			for(i = 0; i<cantidadSalon;i++)
			{
				pAux = ll_get(this,i);
				if(pAux != NULL)
				{
					Salon_printOne(pAux);
				}

			}
		}

		retorno = 0;

	}
    return retorno;
}


/// @fn int controller_SalonsaveAsBinary(char*, LinkedList*)
/// @brief Guardar Salones en archivo binario
///
/// @pre
/// @post
/// @param path
/// @param this
/// @return -1 si alguno de los parámetros es NULL, -2 si el puntero al archivo es NULL, 0 si salio todo bien
int controller_SalonsaveAsBinary(char* path , LinkedList* this)
{
	int retorno;
	int i;
	int cantidadSalon;
	FILE* pArchivo;
	Salon* auxSalon;
	cantidadSalon = ll_len(this);
	retorno = -1;

	if(path != NULL && this != NULL)
	{
		retorno = -2;
		pArchivo = fopen(path,"wb");
		if(pArchivo != NULL)
		{
			if(cantidadSalon>0)
			{
				//CUANDO LOS GUARDA, LOS GUARDA DE FORMA ORDENADA POR ID
				controller_sortSalonById(this);
				for(i=0;i<cantidadSalon;i++)
				{
					auxSalon = ll_get(this, i);
					fwrite(auxSalon,sizeof(Salon),1,pArchivo);
				}
			}
			retorno = 0;
		}
		fclose(pArchivo);
	}
    return retorno;
}

/** \brief Ordenar Salones por ID
 *
 * \param this LinkedList*
 * \return int -1 si no se ingresaron correctamente los parámetros, 0 si salio todo bien
 *
 */
int controller_sortSalonById(LinkedList* this)
{
	int retorno;
	retorno = -1;
	if(this != NULL)
	{
		ll_sort(this,Salon_sortById,1);
		retorno = 0;
	}
    return retorno;
}


/** \brief Modificar datos de Salon
 *
 * \param this LinkedList*
 * \return int -1 si no se ingresó correctamente alguno de los parámetros, -2 si el id no está en el rango
 * -3 si el id ingresado no se encontró, -4 si la opción de modificar no se seleccionó correctamente
 * -5 si el dato a modificar es erroneo, 0 si salio todo bien
 *
 */
int controller_editSalon(LinkedList* this)
{

	int retorno;
	int i;
	int option;
	int idSalon;
	int tamLista;
	int auxId;
	int indexSalon;
	int auxTipo;
	char nombre[LEN_NAME_SALON];
	char direccion[LEN_DIR_SALON];
	Salon* auxSalon;
	retorno = -1;
	if(this != NULL)
	{
		tamLista = ll_len(this);

		if(tamLista == 0)
		{
			puts("\nNo Hay Salones Cargados\n\n");
		}
		else
		{
			controller_ListSalon(this);
			retorno = -2;
			if(!Utn_GetNumeroInt(&auxId, "Qué Id desea modificar?", "Error. Debe ser entre 1 y 10000", 10000, 1, 3))
			{
				retorno = -3;
				for(i = 0;i<tamLista;i++)
				{

					auxSalon = ll_get(this, i);
					Salon_getId(auxSalon, &idSalon);
					if(idSalon == auxId)
					{
						indexSalon = i;
						break;
					}
				}

				if(indexSalon>=0)
				{	//SI ENCUENTRA EL ID
					retorno = -4;
					if(!Utn_GetNumeroInt(&option, "Qué dato desea modificar?\n1. Nombre\n2. Direccion"
							"\n3. Tipo de salon\nOPCIÓN", "ERROR. debe ser entre 1 y 3", 3, 1, 3))
					{
						retorno = -5;
						switch(option)
						{
						case 1:
							//NOMBRE
							if(!Utn_GetName(nombre, LEN_NAME_SALON, "Ingrese el nuevo nombre", "No es un nombre. Reintente", 3))
							{
								Salon_setNombre(auxSalon, nombre);
								retorno = 0;
							}
							break;
						case 2:
							//DIRECCION

							if(!Utn_GetStringAlfaNumericaPlus(direccion, "Ingrese la nueva direccion", "No es una direccion. Reintente", LEN_DIR_SALON, 3))
							{
								Salon_setDireccion(auxSalon, direccion);
								retorno = 0;
							}
							break;
						case 3:
							//TIPO
							if(!Utn_GetNumeroInt(&auxTipo, "Ingrese el tipo:\n1. Shopping\n"
									"2. Local\nOPCIÓN", "La opción debe ser entre 1 y 2", 2, 1, 3))
							{
								Salon_setTipo(auxSalon, auxTipo);
								retorno = 0;
							}
							break;
						}

					}
				}

			}

		}
	}


    return retorno;

}

//*************JUEGO*************************************************************

/** \brief Carga los datos de los Juegos desde el archivo binario
 *
 * \param path char*
 * \param this LinkedList*
 * \return int -1 si no se ingresó bien alguno de los parámetros, -2 si no se pudo abrir el archivo correctamente o no existe,
 * 0 si se pudo realizar más de una lectura
 *
 */
int controller_JuegoloadFromBinary(char* path , LinkedList* this) //OK
{
	int retorno;
	int retornoParser;

	FILE* pArchivo;

	retorno = -1;
	if(path != NULL && this != NULL)
	{
		retorno = -2;
		pArchivo = fopen(path,"rb");
		if(pArchivo != NULL)
		{
			//CARGO LOS DATOS DEL ARCHIVO EN MEMORIA DINAMICA. SI LAS LECTURAS FUERON 0, RETORNO 1. SI SON
			//MAYORES A 0 LAS LECTURAS, RETORNO 0.
			retornoParser = parser_JuegoFromBinary(pArchivo, this);
			if(retornoParser>0)
			{

				retorno = 0;

			}
			else
			{
				retorno = 1;
			}

		}
		fclose(pArchivo);

	}
    return retorno;
}


/// @fn int controller_sortJuegoById(LinkedList*)
/// @brief
///
/// @pre
/// @post
/// @param this
/// @return -1 si el puntero a LinkedList es NULL, 0 si salio todo bien
int controller_sortJuegoById(LinkedList* this) //OK
{
	int retorno;
	retorno = -1;
	if(this != NULL)
	{
		ll_sort(this,Juego_sortById,1);
		retorno = 0;
	}
    return retorno;
}

/// @fn int controller_JuegosaveAsBinary(char*, LinkedList*)
/// @brief Guardar Juegos en archivo binario
///
/// @pre
/// @post
/// @param path
/// @param this
/// @return -1 si alguno de los parámetros es NULL, -2 si el puntero al archivo es NULL o no existe, 0 si salio todo bien
int controller_JuegosaveAsBinary(char* path , LinkedList* this)
{
	int retorno;
	int i;
	int cantidadJuegos;
	FILE* pArchivo;
	Juego* auxJuego;
	cantidadJuegos = ll_len(this);
	retorno = -1;
	if(path != NULL && this != NULL)
	{
		retorno = -2;
		pArchivo = fopen(path,"wb");
		if(pArchivo != NULL)
		{
			if(cantidadJuegos>0)
			{
				//CUANDO LOS GUARDA, LOS ORDENA POR ID
				controller_sortJuegoById(this);
				for(i=0;i<cantidadJuegos;i++)
				{
					auxJuego = ll_get(this, i);
					fwrite(auxJuego,sizeof(Juego),1,pArchivo);
				}
			}

			retorno = 0;
		}
		fclose(pArchivo);
	}
    return retorno;
}

/** \brief Alta de Juego
 *
 * \param path char*
 * \param this LinkedList*
 * \return int -1 si no se ingresó bien alguno de los parámetros, -2 si no se pudieron ingresar los datos de los Juego correctamente,
 * 0 si salio todo bien
 *
 */
int controller_addJuego(LinkedList* this)
{

	int retorno;
	retorno = -1;

	if(this != NULL)
	{
		retorno = -2;
		if(!Juego_InputsData(this,"No se pudo cargar correctamente"))
		{
			retorno = 0;
		}

	}

	return retorno;
}


/** \brief Listar Juegos
 *
 * \param this LinkedList*
 * \return int -1 si no se ingresaron correctamente los parámetros, 0 si está todo bien
 *
 */
int controller_ListJuego(LinkedList* this)
{
	int retorno;
	int i;
	int cantidadJuego;

	retorno = -1;
	Juego* pAux;

	cantidadJuego = ll_len(this);

	if(this != NULL)
	{
		if(cantidadJuego == 0)
		{
			puts("\nNo hay Juegos para mostrar\n");
		}
		else
		{
			printf("%10s | %25s | %25s | %11s\n","ID","NOMBRE","EMPRESA","TIPO");
			for(i = 0; i<cantidadJuego;i++)
			{
				pAux = ll_get(this,i);
				if(pAux != NULL)
				{
					Juego_printOne(pAux);
				}

			}
		}

		retorno = 0;

	}
    return retorno;
}


//*************ARCADE*************************************************************

/** \brief Carga los datos de los Arcade desde el archivo binario
 *
 * \param path char*
 * \param this LinkedList*
 * \return int -1 si no se ingresó bien alguno de los parámetros, -2 si no se pudo abrir el archivo correctamente,
 * 0 si se pudo realizar más de una lectura
 *
 */
int controller_ArcadeloadFromBinary(char* path , LinkedList* this)
{
	int retorno;
	int retornoParser;

	FILE* pArchivo;

	retorno = -1;
	if(path != NULL && this != NULL)
	{
		//RETORNA -2 SI NO PUDO ABRIR EL ARCHIVO
		retorno = -2;
		pArchivo = fopen(path,"rb");
		if(pArchivo != NULL)
		{
			//CARGO LOS DATOS DEL ARCHIVO EN MEMORIA DINAMICA. SI LAS LECTURAS FUERON 0, RETORNO 1. SI SON
			//MAYORES A 0 LAS LECTURAS, RETORNO 0.
			retornoParser = parser_ArcadeFromBinary(pArchivo, this);
			if(retornoParser>0)
			{

				retorno = 0;

			}
			else
			{
				//SI ES MENOR O IGUAL A 0
				retorno = 1;
			}

		}
		fclose(pArchivo);

	}
    return retorno;
}

/** \brief Alta de Juego
 *
 * \param path char*
 * \param this LinkedList*
 * \return int -1 si no se ingresó bien alguno de los parámetros, -2 si no se pudieron ingresar los datos de los Juego correctamente,
 * 0 si salio todo bien
 *
 */
int controller_addArcade(LinkedList* thisArcades,LinkedList* thisJuegos,LinkedList* thisSalones)
{

	int retorno;
	retorno = -1;

	if(thisArcades != NULL && thisJuegos != NULL && thisSalones != NULL )
	{
		retorno = -2;
		if(!Arcade_InputsData(thisArcades, thisJuegos, thisSalones, "No se pudo cargar correctamente"))
		{
			retorno = 0;
		}

	}

	return retorno;
}


/** \brief Listar Juegos
 *
 * \param this LinkedList*
 * \return int -1 si no se ingresaron correctamente los parámetros, 0 si está todo bien
 *
 */
int controller_ListArcade(LinkedList* thisArcades, LinkedList* thisSalones, LinkedList* thisJuegos)
{
	int retorno;
	int i;
	int cantidadArcades;

	retorno = -1;
	Arcade* pAux;

	cantidadArcades = ll_len(thisArcades);

	if(thisArcades != NULL && thisSalones != NULL && thisJuegos != NULL)
	{
		if(cantidadArcades == 0)
		{
			puts("\nNo hay Arcades para mostrar\n");
		}
		else
		{
			printf("%10s | %25s | %10s | %10s | %25s| %25s| %25s| %25s\n","ID ARCADE","NACIONALIDAD","JUGADORES","FICHAS","JUEGO","GENERO","SALON","SONIDO");
			for(i = 0; i<cantidadArcades;i++)
			{
				pAux = ll_get(thisArcades,i);
				if(pAux != NULL)
				{
					Arcade_printOne(pAux, thisSalones, thisJuegos);
				}

			}
		}

		retorno = 0;

	}
    return retorno;
}



/// @fn int controller_ArcadesaveAsBinary(char*, LinkedList*)
/// @brief Guardar Juegos en archivo binario
///
/// @pre
/// @post
/// @param path
/// @param this
/// @return -1 si alguno de los parámetros es NULL, -2 si el puntero al archivo es NULL, 0 si salio todo bien
int controller_ArcadesaveAsBinary(char* path , LinkedList* this)
{
	int retorno;
	int i;
	int cantidadArcade;
	FILE* pArchivo;
	Arcade* auxArcade;
	cantidadArcade = ll_len(this);
	retorno = -1;
	if(path != NULL && this != NULL)
	{
		retorno = -2;
		pArchivo = fopen(path,"wb");
		if(pArchivo != NULL)
		{
			if(cantidadArcade>0)
			{
				//CUANDO LOS GUARDA, LOS ORDENA POR ID
				controller_sortArcadeById(this);
				for(i=0;i<cantidadArcade;i++)
				{
					auxArcade = ll_get(this, i);
					fwrite(auxArcade,sizeof(Arcade),1,pArchivo);
				}
			}

			retorno = 0;
		}
		fclose(pArchivo);
	}
    return retorno;
}

/** \brief Ordenar Arcades por ID
 *
 * \param this LinkedList*
 * \return int -1 si no se ingresaron correctamente los parámetros, 0 si salio todo bien
 *
 */
int controller_sortArcadeById(LinkedList* this)
{
	int retorno;
	retorno = -1;
	if(this != NULL)
	{
		ll_sort(this,Arcade_sortById,1);
		retorno = 0;
	}
    return retorno;
}


/** \brief Modificar datos de Arcade
 *
 * \param this LinkedList*
 * \return int -1 si no se ingresó correctamente alguno de los parámetros, -2 si el id no está en el rango
 * -3 si el id ingresado no se encontró, -4 si la opción de modificar no se seleccionó correctamente
 * -5 si el dato a modificar es erroneo, 0 si salio todo bien
 *
 */
int controller_editArcade(LinkedList* thisArcades, LinkedList* thisJuegos, LinkedList* thisSalones)
{

	int retorno;
	int indexArcade;
	int auxId;
	int option;
	int jugadores;
	int cantidadArcades;
	int cantidadJuegos;
	int cantidadSalones;
	Arcade* auxArcade;
	retorno = -1;
	if(thisArcades != NULL && thisJuegos != NULL && thisSalones != NULL)
	{
		cantidadArcades = ll_len(thisArcades);
		cantidadJuegos = ll_len(thisJuegos);
		cantidadSalones = ll_len(thisSalones);
		retorno = -2;

		//SI NO HAY JUEGOS NI SALONES, NO SE PUEDE CARGAR
		if(cantidadJuegos>0 && cantidadSalones>0)
		{
			retorno = -3;
			if(cantidadArcades == 0)
			{
				puts("\nNo Hay Arcades Cargados\n\n");
			}
			else
			{
				controller_ListArcade(thisArcades,thisSalones,thisJuegos);
				retorno = -4;
				if(!Utn_GetNumeroInt(&auxId, "Qué Id desea modificar?", "Error. Debe ser entre 1 y 10000", 10000, 1, 3))
				{
					//BUSCO SI HAY UN ARCADE CON ESE INDICE
					retorno = -5;
					indexArcade = Arcade_findById(thisArcades, auxId);

					if(indexArcade>=0)
					{	//SI ENCUENTRA EL ID
						auxArcade = ll_get(thisArcades, indexArcade);
						retorno = -6;
						if(!Utn_GetNumeroInt(&option, "Qué dato desea modificar?\n1. Cantidad de Jugadores\n2. Juego que contiene"
								"\nOPCIÓN", "ERROR. debe ser entre 1 y 2", 2, 1, 3))
						{
							retorno = -7;
							switch(option)
							{
							case 1:
								//CANTIDAD JUGADORES
								if(!Utn_GetNumeroInt(&jugadores, "Ingrese la nueva cantidad", "La cantidad debe estar entre 1 y 4", LIMITE_JUGADORES, 1, 3))
								{
									Arcade_setJugadores(auxArcade, jugadores);
									retorno = 0;
								}
								break;
							case 2:
								//JUEGOS
								controller_ListJuego(thisJuegos);
								if(!Utn_GetNumeroInt(&auxId, "Qué Id de juego desea colocar", "Error. Debe ser entre 1 y 10000", 10000, 1, 3))
								{
									//VERIFICO QUE EXISTA EL JUEGO
									if(Juego_findById(thisJuegos, auxId)>=0)
									{
										Arcade_setIdJuego(auxArcade, auxId);
										retorno = 0;
									}
								}
								break;
							}

						}
					}

				}

			}
		}


	}

    return retorno;
}

/** \brief Baja de Arcade
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int -1 si los parametros ingresados son NULL,-2 si ingresó el usuario mal el ID,
 * -3 si no se encontró usuario con el id, 0 si salio todo bien
 *
 *
 */
int controller_removeArcade(LinkedList* thisArcade)
{
	int retorno;
	int i;
	char confirm;
	int idArcade;
	int cantidadArcades;
	int auxId;
	Arcade* auxArcade;
	retorno = -1;
	auxArcade = NULL;
	cantidadArcades = ll_len(thisArcade);

	if(thisArcade != NULL)
	{

		retorno = -2;
		if(cantidadArcades>0)
		{
			retorno = -3;
			if(!Utn_GetNumeroInt(&auxId, "Qué Id desea dar de baja?", "Error. Debe ser entre 1 y 10000", 10000, 1, 3))
			{
				retorno = -4;

				for(i = 0;i<cantidadArcades;i++)
				{

					auxArcade = ll_get(thisArcade, i);
					Arcade_getIdArcade(auxArcade, &idArcade);
					if(idArcade == auxId)
					{
						retorno = -5;
						//SI LO ENCUENTRA, PIDE CONFIRMAR LA ELIMINACION DEL SALON
						if(!GetCharacter2Options(&confirm, "Se perderan todos los datos. Esta seguro de la baja? S/N", "Ingrese S(si) o N(no)", 'S', 'N', 3))
						{
							if(confirm == 's' || confirm == 'S')
							{
								ll_remove(thisArcade, i);
								retorno = 0;

							}
						}

						break;
					}
				}
			}
		}


	}

    return retorno;
}






/// @fn int Arcade_InputsData(LinkedList*, char[])
/// @brief Agregar datos a una entidad de forma manual
///
/// @pre
/// @post
/// @param this Array de la estructura
/// @param mensajeError
/// @return -1 si alguno de los parametros es NULL, -2 si se ingresó mal el nombre, -3 si ingreso mal la direccion,
/// -4 si ingreso mal el tipo, -5 si ingreso un ID menor o igual a 0, -6 si no se generó una entidad en memoria dinamica
/// 0 si salio todo bien
int Arcade_InputsData(LinkedList* thisArcades,LinkedList* thisJuegos,LinkedList* thisSalones,char mensajeError[])
{
	int retorno;
	int auxTipoSonido;
	int idArcade;
	int idSalon;
	int idJuego;
	int jugadores;
	int cantidadMaxFichas;
	char nacionalidad[LEN_NAC];
	int cantidadSalones;
	int cantidadJuegos;

	retorno = -1;


	if(thisArcades != NULL && thisSalones != NULL && thisJuegos != NULL &&  mensajeError!= NULL)
	{
		cantidadSalones = ll_len(thisSalones);
		cantidadJuegos = ll_len(thisJuegos);

		retorno = -2;
		if(cantidadJuegos>0 && cantidadSalones>0)
		{
			Arcade* arcade;
			//INGRESO MAL NACIONALLIDAD
			retorno = -3;
			if(!Utn_GetName(nacionalidad, LEN_NAC, "Ingrese la nacionalidad", "Error debe ser albetica sin espacios", 3))
			{
				//INGRESO MAL TIPO SONIDO
				retorno = -4;

				if(!Utn_GetNumeroInt(&auxTipoSonido, "Ingrese el tipo de sonido:\n1. Mono\n"
						"2. Estereo\nOPCIÓN", "La opción debe ser entre 1 y 2", 2, 1, 3))
				{
					//NO SE COLOCÓ BIEN CANTIDAD DE JUGADORES
					retorno = -5;

					if(!Utn_GetNumeroInt(&jugadores, "Ingrese la maxima cantidad de Jugadores", "La opción debe ser entre 1 y 4",LIMITE_JUGADORES, 1, 3))
					{

						//NO COLOCÓ BIEN CANTIDAD DE FICHAS
						retorno = -6;
						if(!Utn_GetNumeroInt(&cantidadMaxFichas, "Ingrese la maxima cantidad de Fichas", "La opción debe ser entre 1 y 10",LIMITE_FICHAS, 1, 3))
						{

							controller_ListSalon(thisSalones);
							if(!Utn_GetNumeroInt(&idSalon, "Ingrese ID del salon donde lo colocará", "La opción debe ser entre 1 y 10000",10000, 1, 3))
							{
								//SI NO SE COLOCÓ BIEN EL ID DEL SALON
								retorno = -7;
								if(Salon_findById(thisSalones, idSalon)>=0)
								{
									controller_ListJuego(thisJuegos);
									if(!Utn_GetNumeroInt(&idJuego, "Ingrese ID del juego", "La opción debe ser entre 1 y 10000",10000, 1, 3))
									{
										//SI NO SE COLOCÓ BIEN EL ID DEL JUEGO
										retorno = -8;
										if(Juego_findById(thisJuegos, idJuego)>=0)
										{
											retorno = -9;
											idArcade = Arcade_IdGenerator();
											if(idArcade>0)
											{
												retorno = -10;
												arcade = Arcade_newParametros(idArcade, idJuego, idSalon, auxTipoSonido, jugadores, cantidadMaxFichas, nacionalidad);
												if(arcade != NULL)
												{
													ll_add(thisArcades, arcade);
													puts("\nAlta exitosa\n");
													//printf("%10d | %25s | %10d | %10d | %25s| %25s| %25s| %25s\n",auxIdArcade,cAuxNacionalidad,cantidadJugadores,cantidadMaxFichas,cAuxNombreJuego,cAuxGeneroJuego,cAuxNombreSalon,cAuxTipoSonido);
													printf("%10s | %25s | %10s | %10s | %25s| %25s| %25s| %25s\n","ID ARCADE","NACIONALIDAD","JUGADORES","FICHAS","JUEGO","GENERO","SALON","SONIDO");
													Arcade_printOne(arcade, thisSalones, thisJuegos);
													retorno = 0;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			if(retorno<0)
			{
				printf("\n%s\n",mensajeError);
				free(arcade);
				arcade = NULL;
			}

		}

	}

	return retorno;
}


/// @fn int Arcade_printOne(Arcade*)
/// @brief Imprimir una entidad
///
/// @pre
/// @post
/// @param this puntero a la entidad
/// @return -1 si this es NULL, -2 si alguno de los gets es NULL, -3 si no se pudo encontrar el juego,
/// -4 si no se pudo encontrar el salon 0 si salio todo bien
int Arcade_printOne(Arcade* this,LinkedList* thisSalones,LinkedList* thisJuegos)
{
	int retorno;
	int indexJuego;
	int indexSalon;
	retorno = -1;
	int auxIdArcade;
	int auxIdSalon;
	int auxIdJuego;
	int auxTipoJuego;
	int cantidadMaxFichas;
	int cantidadJugadores;
	int auxTipoSonido;
	char cAuxNacionalidad[LEN_NAC];
	char cAuxTipoSonido[LEN_TIPOSONIDO];
	char cAuxNombreJuego[LEN_NAME_JUEGO];
	char cAuxNombreSalon[LEN_NAME_SALON];
	char cAuxGeneroJuego[LEN_NAME_JUEGO];
	Juego* pAuxJuego;
	Salon* pAuxSalon;
	pAuxJuego = NULL;
	pAuxSalon = NULL;


	if(this != NULL && thisSalones != NULL && thisJuegos != NULL)
	{
		retorno = -2;
		if(!Arcade_getIdArcade(this, &auxIdArcade) && !Arcade_getIdJuego(this, &auxIdJuego) && !Arcade_getIdSalon(this, &auxIdSalon) &&
				!Arcade_getJugadores(this, &cantidadJugadores) && !Arcade_getMaxFichas(this, &cantidadMaxFichas) && !Arcade_getTipoSonido(this, &auxTipoSonido)
				&& !Arcade_getNacionalidad(this, cAuxNacionalidad))
		{
			switch(auxTipoSonido)
			{
			case TIPE_MONO:
				strncpy(cAuxTipoSonido,"Mono",LEN_TIPOSONIDO);
				break;
			case TIPO_ESTE:
				strncpy(cAuxTipoSonido,"Estereo",LEN_TIPOSONIDO);
				break;
			}

			retorno = -3;
			indexJuego = Juego_findById(thisJuegos, auxIdJuego);
			if(indexJuego>=0)
			{
				pAuxJuego = ll_get(thisJuegos, indexJuego);
				if(pAuxJuego != NULL)
				{
					Juego_getNombre(pAuxJuego, cAuxNombreJuego);
					Juego_getTipo(pAuxJuego, &auxTipoJuego);
					switch(auxTipoJuego)
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
					retorno = -4;
					indexSalon = Salon_findById(thisSalones, auxIdSalon);
					if(indexSalon>=0)
					{
						pAuxSalon = ll_get(thisSalones, indexSalon);
						if(pAuxSalon != NULL)
						{
							Salon_getNombre(pAuxSalon, cAuxNombreSalon);
							printf("%10d | %25s | %10d | %10d | %25s| %25s| %25s| %25s\n",auxIdArcade,cAuxNacionalidad,cantidadJugadores,cantidadMaxFichas,cAuxNombreJuego,cAuxGeneroJuego,cAuxNombreSalon,cAuxTipoSonido);
							retorno = 0;
						}

					}



				}

			}

		}

	}
	return retorno;
}


/// @fn int Arcade_printOneSpecial1Arcade* this,LinkedList* thisJuegos)
/// @brief Imprimir un Arcade con sus datos y el nombre del juego que contiene
///
/// @pre
/// @post
/// @param this puntero a la entidad
/// @param thisJuegos array de Juegos
/// @return -1 si this o array de Juegos es NULL, -2 si alguno de los gets es NULL, -3 si no se pudo encontrar el juego,
/// -4 si no se pudo encontrar el salon 0 si salio todo bien
int Arcade_printOneSpecial1(Arcade* this,LinkedList* thisJuegos)
{
	int retorno;
	int indexJuego;
	int auxIdArcade;
	int auxIdJuego;
	int cantidadMaxFichas;
	int cantidadJugadores;
	int auxTipoSonido;
	char cAuxNacionalidad[LEN_NAC];
	char cAuxTipoSonido[LEN_TIPOSONIDO];
	char cAuxNombreJuego[LEN_NAME_JUEGO];
	Juego* pAuxJuego;
	pAuxJuego = NULL;


	retorno = -1;
	if(this != NULL && thisJuegos != NULL)
	{
		retorno = -2;
		if(!Arcade_getIdArcade(this, &auxIdArcade) && !Arcade_getIdJuego(this, &auxIdJuego) &&
				!Arcade_getJugadores(this, &cantidadJugadores) && !Arcade_getMaxFichas(this, &cantidadMaxFichas) && !Arcade_getTipoSonido(this, &auxTipoSonido)
				&& !Arcade_getNacionalidad(this, cAuxNacionalidad))
		{
			switch(auxTipoSonido)
			{
			case TIPE_MONO:
				strncpy(cAuxTipoSonido,"Mono",LEN_TIPOSONIDO);
				break;
			case TIPO_ESTE:
				strncpy(cAuxTipoSonido,"Estereo",LEN_TIPOSONIDO);
				break;
			}

			retorno = -3;
			indexJuego = Juego_findById(thisJuegos, auxIdJuego);
			if(indexJuego>=0)
			{
				pAuxJuego = ll_get(thisJuegos, indexJuego);
				if(pAuxJuego != NULL)
				{
					Juego_getNombre(pAuxJuego, cAuxNombreJuego);
					printf("%10d | %25s | %10d | %10d | %25s| %25s\n",auxIdArcade,cAuxNacionalidad,cantidadJugadores,cantidadMaxFichas,cAuxNombreJuego,cAuxTipoSonido);
					retorno = 0;



				}

			}

		}

	}
	return retorno;
}



/// @fn int Arcade_CountByGeneroGame(LinkedList*, LinkedList*, int)
/// @brief Contar los arcades que contienen un tipo de genero de juego determinado en un salon determinado
///
/// @pre
/// @post
/// @param thisArcade
/// @param thisJuego
/// @param generoGame
/// @return la cantidad de juegos del genero encontrados en arcades.
int Arcade_CountByGeneroGameInSalon(LinkedList* thisArcade, LinkedList* thisJuego, int generoGame, int idSalon)
{
	int i;
	int idJuego;
	int indexJuego;
	int cantidadJuegos;
	int cantidadArcades;
	int idSalonAux;
	int auxTipoJuego;
	int contadorJuegosPorGenero;
	Arcade* pAuxArcade;
	Juego* pAuxJuego;
	pAuxArcade = NULL;
	pAuxJuego = NULL;
	contadorJuegosPorGenero = 0;
	if(thisArcade != NULL && thisJuego != NULL)
	{
		cantidadArcades = ll_len(thisArcade);
		cantidadJuegos = ll_len(thisJuego);
		if(cantidadArcades>0 && cantidadJuegos>0)
		{
			for(i = 0;i<cantidadArcades;i++)
			{
				pAuxArcade = ll_get(thisArcade, i);
				if(pAuxArcade != NULL)
				{
					if(!Arcade_getIdJuego(pAuxArcade, &idJuego) && !Arcade_getIdSalon(pAuxArcade, &idSalonAux))
					{
						indexJuego = Juego_findById(thisJuego, idJuego);
						if(indexJuego>=0 && idSalon == idSalonAux)
						{
							pAuxJuego = ll_get(thisJuego, indexJuego);
							if(pAuxJuego != NULL)
							{
								if(!Juego_getTipo(pAuxJuego, &auxTipoJuego))
								{
									if(auxTipoJuego == generoGame)
									{
										contadorJuegosPorGenero++;
									}
								}

							}
						}
					}
				}
			}
		}
	}

	return contadorJuegosPorGenero;
}

/// @fn int Arcade_printByIDSalon(LinkedList*, LinkedList*, int, int(*)(Arcade*, LinkedList*))
/// @brief
///
/// @pre
/// @post
/// @param thisArcade
/// @param thisJuego
/// @param idSalon id del salon a imprimir
/// @param pFuncImpresion Puntero a la fucion para imprirmir arcades
/// @param pFuncSort Puntero a funcion ordenar arcades.
/// @param order 1 ascendente y 0 descendente
/// @return-1 si alguno de los parámetros es NULL o el ID es menor o igual a 0
/// -2 si no hay arcades ni juegos, -3 si no se encontraron arcades con el id de salon, 0 si salio todo bien
int Arcade_printByIDSalon(LinkedList* thisArcade, LinkedList* thisJuego, int idSalon,int (*pFuncImpresion)(Arcade*,LinkedList*),int (*pFuncSort)(void* this1, void* this2),int order)
{
	int i;
	int cantidadJuegos;
	int flagArcadesEnSalon;
	int cantidadArcades;
	int idSalonAux;
	int retorno;
	Arcade* pAuxArcade;
	pAuxArcade = NULL;
	retorno = -1;
	flagArcadesEnSalon = 1;

	if(thisArcade != NULL && thisJuego != NULL && idSalon>0 && (order == 1 || order == 0))
	{
		cantidadArcades = ll_len(thisArcade);
		cantidadJuegos = ll_len(thisJuego);
		retorno = -2;
		//VERIFICO QUE LA CANTIDAD DE ARCADES Y JUEGOS SEA MAYOR A 0
		if(cantidadArcades>0 && cantidadJuegos>0)
		{
			for(i = 0;i<cantidadArcades;i++)
			{
				ll_sort(thisArcade,pFuncSort,order);
				pAuxArcade = ll_get(thisArcade, i);
				if(pAuxArcade != NULL)
				{
					if(!Arcade_getIdSalon(pAuxArcade, &idSalonAux))
					{
						if(idSalon == idSalonAux)
						{
							if(flagArcadesEnSalon == 1)
							{
								puts("\nDATOS DEL ARCADE\n\n");
								printf("%10s | %25s | %10s | %10s | %25s| %25s\n","ID ARCADE","NACIONALIDAD","JUGADORES","FICHAS","NOMBRE JUEGO","TIPO SONIDO");
								flagArcadesEnSalon = 0;
							}

							pFuncImpresion(pAuxArcade, thisJuego);
						}
					}
				}
			}
			if(flagArcadesEnSalon == 1)
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

/// @fn int Arcade_printAcadeByIdSalon(LinkedList*, LinkedList*, LinkedList*, int)
/// @brief
///
/// @pre
/// @post
/// @param thisArcades Array de arcades
/// @param thisJuegos Array de juegos
/// @param thisSalones Array de salones
/// @param idSalon id de salon buscado
/// @return -1 si se ingresaron los parametros NULL o idSalon<0, -2 si no hay arcades, -3 si la lista clonada
/// no tiene nada, -4 si no se pudo imprimir al menos uno de los elementos de la lista clonada
int Arcade_printAcadeByIdSalon(LinkedList* thisArcades,LinkedList* thisJuegos,LinkedList* thisSalones ,int idSalon)
{

	int retorno;
	int i;
	int flagArcadesEnListaFiltrada;
	int cantidadListaClonada;
	int cantidadArcades;
	LinkedList* listaClonada;
	Arcade* pAuxArcade;
	pAuxArcade = NULL;
	listaClonada = NULL;
	flagArcadesEnListaFiltrada = 1;

	retorno = -1;
	if(thisArcades != NULL && thisJuegos != NULL && thisSalones != NULL && idSalon>0 )
	{
		cantidadArcades = ll_len(thisArcades);
		if(cantidadArcades>0)
		{
			listaClonada = ll_FilterLinkedList(thisArcades,Arcade_FilterByIdSalon,&idSalon,1);
			retorno = -2;
			if(listaClonada != NULL)
			{
				cantidadListaClonada = ll_len(listaClonada);
				retorno = -3;
				if(cantidadListaClonada>0)
				{
					for(i = 0;i<cantidadListaClonada;i++)
					{
						pAuxArcade = ll_get(listaClonada, i);
						if(pAuxArcade != NULL)
						{
							if(flagArcadesEnListaFiltrada == 1)
							{
								printf("%10s | %25s | %10s | %10s | %25s| %25s| %25s| %25s\n","ID ARCADE","NACIONALIDAD","JUGADORES","FICHAS","JUEGO","GENERO","SALON","SONIDO");
								flagArcadesEnListaFiltrada = 0;
							}
							Arcade_printOne(pAuxArcade, thisSalones, thisJuegos);

						}

					}
					ll_deleteLinkedList(listaClonada);
					//SI NO SE PUDO FILTRAR NADA
					if(flagArcadesEnListaFiltrada == 1)
					{
						retorno = -4;
					}
					else
					{
						retorno = 0;
					}
				}
			}
		}

	}

	return retorno;
}






