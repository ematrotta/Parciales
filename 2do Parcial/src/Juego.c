/*
 * Juego.c
 *
 *  Created on: 23 jun. 2022
 *      Author: Emanuel
 */

#include "Juego.h"

/// @fn int Juego_IdGenerator(void)
/// @brief Generar un ID. Tomando de un archivo, buscando el último Id, lo incrementa, guarda en el mismo archivo
/// el nuevo id y éste mismo lo retorna
///
/// @pre
/// @post
/// @return Retorna El Id generado
static int Juego_IdGenerator(void)
{
	int initId;
	initId = 0;

	if(!Juego_GetIdJuegoFromBinary(&initId,ARCHIVO_ULTID_JUEGO))
	{
		initId++;
		Juego_SetLastId(&initId,ARCHIVO_ULTID_JUEGO);
	}
	return initId;
}

/// @fn Juego Juego_new*()
/// @brief Crea un puntero a estructura con memoria dinámica
///
/// @pre
/// @post
/// @return puntero a entidad
Juego* Juego_new()
{
	Juego* p;
	p = (Juego*)malloc(sizeof(Juego));
	return p;
}

/// @fn Juego* Juego_newParametros(int, int, char*, char*)
/// @brief Carga datos a una estructura
///
/// @pre
/// @post
/// @param idJuego
/// @param tipoJuego
/// @param nombreJuego
/// @param empresaJuego
/// @return Si todo salio bien, retorna un puntero en memoria dinamica de la estructura, sino NULL
Juego* Juego_newParametros(int idJuego,int tipoJuego,char* nombreJuego,char* empresaJuego)
{

	Juego* pAuxJuego;
	pAuxJuego = NULL;
	if(nombreJuego != NULL && empresaJuego != NULL)
	{
		if(idJuego>0 && (tipoJuego == TIPO_PLAT || tipoJuego == TIPO_LAB || tipoJuego == TIPO_AVEN || tipoJuego == TIPO_OTRO))
		{
			pAuxJuego = Juego_new();
			if(Juego_setId(pAuxJuego,idJuego)<0 || Juego_setNombre(pAuxJuego, nombreJuego)<0 || Juego_setEmpresa(pAuxJuego, empresaJuego)<0 ||
					Juego_setTipo(pAuxJuego, tipoJuego)<0)
			{
				free(pAuxJuego);
				pAuxJuego = NULL;

			}

		}

	}

	return pAuxJuego;
}

/// @fn int Juego_setId(Juego*, int)
/// @brief Colocar un ID a la entidad
///
/// @pre
/// @post
/// @param this Puntero a la entidad
/// @param id
/// @return -1 si se ingresaron incorrectamente los parámetros, 0 si salio todo bien
int Juego_setId(Juego* this,int id)
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

/// @fn int Juego_getId(Juego*, int*)
/// @brief Obtener un ID de una estructura Juego
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Juego_getId(Juego* this,int* id)
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

/// @fn int Juego_setTipo(Juego*, int)
/// @brief Colocar un TIPO a la entidad
///
/// @pre
/// @post
/// @param this Puntero a la entidad
/// @param id
/// @return -1 si se ingresaron incorrectamente los parámetros, 0 si salio todo bien
int Juego_setTipo(Juego* this,int tipo)
{
	int retorno;
	retorno = -1;


	if(this != NULL && tipo>0)
	{
		this->tipoJuego = tipo;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Juego_getTipo(Juego*, int*)
/// @brief Obtener tipo de una estructura Juego
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Juego_getTipo(Juego* this,int* tipo)
{
	int retorno;
	retorno = -1;

	if(this != NULL && tipo != NULL)
	{
		*tipo = this->tipoJuego;
		retorno = 0;
	}

	return retorno;
}

/// @fn int Juego_setNombre(Juego*, char*)
/// @brief Colocar el Nombre a un Juego
///
/// @pre
/// @post
/// @param this
/// @param nombre
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Juego_setNombre(Juego* this,char* nombreJuego)
{
	int retorno;
	retorno = -1;

	if(this != NULL && nombreJuego != NULL)
	{
		strncpy(this->nombreJuego,nombreJuego,LEN_NAME_JUEGO);
		retorno = 0;
	}

	return retorno;
}

/// @fn int Juego_getNombre(Juego*, char*)
/// @brief Obtener el Nombre de un Juego
///
/// @pre
/// @post
/// @param this
/// @param nombre
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Juego_getNombre(Juego* this,char* nombreJuego)
{
	int retorno;
	retorno = -1;

	if(this != NULL && nombreJuego != NULL)
	{
		strncpy(nombreJuego,this->nombreJuego,LEN_NAME_JUEGO);
		retorno = 0;
	}

	return retorno;
}

/// @fn int Juego_setEmpresa(Juego*, char*)
/// @brief Colocar Empresa a un Juego
///
/// @pre
/// @post
/// @param this
/// @param nombre
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Juego_setEmpresa(Juego* this,char* empresaJuego)
{
	int retorno;
	retorno = -1;

	if(this != NULL && empresaJuego != NULL)
	{
		strncpy(this->empresaJuego,empresaJuego,LEN_EMP_JUEGO);
		retorno = 0;
	}

	return retorno;
}

/// @fn int Juego_getEmpresa(Juego*, char*)
/// @brief Obtener el Nombre de un Juego
///
/// @pre
/// @post
/// @param this
/// @param nombre
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Juego_getEmpresa(Juego* this,char* empresaJuego)
{
	int retorno;
	retorno = -1;

	if(this != NULL && empresaJuego != NULL)
	{
		strncpy(empresaJuego,this->empresaJuego,LEN_EMP_JUEGO);
		retorno = 0;
	}

	return retorno;
}

/// @fn int Juego_printOne(Juego*)
/// @brief Imprimir una entidad
///
/// @pre
/// @post
/// @param this puntero a la entidad
/// @return -1 si this es NULL, -2 si alguno de los gets es NULL, 0 si salio todo bien
int Juego_printOne(Juego* this)
{
	int retorno;
	retorno = -1;
	int auxId;
	char auxNombre[LEN_NAME_JUEGO];
	char auxEmpresa[LEN_EMP_JUEGO];
	char cAuxTipo[LEN_NAME_JUEGO];
	int auxTipo;

	if(this != NULL)
	{
		retorno = -2;
		if(!Juego_getId(this, &auxId) && !Juego_getNombre(this, auxNombre) && !Juego_getEmpresa(this, auxEmpresa)
				&& !Juego_getTipo(this, &auxTipo))
		{
			switch(auxTipo)
			{
			case TIPO_PLAT:
				strncpy(cAuxTipo,"Plataforma",LEN_NAME_JUEGO);
				break;
			case TIPO_LAB:
				strncpy(cAuxTipo,"Laberinto",LEN_NAME_JUEGO);
				break;
			case TIPO_AVEN:
				strncpy(cAuxTipo,"Aventura",LEN_NAME_JUEGO);
				break;
			case TIPO_OTRO:
				strncpy(cAuxTipo,"Otro",LEN_NAME_JUEGO);
				break;
			}
			printf("%10d | %25s | %25s | %11s\n",auxId,auxNombre,auxEmpresa,cAuxTipo);
			retorno = 0;
		}

	}
	return retorno;
}

/// @fn int Juego_SetLastId(int*, char*)
/// @brief Escribir el último ID generado en un archivo binario
///
/// @pre
/// @post
/// @param pId puntero al id
/// @param path
/// @return -1 si alguno de los parámetros es NULL, -2 si no se pudo abrir el archivo, -3 si no pudo hacer ninguna lectura
/// 0 si salio todo bien
int Juego_SetLastId(int* pId, char* path)
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

/// @fn int Juego_GetIdJuegoFromBinary(int*, char*)
/// @brief Tomar el ultimo id de un archivo binario
///
/// @pre
/// @post
/// @param pId Puntero al id
/// @param path
/// @return -1 si alguno de los parámetros es NULL, 0 si salio todo bien
int Juego_GetIdJuegoFromBinary(int* pId, char* path)
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

/// @fn int Juego_InputsData(LinkedList*, char[])
/// @brief Agregar datos a una entidad de forma manual
///
/// @pre
/// @post
/// @param this Array de la estructura
/// @param mensajeError
/// @return -1 si alguno de los parametros es NULL, -2 si se ingresó mal el nombre, -3 si ingreso mal la direccion,
/// -4 si ingreso mal el tipo, -5 si ingreso un ID menor o igual a 0, -6 si no se generó una entidad en memoria dinamica
/// 0 si salio todo bien
int Juego_InputsData(LinkedList* this,char mensajeError[])
{
	int retorno;
	int auxTipo;
	int id;
	char auxNombre[LEN_NAME_JUEGO];
	char auxEmpresa[LEN_EMP_JUEGO];

	retorno = -1;


	if(this != NULL && mensajeError!= NULL)
	{


		Juego* juego;
		//INGRESO MAL EL NOMBRE
		retorno = -2;

		if(!Utn_GetStringAlfaNumericaPlus(auxNombre, "Ingrese un Nombre", "No es un Nombre. Reintente", LEN_NAME_JUEGO, 3))
		{
			//INGRESO MAL EMPRESA
			retorno = -3;

			if(!Utn_GetStringAlfaNumericaPlus(auxEmpresa, "Ingrese una empresa", "No es un Nombre. Reintente", LEN_EMP_JUEGO, 3))
			{
				//INGRESO MAL TIPO
				retorno = -4;

				if(!Utn_GetNumeroInt(&auxTipo, "Ingrese el tipo:\n1. Plataforma\n"
						"2. Laberinto\n3. Aventura\n4. Otro\nOPCIÓN", "La opción debe ser entre 1 y 4", 4, 1, 3))
				{
					//NO SE COLOCÓ BIEN EL ID
					retorno = -5;
					id = Juego_IdGenerator();
					if(id>0)
					{
						retorno = -6;
						juego = Juego_newParametros(id, auxTipo, auxNombre, auxEmpresa);
						if(juego != NULL)
						{
							ll_add(this, juego);
							puts("\nAlta exitosa\n");
							printf("%10s | %25s | %25s | %11s\n","ID","NOMBRE","EMPRESA","TIPO");
							Juego_printOne(juego);
							retorno = 0;
						}


					}



				}
			}
		}

		if(retorno<0)
		{
			printf("\n%s\n",mensajeError);
			free(juego);
			juego = NULL;
		}


	}

	return retorno;
}


/// @fn int Juego_sortById(void*, void*)
/// @brief Retornar un valor comparando 2 elementos de 1 estructura: Id
///
/// @pre
/// @post
/// @param this1
/// @param this2
/// @return -2 si ingresó mal alguno de los parámetros, -1 si el elemento 1 es menor que el 2, 1 si el elemento 1 es mayor que el
///  2, 0 si ambos son iguales
int Juego_sortById(void* this1, void* this2)
{
	int retorno;
	retorno = -2;
	if(this1 != NULL && this2 != NULL)
	{
		Juego* JuegoUno;
		Juego* JuegoDos;
		//CASTEO LOS VOID*
		JuegoUno = (Juego*)this1;
		JuegoDos = (Juego*)this2;
		int idUno;
		int idDos;

		if(!Juego_getId(JuegoUno, &idUno) && !Juego_getId(JuegoDos, &idDos))
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

/// @fn int Juego_sortByName(void*, void*)
/// @brief Retornar un valor comparando 2 elementos de 1 estructura: Nombre
///
/// @pre
/// @post
/// @param this1
/// @param this2
/// @return -2 si ingresó mal alguno de los parámetros, -1 si el elemento 1 es menor que el 2, 1 si el elemento 1 es mayor que el
///  2, 0 si ambos son iguales
int Juego_sortByName(void* this1, void* this2)
{
	int retorno;
	retorno = -1;
	if(this1 != NULL && this2 != NULL)
	{
		Juego* JuegoUno;
		Juego* JuegoDos;
		//CASTEO LOS VOID*
		JuegoUno = (Juego*)this1;
		JuegoDos = (Juego*)this2;
		char nombreUno[LEN_NAME_JUEGO];
		char nombreDos[LEN_NAME_JUEGO];
		int resultadoComparacion;

		retorno = -2;
		if(!Juego_getNombre(JuegoUno, nombreUno)&& !Juego_getNombre(JuegoDos, nombreDos))
		{

			resultadoComparacion = strncmp(nombreUno,nombreDos,LEN_NAME_JUEGO);
			if(resultadoComparacion<0)
			{
				retorno = -1;
			}
			else
			{
				if(resultadoComparacion>0)
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


/// @fn int Juego_findById(LinkedList*, int)
/// @brief Encontrar el indice de la lista donde se encuentra el id buscado
///
/// @pre
/// @post
/// @param this
/// @param id
/// @return -1 si this es NULL o el ID <= 0, -2 si no se pudo encontrar el ID, =<0 con el index
int Juego_findById(LinkedList* this, int id)
{
	int retorno = -1;
	int i;
	int cantidadJuego;
	int auxId;
	Juego* pAuxJuego;
	pAuxJuego = NULL;
	if(this != NULL && id>0)
	{
		retorno = -2;
		cantidadJuego = ll_len(this);
		for(i = 0;i<cantidadJuego;i++)
		{
			pAuxJuego = ll_get(this, i);
			Juego_getId(pAuxJuego, &auxId);
			if(auxId == id)
			{
				retorno = i;
				break;
			}

		}


	}
	return retorno;
}

/// @fn int Juego_findByName(LinkedList*, char*)
/// @brief Encontrar el indice del juego por el nombre
///
/// @pre
/// @post
/// @param this Array Juegos
/// @param name nombreBuscado
/// @return -1 si alguno de los parámetros es NULL, -2 si no hay juegos, Mayor o igual a 0 con el indice
int Juego_findIdByName(LinkedList* this, char* name)
{
	int retorno = -1;
	int i;
	int cantidadJuego;
	char cAuxName[LEN_NAME_JUEGO];
	Juego* pAuxJuego;
	pAuxJuego = NULL;
	if(this != NULL && name != NULL)
	{
		retorno = -2;
		cantidadJuego = ll_len(this);
		if(cantidadJuego>0)
		{
			for(i = 0;i<cantidadJuego;i++)
			{
				pAuxJuego = ll_get(this, i);
				if(pAuxJuego != NULL)
				{
					Juego_getNombre(pAuxJuego, cAuxName);
					if(strncmp(cAuxName,name,LEN_NAME_JUEGO)==0)
					{
						retorno = i;
						break;
					}
				}


			}
		}



	}
	return retorno;
}
