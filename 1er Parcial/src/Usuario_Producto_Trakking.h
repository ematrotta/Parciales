/*
 * Usuario_Producto_Trakking.h
 *
 *  Created on: 15 may. 2022
 *      Author: Emanuel
 */

#ifndef USUARIO_PRODUCTO_TRAKKING_H_
#define USUARIO_PRODUCTO_TRAKKING_H_
#include "Usuario_Producto.h"
#include "Trakking.h"
#define TRUE 0
#define FALSE 1
#define LOW 2

int sTrakking_InputsDataTrakking(sTrakking * trakking, char mensajeError[], sUsuario usuario, int idProducto,int cantidad, sProducto productos[], int lenProductos);
int sTrakking_printOneForUser(sTrakking trakking,sProducto productos [],int lenProductos);
int sTrakking_printAllByTypeUser(sTrakking trakkings[],int lenTrakkings, sProducto productos [],int lenProductos,int idUsuario,int tipoVendedorComprador);
int sTrakking_DevolverStock(sTrakking trakkings[],int lenTrakking, int idTrakking,sProducto productos[],int lenProductos);





#endif /* USUARIO_PRODUCTO_TRAKKING_H_ */
