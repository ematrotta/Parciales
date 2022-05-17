/*
 ============================================================================
 Name        : 1er.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Usuario_Producto_Trakking.h"

#define USUARIOS 6
#define PRODUCTOS 5
#define TRAKKINGS 5

int main(void) {
	setbuf(stdout,NULL);

	int OpcionMenuInicio;
	int OpcionMenuSecundario;

	//HARCODEO DE USUARIOS
	sUsuario usuario[USUARIOS] = {{10000,FALSE,1,"admin@admin.com","1234","peron 1234",9999},
			{10001,FALSE,2,"manu-trotta@hotmail.com","abc456","senador pallares 929",1598},
			{10002,FALSE,2,"ematrotta10@gmail.com","zzzzz","senador pallares 222",1718},
			{10003,LOW,2,"dadodebaja@dadode.com","aaaaa","senador pallares 333",1720}};

	//HARCODEO DE PRODUCTOS
	sProducto productos[PRODUCTOS] = {{10000,FALSE,1,3,11111,"TELE LED",10000},
			{10001,FALSE,2,5,22222,"TERMO",10001},
			{10002,FALSE,3,4,33333,"CARPA",10001},
			{10003,FALSE,4,6,44444,"COMPUTADORA",10002}};

	//sUsuario usuario[USUARIOS];
	//sUsuario_initUsuario(usuario, USUARIOS);

	//sProducto productos[PRODUCTOS];
	//sProducto_initProducto(productos, PRODUCTOS);

	sTrakking trakkings[TRAKKINGS];
	sTrakking_initTrakking(trakkings, TRAKKINGS);

	//*******MENU
	//RETORNO DE MENÚ (PRINCIPAL Y USUARIOS), SI ES 1 VUELVO AL MENU, SI ES 0 SALGO DEL MENU ACTUAL
	int flagMenuPrincipal;
	int flagMenuUsuario;
	int retornoMenuPrincipal;
	flagMenuUsuario = 0;
	flagMenuPrincipal = 0;

	//*******USUARIOS
	sUsuario axiliarUsuario;
	char opcionRegistro;
	char auxiliarMailIngresado[TAM_EMAIL];
	char auxiliarContraseniaIngresada[TAM_PASSWORD];
	int retornoIngresoUsuario;
	int retornoMailIngresado;
	int flagIngresoSistema;
	flagIngresoSistema = 0;
	int intentosContrasenia;
	int flagPrimerUsuario;
	int indexUsuarioEnSistema;
	flagPrimerUsuario = 1; //MODIFICAR A 0 CUANDO DESCOMENTE LOS ARRAY DE USUARIO

	//*********PRODUCTOS
	sProducto axiliarProducto;
	int retornoProductoIngresado;
	int flagPrimerProducto;
	flagPrimerProducto = 1; //MODIFICAR A 0 CUANDO DESCOMENTE EL ARRAY DE PRODUCTOS

	//********TRAKKING/VENTAS
	sTrakking auxiliarTrakking;
	int axuiliarIdProducto;
	int indexIdProducto;
	int cantidadProducto;
	char opcionConfirmarTrakking;
	float importeAbonar;
	int auxiliarBajaTrekking;
	int flagPrimerTrakking;
	flagPrimerTrakking = 0;

	//*********ADMIN
	int auxiliarBajaUsuario;
	char opcionConfirmarBaja;



	do
	{
		retornoMenuPrincipal = Utn_GetNumeroInt(&OpcionMenuInicio, "**************************\n"
				"** 1er EXAMEN LAB 1 - H **\n"
				"**************************\n\n"
				"1)INGRESAR\n2)REGISTRARSE\n\n0)SALIR\n\nOPCIÓN", "La opcion debe estar entre 0 y 2", 2, 0, 3);
		if(retornoMenuPrincipal != 0)
		{
			//SI EL RETORNO DEL MENU ES ERRONEO SALE
			break;
		}
		switch(OpcionMenuInicio)
		{
			case 0:
				//SALIR
				flagMenuPrincipal = 0;
				break;
			case 1:
				//INGRESAR
				//SI NO HAY USUARIOS
				if(flagPrimerUsuario == 0)
				{
					puts("\nNo hay usuarios Ingresados en el sistema. Quiere ser el primero?\n"
							"¡¡REGISTRESE!!");
				}
				else
				{
					//SOLICITO INGRESO DE MAIL Y CONTRASEÑA
					if(Utn_GetMail(auxiliarMailIngresado, TAM_EMAIL, "\nIngrese su mail", "Error no es un mail", 3)==0)
					{
						Utn_GetString(auxiliarContraseniaIngresada, "Ingrese su contraseña", "ERROR. Max cantidad de caracteres 9",TAM_PASSWORD,3);
						retornoIngresoUsuario = sUsuario_ValidarMailyPassword(usuario, USUARIOS, auxiliarMailIngresado, auxiliarContraseniaIngresada);
						//VERIFICO CUAL FUE EL RESULTADO DEL INGRESO
						switch(retornoIngresoUsuario)
						{
						case 0:
							flagIngresoSistema = 1;
							break;
						case -2:
							//LA CONTRASEÑA ES ERRONEA
							puts("La contraseña es incorrecta");
							intentosContrasenia = 3;
							while(intentosContrasenia>0)
							{
								Utn_GetString(auxiliarContraseniaIngresada, "Ingrese Nuevamente la contraseña", "ERROR. Max cantidad de caracteres 9",TAM_PASSWORD,3);
								if(sUsuario_ValidarMailyPassword(usuario, USUARIOS, auxiliarMailIngresado, auxiliarContraseniaIngresada)==0)
								{
									//SI INGRESO BIEN LOS DATOS, ROMPO E INGRESO AL SISTEMA
									retornoIngresoUsuario = 0;
									flagIngresoSistema = 1;
									break;
								}
								else
								{
									printf("\nTiene %d intentos más\n",intentosContrasenia-1);
									intentosContrasenia--;

								}
							}
							if(intentosContrasenia == 0)
							{
								//SI NO PUDO INGRESAR BIEN LA CONTRASEÑA, VUELVE AL INICIO
								flagMenuPrincipal = 1;
							}

							break;
						case -3:
							puts("El mail no existe.");
							//SI EL MAIL NO EXISTE, PUEDE CREAR UNO
							if(GetCharacter2Options(&opcionRegistro, "Desea registrarse? S/N", "Error S (Si) o N (No)", 'S', 'N', 3)==0)
							{
								//SI EL INGRESO DE DATOS SE PUDO REALIZAR CORRECTAMENTE
								if(opcionRegistro == 's' || opcionRegistro == 'S')
								{
									if(sUsuario_InputsDataUsuario(&axiliarUsuario, "No se pudo registrar correcatmente")==0)
									{
										retornoMailIngresado = sUsuario_addUsuario(usuario, USUARIOS, axiliarUsuario.domicilio, axiliarUsuario.correo, axiliarUsuario.password, axiliarUsuario.tipoUsuario, axiliarUsuario.codigoPostal);
										if(retornoMailIngresado ==0)
										{
											puts("\nIngreso Exitoso!\n");

										}
										else
										{
											if(retornoMailIngresado == -2)
											{
												puts("\nEl Mail ya se encuentra registrado\n");
											}
											else
											{
												puts("\nLo sentimos. Ya no hay espacio para cargar un nuevo usuario\n");
											}
										}
									}

								}
							}

						}
					}

				}
				//DE CUALQUIER MANERA VUELVE AL MENU DE INICIO
				flagMenuPrincipal = 1;
				break;
			case 2:
				//REGISTRARSE
				//SI SE INGRESARON LOS DATOS CORRECTAMENTE O NO, VUELVO AL INICIO
				if(sUsuario_InputsDataUsuario(&axiliarUsuario, "No se pudo registrar correcatmente")==0)
				{
					retornoMailIngresado = sUsuario_addUsuario(usuario, USUARIOS, axiliarUsuario.domicilio, axiliarUsuario.correo, axiliarUsuario.password, axiliarUsuario.tipoUsuario, axiliarUsuario.codigoPostal);
					if(retornoMailIngresado ==0)
					{
						puts("\nIngreso Exitoso!\n");
						flagPrimerUsuario = 1;
					}
					else
					{
						if(retornoMailIngresado == -2)
						{
							puts("El Mail ya se encuentra registrado\n");
						}
						else
						{
							puts("\nLo sentimos. Ya no hay espacio para cargar un nuevo usuario\n");
						}
					}

				}
				flagMenuPrincipal = 1;
				break;
		}

		//INGRESO AL SISTEMA
		if(retornoIngresoUsuario == 0 && flagIngresoSistema == 1)
		{

			//BUSCO EL INDICE DONDE ESTA EL USUARIO QUE INGRESO
			indexUsuarioEnSistema = sUsuario_findUsuarioByMail(usuario, USUARIOS, auxiliarMailIngresado);

			//VERIFICO QUE NO ESTE DADO DE BAJA
			if(usuario[indexUsuarioEnSistema].isEmpty == FALSE)//SI ESTA ACTIVO
			{
				//SI EL USUARIO ES COMUN
				if(usuario[indexUsuarioEnSistema].tipoUsuario == TIPO_USUARIO_COMUN)
				{
					do
					{
						if(Utn_GetNumeroInt(&OpcionMenuSecundario, "**************************\n"
								"** 1er EXAMEN LAB 1 - H **\n"
								"********* USUARIO ********\n\n"
								"1)COMPRAR\n2)VENDER\n3)ESTADO DE COMPRAS\n4)ESTADO DE VENTAS\n0)SALIR\n\nOPCIÓN", "La opcion debe estar entre 0 y 2", 4, 0, 3)==0)
						{
							switch(OpcionMenuSecundario)
							{
								case 0://SALIR DE LA CUENTA
									//SACO AL USUARIO QUE PUEDA ESTAR LOGEADO
									flagIngresoSistema = 0;
									//SALGO DEL MENU DE USUARIO
									flagMenuUsuario = 0;
									flagMenuPrincipal = 1;
									break;
								case 1://COMPRAR
									//SI NO HAY PRODUCTOS CARGADOS, NO SE PUEDE COMPRAR
									if(flagPrimerProducto == 0)
									{
										puts("\nNo hay ningún producto cargado en la base\n"
												"seleccione la opción 'Vender' e ingrese el 1ro!");
										flagMenuUsuario = 1;
									}
									else
									{
										puts("\nQué Producto desea comprar?:\n");
										//ORDENO LOS PRODUCTOS POR CATEGORIA ASCENDENTE
										sProducto_sortProductosByCategory(productos, PRODUCTOS, 1);
										//SI HAY PRODUTOS EN ALGUNA CATEGORIA LOS IMPRIMO
										if(sProducto_printAllProductoByCategory(productos, PRODUCTOS) == 0)
										{
											//PIDO
											Utn_GetNumeroInt(&axuiliarIdProducto, "Ingrese el ID del producto o 0 para volver al menu", "El id debe estar entre 100000 y 1000", 100000, 0, 3);
											{
												if(axuiliarIdProducto == 0)
												{
													//SI LA OPCION INGRESADA ES 0 VUELVE AL MENU DE USUARIO
												}
												else
												{
													indexIdProducto = sProducto_findProductoById(productos, PRODUCTOS, axuiliarIdProducto);
													//SI SE ENCONTRO UN UNIDICE Y ESTA HABILITADO PARA LA COMPRA
													if(indexIdProducto>= 0 && productos[indexIdProducto].isEmpty == FALSE)
													{
														//SI ENCUENTRA EL ID DEL PRODUCTO QUE INGRESO
														printf("\nCantidad actual: %d\n",productos[indexIdProducto].stock);
														//PERMITE INGRESAR LA CANTIDAD
														if(Utn_GetNumeroInt(&cantidadProducto, "Cantidad a comprar", "Debe comprar entre 1 y el maximo de stock",productos[indexIdProducto].stock,1, 3)==0)
														{
															//SI LA CANTIDAD A COMPRAR ES MENOR QUE LA DISPONIBLE PERMITE SE CARGAN LOS DATOS A UN TRAKKING AUXILIAR
															if(sTrakking_InputsDataTrakking(&auxiliarTrakking, "No se pudo cargar la compra correctamente", usuario[indexUsuarioEnSistema], axuiliarIdProducto, cantidadProducto, productos, PRODUCTOS)==0)
															{
																importeAbonar = sProducto_importePorCompra(productos, PRODUCTOS, cantidadProducto, productos[indexIdProducto].idProducto);
																printf("\nEl importe a abonar es de %.2f\n",importeAbonar);
																//SE PIDE LA CONFIRMACION PARA TERMINAR DE GENERAR EL TRAKKING
																if(GetCharacter2Options(&opcionConfirmarTrakking, "Desea confirmar la operación? S/N", "La respuesta debe ser S (si) / N (no)", 'S', 'N', 3) == 0)
																{
																	if(opcionConfirmarTrakking == 'S' || opcionConfirmarTrakking == 's')
																	{
																		//SI CONFIRMA, SE GENERA EL TRAKKING EN UN ESPACIO LIBRE
																		if(sTrakking_addTrakking(trakkings, TRAKKINGS, auxiliarTrakking.distanciaKm, auxiliarTrakking.cantidad, auxiliarTrakking.FK_idProducto, auxiliarTrakking.FK_idVendedor, auxiliarTrakking.FK_idComprador) == 0)
																		{
																			productos[indexIdProducto].stock -= auxiliarTrakking.cantidad;
																			puts("\nYa es tuyo y está en camino\n");
																			//EVALUO SI EL PRODUCTO DEJO DE TENER STOCK Y LO PAUSO
																			sProducto_PausarProducto(productos, PRODUCTOS, productos[indexIdProducto].idProducto);
																			flagPrimerTrakking = 1;
																		}
																		else
																		{
																			//SI YA NO HAY ESPACIO EN EL ARRAY DE TRAKKING
																			puts("\nEl sistema ya no admite compras\n");
																		}

																	}

																}
															}
														}

													}
													else
													{
														//SI NO SE ENCONTRÓ EL INDICE DEL PRODUCTO SELECCIONADO O NO ESTA ACTIVO VUELVO AL MENU
														puts("\nNo se encontró el producto seleccionado\n");

													}
												}
											}

										}
										else
										{
											//SI NO HAY PRODUCTOS PUBLICADOS
											puts("\nNo hay productos publicados\n");
										}

									}
									flagMenuUsuario = 1;
									break;
								case 2://VENDER
									//CARGAR PRODUCTO NUEVO
									puts("\nVamos a preparar la publicacion\n");
									if(sProducto_InputsDataProducto(&axiliarProducto, "No se pudo ingresar el producto correctamente")==0)
									{
										//CARGO EN UN AUXILIAR LOS DATOS DEL PRODUCTO
										retornoProductoIngresado = sProducto_addProducto(productos, PRODUCTOS, axiliarProducto.nombreDelProducto, axiliarProducto.precio, axiliarProducto.categoria, axiliarProducto.stock, usuario[indexUsuarioEnSistema]);
										if(retornoProductoIngresado ==0)
										{
											puts("\nIngreso Exitoso!\n");
											flagPrimerProducto = 1;
										}
										else
										{
											puts("\nLo sentimos. Ya no hay espacio para cargar un nuevo producto\n");
										}
									}

									flagMenuUsuario =1;
									break;
								case 3://ESTADO DE COMPRAS
									//ORDENO LOS TRAKKINGS POR SU ID
									sTrakking_sortTrakkings(trakkings, TRAKKINGS, -1);
									//ACTUALIZO LOS ESTADOS DE TODOS LOS TRAKKINGS
									sTrakking_ActualizarEstadosTrakking(trakkings, TRAKKINGS);
									printf("\n|%-15s|%-25s|%-15s|%-15s\n","ID TRAKKING","NOMBRE DEL PRODUCTO","CANTIDAD","ESTADO");
									if(sTrakking_printAllByTypeUser(trakkings, TRAKKINGS, productos, PRODUCTOS, usuario[indexUsuarioEnSistema].idUsuario, 1)!=0)
									{
										puts("Usted no tiene compras\n");
									}
									else
									{
										//PREGUNTO SI QUIERE DAR DE BAJA ALGUN TRAKKING
										if(Utn_GetNumeroInt(&auxiliarBajaTrekking, "Desea dar algúna compra de baja? Ingrese ID o 0 para volver al menú", "ERROR. Debe ingresar un número entre ", 1000000, 0, 3)==0)
										{
											if(auxiliarBajaTrekking == 0)
											{
												//VOLVER AL MENU
											}
											else
											{
												//ACTUALIZO EL TRAKKING HASTA ULTIMO MOMENTO
												if(sTrakking_ActualizarEstadosTrakking(trakkings, TRAKKINGS)==0 && sTrakking_BajaTrakking(trakkings,TRAKKINGS, auxiliarBajaTrekking)==0)
												{
													puts("\nCompra cancelada\n");
													//DEVUELVO AL STOCK LA CANTIDAD DEL TRAKKING, SI HABÍA QUEDADO PAUSADA POR FALTA DE STOCK, LA REACTIVO
													sTrakking_DevolverStock(trakkings,TRAKKINGS,auxiliarBajaTrekking,productos,PRODUCTOS);

												}
												else
												{
													puts("\nEl id no se encontro o la compra ya esta cumplida/cancelada\n");
												}
											}

										}
									}

									flagMenuUsuario =1;

									break;
								case 4://ESTADO DE VENTAS
									sTrakking_sortTrakkings(trakkings, TRAKKINGS, -1);
									sTrakking_ActualizarEstadosTrakking(trakkings, TRAKKINGS);
									printf("\n|%-15s|%-25s|%-15s|%-15s\n","ID TRAKKING","NOMBRE DEL PRODUCTO","CANTIDAD","ESTADO");
									if(sTrakking_printAllByTypeUser(trakkings, TRAKKINGS, productos, PRODUCTOS, usuario[indexUsuarioEnSistema].idUsuario, 0)!=0)
									{
										puts("Usted no tiene ventas\n");
									}
									flagMenuUsuario =1;
									break;
							}
						}
						else
						{
							//SI LA OPCION INGRESADA NO ES CORRECTA
							flagMenuUsuario = 0;
						}

					}while(flagMenuUsuario == 1);

				}
				else
				{
					//SI ES ADMIN
					do
					{
						if(Utn_GetNumeroInt(&OpcionMenuSecundario, "**************************\n"
								"** 1er EXAMEN LAB 1 - H **\n"
								"********** ADMIN *********\n\nGESTION E INFORMES\n\n"
								"1)LISTAR ESTADO DE TODOS LOS USUARIOS\n2)LISTAR TODOS LOS PRODUCTOS POR CATEGORIA"
								"\n3)BAJA DE UN PRODUCTO\n4)BAJA DE UN USUARIO\n5)VER TRAKKING GLOBAL\n0)SALIR\n\nOPCIÓN", "La opcion debe estar entre 0 y 5", 5, 0, 3)==0)
						{

							switch(OpcionMenuSecundario)
							{
							case 0:
								//SACO AL USUARIO QUE PUEDA ESTAR LOGEADO
								flagIngresoSistema = 0;
								//SALGO DEL MENU DE USUARIO
								flagMenuUsuario = 0;
								flagMenuPrincipal = 1;
								break;
							case 1:
								//LISTAR ESTADO DE TODOS LOS USUARIOS
								if(flagPrimerUsuario == 0)
								{
									puts("\nAún no se registró ningun usuario en sistema\n");
								}
								else
								{
									printf("\n|%-15s|%-30s|%-25s\n","ID USUARIO","CORREO ELECTRONICO","ESTADO");
									sUsuario_printUsuariosForAdmin(usuario, USUARIOS);
								}
								puts("\n");
								flagMenuUsuario =1;
								break;
							case 2:
								//LISTAR TODOS LOS PRODUCTOS POR CATEGORIA
								if(flagPrimerProducto == 0)
								{
									puts("\nAún no se ingresaron productos al sistema\n");
								}
								else
								{
									sProducto_sortProductosByName(productos,PRODUCTOS,1);
									sProducto_sortProductosByCategory(productos, PRODUCTOS, 1);
									sProducto_printAllProductoByCategory(productos, PRODUCTOS);
								}
								flagMenuUsuario =1;
								break;
							case 3:
								//BAJA DE UN PRODUCTO
								if(flagPrimerProducto == 0)
								{
									puts("\nAún no se ingresaron productos al sistema\n");

								}
								else
								{

									//ORDENO LOS PORDUCTOS POR CATEGORIA E IMPRIMO
									sProducto_sortProductosByCategory(productos, PRODUCTOS, 1);
									if(sProducto_printAllProductoByCategory(productos, PRODUCTOS) == 0)
									{
										//PIDO
										if(Utn_GetNumeroInt(&axuiliarIdProducto, "\nIngrese el ID del producto que desea dar de baja o 0 para volver al menu", "El id debe estar entre 100000 y 1000", 100000, 0, 3)==0)
										{
											if(axuiliarIdProducto == 0)
											{
												//SI LA OPCION INGRESADA ES 0 VUELVE AL MENU DE USUARIO
											}
											else
											{
												if(GetCharacter2Options(&opcionConfirmarBaja, "Desea confirmar la baja del producto S/N", "Debe igresar S (si) o N (no)", 'S', 'N', 3) == 0)
												{
													if(opcionConfirmarBaja == 'S' || opcionConfirmarBaja == 's')
													{
														if(sProducto_removeProducto(productos, PRODUCTOS, axuiliarIdProducto) == 0)
														{
															puts("\nBaja de producto Exitosa\n");
														}

													}
												}

											}
										}
									}
									flagMenuUsuario =1;
									break;
							case 4:
								//BAJA DE UN USUARIO
								if(flagPrimerUsuario == 0)
								{
									puts("\nAún no se ingresó ningún usuario");

								}
								else
								{
									printf("\n|%-15s|%-30s|%-25s\n","ID USUARIO","CORREO ELECTRONICO","ESTADO");

									sUsuario_printUsuariosForAdminActives(usuario, USUARIOS);

									if(Utn_GetNumeroInt(&auxiliarBajaUsuario, "\nIngrese el usuario que desea dar de baja o 0 si quiere salir", "ERROR. Debe ser entre 100000 y 0", 100000, 0, 3)==0)
									{
										if(auxiliarBajaUsuario == 0)
										{
											//SOLO VOLVER AL MENU
										}
										else
										{
											if(GetCharacter2Options(&opcionConfirmarBaja, "Desea confirmar la baja del usuario y todos sus productos? S/N", "Debe igresar S (si) o N (no)", 'S', 'N', 3) == 0)
											{
												if(opcionConfirmarBaja == 'S' || opcionConfirmarBaja == 's')
												{
													if(sUsuario_removeUsuario(usuario, USUARIOS, auxiliarBajaUsuario, productos, PRODUCTOS)==0)
													{
														puts("\nBaja de usuario Exitosa\n");
													}
													else
													{
														puts("\nNo se encontro el usuario\n");
													}


												}
											}

										}
									}
								}
								flagMenuUsuario =1;
								break;
							case 5:
								//VER TRAKKING GLOBAL
								if(flagPrimerTrakking == 0)
								{
									puts("\nAún no se generó ningún trakking\n");
								}
								else
								{
									sTrakking_sortTrakkings(trakkings, TRAKKINGS, -1);
									sTrakking_ActualizarEstadosTrakking(trakkings, TRAKKINGS);
									printf("\n|%-15s|%-20s|%-15s|%-15s\n","ID TRAKKING","ESTADO","ID COMPRADOR","ID VENDEDOR");
									sTrakking_printTrakkingsForAdmin(trakkings, TRAKKINGS);
								}
								puts("\n");
								flagMenuUsuario =1;
								break;
								}
							}

						}
						else
						{
							//SI EL USUARIO NO INGRESA BIEN LA OPCION DE MENÚ
							flagMenuUsuario = 0;
							flagMenuPrincipal=1;
						}


					}while(flagMenuUsuario == 1);


				}
			}
			else
			{
				puts("\nSu usuario fue dado de baja\n");
				flagMenuPrincipal=1;
			}

		}

	}while(flagMenuPrincipal == 1);


	return retornoMenuPrincipal;
}
