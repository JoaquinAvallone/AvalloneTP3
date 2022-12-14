#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Seleccion.h"
#include "Jugador.h"

Seleccion* selec_new()
{
	Seleccion* newSeleccion = (Seleccion*) malloc(sizeof(Seleccion));

	if(newSeleccion != NULL)
	{
		newSeleccion->id=0;
		*(newSeleccion->pais)='\0';
		*(newSeleccion->confederacion)='\0';
		newSeleccion->convocados=0;
	}

	return newSeleccion;
}

Seleccion* selec_newParametros(char* idStr,char* paisStr,char* confederacionStr, char* convocadosStr)
{
	Seleccion* pNewSeleccion = selec_new();

	if(pNewSeleccion != NULL)
	{
		if(!(selec_setId(pNewSeleccion, atoi(idStr)) && selec_setPais(pNewSeleccion, paisStr) && selec_setConfederacion(pNewSeleccion, confederacionStr) &&
			 selec_setConvocados(pNewSeleccion, atoi(convocadosStr))))
		{
			free(pNewSeleccion);
			pNewSeleccion = NULL;
		}
	}

	return pNewSeleccion;
}

void selec_delete(Seleccion* this)
{
	free(this);
}


int selec_setId(Seleccion* this, int id)
{
	int retorno = 0;

	if(this!= NULL && id >=1 && id <=32)
	{
		this->id=id;
		retorno=1;
	}

	return retorno;
}

int selec_getId(Seleccion* this,int* id)
{
	int retorno = 0;

	if(this!=NULL && id!=NULL)
	{
		*id = this->id;
		retorno = 1;
	}
	return retorno;
}

int selec_setPais(Seleccion* this, char* pais)
{
	int retorno=0;
	int largoCad;
	char auxCad[200];

	largoCad = strlen(pais);

	if(this !=NULL && pais!=NULL && strlen(pais)<30)
	{
		strcpy(auxCad, pais);
		//strlwr(auxCad);
		auxCad[0]=toupper(auxCad[0]);
		for(int i=0; i<largoCad; i++)
		{
			if(pais[i] == ' ')
			{
				auxCad[i+1]=toupper(auxCad[i+1]);
			}
		}
		strcpy(this->pais, auxCad);
		retorno = 1;
	}
	else
	{
		printf("El nombre del pais ingresado es demsiado largo.\n");
	}

	return retorno;
}

int selec_getPais(Seleccion* this,char* pais)
{
	int retorno=0;

	if(this!=NULL && pais!=NULL)
	{
		strcpy(pais, this->pais);
		retorno=1;
	}

	return retorno;
}

int selec_setConfederacion(Seleccion* this, char* confederacion)
{
	int retorno=0;
	int largoCad;
	char auxCad[200];

	largoCad = strlen(confederacion);

	if(this !=NULL && confederacion!=NULL && strlen(confederacion)<30)
	{
		strcpy(auxCad, confederacion);
		//strlwr(auxCad);
		auxCad[0]=toupper(auxCad[0]);
		for(int i=0; i<largoCad; i++)
		{
			if(confederacion[i] == ' ')
			{
				auxCad[i+1]=toupper(auxCad[i+1]);
			}
		}
		strcpy(this->confederacion, auxCad);
		retorno = 1;
	}
	else
	{
		printf("El nombre del pais ingresado es demsiado largo.\n");
	}

	return retorno;
}

int selec_getConfederacion(Seleccion* this,char* confederacion)
{
	int retorno=0;

	if(this!=NULL && confederacion!=NULL)
	{
		strcpy(confederacion, this->confederacion);
		retorno=1;
	}

	return retorno;
}


int selec_setConvocados(Seleccion* this,int convocados)
{
	int retorno = 0;

	if(this != NULL && convocados<1000)
	{
		this->convocados=convocados;
		retorno=1;
	}

	return retorno;
}

int selec_getConvocados(Seleccion* this,int* convocados)
{
	int retorno = 0;

	if(this!=NULL && convocados!=NULL)
	{
		*convocados = this->convocados;
		retorno = 1;
	}
	return retorno;
}


int ordenarSeleccionesPorConfederacion(void* pSelecI, void* pSelecJ)
{
	int retorno = -1;
	char confI[30];
	char confJ[30];
	Seleccion* auxSelecI=NULL;
	Seleccion* auxSelecJ=NULL;

	if(pSelecI!=NULL && pSelecJ!=NULL)
	{
		auxSelecI=(Seleccion*)pSelecI;
		auxSelecJ=(Seleccion*)pSelecJ;

		selec_getConfederacion(auxSelecI, confI);
		selec_getConfederacion(auxSelecJ, confJ);

		if(strcmp(confI,confJ)>0)
		{
			retorno=1;
		}
		else
		{
			if(strcmp(confI,confJ)==0)
			{
				retorno=0;
			}
		}
	}

	return retorno;
}


