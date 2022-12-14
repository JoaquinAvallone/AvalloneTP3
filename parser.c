#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Jugador.h"
#include "Seleccion.h"

/** \brief Parsea los datos de los jugadores desde el archivo jugadores.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 */
int parser_JugadorFromText(FILE* pFile , LinkedList* pArrayListJugador)
{
	int retorno=0;
	Jugador* auxJuga;
	char buffer[6][100];

	if(pFile!=NULL && pArrayListJugador!=NULL)
	{
		fscanf(pFile, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);

		while(!feof(pFile))
		{
			fscanf(pFile, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);
			auxJuga=jug_newParametrosStr( buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);

			if(auxJuga != NULL)
			{
				ll_add(pArrayListJugador, auxJuga);
				retorno = 1;
			}
		}
		fclose(pFile);
	}
    return retorno;;
}

/** \brief Parsea los datos de los jugadores desde el archivo binario.
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int parser_JugadorFromBinary(FILE* pFile , LinkedList* pArrayListJugador)
{
	int retorno=0;
	Jugador* auxJuga;

	if(pFile!=NULL && pArrayListJugador)
	{
		while(!feof(pFile))
		{
			auxJuga=jug_new();
			fread(auxJuga, sizeof(Jugador), 1, pFile);
			ll_add(pArrayListJugador, auxJuga);
			retorno=1;
		}
	}

    return retorno;
}


/** \brief Parsea los datos de los selecciones desde el archivo selecciones.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int parser_SeleccionFromText(FILE* pFile , LinkedList* pArrayListSeleccion)
{
	int retorno=0;
	Seleccion* auxSelec;
	char buffer[4][30];

	if(pFile!=NULL && pArrayListSeleccion)
	{
		fscanf(pFile, "%[^,], %[^,], %[^,], %[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);
		while(!feof(pFile))
		{
			fscanf(pFile, "%[^,], %[^,], %[^,], %[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);
			auxSelec=selec_newParametros(buffer[0], buffer[1], buffer[2], buffer[3]);
			if(auxSelec!=NULL)
			{
				ll_add(pArrayListSeleccion, auxSelec);
				retorno=1;
			}
		}
	}
    return retorno;
}

