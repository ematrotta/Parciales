#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
	LinkedList* this;
    this = (LinkedList*)malloc(sizeof(LinkedList));
    if(this != NULL)
    {
    	this->pFirstNode = NULL;
    	this->size = 0;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pAux;
	pAux = NULL;
	int i;
	if(this != NULL && nodeIndex>=0 && ll_len(this)>nodeIndex)
	{
		pAux = this->pFirstNode;
		for(i = 0;i<nodeIndex;i++)
		{
			pAux = pAux->pNextNode;
		}
	}

	return pAux;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
	int retorno;
	int cantidadNodos;
	Node* pAux;
	Node* pNodoAnterior;
	pAux = NULL;
	pNodoAnterior = NULL;
	cantidadNodos = ll_len(this);
	retorno = -1;
	if(this != NULL && nodeIndex>=0 && cantidadNodos>=nodeIndex)
	{
		pAux = (Node*)malloc(sizeof(Node));
		if(pAux != NULL)
		{
			if(nodeIndex == 0)
			{
				pAux->pNextNode = this->pFirstNode;
				this->pFirstNode = pAux;
			}
			else
			{
				pNodoAnterior = getNode(this,nodeIndex-1);
				pAux->pNextNode = pNodoAnterior->pNextNode;
				pNodoAnterior->pNextNode = pAux;
			}
			pAux->pElement = pElement;
			this->size++;
			retorno = 0;
		}

	}

    return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int retorno = -1;
    int cantidadNodos;
    cantidadNodos = ll_len(this);
    if(this != NULL)
    {
    	addNode(this, cantidadNodos, pElement);
    	retorno = 0;
    }

    return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    int cantidadNodos;
    Node* pAux;
    cantidadNodos = ll_len(this);
    if(this != NULL && index>=0 && index<cantidadNodos)
    {
		pAux = getNode(this, index);
		returnAux = pAux->pElement;
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    int cantidadNodos;
    Node* pAux;
    cantidadNodos = ll_len(this);

    if(this != NULL && index>= 0 && index<cantidadNodos)
    {
		pAux = getNode(this, index);
		pAux->pElement =  pElement;
		returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    int cantidadNodos;
    Node* pAux;
    Node* pAnterior;
    pAnterior = NULL;
    pAux = NULL;
    cantidadNodos = ll_len(this);
    if(this != NULL && index>=0 && index<cantidadNodos)
    {
    	pAux = getNode(this, index);
    	if(index == 0)
    	{
    		this->pFirstNode = pAux->pNextNode;
    	}
    	else
    	{
    		pAnterior = getNode(this, index-1);
    		pAnterior->pNextNode = pAux->pNextNode;
    	}
    	free(pAux);
    	this->size--;


    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int cantidadNodos;
    int i;
    cantidadNodos = ll_len(this);
    if(this != NULL)
    {
    	for(i = 0;i<cantidadNodos;i++)
    	{
    		ll_remove(this, 0);
    	}
    	returnAux = 0;

    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(!ll_clear(this))
    	{
    		free(this);
    		returnAux = 0;
    	}

    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int cantidadNodos;
    int i;
    void* pAux;
    pAux = NULL;
    cantidadNodos = ll_len(this);
    if(this != NULL)
    {
        for(i = 0;i<cantidadNodos;i++)
        {
        	pAux = ll_get(this, i);
        	if(pAux == pElement)
        	{
        		returnAux = i;
        		break;
        	}

        }
    }


    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    int cantidadNodos;
    cantidadNodos = ll_len(this);
    if(this != NULL)
    {
    	returnAux = 0;
    	if(cantidadNodos == 0)
    	{
    		returnAux = 1;
    	}
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int retorno = -1;
    int cantidadNodos;
    cantidadNodos = ll_len(this);
    if(this != NULL && index>= 0 && index<=cantidadNodos)
    {
    	if(addNode(this, index, pElement)==0)
    	{
    		retorno = 0;
    	}

    }

    return retorno;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    int cantidadNodos;
    cantidadNodos = ll_len(this);
    if(this != NULL && index>= 0 && index<cantidadNodos)
    {
    	returnAux = ll_get(this, index);
    	ll_remove(this, index);
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	returnAux = 0;
    	if(ll_indexOf(this, pElement)>=0)
    	{
    		returnAux = 1;
    	}

    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int cantidadNodosThis2;
    int i;
    void* pElement;
    cantidadNodosThis2 = ll_len(this2);
    if(this != NULL && this2 != NULL)
    {
    	returnAux = 1;
    	for(i = 0;i<cantidadNodosThis2;i++)
    	{
    		pElement = ll_get(this2, i);
    		if(ll_contains(this, pElement) != 1)
    		{
    			returnAux = 0;
    			break;
    		}
    	}

    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int cantidadNodos;
    void* pElement;
    int i;
    cantidadNodos = ll_len(this);
    pElement = NULL;
    if(this != NULL && from>=0 && from<to && to<=cantidadNodos)
    {
    	cloneArray = ll_newLinkedList();
    	if(cloneArray != NULL)
    	{
        	for(i = from;i<to;i++)
        	{
        		pElement = ll_get(this, i);
        		//NO VERIFICO QUE PELEMENT SEA != NULL PORQUE TIENE QUE SER UNA COPIA EXACTA
        		ll_add(cloneArray, pElement);

        	}
    	}


    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int cantidadNodos;
    cantidadNodos = ll_len(this);
    cloneArray = ll_subList(this, 0, cantidadNodos);

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int i;
    int j;
    int cantidadNodos;
    int retornoFuncion;
    void* pElementUno;
    void* pElementDos;
    cantidadNodos = ll_len(this);

    if(this != NULL && pFunc != NULL && (order == 1 || order == 0))
    {
    	for(i=0;i<cantidadNodos-1;i++)
    	{
    		for(j = i+1;j<cantidadNodos;j++)
    		{
    			pElementUno = ll_get(this, i);
    			pElementDos = ll_get(this, j);
    			retornoFuncion = pFunc(pElementUno,pElementDos);
    			if((order == 1 && retornoFuncion>0)||(order == 0 && retornoFuncion<0))
    			{
    				ll_set(this, j, pElementUno);
    				ll_set(this, i, pElementDos);
    			}
    		}
    	}
    	returnAux = 0;


    }

    return returnAux;

}


