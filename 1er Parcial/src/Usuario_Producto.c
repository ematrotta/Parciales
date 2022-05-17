/*
 * Producto_Producto.c
 *
 *  Created on: 15 may. 2022
 *      Author: Emanuel
 */

#include "Usuario_Producto.h"

///Generador de id de producto
static int initId = 10000;
static int sProducto_IdGenerator(void)
{
	return initId++;
}

/// @fn int sProducto_addProducto(sProducto*, int, int, int, char[], float, short int, int, sProducto*, int)
/// @brief Agregar datos a una entidad
///
/// @pre
/// @post
/// @param listProducto array de productos
/// @param lenProducto tamaño del array
/// @param id producto
/// @param nombre
/// @param precio
/// @param categoriaProducto
/// @param stock
/// @param vendedor array de usuarios
/// @param indexProducto indice de array de usuarios
/// @return -1 si los parametros ingresados son incorrectos, -2 si no se encontro un indice libre, 0 si salio todo bien
int sProducto_addProducto(sProducto* listProducto, int lenProducto, char nombre[],float precio,short int categoriaProducto,int stock,sUsuario usuario)
{
	int retorno;
	int indiceLibre;


	retorno = -1;
	//BUSCA DENTRO DE UN ARRAY DE ENTIDADES, UN ESPACIO LIBRE

	if(listProducto != NULL && lenProducto>0 && nombre != NULL)
	{
		indiceLibre = sProducto_findFreeSpace(listProducto, lenProducto);
		if(indiceLibre>=0)
		{
			listProducto[indiceLibre].idProducto = sProducto_IdGenerator();
			strncpy(listProducto[indiceLibre].nombreDelProducto,nombre,TAM_NOMBRE_PRODUCTO);
			listProducto[indiceLibre].categoria = categoriaProducto;
			listProducto[indiceLibre].precio = precio;
			listProducto[indiceLibre].stock = stock;
			listProducto[indiceLibre].FK_idUsuario = usuario.idUsuario;
			listProducto[indiceLibre].isEmpty = FALSE;
			retorno = 0;
		}
		else
		{
			retorno = -2;
		}


	}
	return retorno;
}

//****************BAJA************************************************

/// @fn int sUsuario_removeUsuario(sUsuario*, int, int)
/// @brief Dar de baja un usuario y todas sus publicaciones
///
/// @pre
/// @post
/// @param list array
/// @param len tamaño del array
/// @param id id a dar de baja
/// @return -1 si no se ingresaron correctamente los parámetros o no se encontro el usuario, 0 si salio bien
int sUsuario_removeUsuario(sUsuario* list, int len, int id,sProducto productos[],int lenProductos)
{
	int retornoBaja;
	int retorno;
	int i;

	retorno = -1;
	if(list != NULL && len>0 && productos != NULL && lenProductos>0)
	{
		//OBTENGO EL ID DONDE SE ENCUENTRA EL USUARIO
		retornoBaja = sUsuario_findUsuarioById(list, len, id);
		if(retornoBaja >=0)
		{
			if(list[retornoBaja].isEmpty == FALSE)
			{
				//CAMBIO EL ESTADO A LOW
				list[retornoBaja].isEmpty = LOW;
				for(i= 0;i<lenProductos;i++)
				{
					if(productos[i].FK_idUsuario == id)
					{
						if(productos[i].isEmpty == FALSE || productos[i].isEmpty == PAUSED)
						{
							productos[i].isEmpty =  LOW;
						}

					}
				}
				retorno = 0;
			}

		}

	}

	return retorno;
}

