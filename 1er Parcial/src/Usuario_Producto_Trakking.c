/*
 * Usuario_Producto_Trakking.c
 *
 *  Created on: 15 may. 2022
 *      Author: Emanuel
 */
#include "Usuario_Producto_Trakking.h"


/// @fn int sTrakking_InputsDataTrakking(sTrakking*, char[], sUsuario, int, int, sProducto[], int)
/// @brief Ingresar datos a una entidad
///
/// @pre
/// @post
/// @param trakking punero a entidad
/// @param mensajeError
/// @param usuario entidad de usuario
/// @param idProducto
/// @param cantidad
/// @param productos array de productos
/// @param lenProductos tamaño del array
/// @return -1 si no se ingresaron correctamente los parámetros,
/// -2 si no se encuentra el id de producto pasado por parámetro,
/// -3 si el codigo postal del usuario no esta en ninguno de los rangos
/// 0 si salio todo bien
int sTrakking_InputsDataTrakking(sTrakking * trakking, char mensajeError[], sUsuario usuario, int idProducto,int cantidad, sProducto productos[], int lenProductos)
{
	sTrakking auxiliar;
	int retorno;
	int auxiliarcantidadKm;
	int indiceProducto;

	retorno = -1;
	if(trakking != NULL && mensajeError != NULL && idProducto>=0 && cantidad>0 && productos!= NULL && lenProductos>0)
	{
		//BUSCO LA CANTIDAD DE KM DEL USUARIO LOGUEADO
		auxiliarcantidadKm = sTrakking_KmCodigoPostal(usuario.codigoPostal);
		if(auxiliarcantidadKm>=0)
		{
			//ASIGNO CANTIDAD DE KM
			auxiliar.distanciaKm = auxiliarcantidadKm;
			indiceProducto = sProducto_findProductoById(productos, lenProductos, idProducto);
			if(indiceProducto>=0)
			{
				//ASIGNO EL ID DEL VENDEDOR
				auxiliar.FK_idVendedor = productos[indiceProducto].FK_idUsuario;
				//LE ASIGNO LA CANTIDAD INGRESADA POR PARÁMETRO
				auxiliar.cantidad = cantidad;
				//ASIGNO EL ID DE PRODUCTO INGRESADO POR PARÁMETRO
				auxiliar.FK_idProducto = idProducto;
				//ASIGNO EL USUARIO COMPRADOR
				auxiliar.FK_idComprador = usuario.idUsuario;
				//ASIGNO TODA LA INFORMACION AL AUXILIAR DE TRAKKING
				(*trakking) = auxiliar;
				retorno = 0;
			}
			else
			{
				//SI NO SE ENCUENTRA EL INDICE DE PRODUCTO PASADO POR PARÁMETRO
				retorno = -2;
			}

		}
		else
		{
			//SI EL CODIGO POSTAL FUE ERRONEO
			retorno = -3;
		}
	}
	if(retorno<0)
	{
		printf("\n%s\n",mensajeError);
	}
	return retorno;
}


/// @fn int sTrakking_printOneForUser(sTrakking, sProducto[], int)
/// @brief Imprimir un producto para un usuario comun
///
/// @pre
/// @post
/// @param trakking
/// @param productos array
/// @param lenProductos tamaño del array
/// @return -1 si no se ingresaron correctamente los parametros, 0 si salio todo bien
int sTrakking_printOneForUser(sTrakking trakking,sProducto productos [],int lenProductos)
{
	int retorno;
	int i;
	char auxiliarEstado[TAM_AUXILIAR_ESTADO];

	retorno = -1;
	if(productos != NULL && lenProductos>0)
	{

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

		for(i = 0;i<lenProductos;i++)
		{
			if(productos[i].idProducto == trakking.FK_idProducto)
			{
				//ID TRAKKING|NOMBRE|CANTIDAD|ESTADO
				printf("|%-15d|%-25s|%-15d|%-15s\n",trakking.idTrakking,productos[i].nombreDelProducto,trakking.cantidad,auxiliarEstado);
				retorno = 0;
				break;
			}

		}
	}

	return retorno;
}

/// @fn int sTrakking_printAllByTypeUser(sTrakking[], int, sProducto[], int, int, int)
/// @brief Imprimir todos los trakkings segun usuario y si es vendedor o comprador
///
/// @pre
/// @post
/// @param trakkings array de trakking
/// @param lenTrakkings tamaño array
/// @param productos array productos
/// @param lenProductos tamaño array
/// @param idUsuario usuario a imprimir sus trakking
/// @param tipoVendedorComprador 1 si es comprador o 0 si es vendedor
/// @return -1 si no se ingresaron bien los parametros, -2 si no se encontro el 1 de usuario,0 si salio todo bien
int sTrakking_printAllByTypeUser(sTrakking trakkings[],int lenTrakkings, sProducto productos [],int lenProductos,int idUsuario,int tipoVendedorComprador)
{
	int retorno;
	int i;
	int flagMatchUsuario;

	retorno = -1;
	flagMatchUsuario = 0;
	if(productos != NULL && lenProductos>0 && trakkings != NULL && lenTrakkings>0 && (tipoVendedorComprador == 1 || tipoVendedorComprador == 0))
	{
		retorno = 0;

		//SI ES UN COMPRADOR
		if(tipoVendedorComprador == 1)
		{
			for(i = 0;i<lenTrakkings;i++)
			{
				if(trakkings[i].FK_idComprador == idUsuario)
				{
					sTrakking_printOneForUser(trakkings[i], productos, lenProductos);
					flagMatchUsuario = 1;
				}
			}
			puts("\n");
			if(flagMatchUsuario == 0)
			{
				retorno = -2;
			}
		}
		else
		{
			for(i = 0;i<lenTrakkings;i++)
			{
				//SI ES VENDEDOR 0
				if(trakkings[i].FK_idVendedor == idUsuario)
				{
					sTrakking_printOneForUser(trakkings[i], productos, lenProductos);
					flagMatchUsuario = 1;
				}
			}
			puts("\n");
			if(flagMatchUsuario == 0)
			{
				retorno = -2;
			}
		}
	}

	return retorno;
}

/// @fn int sTrakking_DevolverStock(sTrakking[], int, int, sProducto[], int)
/// @brief Devolver el stock a un producto, y reactivar la publicacion luego de una baja de trakking
///
/// @pre
/// @post
/// @param trakkings array de trakkings
/// @param lenTrakking tamaño
/// @param idTrakking idTrakking dado de baja
/// @param productos array de productos
/// @param lenProductos tamaño
/// @return -1 si los parametros no se ingresaron correctamente, -2 si no se encontro el indice de producto
/// -3 si no se encontró el indice de trakking, 0 si salio bien
int sTrakking_DevolverStock(sTrakking trakkings[],int lenTrakking, int idTrakking,sProducto productos[],int lenProductos)
{
	int retorno;
	int indiceTrakkingDeBaja;
	int indiceProducto;

	retorno = -1;
	if(trakkings != NULL && lenTrakking>0 && productos != NULL && lenProductos>0)
	{
		indiceTrakkingDeBaja = sTrakking_findTrakkingById(trakkings, lenTrakking, idTrakking);
		if(indiceTrakkingDeBaja>=0)
		{
			indiceProducto = sProducto_findProductoById(productos, lenProductos, trakkings[indiceTrakkingDeBaja].FK_idProducto);

			if(indiceProducto>=0)
			{
				//SUMO LA CANTIDAD AL STOCK
				productos[indiceProducto].stock += trakkings[indiceTrakkingDeBaja].cantidad;
				//SI LA PUBLICACION ESTABA PAUSADA, LA REACTIVO
				if(productos[indiceProducto].isEmpty == PAUSED && (productos[indiceProducto].stock >0))
				{
					productos[indiceProducto].isEmpty = FALSE;//REACTIVAR
				}
				retorno = 0;
			}
			else
			{
				//SI NO SE ENCONTRO EL INDICE DE PRODUCTO
				retorno = -2;
			}

		}
		else
		{
			//SI NO ENCONTRO NINGUN TRAKKING
			retorno = -3;
		}


	}


	return retorno;

}


