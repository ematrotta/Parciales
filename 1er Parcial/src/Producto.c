/*
 * Producto.c
 *
 *  Created on: 15 may. 2022
 *      Author: Emanuel
 */

#include "Producto.h"


/// @fn int sProducto_initProducto(sProducto*, int)
/// @brief Inicializar todos los campos isEmpty
///
/// @pre
/// @post
/// @param list Array
/// @param len Tamaño del array
/// @return -1 si está mal, 0 si esta bien
int sProducto_initProducto(sProducto * list, int len)
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

/// @fn int sProducto_findFreeSpace(sProducto*, int)
/// @brief Encontrar un espacio Libre
///
/// @pre
/// @post
/// @param list Array
/// @param len tamaño del array
/// @return -1 si no encontro espacios libres, >=0 correspondiente al indice libre
int sProducto_findFreeSpace(sProducto * list, int len)
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

/// @fn int sProducto_findProductoById(sProducto*, int, int)
/// @brief Buscar Indice de entidad según id
///
/// @pre
/// @post
/// @param list array
/// @param len tamaño del array
/// @param id id a buscar
/// @return -2 si array = NULL o tamaño de array<=0, -1 si no se encontró el id, Indice si salio todo bien
int sProducto_findProductoById(sProducto * list,int len,int id)
{
	int retorno;
	int i;

	retorno = -2;
	if(list != NULL && len>0)
	{
		retorno = -1;
		for(i = 0;i<len;i++)
		{
			if(list[i].idProducto == id)
			{
				retorno = i;
				break;
			}

		}
	}

	return retorno;
}

/// @fn int sProducto_findProductoByCategory(sProducto*, int, int)
/// @brief Buscar si hay al menos un producto de la categoria (Activos)
///
/// @pre
/// @post
/// @param list array
/// @param len tamaño del array
/// @param categoria
/// @return -2 si array = NULL o tamaño de array<=0, -1 si no se encontró ninguno con categoria, 0 si encontró al menos uno
int sProducto_findProductoByCategory(sProducto * list,int len,int categoria)
{
	int retorno;
	int i;

	retorno = -2;
	if(list != NULL && len>0)
	{
		retorno = -1;
		for(i = 0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE && list[i].categoria == categoria)
			{
				retorno = 0;
				break;
			}

		}
	}

	return retorno;
}


/// @fn int sProducto_InputsDataProducto(sProducto *, char[])
/// @brief Ingresar datos a una entidad
///
/// @pre
/// @post
/// @param producto
/// @param mensajeError
/// @return -1 si no esta dentro del rango de stock, -2 si el precio es erroneo, -3 Si no esta en el rango de categorias,
///-4 si el tamaño del nombre supera la memoria reservada, -5 si no se ingresaron todos los datos por parámetro
int sProducto_InputsDataProducto(sProducto * producto,char mensajeError[])
{
	sProducto auxiliar;
	int retorno;

	if(producto != NULL && mensajeError != NULL)
	{
			//INGRESO NOMBRE DEL PRODUCTO
			if(Utn_GetString(auxiliar.nombreDelProducto, "Ingrese un nombre", "ERROR. Maxima cantidad de caracteres: 24", TAM_NOMBRE_PRODUCTO, 3) == 0)
			{
				//INGRESO CATEGORIA
				if(	Utn_GetNumeroShortInt(&auxiliar.categoria, "Ingrese una categoria:\n"
						"1)Vehiculos\n2)Supermercado\n3)Tecnología\n4)Electrodomesticos\n"
						"5)Jueguetes\n6)Moda\n7)Deportes\n8)Cuidado personal\n\nOPCIÓN", "Debe ser entre 1 y 8", 8, 1, 3) == 0)
				{
					//INGRESO PRECIO
					if(Utn_GetNumeroFloat(&auxiliar.precio, "Ingrese el valor", "debe ser superior a 100 y menor que 1000000", 1000000, 100, 3)==0)
					{
						//INGRESO STOCK
						if(Utn_GetNumeroInt(&auxiliar.stock, "Ingrese su stock", "Debe ser mayor a 0 y menor que 100", 100, 1, 3)==0)
						{
							(*producto) = auxiliar;
							retorno = 0;
						}
						else
						{
							//SI NO ESTA DENTRO DEL RANGO DE STOCK
							retorno = -1;
						}
					}
					else
					{
						//SI EL PRECIO ES ERRONEO
						retorno = -2;
					}
				}
				else
				{
					//SI NO ESTA DENTRO DEL RANGO DE LAS CATEGORIAS
					retorno = -3;
				}
			}
			else
			{
				//SI EL NOMBRE DEL PRODUCTO SUPERA EL LIMITE DE MEMORIA RESERVADA
				retorno = -4;
			}
		}
	else
	{
		//SI NO SE INGRESARON TODOS LOS PARAMETROS
		retorno = -5;
	}
	if(retorno<0)
	{
		printf("\n%s\n",mensajeError);
	}
	return retorno;
}


/// @fn void sProducto_printOne(sProducto)
/// @brief Imprimir Una entidad
///
/// @pre
/// @post
/// @param producto
void sProducto_printOne(sProducto producto)
{
	//AUXILIAR PARA MOSTRAR CADENA EN TIPO DE PASAJERO
	char auxiliarTypeProducto[TAM_CATEGORIA_PRODUCTO];


	switch(producto.categoria)
	{
	case 1:
		strncpy(auxiliarTypeProducto,"Vehiculos",sizeof(auxiliarTypeProducto));
		break;
	case 2:
		strncpy(auxiliarTypeProducto,"Supermercado",sizeof(auxiliarTypeProducto));
		break;
	case 3:
		strncpy(auxiliarTypeProducto,"Tecnología",sizeof(auxiliarTypeProducto));
		break;
	case 4:
		strncpy(auxiliarTypeProducto,"Electrodomesticos",sizeof(auxiliarTypeProducto));
		break;
	case 5:
		strncpy(auxiliarTypeProducto,"Jueguetes",sizeof(auxiliarTypeProducto));
		break;
	case 6:
		strncpy(auxiliarTypeProducto,"Moda",sizeof(auxiliarTypeProducto));
		break;
	case 7:
		strncpy(auxiliarTypeProducto,"Deportes",sizeof(auxiliarTypeProducto));
		break;
	case 8:
		strncpy(auxiliarTypeProducto,"Cuidado personal",sizeof(auxiliarTypeProducto));
		break;
	}
	//IMPRESIÓN DE 1 PASAJERO EN FORMA TABULAR

	//CATEGORIA,NOMBRE DEL PRODUCTO,PRECIO,ID DE PRODUCTO,ID USUARIO,STOCK,ESTADO DE PRODUCTO
	printf("|%-25s|%-30s|%-12.2f|%-15d|%-15d|%-10d|%-8d|\n",auxiliarTypeProducto,producto.nombreDelProducto,producto.precio,producto.idProducto,producto.FK_idUsuario,producto.stock,producto.isEmpty);
}

/// @fn int sProducto_printProductsByCategory(sProducto*, int,int)
/// @brief Imprimir todas las entidades de un array que se hayan ingresado y que esten activas
///
/// @pre
/// @post
/// @param list Array
/// @param len Tamaño del array
/// @param category categoria del producto
/// @return -1 si array = NULL o tamaño es <= 0,-2 si no se encontraron productos
/// de la categoria, 0 si salio bien
int sProducto_printProductsByCategory(sProducto* list,int len,int category)
{

	int retorno;
	int i;
	int flagProducto;
	flagProducto = 0;
	char auxiliarTypeProducto[TAM_CATEGORIA_PRODUCTO];

	retorno = -1;

	if(list != NULL && len>0 && category>0)
	{
		switch(category)
		{
			case 1:
				strncpy(auxiliarTypeProducto,"Vehiculos",sizeof(auxiliarTypeProducto));
				break;
			case 2:
				strncpy(auxiliarTypeProducto,"Supermercado",sizeof(auxiliarTypeProducto));
				break;
			case 3:
				strncpy(auxiliarTypeProducto,"Tecnología",sizeof(auxiliarTypeProducto));
				break;
			case 4:
				strncpy(auxiliarTypeProducto,"Electrodomesticos",sizeof(auxiliarTypeProducto));
				break;
			case 5:
				strncpy(auxiliarTypeProducto,"Jueguetes",sizeof(auxiliarTypeProducto));
				break;
			case 6:
				strncpy(auxiliarTypeProducto,"Moda",sizeof(auxiliarTypeProducto));
				break;
			case 7:
				strncpy(auxiliarTypeProducto,"Deportes",sizeof(auxiliarTypeProducto));
				break;
			case 8:
				strncpy(auxiliarTypeProducto,"Cuidado personal",sizeof(auxiliarTypeProducto));
				break;
		}
		for(i = 0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				if(list[i].categoria == category)
				{

					sProducto_printOne(list[i]);
					flagProducto = 1;
					retorno = 0;
				}
			}

		}
		if(flagProducto == 0)
		{
			retorno = -2;
		}
	}

	return retorno;
}


/// @fn int sProducto_printProductsByUser(sProducto*, int)
/// @brief Imprimir todas las entidades de un array que se hayan ingresado y que esten activas
///
/// @pre
/// @post
/// @param list Array
/// @param len Tamaño del array
/// @param idUsuario id del usuario que debe tener el producto
/// @return -1 si array = NULL o tamaño es <= 0,-2 si no se encontraron productos
/// asociados al id de usuario,0 si salio bien
int sProducto_printProductsByUser(sProducto* list,int len,int idUsuario)
{

	int retorno;
	int i;
	int flagProducto;

	flagProducto = 0;

	retorno = -1;

	if(list != NULL && len>0)
	{
		for(i = 0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				if(list[i].FK_idUsuario == idUsuario)
				{
					sProducto_printOne(list[i]);
					flagProducto = 1;
					retorno = 0;
				}
			}

		}
		if(flagProducto == 0)
		{
			retorno = -2;
		}
	}

	return retorno;
}


/// @fn int sProducto_sortProductosByCategory(sProducto*, int, int)
/// @brief Ordenar array de entidad segun CATEGORIA
///
/// @pre
/// @post
/// @param list Array
/// @param len Tamaño del array
/// @param order 1 ascendente, -1 si es decreciente
/// @return -1 si array = NULL o tamaño de array<=0 o Order != 1 o !=-1, 0 si salio bien
int sProducto_sortProductosByCategory(sProducto* list, int len, int order)
{
	int retorno;
	int i;
	int flagNoEstaOrdenado;

	sProducto auxiliar;
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
					//SI SUECEDE QUE ES MAYOR EL ANTERIOR
					if(list[i].categoria < list[i-1].categoria)
					{
						//CAMBIO LOS VALORES EN LAS  POSICIONES
						auxiliar = list[i-1];
						list[i-1] = list[i];
						list[i] = auxiliar;
						flagNoEstaOrdenado = 1;
						//ROMPO
						break;
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
					//SI SUCEDE QUE ES MAYOR EL POSTERIOR
					if(list[i].categoria > list[i-1].categoria)
					{
						auxiliar = list[i];
						list[i] = list[i-1];
						list[i-1] = auxiliar;
						flagNoEstaOrdenado = 1;
						//ROMPO
						break;
					}
				}

			}

		}
		retorno = 0;
	}


	return retorno;
}

/// @fn int sProducto_sortProductosByName(sProducto*, int, int)
/// @brief Ordenar array de entidad según nombre de producto
///
/// @pre
/// @post
/// @param list Array
/// @param len Tamaño del array
/// @param order 1 si el orden es ascendente, -1 si es decreciente
/// @return -1 si array = NULL o tamaño de array<=0 o Order != 1 o !=-1
int sProducto_sortProductosByName(sProducto* list, int len, int order)
{
	int retorno;
	int i;
	int j;
	int flagNoEstaOrdenado;

	sProducto auxiliar;
	flagNoEstaOrdenado = 1;

	retorno = -1;

	if(list != NULL && len>0 && (order == 1 || order == -1))
	{
		//ORDENAMIENTO ALFABETICO ASCENDENTE
		if(order == 1)
		{
			while(flagNoEstaOrdenado == 1)
			{

				//RECORRO LAS ENTIDADES Y COMPARO POSICION POSICION POSTERIOR CON
				//POSICION ANTERIOR
				flagNoEstaOrdenado = 0;
				for(i=1;i<len;i++)
				{
					//INICIO EN EL INDICE 0 DE LA CADENA DENTRO DEL CAMPO LAST NAME
					for(j=0;j<TAM_NOMBRE_PRODUCTO;j++)
					{
						//SI LA POSICION EN LA CADENA DEL CAMPO LAST NAME DE LA ENTIDAD SUPERIOR
						//ES INFERIOR CAMBIO LOS LUGARES DE LAS ENTIDADES
						if(list[i].nombreDelProducto[j] < list[i-1].nombreDelProducto[j])
						{
							auxiliar = list[i-1];
							list[i-1] = list[i];
							list[i] = auxiliar;
							flagNoEstaOrdenado = 1;
							break;
						}
						else
						{
							//SI LA POSICION EN LA CADENA DE LA ENTIDAD SUPERIOR
							//ES SUPERIOR, SALGO DEL FOR QUE INDICA EL INDEX DE LA CADENA
							//EN EL CAMPO LAS NAME
							//INDICA QUE YA ESTA ORDENADO
							if(list[i].nombreDelProducto[j] > list[i-1].nombreDelProducto[j])
							{
								break;
							}
							//SI ES IGUAL, PASA AL SIGUIENTE INDICE
							else
							{
								continue;
							}
						}


					}

				}

			}

		}
		else
		{
			while(flagNoEstaOrdenado == 1)
			{
				//RECORRO LAS ENTIDADES Y COMPARO POSICION POSICION POSTERIOR CON
				//POSICION ANTERIOR
				flagNoEstaOrdenado = 0;
				for(i=1;i<len;i++)
				{
					//INICIO EN EL INDICE 0 DE LA CADENA DENTRO DEL CAMPO LAST NAME
					for(j=0;j<TAM_NOMBRE_PRODUCTO;j++)
					{
						//SI LA POSICION EN LA CADENA DEL CAMPO LAST NAME DE LA ENTIDAD SUPERIOR
						//ES SUPERIOR CAMBIO LOS LUGARES DE LAS ENTIDADES
						if(list[i].nombreDelProducto[j] > list[i-1].nombreDelProducto[j])
						{
							auxiliar = list[i];
							list[i] = list[i-1];
							list[i-1] = auxiliar;
							flagNoEstaOrdenado = 1;
							break;
						}
						else
						{	//SI LA POSICION EN LA CADENA DE LA ENTIDAD SUPERIOR
							//ES INFERIOR, SALGO DEL FOR QUE INDICA EL INDEX DE LA CADENA
							//EN EL CAMPO LAS NAME
							//INDICA QUE YA ESTA ORDENADO
							if(list[i].nombreDelProducto[j] < list[i-1].nombreDelProducto[j])
							{
								break;
							}
							else
							{
								//SI ES IGUAL, PASA AL SIGUIENTE INDICE
								continue;
							}
						}

					}

				}

			}
		}
		retorno = 0;
	}

	return retorno;
}


/// @fn int sProducto_printAllProductoByCategory(sProducto*, int)
/// @brief Mostrar todos los productos dados de alta (activos) por categoria
///
/// @pre
/// @post
/// @param list array de Producto
/// @param len tamaño del array
/// @return -1 si no se ingresaron correctamente los parámetros, 0 si salio todo bien
int sProducto_printAllProductoByCategory(sProducto* list,int len)
{
	int retorno;

	retorno = -1;
	if(list != NULL && len>0)
	{

		printf("|%-25s|%-30s|%-12s|%-15s|%-15s|%-10s|%-8s|\n","CATEGORIA","NOMBRE DEL PRODUCTO","PRECIO","ID PRODUCTO","ID VENDEDOR","STOCK","ESTADO");
		if(sProducto_findProductoByCategory(list, len, 1)==0)//CATEGORIA 1 VEHICULOS
		{
			sProducto_printProductsByCategory(list, len, 1);
			retorno = 0;
		}
		if(sProducto_findProductoByCategory(list, len, 2)==0)//CATEGORIA 2 SUPERMERCADO
		{
			sProducto_printProductsByCategory(list, len, 2);
			retorno = 0;
		}
		if(sProducto_findProductoByCategory(list, len, 3)==0)//CATEGORIA 3 TECNOLOGIA
		{
			sProducto_printProductsByCategory(list, len, 3);
			retorno = 0;
		}
		if(sProducto_findProductoByCategory(list, len, 4)==0)//CATEGORIA 4 ELECTRODOMESTICOS
		{
			sProducto_printProductsByCategory(list, len, 4);
			retorno = 0;
		}

		if(sProducto_findProductoByCategory(list, len, 5)==0)//CATEGORIA 5 JUGUETES
		{
			sProducto_printProductsByCategory(list, len, 5);
			retorno = 0;
		}
		if(sProducto_findProductoByCategory(list, len, 6)==0)//CATEGORIA 6 MODA
		{
			sProducto_printProductsByCategory(list, len, 6);
			retorno = 0;
		}
		if(sProducto_findProductoByCategory(list, len, 7)==0)//CATEGORIA 7 DEPORTES
		{
			sProducto_printProductsByCategory(list, len, 7);
			retorno = 0;
		}
		if(sProducto_findProductoByCategory(list, len, 8)==0)//CATEGORIA 8 CUIDADO PERSONAL
		{
			sProducto_printProductsByCategory(list, len, 8);
			retorno = 0;
		}

	}

	return retorno;
}

/// @fn int sProducto_PausarProducto(sProducto[], int, int)
/// @brief Pausar una antidad
///
/// @pre
/// @post
/// @param productos array
/// @param lenProductos tamaño del array
/// @param idProductoAPausar
/// @return 1 si el producto tiene stock, 0 si ya no tiene stock y se pauso, -1 si no se ingresaron
/// correctamente los parámetros, -2 si no se encontro el id;
int sProducto_PausarProducto(sProducto productos[], int lenProductos, int idProductoAPausar)
{
	int retorno;
	int i;
	retorno = -1;

	if(productos != NULL && lenProductos>0 && idProductoAPausar)
	{
		for(i=0;i<lenProductos;i++)
		{
			if(productos[i].idProducto == idProductoAPausar)
			{
				if(productos[i].stock == 0)
				{
					productos[i].isEmpty = PAUSED;
					retorno = 0;
					break;
				}
				else
				{
					retorno = 1;
				}

			}
			retorno = -2;
		}
	}
	return retorno;
}

/// @fn int sProducto_importePorCompra(sProducto[], int, int, int)
/// @brief Calcular importe de compra
///
/// @pre
/// @post
/// @param productos
/// @param len
/// @param cantidad cantidad comprada
/// @param idProducto
/// @return -1 si no se ingresaron bien los parametros, -2 si no se encontro el producto, importe si salio todo bien
int sProducto_importePorCompra(sProducto productos[],int len,int cantidad,int idProducto)
{
	int retorno;
	int indiceProducto;
	float resultado;

	retorno = -1;
	indiceProducto = sProducto_findProductoById(productos, len, idProducto);
	if(indiceProducto>=0)
	{
		MultiplicarFloat(productos[indiceProducto].precio, (float)cantidad, &resultado);
		retorno = resultado;
	}
	else
	{
		retorno = -2;
	}

	return retorno;
}

/// @fn int sProducto_removeProducto(sProducto*, int, int)
/// @brief Dar de baja una entidad dentro de un array
///
/// @pre
/// @post
/// @param list array
/// @param len tamaño del array
/// @param id id a dar de baja
/// @return -1 si array = NULL o len<=0 o no se encontro el id
int sProducto_removeProducto(sProducto* list, int len, int id)
{
	int retornoBaja;
	int retorno;

	retorno = -1;
	if(list != NULL && len>0)
	{
		//OBTENGO EL ID DONDE SE ENCUENTRA EL PASAJERO PASADO POR ID
		retornoBaja = sProducto_findProductoById(list, len, id);
		if(retornoBaja >=0)
		{
			//CAMBIO EL ESTADO A LOW
			list[retornoBaja].isEmpty = LOW;
			retorno = 0;
		}
	}

	return retorno;
}

