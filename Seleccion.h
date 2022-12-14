#include "LinkedList.h"

#ifndef selec_H_INCLUDED
#define selec_H_INCLUDED

typedef struct
{
	int id;
	char pais[30];
	char confederacion[30];
	int convocados;
}Seleccion;

Seleccion* selec_new();
Seleccion* selec_newParametros(char* idStr,char* paisStr,char* confederacionStr, char* convocadosStr);
void selec_delete();

int selec_setId(Seleccion* this, int id);
int selec_getId(Seleccion* this,int* id);

int selec_setPais(Seleccion* this, char* pais);
int selec_getPais(Seleccion* this,char* pais);

int selec_setConfederacion(Seleccion* this, char* confederacion);
int selec_getConfederacion(Seleccion* this,char* confederacion);
//int selec_getIsEmpty(Seleccion* this,int* isEmpty);

int selec_setConvocados(Seleccion* this,int convocados);
int selec_getConvocados(Seleccion* this,int* convocados);

int ordenarSeleccionesPorConfederacion(void* pSelecI, void* pSelecJ);


#endif // selec_H_INCLUDED
