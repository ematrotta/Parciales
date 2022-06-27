/*
 * Arcade.c
 *
 *  Created on: 23 jun. 2022
 *      Author: Emanuel
 */

#include "Arcade.h"

/// @fn int Arcade_IdGenerator(void)
/// @brief Generar un ID. Tomando de un archivo, buscando el último Id, lo incrementa, guarda en el mismo archivo
/// el nuevo id y éste mismo lo retorna
///
/// @pre
/// @post
/// @return Retorna El Id generado
int Arcade_IdGenerator(void)
{
	int initId;
	initId = 0;

	if(!Arcade_GetIdArcadeFromBinary(&initId,ARCHIVO_ULTID_ARCADE))
	{
		initId++;
		Arcade_SetLastId(&initId,ARCHIVO_ULTID_ARCADE);
	}
	return initId;
}

/// @fn Arcade Arcade_new*()
/// @brief Crea un puntero a estructura con memoria dinámica
///
/// @pre
/// @post
/// @return puntero a entidad
Arcade* Arcade_new()
{
	Arcade* p;
	p = (Arcade*)malloc(sizeof(Arcade));
	return p;
}

/// @fn Arcade Arcade_newParametros*(int, int, int, int, int, int, char*)
/// @brief Carga datos a una estructura
///
/// @pre
/// @post
/// @param idArcade
/// @param idJuego
/// @param idSalon
/// @param tipoSonido
/// @param cantJugadores
/// @param maxFichas
/// @param nacionalidad
/// @return Si todo salio bien, retorna un puntero en memoria dinamica de la estructura, sino NULL
Arcade* Arcade_newParametros(int idArcade,int idJuego,int idSalon,int tipoSonido,int cantJugadores,int maxFichas,char* nacionalidad)
{

	Arcade* pAuxArcade;
	pAuxArcade = NULL;
	if(nacionalidad != NULL)
	{
		if(idArcade>0 && idJuego>0 && idSalon>0 && cantJugadores>0 && maxFichas>0 && (tipoSonido == TIPO_ESTE || tipoSonido == TIPE_MONO))
		{
			pAuxArcade = Arcade_new();
			if(Arcade_setIdArcade(pAuxArcade,idArcade)<0 || Arcade_setIdJuego(pAuxArcade,idJuego)<0 || Arcade_setIdSalon(pAuxArcade,idSalon)<0
					||Arcade_setTipoSonido(pAuxArcade, tipoSonido)<0 || Arcade_setJugadores(pAuxArcade, cantJugadores)<0 ||
					Arcade_setMaxFichas(pAuxArcade, maxFichas)<0 || Arcade_setNacionalidad(pAuxArcade, nacionalidad)<0)

			{
				free(pAuxArcade);
				pAuxArcade = NULL;

			}

		}

	}

	return pAuxArcade;
}

/// @fn int Arcade_setIdArcade(Arcade*, int)
/// @brief Colocar un ID a la entidad
///
/// @pre
/// @post
/// @param this Puntero a la entidad
/// @param id
/// @return -1 si se ingresaron incorrectamente los parámetros, 0 si salio todo bien
int Arcade_setIdArcade(Arcade* this,int id)
{
	int retorno;
	retorno = -1;


	if(this != NULL && id>0)
	{
		this->idArcade = id;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Arcade_getIdArcade(Arcade*, int*)
/// @brief Obtener un ID de una estructura Arcade
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Arcade_getIdArcade(Arcade* this,int* id)
{
	int retorno;
	retorno = -1;

	if(this != NULL && id != NULL)
	{
		*id = this->idArcade;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Arcade_setIdJuego(Arcade*, int)
/// @brief Colocar un ID Juego a la entidad
///
/// @pre
/// @post
/// @param this Puntero a la entidad
/// @param id
/// @return -1 si se ingresaron incorrectamente los parámetros, 0 si salio todo bien
int Arcade_setIdJuego(Arcade* this,int id)
{
	int retorno;
	retorno = -1;


	if(this != NULL && id>0)
	{
		this->idJuego = id;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Arcade_getIdJuego(Arcade*, int*)
/// @brief Obtener un ID de Juego dentro de la estructura Arcade
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Arcade_getIdJuego(Arcade* this,int* id)
{
	int retorno;
	retorno = -1;

	if(this != NULL && id != NULL)
	{
		*id = this->idJuego;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Arcade_setIdSalon(Arcade*, int)
/// @brief Colocar un ID Salon a la entidad
///
/// @pre
/// @post
/// @param this Puntero a la entidad
/// @param id
/// @return -1 si se ingresaron incorrectamente los parámetros, 0 si salio todo bien
int Arcade_setIdSalon(Arcade* this,int id)
{
	int retorno;
	retorno = -1;


	if(this != NULL && id>0)
	{
		this->idSalon = id;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Arcade_getIdSalon(Arcade*, int*)
/// @brief Obtener un ID de Salon dentro de la estructura Arcade
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Arcade_getIdSalon(Arcade* this,int* id)
{
	int retorno;
	retorno = -1;

	if(this != NULL && id != NULL)
	{
		*id = this->idSalon;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Arcade_setJugadores(Arcade*, int)
/// @brief Colocar cantidadJugadores a la entidad
///
/// @pre
/// @post
/// @param this Puntero a la entidad
/// @param id
/// @return -1 si se ingresaron incorrectamente los parámetros, 0 si salio todo bien
int Arcade_setJugadores(Arcade* this,int cantidadJugadores)
{
	int retorno;
	retorno = -1;


	if(this != NULL && cantidadJugadores>0)
	{
		this->cantidadJugadores = cantidadJugadores;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Arcade_getJugadores(Arcade*, int*)
/// @brief Obtener cantidad Jugadores dentro de la estructura Arcade
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Arcade_getJugadores(Arcade* this,int* cantidadJugadores)
{
	int retorno;
	retorno = -1;

	if(this != NULL && cantidadJugadores != NULL)
	{
		*cantidadJugadores = this->cantidadJugadores;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Arcade_setMaxFichas(Arcade*, int)
/// @brief Colocar cantidad de fichas a la entidad
///
/// @pre
/// @post
/// @param this Puntero a la entidad
/// @param id
/// @return -1 si se ingresaron incorrectamente los parámetros, 0 si salio todo bien
int Arcade_setMaxFichas(Arcade* this,int cantidadMaxFichas)
{
	int retorno;
	retorno = -1;


	if(this != NULL && cantidadMaxFichas>0)
	{
		this->cantidadMaxFichas = cantidadMaxFichas;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Arcade_getMaxFichas(Arcade*, int*)
/// @brief Obtener Maxima Cantidad de fichas dentro de la estructura Arcade
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Arcade_getMaxFichas(Arcade* this,int* cantidadMaxFichas)
{
	int retorno;
	retorno = -1;

	if(this != NULL && cantidadMaxFichas != NULL)
	{
		*cantidadMaxFichas = this->cantidadMaxFichas;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Arcade_setTipoSonido(Arcade*, int)
/// @brief Colocar un TIPO de sonido a la entidad
///
/// @pre
/// @post
/// @param this Puntero a la entidad
/// @param id
/// @return -1 si se ingresaron incorrectamente los parámetros, 0 si salio todo bien
int Arcade_setTipoSonido(Arcade* this,int tipo)
{
	int retorno;
	retorno = -1;


	if(this != NULL && tipo>0)
	{
		this->tipoSonido = tipo;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Arcade_getTipo(Arcade*, int*)
/// @brief Obtener tipo de sonido una estructura Arcade
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Arcade_getTipoSonido(Arcade* this,int* tipo)
{
	int retorno;
	retorno = -1;

	if(this != NULL && tipo != NULL)
	{
		*tipo = this->tipoSonido;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Arcade_setNacionalidad(Arcade*, char*)
/// @brief Colocar Nacionalidad a un Arcade
///
/// @pre
/// @post
/// @param this
/// @param nombre
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Arcade_setNacionalidad(Arcade* this,char* nacionalidad)
{
	int retorno;
	retorno = -1;

	if(this != NULL && nacionalidad != NULL)
	{
		strncpy(this->nacionalidad,nacionalidad,LEN_NAC);
		retorno = 0;
	}

	return retorno;
}

/// @fn int Arcade_getNacionalidad(Arcade*, char*)
/// @brief Obtener Nacionalidad de un Arcade
///
/// @pre
/// @post
/// @param this
/// @param nombre
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Arcade_getNacionalidad(Arcade* this,char* nacionalidad)
{
	int retorno;
	retorno = -1;

	if(this != NULL && nacionalidad != NULL)
	{
		strncpy(nacionalidad,this->nacionalidad,LEN_NAC);
		retorno = 0;
	}

	return retorno;
}


/// @fn int Arcade_SetLastId(int*, char*)
/// @brief Escribir el último ID generado en un archivo binario
///
/// @pre
/// @post
/// @param pId puntero al id
/// @param path
/// @return -1 si alguno de los parámetros es NULL, -2 si no se pudo abrir el archivo, -3 si no pudo hacer ninguna lectura
/// 0 si salio todo bien
int Arcade_SetLastId(int* pId, char* path)
{
	int retorno;
	retorno = -1;
	if(path != NULL && pId != NULL)
	{
		retorno = -2;

		FILE* pArchivo = fopen(path,"wb");
		if(pArchivo != NULL)
		{
			retorno = -3;
			retorno = fwrite(pId,sizeof(int),1,pArchivo);
			if(retorno == 1)
			{
				retorno = 0;
			}

		}
		fclose(pArchivo);
	}

	return retorno;
}

/// @fn int Arcade_GetIdArcadeFromBinary(int*, char*)
/// @brief Tomar el ultimo id de un archivo binario
///
/// @pre
/// @post
/// @param pId Puntero al id
/// @param path
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Arcade_GetIdArcadeFromBinary(int* pId, char* path)
{

	int retorno;
	int auxUltimoId;
	int retornoLectura;
	retorno = -1;

	if(path != NULL && pId != NULL)
	{

		retorno = -2;
		FILE* pArchivo = fopen(path,"rb");
		if(pArchivo != NULL)
		{

			retornoLectura = fread(&auxUltimoId,sizeof(int),1,pArchivo);
			if(retornoLectura == 1)
			{
				*pId = auxUltimoId;
				retorno = 0;
			}

		}
		fclose(pArchivo);
		//SI NO PUDO LEER NADA DEL ARCHIVO O LA LECTURA FUE 0, EL VALOR DEL PRIMER ID ES 0
		if(retornoLectura == 0 || retorno == -2)
		{

			*pId = 0;
			retorno = 0;
		}
	}
    return retorno;
}

/*
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
int Arcade_InputsData(LinkedList* this,char mensajeError[])
{
	int retorno;
	int auxTipo;
	int id;
	char auxNombre[LEN_NAME_SALON];
	char auxDireccion[LEN_DIR_SALON];

	retorno = -1;


	if(this != NULL && mensajeError!= NULL)
	{


		Arcade* arcade;
		//INGRESO MAL EL NOMBRE
		retorno = -2;

		if(!Utn_GetStringAlfaNumericaPlus(auxNombre, "Ingrese un Nombre", "No es un Nombre. Reintente", LEN_NAME_SALON, 3))
		{
			//INGRESO MAL DIRECCION
			retorno = -3;

			if(!Utn_GetStringAlfaNumericaPlus(auxDireccion, "Ingrese una dirección", "No es una Direccion. Reintente", LEN_DIR_SALON, 3))
			{
				//INGRESO MAL TIPO
				retorno = -4;

				if(!Utn_GetNumeroInt(&auxTipo, "Ingrese el tipo:\n1. Shopping\n"
						"2. Local\nOPCIÓN", "La opción debe ser entre 1 y 2", 2, 1, 3))
				{
					//NO SE COLOCÓ BIEN EL ID
					retorno = -5;
					id = Arcade_IdGenerator();
					if(id>0)
					{
						retorno = -6;
						arcade = Arcade_newParametros(id, auxTipo, auxNombre, auxDireccion);
						if(arcade != NULL)
						{
							ll_add(this, arcade);
							puts("\nAlta exitosa\n");
							printf("%10s | %25s | %25s | %11s\n\n","ID","NOMBRE","DIRECCION","TIPO");
							Arcade_printOne(arcade);
							retorno = 0;
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

	return retorno;
}

*/
/// @fn int Arcade_sortById(void*, void*)
/// @brief Retornar un valor comparando 2 elementos de 1 estructura: Id
///
/// @pre
/// @post
/// @param this1
/// @param this2
/// @return -2 si ingresó mal alguno de los parámetros, -1 si el elemento 1 es menor que el 2, 1 si el elemento 1 es mayor que el
///  2, 0 si ambos son iguales
int Arcade_sortById(void* this1, void* this2)
{
	int retorno;
	retorno = -2;
	if(this1 != NULL && this2 != NULL)
	{
		Arcade* ArcadeUno;
		Arcade* ArcadeDos;
		//CASTEO LOS VOID*
		ArcadeUno = (Arcade*)this1;
		ArcadeDos = (Arcade*)this2;
		int idUno;
		int idDos;

		if(!Arcade_getIdArcade(ArcadeUno, &idUno) && !Arcade_getIdArcade(ArcadeDos, &idDos))
		{

			if(idUno<idDos)
			{
				retorno = -1;
			}
			else
			{
				if(idUno>idDos)
				{
					retorno = 1;
				}
				else
				{
					retorno = 0;
				}

			}
		}
	}

	return retorno;
}


/// @fn int Arcade_findById(LinkedList*, int)
/// @brief Encontrar el indice de la lista donde se encuentra el id buscado
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si this es NULL o el ID <= 0, -2 si no se pudo encontrar el ID, =<0 con el index
int Arcade_findById(LinkedList* this, int id)
{
	int retorno = -1;
	int i;
	int cantidadArcade;
	int auxId;
	Arcade* pAuxArcade;
	pAuxArcade = NULL;
	if(this != NULL && id>0)
	{
		retorno = -2;
		cantidadArcade = ll_len(this);
		for(i = 0;i<cantidadArcade;i++)
		{
			pAuxArcade = ll_get(this, i);
			Arcade_getIdArcade(pAuxArcade, &auxId);
			if(auxId == id)
			{
				retorno = i;
				break;
			}

		}

	}
	return retorno;
}

/// @fn int Arcade_findByIdSalon(LinkedList*, int)
/// @brief Encontrar Arcades con un ID de salon
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si this es NULL o el ID <= 0, -2 si no se pudo encontrar el ID, =<0 con el index
int Arcade_findByIdSalon(LinkedList* this, int id)
{
	int retorno = -1;
	int i;
	int cantidadArcade;
	int auxId;
	Arcade* pAuxArcade;
	pAuxArcade = NULL;
	if(this != NULL && id>0)
	{
		retorno = -2;
		cantidadArcade = ll_len(this);
		for(i = 0;i<cantidadArcade;i++)
		{
			pAuxArcade = ll_get(this, i);
			if(pAuxArcade != NULL)
			{
				Arcade_getIdSalon(pAuxArcade, &auxId);
				if(auxId == id)
				{
					retorno = i;
					break;
				}
			}


		}


	}
	return retorno;
}

