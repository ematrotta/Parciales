/*
 * Usuario.c
 *
 *  Created on: 11 may. 2022
 *      Author: Emanuel
 */


#include "Usuario.h"


//********************** FUNCIONES PARA EL ALTA********************************

static int initId = 10000;
static int sUsuario_IdGenerator(void)
{
	return initId++;
}

/// @fn int sUsuario_findUsuarioById(sUsuario*, int, int)
/// @brief Buscar Indice de entidad según id
///
/// @pre
/// @post
/// @param list array
/// @param len tamaño del array
/// @param id id a buscar
/// @return -2 si array = NULL o tamaño de array<=0, -1 si no se encontró el id, Indice si salio todo bien
int sUsuario_findUsuarioById(sUsuario * list,int len,int id)
{
	int retorno;
	int i;

	retorno = -2;
	if(list != NULL && len>0)
	{
		retorno = -1;
		for(i = 0;i<len;i++)
		{
			if(list[i].idUsuario == id)
			{
				retorno = i;
				break;
			}

		}
	}

	return retorno;
}

/// @fn int sUsuario_findUsuarioByMail(sUsuario*, int, char[])
/// @brief Buscar Indice de entidad según Mail
///
/// @pre
/// @post
/// @param list array
/// @param len tamaño del array
/// @param id id a buscar
/// @return -2 si array = NULL o tamaño de array<=0, -1 si no se encontró el id, Indice si salio todo bien
int sUsuario_findUsuarioByMail(sUsuario * list,int len,char mail[])
{
	int retorno;
	int i;

	retorno = -2;
	if(list != NULL && mail!=NULL && len>0)
	{
		retorno = -1;
		for(i = 0;i<len;i++)
		{
			if(strncmp(list[i].correo,mail,TAM_EMAIL)==0)
			{
				retorno = i;
				break;
			}

		}
	}

	return retorno;
}


/// @fn int sUsuario_InputsDataUsuario(sUsuario *, char[])
/// @brief Ingresar datos a una entidad
///
/// @pre
/// @post
/// @param usuario puntero a estructura de un usuario
/// @param mensajeError
/// @return -1 si el tipo es erroneo, -2 si no es CP, -3 Si no es un domicilio,
///-4 si no es correcta la contraseña, -5 Si no es un mail,-6 si no se ingresaron todos los parametros
int sUsuario_InputsDataUsuario(sUsuario * usuario, char mensajeError[])
{
	sUsuario auxiliar;
	int retorno;

	if(usuario != NULL && mensajeError != NULL)
	{
		//INGRESO CORREO ELECTRONICO
		if(Utn_GetMail(auxiliar.correo,TAM_EMAIL, "\nIngrese el su correo electrónico", "ERROR. No es un mail", 3) == 0)
		{
			//INGRESO CONTRASEÑA
			if(Utn_GetString(auxiliar.password, "Ingrese una contraseña", "ERROR. Maxima cantidad de caracteres: 9", TAM_PASSWORD, 3) == 0 && GetPassword(auxiliar.password,4,TAM_PASSWORD,"Error. debe contener entre 4 y 9 caracteres")==0)
			{
				//INGRESO DOMICILIO
				if(Utn_GetStringAlfaNumericaPlus(auxiliar.domicilio, "Ingrese su direccion", "ERROR. Maxima cantidad de caracteres: 49", TAM_DOMICILIO, 3) == 0)
				{
					//INGRESO CP
					if(Utn_GetNumeroInt(&auxiliar.codigoPostal, "Ingrese codigo postal", "ERROR. El número debe estar entre 0001 y 9999", 9999, 1, 3)==0)
					{
						//INGRESO TIPO DE USUARIO
						if(Utn_GetNumeroShortInt(&auxiliar.tipoUsuario, "Ingrese el tipo de Usuario:\n\t1)Admin.\n\t2)Comun.\nOPCIÓN", "ERROR. Debe ser entre 1 y 2", TIPO_USUARIO_COMUN, TIPO_USUARIO_ADMIN, 3) == 0)
						{
							(*usuario) = auxiliar;
							retorno = 0;
						}
						else
						{
							//SI LO INGRESADO COMO TIPO ES ERRONEO
							retorno = -1;
						}
					}
					else
					{
						//SI EL CODIGO POSTAL ES ERRONEO
						retorno = -2;
					}
				}
				else
				{
					//SI NO ES UN DOMICILIO
					retorno = -3;
				}
			}
			else
			{
				//SI NO ES ES CORRECTA LA CONTRASEÑA
				retorno = -4;
			}
		}
		else
		{
			//SI NO MAIL
			retorno = -5;
		}
	}
	else
	{
		//SI NO SE INGRESARON TODOS LOS PARAMETROS
		retorno = -6;
	}
	if(retorno<0)
	{
		printf("\n%s\n",mensajeError);
	}
	return retorno;
}



/// @fn int sUsuario_addUsuario(sUsuario*, int, int, char[], char[], char[], int, int)
/// @brief
///
/// @pre
/// @post
/// @param list array de Usuario
/// @param len tamaño del array
/// @param id id del usuario que se va a cargar
/// @param direccion
/// @param mail
/// @param password
/// @param tipoUsuario
/// @param codigoPostal
/// @return -1 si no se pudo cargar, -2 si el mail ya esta ingresado, 0 si se pudo cargar
int sUsuario_addUsuario(sUsuario* list, int len, char direccion[],char mail[],char password[],short int tipoUsuario,int codigoPostal)
{
	int retorno;
	int indiceLibre;


	retorno = -1;
	//BUSCA DENTRO DE UN ARRAY DE ENTIDADES, UN ESPACIO LIBRE
	indiceLibre = sUsuario_findFreeSpace(list, len);
	if(list != NULL && direccion != NULL && mail != NULL && password != NULL &&len>0 && indiceLibre>=0)
	{
		//SI EL MAIL NO ESTA INGRESADO, PERMITO EL REGISTRO
		if(sUsuario_findUsuarioByMail(list, len, mail)==-1)
		{
			list[indiceLibre].idUsuario = sUsuario_IdGenerator();
			strncpy(list[indiceLibre].correo,mail,TAM_EMAIL);
			strncpy(list[indiceLibre].domicilio,direccion,TAM_DOMICILIO);
			list[indiceLibre].codigoPostal = codigoPostal;
			list[indiceLibre].tipoUsuario = tipoUsuario;
			strncpy(list[indiceLibre].password,password,TAM_PASSWORD);
			list[indiceLibre].isEmpty = FALSE;
			retorno = 0;
		}
		else
		{
			retorno = -2;
		}
	}
	return retorno;
}


/// @fn int sUsuario_ValidarMailyPassword(sUsuario*, int, char[], char[])
/// @brief Validar que exista el usuario y su contraseña sea correcta
///
/// @pre
/// @post
/// @param list array de usuarios
/// @param len atamio de array
/// @param mail
/// @param password
/// @return -1 si no estan bien ingresados los parametros
/// -2 si la contraseña no corresponde al mail
/// -3 si el mail no existe
int sUsuario_ValidarMailyPassword(sUsuario * list,int len,char mail[],char password[])
{
	int retorno;
	int i;

	//SI NO SE INGRESARON TODOS LOS PARAMETROS
	retorno = -1;
	if(list != NULL && mail != NULL && password != NULL && len>0)
	{
		i = sUsuario_findUsuarioByMail(list, len, mail);
		if(i>=0)
		{
			//COMPARO LAS CONTRASEÑAS DEL INDICE QUE ME ARROJA LA FUNCION BUSCAR POR USUARIO
			if(strncmp(list[i].password,password,TAM_PASSWORD)==0)
			{
				retorno = 0;
			}
			else
			{
				//SI EL PASSWORD DEL MAIL INGRESADO ES INCORRECTO
				retorno = -2;
			}
		}
		else
		{
			//SI NO EXISTE EL MAIL
			retorno = -3;
		}



	}

	return retorno;
}


/// @fn int sUsuario_initUsuario(sUsuario*, int)
/// @brief Inicializar todos los campos isEmpty
///
/// @pre
/// @post
/// @param list Array
/// @param len Tamaño del array
/// @return -1 si está mal, 0 si esta bien
int sUsuario_initUsuario(sUsuario * list, int len)
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

/// @fn int sUsuario_findFreeSpace(sUsuario*, int)
/// @brief Encontrar un espacio Libre
///
/// @pre
/// @post
/// @param list Array
/// @param len tamaño del array
/// @return -1 si no encontro espacios libres, >=0 correspondiente al indice libre
int sUsuario_findFreeSpace(sUsuario * list, int len)
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


/// @fn void sUsuario_printOne(sUsuario)
/// @brief Imprimir Una entidad
///
/// @pre
/// @post
/// @param usuario
void sUsuario_printOne(sUsuario usuario)
{
	//AUXILIAR PARA MOSTRAR CADENA EN TIPO DE PASAJERO
	char auxiliarTypeUsuario[TAM_TIPO_USUARIO];


	switch(usuario.tipoUsuario)
	{
	case TIPO_USUARIO_ADMIN:
		strncpy(auxiliarTypeUsuario,"Admin",sizeof(auxiliarTypeUsuario));
		break;
	case TIPO_USUARIO_COMUN:
		strncpy(auxiliarTypeUsuario,"Común",sizeof(auxiliarTypeUsuario));
		break;
	}
	//IMPRESIÓN DE 1 PASAJERO EN FORMA TABULAR
	printf("|%-30s|%-15s|%-55s|%-8d|%-8d|%-15s|\n",usuario.correo,usuario.password,usuario.domicilio,usuario.codigoPostal,usuario.idUsuario,auxiliarTypeUsuario);
}


/// @fn int sUsuario_printUsuarios(sUsuario*, int)
/// @brief Imprimir todas las entidades de un array que se hayan ingresado y que esten activas
///
/// @pre
/// @post
/// @param list Array
/// @param len Tamaño del array
/// @return -1 si array = NULL o tamaño es <= 0, 0 si salio bien
int sUsuario_printUsuarios(sUsuario* list,int len)
{

	int retorno;
	int i;

	retorno = -1;

	if(list != NULL && len>0)
	{
		for(i = 0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE && list[i].tipoUsuario != TIPO_USUARIO_ADMIN )
			{
				sUsuario_printOne(list[i]);
			}

		}
		retorno = 0;
	}

	return retorno;
}


/// @fn int sUsuario_printAllIdByInit(sUsuario*, int, int)
/// @brief Imprimir todas los id de entidades segun su estado
///
/// @pre
/// @post
/// @param list array
/// @param len tamaño del array
/// @param status estado
/// @return -1 si no encuentra entidades según estado, -2 si array es NULL o tamaño array <=0, 0 si salio bien
int sUsuario_printAllIdByInit(sUsuario* list,int len,int init)
{
	int retorno;
	int i;
	int flag;

	retorno = 0;
	flag = 0;

	if(list != NULL && len>0)
	{
		for(i = 0;i<len;i++)
		{
			if(list[i].isEmpty == init)
			{
				printf("\nID: %d\n",list[i].idUsuario);
				flag = 1;
			}
		}
		if(flag == 0)
		{
			retorno = -1;
		}
	}
	else
	{
		retorno = -2;
	}

	return retorno;
}

/// @fn void sUsuario_printOneForAdmin(sUsuario)
/// @brief Imprimir Una entidad para visualizacion del admin
///
/// @pre
/// @post
/// @param usuario
void sUsuario_printOneForAdmin(sUsuario usuario)
{
	//AUXILIAR PARA MOSTRAR CADENA EN TIPO DE PASAJERO
	char auxiliarEstado[25];


	switch(usuario.isEmpty)
	{
	case FALSE:
		strncpy(auxiliarEstado,"ACTIVO",sizeof(auxiliarEstado));
		break;
	case LOW:
		strncpy(auxiliarEstado,"DADO DE BAJA",sizeof(auxiliarEstado));
		break;
	}

	//IMPRESIÓN DE 1 PASAJERO EN FORMA TABULAR
	printf("|%-15d|%-30s|%-25s\n",usuario.idUsuario,usuario.correo,auxiliarEstado);
}

/// @fn int sUsuario_printUsuariosForAdmin(sUsuario*, int)
/// @brief Imprimir todas las entidades de un array que se hayan ingresado
///
/// @pre
/// @post
/// @param list Array
/// @param len Tamaño del array
/// @return -1 si array = NULL o tamaño es <= 0, 0 si salio bien
int sUsuario_printUsuariosForAdmin(sUsuario* list,int len)
{

	int retorno;
	int i;

	retorno = -1;

	if(list != NULL && len>0)
	{
		for(i = 0;i<len;i++)
		{

			if(list[i].isEmpty != TRUE)//IMPRIMIR TODOS LOS USUARIOS QUE SE HAYAN INGRESADO
			{
				sUsuario_printOneForAdmin(list[i]);
			}


		}
		retorno = 0;
	}

	return retorno;
}

/// @fn int sUsuario_printUsuariosForAdminActives(sUsuario*, int)
/// @brief Imprimir todas las entidades de un array (solo activas)
///
/// @pre
/// @post
/// @param list Array
/// @param len Tamaño del array
/// @return -1 si array = NULL o tamaño es <= 0, 0 si salio bien
int sUsuario_printUsuariosForAdminActives(sUsuario* list,int len)
{

	int retorno;
	int i;

	retorno = -1;

	if(list != NULL && len>0)
	{
		for(i = 0;i<len;i++)
		{

			if(list[i].isEmpty == FALSE && list[i].tipoUsuario != TIPO_USUARIO_ADMIN)//IMPRIMIR TODOS LOS USUARIOS QUE SE HAYAN INGRESADO
			{
				sUsuario_printOneForAdmin(list[i]);
			}


		}
		retorno = 0;
	}

	return retorno;
}

