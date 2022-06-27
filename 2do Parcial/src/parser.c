#include "parser.h"

/** \brief Parsea los datos los datos de una entidad desde el archivo binario.
 *
 * \param pfile Puntero al archivo
 * \param this LinkedList*
 * \return int 0 si alguno de los parámetros es NULL O no pudo realizar ninguna lectura, <1 si pudo realizar lecturas
 *
 */

int parser_SalonFromBinary(FILE* pFile , LinkedList* this)
{
	int cantidadLecturas;
	int retornoRead;
	cantidadLecturas = 0;
	Salon* auxSalon;

	if(pFile != NULL && this)
	{
		do
		{
			//PRIMERO LE ASIGNO MEMORIA DINAMICA
			auxSalon = Salon_new();
			retornoRead = fread(auxSalon,sizeof(Salon),1,pFile);
			if(retornoRead == 1 && auxSalon != NULL)
			{
				ll_add(this, auxSalon);
				cantidadLecturas++;
			}

		}while(!feof(pFile));
	}

    return cantidadLecturas;
}

/** \brief Parsea los datos los datos de una entidad desde el archivo binario.
 *
 * \param pfile Puntero al archivo
 * \param this LinkedList*
 * \return int 0 si alguno de los parámetros es NULL O no pudo realizar ninguna lectura, <1 si pudo realizar lecturas
 *
 */

int parser_JuegoFromBinary(FILE* pFile , LinkedList* this)
{
	int cantidadLecturas;
	int retornoRead;
	cantidadLecturas = 0;
	Juego* auxJuego;

	if(pFile != NULL && this)
	{
		do
		{
			//PRIMERO LE ASIGNO MEMORIA DINAMICA
			auxJuego = Juego_new();
			retornoRead = fread(auxJuego,sizeof(Salon),1,pFile);
			if(retornoRead == 1 && auxJuego != NULL)
			{
				ll_add(this, auxJuego);
				cantidadLecturas++;
			}

		}while(!feof(pFile));
	}

    return cantidadLecturas;
}

/** \brief Parsea los datos los datos de una entidad desde el archivo binario.
 *
 * \param pfile Puntero al archivo
 * \param this LinkedList*
 * \return int 0 si alguno de los parámetros es NULL O no pudo realizar ninguna lectura, <1 si pudo realizar lecturas
 *
 */

int parser_ArcadeFromBinary(FILE* pFile , LinkedList* this)
{
	int cantidadLecturas;
	int retornoRead;
	cantidadLecturas = 0;
	Arcade* auxArcade;

	if(pFile != NULL && this)
	{
		do
		{
			//PRIMERO LE ASIGNO MEMORIA DINAMICA
			auxArcade = Arcade_new();
			retornoRead = fread(auxArcade,sizeof(Salon),1,pFile);
			if(retornoRead == 1 && auxArcade != NULL)
			{
				ll_add(this, auxArcade);
				cantidadLecturas++;
			}

		}while(!feof(pFile));
	}

    return cantidadLecturas;
}


