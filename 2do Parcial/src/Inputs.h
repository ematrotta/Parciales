/*
 * Inputs.h
 *
 *  Created on: 23 abr. 2022
 *      Author: Emanuel
 */

#ifndef INPUTS_H_
#define INPUTS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_NAME 50
#define TAM_EMAIL 25

//OPERAIONES MATEMATICAS

//OPERACIONES CON ENTEROS

int DividirInt(int dividendo,int divisor,char mensajeError[],float *resultado);
int RestarInt(int numero1,int numero2,int*resultado);
int SumarInt(int numero1,int numero2,int*resultado);
int MultiplicarInt(int numero1,int numero2,int*resultado);
int PorcentajeInt(int numero,int porcentajeAplicado,char operacion,float*resultado);
float Promedio2NumerosInt(int num1,int num2);


//OPERACIONES CON FLOTANTES
int PorcentajeFloat(float numero,float porcentajeAplicado,char operacion,float*resultado);
int DividirFloat(float dividendo,float divisor,char mensajeError[],float *resultado);
int RestarFloat(float numero1,float numero2,float*resultado);
int SumarFloat(float numero1,float numero2,float*resultado);
int MultiplicarFloat(float numero1,float numero2,float*resultado);

//FUNCIONES DE EVALUACION
int EsNumerica(char arrayEvaluado[]);
int EsNombre(char arrayEvaluado[]);
int EsMail(char arrayEvaluado[]);
int EsCuit(char arrayEvaluado[]);
int EsAlphaNumericaPlus(char arrayEvaluado[]);


//FUNCIONES PARA INGRESO DE DATOS
int MyGets(char arrayIngresado[],int tam);
int GetIntegrer(int * pNumero);
int GetFloat(float * pNumero);
int GetCuit(int * pNumero);
int GetPassword(char passwordInput[],int minChar,int maxChar,char mensajeError[]);
int GetCharacter2Options(char * pChar,char mensaje[],char mensajeError[],char op1,char op2, int reintentos);
int Utn_GetName(char name[],int tam, char mensaje[],char mensajeError[],int reintentos);
int Utn_GetMail(char mail[],int tam, char mensaje[],char mensajeError[],int reintentos);
int Utn_GetNumeroInt(int * pNumero,char mensaje[],char mensajeError[], int max, int min, int reintentos);
int Utn_GetNumeroShortInt(short * pNumero,char mensaje[],char mensajeError[], int max, int min, int reintentos);
int Utn_GetNumeroFloat(float * pNumero,char mensaje[],char mensajeError[], float max, float min, int reintentos);
int Utn_GetChar(char * pchar,char mensaje[],char mensajeError[], char max, char min, int reintentos);
int Utn_GetString(char cadenaAIngresar[],char mensaje[],char mensajeError[], int tam, int reintentos);
int Utn_GetStringAlfaNumericaPlus(char cadenaAIngresar[],char mensaje[],char mensajeError[], int tam, int reintentos);


//FUNCIONES PARA ARRAYS

int CopiarArrayInt(int arrayOriginal[],int arrayCopiado[],int tam);
int CopiarArrayFloat(float arrayOriginal[],float arrayCopiado[],int tam);
int IngresarValoresIntArray(int array[],int tam,char mensajeError[]);
int OrdenarArrayIntIneficiente(int arrayDesordeando[],int tam);
int OrdenarArrayIntEficiente(int arrayDesordeando[],int tam);
int OrdenamientoPorInsercion(int arrayDesordeando[],int tam);


#endif /* INPUTS_H_ */
