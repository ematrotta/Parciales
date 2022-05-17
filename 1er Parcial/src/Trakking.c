/*
 * Trakking.c
 *
 *  Created on: 15 may. 2022
 *      Author: Emanuel
 */

#include "Trakking.h"

static int initId = 10000;
static int sTrakking_IdGenerator(void)
{
	return initId++;
}

//FUNCION PARA OBTENER EL TIEMPO ACTUAL
long int time_current(void)
{
	return time(NULL);
}

//FUNCION PARA AGREGAR EL TIEMPO
long int time_Add(double secondsAdd)
{
	return secondsAdd + time_current();
}

/// @fn int sTrakking_findTrakkingById(sTrakking*, int, int)
/// @brief Buscar Indice de entidad según id
///
/// @pre
/// @post
/// @param list array
/// @param len tamaño del array
/// @param id id a buscar
/// @return -2 si array = NULL o tamaño de array<=0, -1 si no se encontró el id, Indice si salio todo bien
int sTrakking_findTrakkingById(sTrakking * list,int len,int id)
{
	int retorno;
	int i;

	retorno = -2;
	if(list != NULL && len>0)
	{
		retorno = -1;
		for(i = 0;i<len;i++)
		{
			if(list[i].idTrakking == id)
			{
				retorno = i;
				break;
			}

		}
	}

	return retorno;
}

/// @fn int sTrakking_KmCodigoPostal(int)
/// @brief Calcular cantidad de Km segun rango por codigo postal
///
/// @pre
/// @post
/// @param codigoPostal codigo postal del trakking
/// @return -1 si no se ingreso un codigo postal, cantidad de km si salio todo bien
int sTrakking_KmCodigoPostal(int codigoPostal)
{

	int retorno;
	retorno = -1;
	if(codigoPostal>=0001 && codigoPostal<=1000)
	{
		retorno = 20;
	}
	else
	{
		if(codigoPostal>=1001 && codigoPostal<=3000)
		{
			retorno = 30;
		}
		else
		{
			if(codigoPostal>=3001 && codigoPostal<=5000)
			{
				retorno = 50;
			}
			else
			{
				if(codigoPostal>=5001 && codigoPostal<=8000)
				{
					retorno = 80;
				}
				else
				{
					if(codigoPostal>=8001 && codigoPostal<=9999)
					{
						retorno = 150;
					}
					else
					{
						//SI NO ESTA DENTRO DE NINGÚN RANGO
						retorno = -1;
					}
				}
			}

		}
	}

	return retorno;
}

/// @fn int sTrakking_initTrakking(sTrakking*, int)
/// @brief Inicializar todos los campos isEmpty
///
/// @pre
/// @post
/// @param list Array
/// @param len Tamaño del array
/// @return -1 si está mal, 0 si esta bien
int sTrakking_initTrakking(sTrakking * list, int len)
{
	int retorno;
	int i;
	retorno = -1;

	if(list != NULL && len>0)
	{
		for(i = 0;i<len;i++)
		{
			//SELECCIONO EL CAMPO IS EMPTY E INICIALIZO
			list[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/// @fn int sTrakking_findFreeSpace(sTrakking*, int)
/// @brief Encontrar un espacio Libre
///
/// @pre
/// @post
/// @param list Array
/// @param len tamaño del array
/// @return -1 si no encontro espacios libres, >=0 correspondiente al indice libre
int sTrakking_findFreeSpace(sTrakking * list, int len)
{
	int retorno;
	int i;

	retorno = -1;

	if(list != NULL && len>0)
	{
		for(i = 0;i<len;i++)
		{
			//BUSCO EN UN ARRAY ALGUNA ENTIDAD QUE SE ENCUENTRE LIBRE Y ARROJO SU INDICE
			if(list[i].isEmpty == TRUE)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/// @fn int sTrakking_addTrakking(sTrakking*, int, int, int, int, int, int, int)
/// @brief Cargar datos a una entidad dentro de un array
///
/// @pre
/// @post
/// @param listTrakking array de trakkings
/// @param lenTrakking tamaño del array
/// @param id trakking
/// @param distancia
/// @param cantidad
/// @param FK_IdProducto
/// @param FK_IdVendedor
/// @param FK_IdComprador
/// @return -1 si no estan bien los parametros, 0 si salio todo bien
int sTrakking_addTrakking(sTrakking* listTrakking, int lenTrakking, int distancia,int cantidad,int FK_IdProducto ,int FK_IdVendedor,int FK_IdComprador)
{
	int retorno;
	int indiceLibre;
	int tiempoSegunDistancia;


	retorno = -1;
	//BUSCA DENTRO DE UN ARRAY DE ENTIDADES, UN ESPACIO LIBRE
	indiceLibre = sTrakking_findFreeSpace(listTrakking, lenTrakking);
	if(listTrakking != NULL && lenTrakking>0 && indiceLibre>=0)
	{
		listTrakking[indiceLibre].idTrakking = sTrakking_IdGenerator();
		listTrakking[indiceLibre].distanciaKm = distancia;
		listTrakking[indiceLibre].cantidad = cantidad;
		listTrakking[indiceLibre].FK_idComprador = FK_IdComprador;
		listTrakking[indiceLibre].FK_idVendedor = FK_IdVendedor;
		listTrakking[indiceLibre].FK_idProducto = FK_IdProducto;
		//CALCULO CADA 10 KM CUANTOS SEGUNDOS DEBEN TRANSCURRIR
		tiempoSegunDistancia = (distancia/10);
		MultiplicarInt(tiempoSegunDistancia, 20,&tiempoSegunDistancia);
		listTrakking[indiceLibre].horaLlegada = time_Add(tiempoSegunDistancia);
		listTrakking[indiceLibre].isEmpty = FALSE;
		retorno = 0;

	}
	return retorno;
}

/*
/// @fn void sTrakking_printOne(sTrakking)
/// @brief Imprimir Una entidad
///
/// @pre
/// @post
/// @param trakking
void sTrakking_printOne(sTrakking trakking) //IMPRIMIR UNO PARA DEBBUGGER
{
	char auxiliarEstado[TAM_AUXILIAR_ESTADO];
	switch(trakking.isEmpty)
	{
	case FALSE:
		strncpy(auxiliarEstado,"EN VIAJE",TAM_AUXILIAR_ESTADO);
		break;
	case LOW:
		strncpy(auxiliarEstado,"CANCELADO",TAM_AUXILIAR_ESTADO);
		break;
	case ENTREGADO:
		strncpy(auxiliarEstado,"ENTREGADO",TAM_AUXILIAR_ESTADO);
		break;
	}
	//IMPRESIÓN DE 1 TRAKKING EN FORMA TABULAR
	//ID TRAKKING|IS EMPTY|CANTIDAD|DISTANCIA KM|HORA DE LLEGADA|ID DE PRODUCTO|ID COMPRADOR|ID VENDEDOR
	printf("|%-8d|%-15s|%-8d|%-8d|%-20ld|%-8d|%-8d|%-8d|\n",trakking.idTrakking,auxiliarEstado,trakking.cantidad,trakking.distanciaKm,trakking.horaLlegada,trakking.FK_idProducto,
			trakking.FK_idComprador,trakking.FK_idVendedor);
}
*/

/// @fn int sTrakking_sortTrakkings(sTrakking*, int, int)
/// @brief Ordenar array de entidad
///
/// @pre
/// @post
/// @param list Array
/// @param len Tamaño del array
/// @param order 1 ascendente, -1 si es decreciente
/// @return -1 si array = NULL o tamaño de array<=0 o Order != 1 o !=-1, 0 si salio bien
int sTrakking_sortTrakkings(sTrakking* list, int len, int order)
{
	int retorno;
	int i;
	int flagNoEstaOrdenado;

	sTrakking auxiliar;
	flagNoEstaOrdenado = 1;

	retorno = -1;

	if(list != NULL && len>0 && (order == 1 || order == -1))
	{
		//ORDENAMIENTO ASCENDENTE
		if(order == 1)
		{
			while(flagNoEstaOrdenado == 1)
			{

				//RECORRO LAS ENTIDADES Y COMPARO POSICION POSTERIOR CON
				//POSICION ANTERIOR
				flagNoEstaOrdenado = 0;
				for(i=1;i<len;i++)
				{
					//SI HAY ENTIDADES DISTINTAS DE LIBRES PARA ORDENAR
					if(list[i].isEmpty != TRUE)
					{
						//SI SUECEDE QUE ES MAYOR EL ANTERIOR
						if(list[i].idTrakking < list[i-1].idTrakking)
						{
							//CAMBIO LOS VALORES EN LAS  POSICIONES
							auxiliar = list[i-1];
							list[i-1] = list[i];
							list[i] = auxiliar;
							flagNoEstaOrdenado = 1;
							//ROMPO
							break;
						}
						//SI ENCUENTRA AL MENOS UNA ENTIDAD NO LIBRE
						retorno = 0;
					}

				}


			}

		}
		//ORDENAMIENTO DESCENDENTE
		else
		{

			while(flagNoEstaOrdenado == 1)
			{
				//RECORRO LAS ENTIDADES Y COMPARO POSICION POSICION POSTERIOR CON
				//POSICION ANTERIOR
				flagNoEstaOrdenado = 0;
				for(i=1;i<len;i++)
				{
					if(list[i].isEmpty != TRUE)
					{
						//SI SUCEDE QUE ES MAYOR EL POSTERIOR
						if(list[i].idTrakking > list[i-1].idTrakking)
						{
							auxiliar = list[i];
							list[i] = list[i-1];
							list[i-1] = auxiliar;
							flagNoEstaOrdenado = 1;
							//ROMPO
							break;
						}
						retorno = 0;
					}

				}

			}

		}
	}


	return retorno;
}

/// @fn int sTrakking_ActualizarEstadosTrakking(sTrakking[], int)
/// @brief actualizar los estados de los trakkings a en viaje o entregado
///
/// @pre
/// @post
/// @param trakkings
/// @param lenTrakkings
/// @return -1 si no se ingresaron correctamente los parámetros o si no encontró estados para actualizar
/// // si pudo atualizar estados
int sTrakking_ActualizarEstadosTrakking(sTrakking trakkings[],int lenTrakkings)
{
	int retorno;
	int i;

	retorno = -1;
	if(trakkings != NULL && lenTrakkings>0)
	{
		for(i = 0;i<lenTrakkings;i++)
		{
			if(trakkings[i].isEmpty == FALSE)
			{
				if(((trakkings[i].horaLlegada)-time_current())>0)
				{
					//SI LA DIFERENCIA ENTRE EL TIEMPO ACTUAL Y LA DE LLEGADA ES MAYOR
					trakkings[i].isEmpty = FALSE;//EN VIAJE
				}
				else
				{	//SI ES MENOR O IGUAL QUE 0
					trakkings[i].isEmpty = ENTREGADO;//ENTREGADO
				}
				retorno = 0;
			}

		}

	}
	return retorno;
}


/// @fn int sTrakking_BajaTrakking(sTrakking[], int, int)
/// @brief Dar de baja un trakking solo si está en camino
///
/// @pre
/// @post
/// @param trakkings array
/// @param lenTrakkings tamaño array
/// @param idTrekkingBaja
/// @return -1 si no hay trakkings en camino o el ingresado no se encuentra, 0 si salio bien la baja
int sTrakking_BajaTrakking(sTrakking trakkings[],int lenTrakkings, int idTrakkingBaja)
{
	int retorno;
	int i;

	retorno = -1;
	if(trakkings != NULL && lenTrakkings>0)
	{
		for(i = 0;i<lenTrakkings;i++)
		{
			if(trakkings[i].isEmpty == FALSE)//SI ESTA EN CAMINO
			{
				if(trakkings[i].idTrakking == idTrakkingBaja)
				{
					//SI LA DIFERENCIA ENTRE EL TIEMPO ACTUAL Y LA DE LLEGADA ES MAYOR
					trakkings[i].isEmpty = LOW;//CANCELAR
					retorno = 0;
					break;
				}

			}

		}

	}
	return retorno;
}


/// @fn void sTrakking_printOneForAdmin(sTrakking)
/// @brief Imprimir Una entidad para visualizacion del admin
///
/// @pre
/// @post
/// @param usuario
void sTrakking_printOneForAdmin(sTrakking trakking)
{
	//AUXILIAR PARA MOSTRAR CADENA EN TIPO DE PASAJERO
	char auxiliarEstado[25];


	switch(trakking.isEmpty)
	{
	case FALSE:
		strncpy(auxiliarEstado,"EN TRANSITO",sizeof(auxiliarEstado));
		break;
	case LOW:
		strncpy(auxiliarEstado,"CANCELADO",sizeof(auxiliarEstado));
		break;
	case ENTREGADO:
		strncpy(auxiliarEstado,"ENTREGADO",sizeof(auxiliarEstado));
		break;

	}

	//IMPRESIÓN DE 1 PASAJERO EN FORMA TABULAR
	printf("|%-15d|%-20s|%-15d|%-15d\n",trakking.idTrakking,auxiliarEstado,trakking.FK_idComprador,trakking.FK_idComprador);
}

/// @fn int sTrakking_printTrakkingsForAdmin(sTrakking*, int)
/// @brief Imprimir todas las entidades de un array que se hayan ingresado
///
/// @pre
/// @post
/// @param list Array
/// @param len Tamaño del array
/// @return -1 si array = NULL o tamaño es <= 0, 0 si salio bien
int sTrakking_printTrakkingsForAdmin(sTrakking* list,int len)
{

	int retorno;
	int i;

	retorno = -1;

	if(list != NULL && len>0)
	{
		for(i = 0;i<len;i++)
		{

			if(list[i].isEmpty != TRUE)//IMPRIMIR TODOS LOS QUE ESTEN
			{
				sTrakking_printOneForAdmin(list[i]);
			}


		}
		retorno = 0;
	}

	return retorno;
}

