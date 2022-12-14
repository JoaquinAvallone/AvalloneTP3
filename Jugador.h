#include "LinkedList.h"

#ifndef jug_H_INCLUDED
#define jug_H_INCLUDED

typedef struct
{
	int id;
	char nombreCompleto[100];
	int edad;
	char posicion[30];
	char nacionalidad[30];
	int idSeleccion;
}Jugador;

Jugador* jug_new();

Jugador* jug_newParametros(int* id,char* nombreCompleto,int* edad, char* posicion, char* nacionalidad, int* idSeleccion);

Jugador* jug_newParametrosStr(char* idStr,char* nombreCompletoStr,char* edadStr, char* posicionStr, char* nacionalidadStr, char* idSeleccionStr);

void jug_delete(Jugador* this);

int jug_setId(Jugador* this,int id);
int jug_getId(Jugador* this,int* id);

int jug_setNombreCompleto(Jugador* this,char* nombreCompleto);
int jug_getNombreCompleto(Jugador* this,char* nombreCompleto);

int jug_setPosicion(Jugador* this,char* posicion);
int jug_getPosicion(Jugador* this,char* posicion);

int jug_setNacionalidad(Jugador* this,char* nacionalidad);
int jug_getNacionalidad(Jugador* this,char* nacionalidad);

int jug_setEdad(Jugador* this,int edad);
int jug_getEdad(Jugador* this,int* edad);

int jug_setIdSeleccion(Jugador* this,int idSeleccion);
int jug_getSIdSeleccion(Jugador* this,int* idSeleccion);



int ordenarJugadoresPorNacionalidad(void* pJugaI, void* pJugaJ);
int ordenarJugadoresPorNombre(void* pJugaI, void* pJugaJ);
int ordenarJugadoresPorEdad(void* pJugaI, void* pJugaJ);

//int jug_setIsEmpty(Jugador* this,int isEmpty);
//int jug_getIsEmpty(Jugador* this,int* isEmpty);


#endif // jug_H_INCLUDED
