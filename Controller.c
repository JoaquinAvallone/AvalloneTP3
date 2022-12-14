#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Jugador.h"
#include "validaciones.h"
#include "menus.h"
#include "parser.h"
#include "Seleccion.h"


char *itoa(int value, char *result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) {
        *result = '\0';
        return result;
    }

    char *ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 +
                                                                                           (tmp_value - value * base)];
    } while (value);

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}


/** \brief Carga los datos de los jugadores desde el archivo jugadores.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_cargarJugadoresDesdeTexto(char* path , LinkedList* pArrayListJugador)
{
	int retorno=0;
	FILE* file = NULL;
	if(pArrayListJugador!=NULL)
	{
		file=fopen(path,"r");
		if(file!=NULL)
		{
			parser_JugadorFromText(file, pArrayListJugador);
			retorno=1;
		}
	}
	fclose(file);
    return retorno;
}

/** \brief Carga los datos de los jugadores desde el archivo generado en modo binario.
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_cargarJugadoresDesdeBinario(char* path , LinkedList* pArrayListJugador)
{
	int retorno=0;
	FILE* file = NULL;

	if(pArrayListJugador!=NULL)
	{
		file=fopen(path, "rb");
		if(file!=NULL)
		{
			parser_JugadorFromBinary(file, pArrayListJugador);
			retorno=1;
		}
	}
	fclose(file);

    return retorno;
}

int controller_nextId(char* id)
{
	int retorno=0;
	char auxCadId[50];
	int auxId = 0;
	FILE* fileId = fopen("nextId.txt", "w");

	if(fileId!=NULL)
	{
		fprintf(fileId, "371");
	}
	fclose(fileId);

	fileId=fopen("nextId.txt", "r");
	if(fileId!=NULL)
	{
		fscanf(fileId, "%[^\n]", auxCadId);
		strcpy(id, auxCadId);
		itoa(auxId, auxCadId, 10);
		auxId++;
	}
	fclose(fileId);

	fileId=fopen("nextId.txt", "w");
	if(fileId!=NULL)
	{
		fprintf(fileId, "%d", auxId);
		retorno=1;
	}
	fclose(fileId);

	return retorno;
}


/** \brief Alta de jugadores
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_agregarJugador(LinkedList* pArrayListJugador)
{
	int retorno = 0;
	Jugador* auxJugador;
	char id[30];
	char nombreCompleto[100];
	int edad;
	char auxEdad[30];
	char posicion[30];
	char nacionalidad[30];
	int idNacionalidad;
	int opcionPosicion;

	if(pArrayListJugador!=NULL)
	{
		limpiarConsola();
		printf("              ***ALTA JUGADOR***\n\n");
		controller_nextId(id);

		utn_getString( nombreCompleto, "Ingrese nombre completo del jugador: ", "ERROR. Vuelva a intentarlo.\n", 50);

		utn_getNumeroInt( &edad, "Ingrese edad :", "ERROR.", 17, 50, 50);
		itoa(edad, auxEdad, 10);

		menuPosiciones();
		utn_getNumeroInt(&opcionPosicion, "ingrese opcion", "La opcion elegida no existe, vuelva a intentarlo: ", 1, 11, 50);
		cargarPosicion(opcionPosicion, posicion);

		menuNacionalidades();
		utn_getNumeroInt(&idNacionalidad, "ingrese id nacionalidad: ", "ERRO. Vuelva a intentarlo", 1, 32, 50);
		cargarNacionalidades(idNacionalidad, nacionalidad);

		auxJugador=jug_newParametrosStr(id, nombreCompleto, auxEdad, posicion, nacionalidad, "0");
		if(auxJugador!=NULL)
		{
			ll_add(pArrayListJugador, auxJugador);
			retorno = 1;
		}
	}

    return retorno;
}

int controller_buscarIdJugador(LinkedList* pArrayListJugador, int id, int* pIndice)
{
	int retorno=0;
	int indice= -1;
	int tam;
	Jugador* auxJugador;

	if(pArrayListJugador != NULL)
	{
		tam = ll_len(pArrayListJugador);

		for(int i=0; i < tam; i++)
		{
			auxJugador = (Jugador*) ll_get(pArrayListJugador,i);
			if(auxJugador->id == id)
			{
				indice = ll_indexOf(pArrayListJugador, auxJugador);
				break;
			}
		}
		*pIndice=indice;
		retorno = 1;
	}
	return retorno;
}

/** \brief Modificar datos del jugador
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_editarJugador(LinkedList* pArrayListJugador, LinkedList* listaSeleccion)
{
	int retorno = 0;
	Jugador* auxJugador;
	char respuesta;
	int auxId;
	int indice;
	char auxNombreJugador[100];
	int auxEdad;
	int opcionPosicion;
	int opcionModificacion;
	char auxPosicion[30];
	char auxNacionalidad[30];
	int idNacionalidad;

	if(pArrayListJugador != NULL)
	{
		limpiarConsola();
		printf("                     ***MODIFICAR JUGADOR***");
		controller_listarJugadores(pArrayListJugador, listaSeleccion);
		printf("Ingrese id del jugador a editar: ");
		scanf("%d", &auxId);
		controller_buscarIdJugador(pArrayListJugador, auxId, &indice);

		if(indice==-1)
		{
			printf("No existe ningun jugador con el id: %d.\n", auxId);
		}
		else
		{

			auxJugador = (Jugador*)ll_get(pArrayListJugador, indice);
			printf(" \n\n                     EL JUGADOR QUE DESEA MODIFICAR ES EL SIGUIENTE:\n\n");
			printf( "========================================================================================================\n"
					"|                                        ***LISTA JUGADORES***                                         |\n"
					"========================================================================================================\n"
					"|  ID  |          NOMBRE           | EDAD |       POSICION       |   NACIONALIDAD    |    SELECCION    |\n"
					"--------------------------------------------------------------------------------------------------------\n");
			controller_listarJugador(auxJugador, listaSeleccion);
			printf( "========================================================================================================\n");
			fpurge(stdin);
			utn_getCharSeguir(&respuesta, "\n\nConfirma modificacion?: s(si)o n(no)", "ERROR. Vuelve a intentarlo.\n", 50);
			if(respuesta=='s')
			{
				printf("\n\n");
				switch(menuModificacion(&opcionModificacion))
				{
				case 1:
					fpurge(stdin);
					utn_getString(auxNombreJugador, "Ingrese nuevo nombre: ", "Error. Vuelva a intentarlo.\n", 50);
					jug_setNombreCompleto(auxJugador, auxNombreJugador);
					break;
				case 2:
					fpurge(stdin);
					utn_getNumeroInt(&auxEdad, "Ingrese nueva edad del jugador: ", "Error. Vuelva a intentarlo.\n", 17, 50, 50);
					jug_setEdad(auxJugador, auxEdad);
					break;
				case 3:
					menuPosiciones();
					fpurge(stdin);
					utn_getNumeroInt(&opcionPosicion, "ingrese opcion", "La opcion elegida no existe, vuelva a intentarlo: ", 1, 11, 50);
					cargarPosicion(opcionPosicion, auxPosicion);
					jug_setPosicion(auxJugador, auxPosicion);
					break;
				case 4:
					menuNacionalidades();
					fpurge(stdin);
					utn_getNumeroInt(&idNacionalidad, "ingrese id nacionalidad: ", "ERRO. Vuelva a intentarlo", 1, 32, 50);
					cargarNacionalidades(idNacionalidad, auxNacionalidad);
					jug_setNacionalidad(auxJugador, auxNacionalidad);
					break;
				default:
					printf("La opcion ingresada es incorrecta.\n");
				}
				retorno=1;
			}
			else
			{
				printf("Modificacion cancelada.\n");
			}
		}
	}
    return retorno;
}



/** \brief Baja del jugador
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_removerJugador(LinkedList* pArrayListJugador, LinkedList* listaSeleccion)
{
	int retorno = 0;
	Jugador* auxJugador;
	int auxId;
	int indice;
	char respuesta;

	if(pArrayListJugador != NULL)
	{
		limpiarConsola();
		printf("                     ***BAJA DE JUGADOR***");
		controller_listarJugadores(pArrayListJugador, listaSeleccion);
		utn_getNumeroInt(&auxId,"Ingrese id del jugador a remover: " , "ERROR.\n", 1, 700, 50);
		controller_buscarIdJugador(pArrayListJugador, auxId, &indice);

		if(indice==-1)
		{
			printf("No existe ningun jugador con el id: %d.\n", auxId);
		}
		else
		{
			auxJugador = (Jugador*)ll_get(pArrayListJugador, indice);
			printf("                      EL JUGADOR QUE DESEA REMOVER ES EL SIGUIENTE:\n\n");
			printf( "========================================================================================================\n"
					"|                                        ***LISTA JUGADORES***                                         |\n"
					"========================================================================================================\n"
					"|  ID  |          NOMBRE           | EDAD |       POSICION       |   NACIONALIDAD    |    SELECCION    |\n"
					"--------------------------------------------------------------------------------------------------------\n");
			controller_listarJugador(auxJugador, listaSeleccion);
			printf( "========================================================================================================\n");
			utn_getCharSeguir(&respuesta, "\n\nConfirma baja?: s(si)o n(no)", "ERROR. Vuelve a intentarlo.\n", 50);
			if(respuesta=='s')
			{
				auxJugador=(Jugador*)ll_get(pArrayListJugador, indice);
				ll_remove(pArrayListJugador, indice);
				jug_delete(auxJugador);
				retorno=1;
			}
		}
	}
    return retorno;
}


int controller_listarJugador(Jugador* unJugador, LinkedList* listaSeleccion)
{
    int todoOk = 0;
    int id;
    int idSelec;
    char nombreCompleto[100];
    int edad;
    char posicion[30];
    char nacionalidad[30];
    char seleccion[30];


    if(unJugador!=NULL)
    {
    	jug_getSIdSeleccion(unJugador, &idSelec);
        if(jug_getId(unJugador, &id)
           && jug_getNombreCompleto(unJugador, nombreCompleto)
           && jug_getEdad(unJugador, &edad)
           && jug_getPosicion(unJugador, posicion)
		   && jug_getNacionalidad(unJugador, nacionalidad)
		   && cargarNombreSeleccion(listaSeleccion, idSelec, seleccion))
           {
                printf("| %-4d |  %-24s |  %-2d  | %-20s | %-16s  | %-16s|\n", id, nombreCompleto, edad, posicion, nacionalidad, seleccion);
                todoOk = 1;
           }
    }

    return todoOk;
}

/** \brief Listar jugadores
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_listarJugadores(LinkedList* pArrayListJugador, LinkedList* listaSeleccion)
{
	int retorno = 0;
	int tam = ll_len(pArrayListJugador);
	Jugador* auxJugador = NULL;

	if(pArrayListJugador != NULL && tam > 0 && listaSeleccion != NULL)
	{
		limpiarConsola();
		printf( "========================================================================================================\n"
				"|                                        ***LISTA JUGADORES***                                         |\n"
				"========================================================================================================\n"
				"|  ID  |          NOMBRE           | EDAD |       POSICION       |   NACIONALIDAD    |    SELECCION    |\n"
				"--------------------------------------------------------------------------------------------------------\n");

		for(int i=0; i < tam; i++)
		{
			auxJugador = (Jugador*)ll_get(pArrayListJugador, i);
			controller_listarJugador(auxJugador, listaSeleccion);
		}
		printf("========================================================================================================\n");
		retorno=1;
	}
    return retorno;
}


int cargarNombreSeleccion(LinkedList* pArrayListSeleccion, int idSeleccion, char* pNacionalidad)
{
	int retorno=0;
	Seleccion* auxSeleccion;
	int idSelec;
	char pais[30];
	int largo = ll_len(pArrayListSeleccion);

	if(pArrayListSeleccion!=NULL && pNacionalidad!=NULL)
	{
		for(int i=0; i<largo; i++)
		{
			auxSeleccion=(Seleccion*) ll_get(pArrayListSeleccion, i);
			selec_getId(auxSeleccion, &idSelec);
			selec_getPais(auxSeleccion, pais);
			if(idSelec == idSeleccion)
			{
				strcpy(pNacionalidad, pais);
				break;
			}
			else
			{
				if(idSeleccion == 0)
				{
					strcpy(pNacionalidad, "No convocado");
				}
			}
		}
		retorno=1;
	}

	return retorno;
}

/** \brief Ordenar jugadores
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_ordenarJugadores(LinkedList* pArrayListJugador, LinkedList* pArrayListSeleccion)
{

	int retorno = 0;
	int opcion;
	int opcionCriterio = -1;

	if(pArrayListJugador!=NULL && pArrayListSeleccion!= NULL)
	{
		do{
			limpiarConsola();
			menuOrdenamiento(&opcion);
			if(opcion!=5)
			{
				fpurge(stdin);
				utn_getNumeroInt(&opcionCriterio, "Seleccione un criterio de ordenamiento: 1 para descendente o 0 para ascendente.\n", "ERROR.\n", 0, 1, 50);

			}
			switch(opcion)
			{
			fpurge(stdin);
				case 1:
					ll_sort(pArrayListJugador, ordenarJugadoresPorNacionalidad, opcionCriterio);
					controller_listarJugadores(pArrayListJugador, pArrayListSeleccion);
					pausa();
					break;
				case 2:
					ll_sort(pArrayListSeleccion, ordenarSeleccionesPorConfederacion, opcionCriterio);
					controller_listarSelecciones(pArrayListSeleccion);
					pausa();
					break;
				case 3:
					ll_sort(pArrayListJugador, ordenarJugadoresPorEdad, opcionCriterio);
					controller_listarJugadores(pArrayListJugador, pArrayListSeleccion);
					pausa();
					break;
				case 4:
					ll_sort(pArrayListJugador, ordenarJugadoresPorNombre, opcionCriterio);
					controller_listarJugadores(pArrayListJugador, pArrayListSeleccion);
					pausa();
					break;
			}
		}while(opcion!=5);
		retorno=1;
	}


    return retorno;
}



/** \brief Guarda los datos de los jugadores en el archivo jugadores.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_guardarJugadoresModoTexto(char* path , LinkedList* pArrayListJugador, LinkedList* pArrayListSelecciones)
{
	int retorno = 0;
	int cant;
	int tam;
	int idSelec;
	int id;
	char nombreCompleto[100];
	int edad;
	char posicion[30];
	char nacionalidad[30];
	Jugador* auxJugador = NULL;
	FILE* f = NULL;
	char seleccionAuxCad[30];

	if(path != NULL && pArrayListJugador!=NULL && pArrayListSelecciones!=NULL)
	{
		f = fopen(path, "w");
		tam = ll_len(pArrayListJugador);

		if(f == NULL)
		{
			printf("no se pudo abrir el archivo");
		}
		else
		{
			for(int i = 0; i < tam ; i++)
			{
				auxJugador = (Jugador*) ll_get(pArrayListJugador, i);

				if(auxJugador != NULL)
				{
					jug_getId(auxJugador, &id);
					jug_getNombreCompleto(auxJugador, nombreCompleto);
					jug_getEdad(auxJugador, &edad);
					jug_getPosicion(auxJugador, posicion);
					jug_getNacionalidad(auxJugador, nacionalidad);
					jug_getSIdSeleccion(auxJugador, &idSelec);
					cargarNombreSeleccion(pArrayListSelecciones, idSelec, seleccionAuxCad);
					cant = fprintf(f, "%d,%s,%d,%s,%s,%s\n", id, nombreCompleto, edad, posicion, nacionalidad, seleccionAuxCad);
					if(cant < 6)
					{
						break;
					}
					else
					{
						retorno = 1;
					}
				}
			}
		}
	}
	fclose(f);
	return retorno;
}

/** \brief Guarda los datos de los jugadores en el archivo binario.
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 *
 */
int controller_guardarJugadoresModoBinario(char* path , LinkedList* pArrayListJugador)
{
	int retorno = 0;
	int tam;
	FILE* f;
	Jugador* auxJuga = NULL;

	if(path!=NULL && pArrayListJugador!=NULL)
	{
		f = fopen(path,"wb");
		tam=ll_len(pArrayListJugador);
		for(int i=0; i<tam;i++)
		{
			auxJuga=(Jugador*)ll_get(pArrayListJugador,i);
			fwrite(auxJuga,sizeof(Jugador),1,f);
			retorno = 1;
		}
	}
	return retorno;
}



/** \brief Carga los datos de los selecciones desde el archivo selecciones.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_cargarSeleccionesDesdeTexto(char* path , LinkedList* pArrayListSeleccion)
{
	int retorno = 0;
	FILE* f = fopen(path, "r");

	if(f!=NULL && pArrayListSeleccion!=NULL)
	{
		parser_SeleccionFromText(f, pArrayListSeleccion);
		retorno = 1;
	}

	fclose(f);
	return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_editarSeleccion(LinkedList* pArrayListSeleccion)
{
    return 1;
}


int listarSeleccion(Seleccion* unaSeleccion)
{
    int retorno = 0;
    int id;
    char pais[30];
    char confederacion[30];
    int convocados;

    if(unaSeleccion!=NULL)
    {
        if(selec_getId(unaSeleccion, &id) && selec_getPais(unaSeleccion, pais) && selec_getConfederacion(unaSeleccion, confederacion)
           && selec_getConvocados(unaSeleccion, &convocados))
	    {
			printf("|  %-2d  |   %-16s  |   %-9s   |     %-4d     |\n", id, pais, confederacion, convocados);
			retorno = 1;
	    }
    }

    return retorno;
}

/** \brief Listar selecciones
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_listarSelecciones(LinkedList* pArrayListSeleccion)
{
	int retorno = 0;
	int tam;
	Seleccion* auxSeleccion = NULL;

	if(pArrayListSeleccion != NULL)
	{
		tam = ll_len(pArrayListSeleccion);
		limpiarConsola();
		printf( "=============================================================\n"
				"|                   ***LISTA SELECCIONES***                 |\n"
				"=============================================================\n"
				"|  ID  |        PAIS         | CONFEDERACION |   CONVOCADO  |\n"
				"-------------------------------------------------------------\n");

		for(int i=0; i<tam; i++)
		{
			auxSeleccion = (Seleccion*)ll_get(pArrayListSeleccion, i);
			listarSeleccion(auxSeleccion);
		}
		printf( "=============================================================\n");
		retorno=1;
	}
	return retorno;
}

/** \brief Ordenar selecciones
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_ordenarSelecciones(LinkedList* pArrayListSeleccion)
{
    return 1;
}

/** \brief Guarda los datos de los selecciones en el archivo selecciones.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListSeleccion LinkedList*
 * \return int
 *
 */
int controller_guardarSeleccionesModoTexto(char* path , LinkedList* pArrayListSeleccion)
{
    return 1;
}

int controller_convocarJugador(LinkedList* pArrayListJugador,LinkedList* pArrayListSeleccion)
{
	int retorno = 0;
	Jugador* auxJugador;
	Seleccion* auxSeleccion;
	int auxId;
	int idSeleccion;
	int indice;
	int indiceSeleccion;
	char respuesta;
	char respuestaSeleccion;
	int cantConvocados;

	if(pArrayListJugador !=NULL && pArrayListSeleccion !=NULL)
	{
		limpiarConsola();
		printf("                     ***CONVOCAR JUGADOR***");

		controller_listarJugadores(pArrayListJugador, pArrayListSeleccion);
		utn_getNumeroInt(&auxId,"Ingrese id del jugador a convocar: " , "ERROR.\n", 1, 700, 50);
		controller_buscarIdJugador(pArrayListJugador, auxId, &indice);
		if(indice==-1)
		{
			printf("No existe ningun jugador con el id: %d.\n", auxId);
		}
		else
		{

			auxJugador = (Jugador*)ll_get(pArrayListJugador, indice);
			printf("                      EL JUGADOR QUE DESEA CONVOCAR ES EL SIGUIENTE:\n\n");
			printf( "========================================================================================================\n"
					"|                                             ***JUGADOR***                                            |\n"
					"========================================================================================================\n"
					"|  ID  |          NOMBRE           | EDAD |       POSICION       |   NACIONALIDAD    |    SELECCION    |\n"
					"--------------------------------------------------------------------------------------------------------\n");
			controller_listarJugador(auxJugador, pArrayListSeleccion);
			printf("========================================================================================================\n");
			utn_getCharSeguir(&respuesta, "\n\nConfirma convocacion?: s(si)o n(no)", "ERROR. Vuelve a intentarlo.\n", 50);
			if(respuesta == 's')
			{
				controller_listarSelecciones(pArrayListSeleccion);
				utn_getNumeroInt(&idSeleccion,"Ingrese id de la seleccion a convocar: " , "ERROR.\n", 1, 700, 50);
				controller_buscarIdSeleccion(idSeleccion, pArrayListSeleccion, &indiceSeleccion);
				if(indiceSeleccion == -1)
				{
					printf("No existe ninguna seleccion con el id: %d.\n", idSeleccion);
				}
				else
				{
					auxSeleccion = (Seleccion*)ll_get(pArrayListSeleccion, indiceSeleccion);
					printf("               LA SELECCION ELEGIDA ES LA SIGUIENTE: \n\n");
					printf( "=============================================================\n"
							"|                   ***LISTA SELECCIONES***                 |\n"
							"=============================================================\n"
							"|  ID  |        PAIS         | CONFEDERACION |   CONVOCADO  |\n"
							"-------------------------------------------------------------\n");
					listarSeleccion(auxSeleccion);
					printf( "=============================================================\n");
					utn_getCharSeguir(&respuestaSeleccion, "\n\nConfirma Seleccion?: s(si)o n(no)", "ERROR. Vuelve a intentarlo.\n", 50);
					selec_getConvocados(auxSeleccion, &cantConvocados);
					if(respuestaSeleccion == 's' && cantConvocados < 22)
					{
						jug_setIdSeleccion(auxJugador, idSeleccion);
						auxSeleccion->convocados = cantConvocados + 1;
					}
					else
					{
						printf("Ya hay 22 convocados en la seleccion ingresada.\n");
					}
				}
			}
			else
			{
				printf("La convocacion fue cancelada por el usuario.\n");
			}
		}
	}

	return retorno;
}

int controller_quitarJugaSeleccion(LinkedList* pArrayListJugador,LinkedList* pArrayListSeleccion)
{
	int retorno = 0;
	Jugador* auxJugador;
	Seleccion* auxSeleccion;
	int auxId;
	int idSeleccion;
	int indice;
	int indiceSeleccion;
	char respuesta;
	int cantConvocados;

	if(pArrayListJugador !=NULL && pArrayListSeleccion !=NULL)
	{
		limpiarConsola();
		printf("                     ***QUITAR JUGADOR DE SELECCION***");

		controller_listarJugadores(pArrayListJugador, pArrayListSeleccion);
		utn_getNumeroInt(&auxId,"Ingrese id del jugador a quitar de la seleccion: " , "ERROR.\n", 1, 700, 50);
		controller_buscarIdJugador(pArrayListJugador, auxId, &indice);
		if(indice==-1)
		{
			printf("No existe ningun jugador con el id: %d.\n", auxId);
		}
		else
		{

			auxJugador = (Jugador*)ll_get(pArrayListJugador, indice);
			printf("                      EL JUGADOR QUE DESEA QUITAR ES EL SIGUIENTE:\n\n");
			printf( "========================================================================================================\n"
					"|                                             ***JUGADOR***                                            |\n"
					"========================================================================================================\n"
					"|  ID  |          NOMBRE           | EDAD |       POSICION       |   NACIONALIDAD    |    SELECCION    |\n"
					"--------------------------------------------------------------------------------------------------------\n");
			controller_listarJugador(auxJugador, pArrayListSeleccion);
			printf("========================================================================================================\n");
			utn_getCharSeguir(&respuesta, "\n\nConfirma quitar al jugador?: s(si)o n(no)", "ERROR. Vuelve a intentarlo.\n", 50);
			jug_getSIdSeleccion(auxJugador, &idSeleccion);
			if(idSeleccion==0)
			{
				printf("El jugador no esta convocado en ninguna seleccion.\n");
			}
			else
			{
				controller_buscarIdSeleccion(idSeleccion, pArrayListSeleccion, &indiceSeleccion);
				auxSeleccion = (Seleccion*)ll_get(pArrayListSeleccion, indiceSeleccion);
				selec_getConvocados(auxSeleccion, &cantConvocados);
				if(cantConvocados > 0)
				{
					if(respuesta == 's')
					{
						auxJugador->idSeleccion = 0;
						auxSeleccion->convocados = cantConvocados - 1;
						retorno = 1;
					}
					else
					{
						printf("Baja de seleccion cancelada por el usuario.\n");
					}
				}
			}
		}
	}

	return retorno;
}

int controller_listarJugadoresConvocados(LinkedList* pArrayListJugador, LinkedList* pArrayListSeleccion)
{
	int retorno = 0;
	Jugador* auxJugador = NULL;
	int tam;
	int idSeleccion;
	int flag=0;

	if(pArrayListJugador != NULL)
	{
		limpiarConsola();
		printf( "========================================================================================================\n"
				"|                                  ***LISTA JUGADORES CONVOCADOS***                                    |\n"
				"========================================================================================================\n"
				"|  ID  |          NOMBRE           | EDAD |       POSICION       |   NACIONALIDAD    |    SELECCION    |\n"
				"--------------------------------------------------------------------------------------------------------\n");
		tam = ll_len(pArrayListJugador);
		for(int i=0; i<tam; i++)
		{
			auxJugador = (Jugador*)ll_get(pArrayListJugador, i);
			jug_getSIdSeleccion(auxJugador, &idSeleccion);
			if(idSeleccion != 0)
			{
				controller_listarJugador(auxJugador, pArrayListSeleccion);
				flag=1;
				retorno = 1;
			}
		}
		if(!flag)
		{
			printf("|                          No hay jugadores convocados en ninguna seleccion.                           |\n");
		}
		printf("========================================================================================================\n");
	}

	return retorno;
}

int controller_buscarIdSeleccion(int id, LinkedList* pArrayListSeleccion, int* pIndice)
{
	int retorno = 0;
	int indice = -1;
	int tam;
	int auxId;

	Seleccion* auxSeleccion = NULL;

	if(pArrayListSeleccion!=NULL)
	{
		tam=ll_len(pArrayListSeleccion);

		for(int i=0;i<tam;i++)
		{
			auxSeleccion=ll_get(pArrayListSeleccion,i);
			selec_getId(auxSeleccion, &auxId);
			if(auxId == id)
			{
				indice=ll_indexOf(pArrayListSeleccion, auxSeleccion);
				retorno = 1;
			}
		}
	}
	*pIndice = indice;
	return retorno;
}

int nuevaListaBinarioPorConfederacion(LinkedList* pArrayListJugador, LinkedList* pArrayListSeleccion,LinkedList* pListaJugadoresPorConf)
{
    int retorno=0;
    Jugador* auxJugador=NULL;
    Seleccion* auxSeleccion=NULL;
    int opcionConf;
    int tamJuga;
    int tamSelec;
    int idSeleccion;
    int idSeleccionAux;
    int flag=0;
    char confederacionesStr[30];
    char confederacionStrAux[30];

    if(pArrayListJugador!=NULL && pArrayListSeleccion!=NULL && pListaJugadoresPorConf!=NULL)
    {
		menuConfederaciones(&opcionConf);
		opcionesConfederaciones(opcionConf, confederacionesStr);
		tamJuga=ll_len(pArrayListJugador);
		tamSelec=ll_len(pArrayListSeleccion);
        for(int i=0; i<tamJuga ;i++)
        {
        	auxJugador=ll_get(pArrayListJugador, i);
            jug_getSIdSeleccion(auxJugador, &idSeleccion);

            for(int j=0;j<tamSelec;j++)
            {
            	auxSeleccion=ll_get(pArrayListSeleccion, j);
                selec_getId(auxSeleccion, &idSeleccionAux);
                selec_getConfederacion(auxSeleccion, confederacionStrAux);
                if(idSeleccion!=0 && strcmp(confederacionStrAux, confederacionesStr)==0 && idSeleccion==idSeleccionAux)
                {
                	flag=1;
                    ll_add(pListaJugadoresPorConf, auxJugador);
                }
            }
        }
        if(!flag)
        {
        	printf("No hay jugadores en la confederacion seleccionada.\n");
        }
        retorno=1;
    }

    return retorno;
}
