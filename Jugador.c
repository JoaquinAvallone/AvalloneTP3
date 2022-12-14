#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Jugador.h"
#include "Seleccion.h"

Jugador* jug_new()
{
	Jugador* newJugador = (Jugador*) malloc(sizeof(Jugador));

	if(newJugador != NULL)
	{
		newJugador->id=0;
		*(newJugador->nombreCompleto)='\0';
		newJugador->edad=0;
		*(newJugador->posicion)='\0';
		*(newJugador->nacionalidad)='\0';
		newJugador->idSeleccion=0;
	}

	return newJugador;
}

Jugador* jug_newParametros(int* id,char* nombreCompleto,int* edad, char* posicion, char* nacionalidad, int* idSeleccion)
{
	Jugador* pNewJugador = jug_new();

	if(!(jug_setId(pNewJugador, *id) && jug_setNombreCompleto(pNewJugador, nombreCompleto)
	  && jug_setEdad(pNewJugador, *edad) && jug_setPosicion(pNewJugador, posicion) && jug_setNacionalidad(pNewJugador, nacionalidad)
	  && jug_setIdSeleccion(pNewJugador, *idSeleccion)))
	{
		free(pNewJugador);
		pNewJugador = NULL;
	}

	return pNewJugador;
}

Jugador* jug_newParametrosStr(char* idStr,char* nombreCompletoStr,char* edadStr, char* posicionStr, char* nacionalidadStr, char* idSeleccionStr)
{
	Jugador* pNewJugador = jug_new();

	if(!(jug_setId(pNewJugador, atoi(idStr)) && jug_setNombreCompleto(pNewJugador, nombreCompletoStr)
	  && jug_setEdad(pNewJugador, atoi(edadStr)) && jug_setPosicion(pNewJugador, posicionStr) && jug_setNacionalidad(pNewJugador, nacionalidadStr)
	  && jug_setIdSeleccion(pNewJugador, atoi(idSeleccionStr))))
	{
		free(pNewJugador);
		pNewJugador = NULL;
	}

	return pNewJugador;
}

void jug_delete(Jugador* this)
{
	if(this!=NULL)
	{
		free(this);
	}
}

int jug_setId(Jugador* this,int id)
{
	int retorno = 0;

	if(this!=NULL)
	{
		this->id = id;
		retorno = 1;
	}
	else
	{
		printf("El id ingresado es invalido.\n");
	}

	return retorno;
}

int jug_getId(Jugador* this,int* id)
{
	int retorno = 0;

	if(this!=NULL && id!=NULL)
	{
		*id = this->id;
		retorno = 1;
	}
	return retorno;
}

int jug_setNombreCompleto(Jugador* this,char* nombreCompleto)
{
	int retorno=0;
	int largoCad;
	char auxCad[200];

	largoCad = strlen(nombreCompleto);

	if(this !=NULL && nombreCompleto!=NULL && strlen(nombreCompleto)<100)
	{
		strcpy(auxCad, nombreCompleto);
		//strlwr(auxCad);
		auxCad[0]=toupper(auxCad[0]);
		for(int i=0; i<largoCad; i++)
		{
			if(nombreCompleto[i] == ' ')
			{
				auxCad[i+1]=toupper(auxCad[i+1]);
			}
		}
		strcpy(this->nombreCompleto, auxCad);
		retorno = 1;
	}
	else
	{
		printf("El nombre ingresado es demsiado largo.\n");
	}

	return retorno;
}

int jug_getNombreCompleto(Jugador* this,char* nombreCompleto)
{
	int retorno=0;

	if(this!=NULL && nombreCompleto!=NULL)
	{
		strcpy(nombreCompleto, this->nombreCompleto);
		retorno=1;
	}

	return retorno;
}

int jug_setPosicion(Jugador* this,char* posicion)
{
	int retorno = 0;
	char auxCad[50];

	if(this!=NULL && posicion!=NULL && strlen(posicion)<30)
	{
		strcpy(auxCad, posicion);
		//strcpy(this->posicion, posicion);
		//this->posicion[0]=toupper(this->posicion[0]);
		auxCad[0]= toupper(auxCad[0]);
		strcpy(this->posicion, auxCad);
		retorno = 1;
	}
	else
	{
		printf("La posicion ingresada no es valida.\n");
	}

	return retorno;
}

int jug_getPosicion(Jugador* this,char* posicion)
{
	int retorno=0;

	if(this!=NULL && posicion!=NULL)
	{
		strcpy(posicion, this->posicion);
		retorno=1;
	}

	return retorno;
}

int jug_setNacionalidad(Jugador* this,char* nacionalidad)
{
	int retorno = 0;
	char auxCad[50];

	if(this!=NULL && nacionalidad!=NULL && strlen(nacionalidad)<30)
	{
		strcpy(auxCad, nacionalidad);
		auxCad[0]=toupper(auxCad[0]);
		strcpy(this->nacionalidad, auxCad);
		retorno = 1;
	}

	return retorno;
}

int jug_getNacionalidad(Jugador* this,char* nacionalidad)
{
	int retorno=0;

	if(this!=NULL && nacionalidad!=NULL)
	{
		strcpy(nacionalidad, this->nacionalidad);
		retorno=1;
	}

	return retorno;
}

int jug_setEdad(Jugador* this,int edad)
{
	int retorno = 0;

	if(this!=NULL)
	{
		this->edad = edad;
		retorno = 1;
	}
	else
	{
		printf("La edad ingresada es invalida.\n");
	}

	return retorno;
}

int jug_getEdad(Jugador* this,int* edad)
{
	int retorno = 0;

	if(this!=NULL && edad!=NULL)
	{
		*edad = this->edad;
		retorno = 1;
	}
	return retorno;
}

int jug_setIdSeleccion(Jugador* this,int idSeleccion)
{
	int retorno = 0;

	if(this!=NULL && idSeleccion>=0 && idSeleccion<= 32)
	{
		this->idSeleccion = idSeleccion;
		retorno = 1;
	}
	else
	{
		printf("El id de seleccion ingresado es invalido.\n");
	}

	return retorno;
}

int jug_getSIdSeleccion(Jugador* this,int* idSeleccion)
{
	int retorno = 0;

	if(this!=NULL && idSeleccion!=NULL)
	{
		*idSeleccion = this->idSeleccion;
		retorno = 1;
	}
	return retorno;
}



int ordenarJugadoresPorNacionalidad(void* pJugaI, void* pJugaJ)
{
	int retorno = -1;
	char nacionalidadJugaI[50];
	char nacionalidadJugaJ[50];
	Jugador* auxJugaI = NULL;
	Jugador* auxJugaJ = NULL;

	if(pJugaI!=NULL && pJugaJ!=NULL)
	{
		auxJugaI=(Jugador*) pJugaI;
		auxJugaJ=(Jugador*) pJugaJ;

		jug_getNacionalidad(auxJugaI, nacionalidadJugaI);
		jug_getNacionalidad(auxJugaJ, nacionalidadJugaJ);

		if(strcmp(nacionalidadJugaI, nacionalidadJugaJ) > 0)
		{
			retorno = 1;
		}
		else
		{
			if(strcmp(nacionalidadJugaI, nacionalidadJugaJ) == 0)
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}

int ordenarJugadoresPorNombre(void* pJugaI, void* pJugaJ)
{
	int retorno = -1;
	char nombreJugaI[50];
	char nombreJugaJ[50];
	Jugador* auxJugaI = NULL;;
	Jugador* auxJugaJ = NULL;;

	if(pJugaI!=NULL && pJugaJ!=NULL)
	{
		auxJugaI=(Jugador*) pJugaI;
		auxJugaJ=(Jugador*) pJugaJ;

		jug_getNombreCompleto(auxJugaI, nombreJugaI);
		jug_getNombreCompleto(auxJugaJ, nombreJugaJ);
		if(strcmp(nombreJugaI,nombreJugaJ) > 0)
		{
			retorno=1;
		}
		else
		{
			if(strcmp(nombreJugaI,nombreJugaJ) == 0)
			{
				retorno=0;
			}
		}
	}


	return retorno;
}


int ordenarJugadoresPorEdad(void* pJugaI, void* pJugaJ)
{
	int retorno = 0;
	int edadJugaI;
	int edadJugaJ;
	Jugador* auxJugaI = NULL;;
	Jugador* auxJugaJ = NULL;;

	if(pJugaI!=NULL && pJugaJ!=NULL)
	{
		auxJugaI=(Jugador*) pJugaI;
		auxJugaJ=(Jugador*) pJugaJ;

		jug_getEdad(auxJugaI, &edadJugaI);
		jug_getEdad(auxJugaJ, &edadJugaJ);
		if(edadJugaI>edadJugaJ)
		{
			retorno=1;
		}
		else
		{
			if(edadJugaI<edadJugaJ)
			{
				retorno=-1;
			}
		}
	}
	return retorno;
}
