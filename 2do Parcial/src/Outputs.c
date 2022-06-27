/*
 * Outputs.c
 *
 *  Created on: 23 abr. 2022
 *      Author: Emanuel
 */
#include "Outputs.h"
// FUNCIONES CON ARRAY

/// @fn int ImprimirArrayInt(int[], int)
/// @brief Imprimir un array de enteros
///
/// @pre
/// @post
/// @param array Array a imprimir
/// @param tam Tamaño del array
/// @return -1 si salio todo mal, 0 si salio todo bien
int ImprimirArrayInt(int array[],int tam)
{
    int retorno;
    int i;

    retorno = -1;

    if(array != NULL && tam >0)
    {
        for(i=0;i<tam;i++)
        {
            printf("%d\n",array[i]);
        }
        retorno = 0;
    }
    return retorno;
}

/// @fn int ImprimirArrayFloat(float[], int)
/// @brief Imprimir un array de flotantes
///
/// @pre
/// @post
/// @param array Array a imprimir
/// @param tam Tamaño del array
/// @return -1 si salio mal, 0 si salio bien
int ImprimirArrayFloat(float array[],int tam)
{
    int retorno;
    int i;

    retorno = -1;

    if(array != NULL && tam >0)
    {
        for(i=0;i<tam;i++)
        {
            printf("%f\n",array[i]);
        }
        retorno = 0;
    }
    return retorno;
}
