/*
 * Usuario_Producto.h
 *
 *  Created on: 15 may. 2022
 *      Author: Emanuel
 */

#ifndef USUARIO_PRODUCTO_H_
#define USUARIO_PRODUCTO_H_
#include "Producto.h"
#include "Usuario.h"

int sProducto_addProducto(sProducto* listProducto, int lenProducto, char nombre[],float precio,short int categoriaProducto,int stock,sUsuario usuario);
int sUsuario_removeUsuario(sUsuario* list, int len, int id,sProducto productos[],int lenProductos);
int sProducto_findProductoByIdUser(sProducto * list,int len,int idProducto,int idUsuario);


#endif /* USUARIO_PRODUCTO_H_ */
