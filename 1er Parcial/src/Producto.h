/*
 * Producto.h
 *
 *  Created on: 15 may. 2022
 *      Author: Emanuel
 */

#ifndef PRODUCTO_H_
#define PRODUCTO_H_
#include <string.h>
#include "Inputs.h"
#include "Outputs.h"
#define TAM_NOMBRE_PRODUCTO 25
#define TAM_CATEGORIA_PRODUCTO 30
#define CANTIDAD_PRODUCTOS 10
#define TRUE 0 //LIBRE
#define FALSE 1 //OCUPADO
#define LOW 2 //DADO DE BAJA
#define PAUSED 3 //PAUSADO


typedef struct{
	int idProducto;
	short int isEmpty;
	short int categoria;
	int stock;
	float precio;
	char nombreDelProducto[TAM_NOMBRE_PRODUCTO];
	int FK_idUsuario;

}sProducto;

int sProducto_initProducto(sProducto * list, int len);
int sProducto_findFreeSpace(sProducto * list, int len);
int sProducto_findProductoById(sProducto * list,int len,int id);
int sProducto_findProductoByCategory(sProducto * list,int len,int categoria);
int sProducto_InputsDataProducto(sProducto * producto,char mensajeError[]);
void sProducto_printOne(sProducto producto);
int sProducto_printProductsByCategory(sProducto* list,int len,int category);
int sProducto_printProductsByUser(sProducto* list,int len,int idUsuario);
int sProducto_printAllProductoByCategory(sProducto* list,int len);
int sProducto_sortProductosByCategory(sProducto* list, int len, int order);
int sProducto_sortProductosByName(sProducto* list, int len, int order);
int sProducto_PausarProducto(sProducto productos[], int lenProductos, int idProductoAPausar);
int sProducto_importePorCompra(sProducto productos[],int len,int cantidad,int idProducto);
int sProducto_removeProducto(sProducto* list, int len, int id);

#endif /* PRODUCTO_H_ */
