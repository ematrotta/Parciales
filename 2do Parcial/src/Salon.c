/*
 * Salon.c
 *
 *  Created on: 23 jun. 2022
 *      Author: Emanuel
 */

#include "Salon.h"

/// @fn int Salon_IdGenerator(void)
/// @brief Generar un ID. Tomando de un archivo, buscando el último Id, lo incrementa, guarda en el mismo archivo
/// el nuevo id y éste mismo lo retorna
///
/// @pre
/// @post
/// @return Retorna El Id generado
static int Salon_IdGenerator(void)
{
	int initId;
	initId = 0;

	if(!Salon_GetIdSalonFromBinary(&initId,ARCHIVO_ULTID_SALON))
	{
		initId++;
		Salon_SetLastId(&initId,ARCHIVO_ULTID_SALON);
	}
	return initId;
}

/// @fn Salon Salon_new*()
/// @brief Crea un puntero a estructura con memoria dinámica
///
/// @pre
/// @post
/// @return puntero a entidad
Salon* Salon_new()
{
	Salon* p;
	p = (Salon*)malloc(sizeof(Salon));
	return p;
}

/// @fn Salon* Salon_newParametros(int, int, char*, char*)
/// @brief Carga datos a una estructura
///
/// @pre
/// @post
/// @param idSalon
/// @param tipoSalon
/// @param nombreSalon
/// @param direccionSalon
/// @return Si todo salio bien, retorna un puntero en memoria dinamica de la estructura, sino NULL
Salon* Salon_newParametros(int idSalon,int tipoSalon,char* nombreSalon,char* direccionSalon)
{

	Salon* pAuxSalon;
	pAuxSalon = NULL;
	if(nombreSalon != NULL && direccionSalon != NULL)
	{
		if(idSalon>0 && (tipoSalon == TIPE_SHOP || tipoSalon == TIPO_LOC))
		{
			pAuxSalon = Salon_new();
			if(Salon_setId(pAuxSalon,idSalon)<0 || Salon_setNombre(pAuxSalon, nombreSalon)<0 || Salon_setDireccion(pAuxSalon, direccionSalon)<0 ||
					Salon_setTipo(pAuxSalon, tipoSalon)<0)
			{
				free(pAuxSalon);
				pAuxSalon = NULL;

			}

		}

	}

	return pAuxSalon;
}

/// @fn int Salon_setId(Salon*, int)
/// @brief Colocar un ID a la entidad
///
/// @pre
/// @post
/// @param this Puntero a la entidad
/// @param id
/// @return -1 si se ingresaron incorrectamente los parámetros, 0 si salio todo bien
int Salon_setId(Salon* this,int id)
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

/// @fn int Salon_getId(Salon*, int*)
/// @brief Obtener un ID de una estructura Salon
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Salon_getId(Salon* this,int* id)
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

/// @fn int Salon_setTipo(Salon*, int)
/// @brief Colocar un TIPO a la entidad
///
/// @pre
/// @post
/// @param this Puntero a la entidad
/// @param id
/// @return -1 si se ingresaron incorrectamente los parámetros, 0 si salio todo bien
int Salon_setTipo(Salon* this,int tipo)
{
	int retorno;
	retorno = -1;


	if(this != NULL && tipo>0)
	{
		this->tipoSalon = tipo;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Salon_getTipo(Salon*, int*)
/// @brief Obtener tipo de una estructura Salon
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Salon_getTipo(Salon* this,int* tipo)
{
	int retorno;
	retorno = -1;

	if(this != NULL && tipo != NULL)
	{
		*tipo = this->tipoSalon;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Salon_setNombre(Salon*, char*)
/// @brief Colocar el Nombre a un Salon
///
/// @pre
/// @post
/// @param this
/// @param nombre
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Salon_setNombre(Salon* this,char* nombreSalon)
{
	int retorno;
	retorno = -1;

	if(this != NULL && nombreSalon != NULL)
	{
		strncpy(this->nombreSalon,nombreSalon,LEN_NAME_SALON);
		retorno = 0;
	}

	return retorno;
}

/// @fn int Salon_getNombre(Salon*, char*)
/// @brief Obtener el Nombre de un Salon
///
/// @pre
/// @post
/// @param this
/// @param nombre
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Salon_getNombre(Salon* this,char* nombre)
{
	int retorno;
	retorno = -1;

	if(this != NULL && nombre != NULL)
	{
		strncpy(nombre,this->nombreSalon,LEN_NAME_SALON);
		retorno = 0;
	}

	return retorno;
}

/// @fn int Salon_setDireccion(Salon*, char*)
/// @brief Colocar Direccion a un Salon
///
/// @pre
/// @post
/// @param this
/// @param nombre
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Salon_setDireccion(Salon* this,char* direccionSalon)
{
	int retorno;
	retorno = -1;

	if(this != NULL && direccionSalon != NULL)
	{
		strncpy(this->direccionSalon,direccionSalon,LEN_DIR_SALON);
		retorno = 0;
	}

	return retorno;
}

/// @fn int Salon_getNombre(Salon*, char*)
/// @brief Obtener el Nombre de un Salon
///
/// @pre
/// @post
/// @param this
/// @param nombre
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Salon_getDireccion(Salon* this,char* direccion)
{
	int retorno;
	retorno = -1;

	if(this != NULL && direccion != NULL)
	{
		strncpy(direccion,this->direccionSalon,LEN_DIR_SALON);
		retorno = 0;
	}

	return retorno;
}

/// @fn int Salon_printOne(Salon*)
/// @brief Imprimir una entidad
///
/// @pre
/// @post
/// @param this puntero a la entidad
/// @return -1 si this es NULL, -2 si alguno de los gets es NULL, 0 si salio todo bien
int Salon_printOne(Salon* this)
{
	int retorno;
	retorno = -1;
	int auxId;
	char auxNombre[LEN_NAME_SALON];
	char auxDireccion[LEN_DIR_SALON];
	char cAuxTipo[LEN_NAME_SALON];
	int auxTipo;

	if(this != NULL)
	{
		retorno = -2;
		if(!Salon_getId(this, &auxId) && !Salon_getNombre(this, auxNombre) && !Salon_getDireccion(this, auxDireccion)
				&& !Salon_getTipo(this, &auxTipo))
		{
			switch(auxTipo)
			{
			case TIPE_SHOP:
				strncpy(cAuxTipo,"Shopping",LEN_NAME_SALON);
				break;
			case TIPO_LOC:
				strncpy(cAuxTipo,"Local",LEN_NAME_SALON);
				break;
			}
			printf("%10d | %25s | %25s | %11s\n",auxId,auxNombre,auxDireccion,cAuxTipo);
			retorno = 0;
		}

	}
	return retorno;
}

/// @fn int Salon_SetLastId(int*, char*)
/// @brief Escribir el último ID generado en un archivo binario
///
/// @pre
/// @post
/// @param pId puntero al id
/// @param path
/// @return -1 si alguno de los parámetros es NULL, -2 si no se pudo abrir el archivo, -3 si no pudo hacer ninguna lectura
/// 0 si salio todo bien
int Salon_SetLastId(int* pId, char* path)
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

/// @fn int Salon_GetIdSalonFromBinary(int*, char*)
/// @brief Tomar el ultimo id de un archivo binario
///
/// @pre
/// @post
/// @param pId Puntero al id
/// @param path
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Salon_GetIdSalonFromBinary(int* pId, char* path)
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

/// @fn int Salon_InputsData(LinkedList*, char[])
/// @brief Agregar datos a una entidad de forma manual
///
/// @pre
/// @post
/// @param this Array de la estructura
/// @param mensajeError
/// @return -1 si alguno de los parametros es NULL, -2 si se ingresó mal el nombre, -3 si ingreso mal la direccion,
/// -4 si ingreso mal el tipo, -5 si ingreso un ID menor o igual a 0, -6 si no se generó una entidad en memoria dinamica
/// 0 si salio todo bien
int Salon_InputsData(LinkedList* this,char mensajeError[])
{
	int retorno;
	int auxTipo;
	int id;
	char auxNombre[LEN_NAME_SALON];
	char auxDireccion[LEN_DIR_SALON];

	retorno = -1;


	if(this != NULL && mensajeError!= NULL)
	{


		Salon* salon;
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
					id = Salon_IdGenerator();
					if(id>0)
					{
						retorno = -6;
						salon = Salon_newParametros(id, auxTipo, auxNombre, auxDireccion);
						if(salon != NULL)
						{
							ll_add(this, salon);
							puts("\nAlta exitosa");
							printf("%10s | %25s | %25s | %11s\n","ID","NOMBRE","DIRECCION","TIPO");
							Salon_printOne(salon);
							retorno = 0;
						}


					}



				}
			}
		}

		if(retorno<0)
		{
			printf("\n%s\n",mensajeError);
			free(salon);
			salon = NULL;
		}


	}

	return retorno;
}


/// @fn int Salon_sortById(void*, void*)
/// @brief Retornar un valor comparando 2 elementos de 1 estructura: Id
///
/// @pre
/// @post
/// @param this1
/// @param this2
/// @return -2 si ingresó mal alguno de los parámetros, -1 si el elemento 1 es menor que el 2, 1 si el elemento 1 es mayor que el
///  2, 0 si ambos son iguales
int Salon_sortById(void* this1, void* this2)
{
	int retorno;
	retorno = -2;
	if(this1 != NULL && this2 != NULL)
	{
		Salon* SalonUno;
		Salon* SalonDos;
		//CASTEO LOS VOID*
		SalonUno = (Salon*)this1;
		SalonDos = (Salon*)this2;
		int idUno;
		int idDos;

		if(!Salon_getId(SalonUno, &idUno) && !Salon_getId(SalonDos, &idDos))
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

/// @fn int Salon_findById(LinkedList*, int)
/// @brief Encontrar el indice de la lista donde se encuentra el id buscado
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si this es NULL o el ID <= 0, -2 si no se pudo encontrar el ID, =<0 con el index
int Salon_findById(LinkedList* this, int id)
{
	int retorno = -1;
	int i;
	int cantidadSalon;
	int auxId;
	Salon* pAuxSalon;
	pAuxSalon = NULL;
	if(this != NULL && id>0)
	{
		retorno = -2;
		cantidadSalon = ll_len(this);
		for(i = 0;i<cantidadSalon;i++)
		{
			pAuxSalon = ll_get(this, i);
			Salon_getId(pAuxSalon, &auxId);
			if(auxId == id)
			{
				retorno = i;
				break;
			}

		}


	}
	return retorno;
}
