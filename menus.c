#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Jugador.h"
#include "validaciones.h"
#include "menus.h"


int menuPrincipal()
{
	int opcion;
	printf( "        ***MENU PRINCIPAL***\n\n"
			"1.Carga de archivos\n"
			"2.Alta jugador\n"
			"3.Modificacion jugador\n"
			"4.Baja jugador\n"
			"5.Listados\n"
			"6.Convocar jugadores\n"
			"7.Ordenar y listar\n"
			"8.Generar archivo binario\n"
			"9.Cargar archivo binario\n"
			"10.Guardar archivos .csv\n"
			"11.Salir\n");

	utn_getNumeroInt(&opcion, "Ingrese opcion: ", "ERROR.", 1, 11, 100);
	return opcion;
}

int opcionListar()
{
	int opcion;
	limpiarConsola();

	printf(	"         ***OPCIONES DE LISTADOS***\n\n"
			"1.Listar todos los jugadores\n"
			"2.Listar todas las selecciones\n"
			"3.Listar jugadores convocados\n"
			"4.Salir\n");
	utn_getNumeroInt(&opcion, "Ingrese opcion: ", "La opcion ingresada no existe.\n", 1, 4, 100);

	return opcion;
}


int menuConvocacion()
{
	int opcion;
	limpiarConsola();

	printf(	"         ***OPCIONES DE CONVOCACION***\n\n"
			"1.Convocar jugador a una seleccion.\n"
			"2.Quitar jugador de una seleccion.\n");

	utn_getNumeroInt(&opcion, "Ingrese opcion: ", "La opcion ingresada no existe.\n", 1, 2, 100);

	return opcion;
}

int menuConfederaciones(int* pOpcion)
{
	int retorno = 0;
	int opcion;

	if(pOpcion!=NULL)
	{
		printf( "       ***MENU CONFEDERACIONES***  \n\n"
				"1.AFC\n"
				"2.CAF\n"
				"3.CONCACAF\n"
				"4.CONMEBOL\n"
				"5.UEFA\n"
				"6.SALIR\n");
		utn_getNumeroInt(&opcion, "Ingrese opcion: ", "La opcion ingresada no existe.\n", 1, 6, 100);
		retorno = 1;
	}
	*pOpcion = opcion;
	return retorno;
}

int opcionesConfederaciones(int opcion, char* descripcion)
{
	int retorno=0;

	switch(opcion)
	{
	case 1:
		strcpy(descripcion,"AFC");
		break;

	case 2:
		strcpy(descripcion,"CAF");
		break;

	case 3:
		strcpy(descripcion,"CONCACAF");
		break;

	case 4:
		strcpy(descripcion,"CONMEBOL");
		break;

	case 5:
		strcpy(descripcion,"UEFA");
		break;
		retorno=1;
	}

	return retorno;
}

int cargarPosicion(int opcion,char* posicion)
{
    int retorno = 0;

    switch(opcion)
    {
        case 1:
            strcpy(posicion,"Portero");
            break;

        case 2:
            strcpy(posicion,"Defensa Central");
            break;

        case 3:
            strcpy(posicion,"Lateral Izquierdo");
            break;

        case 4:
            strcpy(posicion,"Lateral Derecho");
            break;

        case 5:
            strcpy(posicion,"Pivote");
            break;

        case 6:
            strcpy(posicion,"Mediocentro");
            break;

        case 7:
            strcpy(posicion,"Mediocentro ofensivo");
            break;

        case 8:
            strcpy(posicion,"Extremo Izquierdo");
            break;

        case 9:
            strcpy(posicion,"Extremo Derecho");
            break;

        case 10:
            strcpy(posicion,"Mediapunta");
            break;

        case 11:
            strcpy(posicion,"Delantero Centro");
            break;

            retorno=1;
    }

    return retorno;
}

void menuPosiciones()
{
	printf( "=================================\n"
			"|       LISTA DE POSICIONES     |\n"
			"=================================\n");
	printf( "| OPCION |       POSICION       |\n"
			"---------------------------------\n"
			"|   1    |       Portero        |\n"
			"---------------------------------\n"
			"|   2    |   Defensa Central    |\n"
			"---------------------------------\n"
			"|   3    |  Lateral Izquierdo   |\n"
			"---------------------------------\n"
			"|   4    |   Lateral Derecho    |\n"
			"---------------------------------\n"
			"|   5    |        Pivote        |\n"
			"---------------------------------\n"
			"|   6    |     Mediocentro      |\n"
			"---------------------------------\n"
			"|   7    | Mediocentro ofensivo |\n"
			"---------------------------------\n"
			"|   8    |  Extremo Izquierdo   |\n"
			"---------------------------------\n"
			"|   9    |   Extremo Derecho    |\n"
			"---------------------------------\n"
			"|   10   |     Mediapunta       |\n"
			"---------------------------------\n"
			"|   11   |   Delantero Centro   |\n"
			"=================================\n");
}

int opcionesSeleccion(int id, char* seleccion)
{
	int retorno = 0;

	if(seleccion!= NULL && id>0)
    {
        switch(id)
        {
        case 1:
            strcpy(seleccion,"Alemania");
            break;

        case 2:
            strcpy(seleccion,"Arabia Saudita");
            break;

        case 3:
            strcpy(seleccion,"Argentina")    ;
            break;

        case 4:
            strcpy(seleccion,"Australia")    ;
            break;

        case 5:
            strcpy(seleccion,"Belgica");
            break;

        case 6:
            strcpy(seleccion,"Brasil");
            break;

        case 7:
            strcpy(seleccion,"Camerun");
            break;

        case 8:
            strcpy(seleccion,"Canada");
            break;

        case 9:
            strcpy(seleccion,"Corea del Sur");
            break;

        case 10:
            strcpy(seleccion,"Costa Rica");
            break;

        case 11:
            strcpy(seleccion,"Croacia");
            break;

        case 12:
            strcpy(seleccion,"Dinamarca");
            break;

        case 13:
            strcpy(seleccion,"Ecuador");
            break;

        case 14:
            strcpy(seleccion,"Espana");
            break;

        case 15:
            strcpy(seleccion,"Estados Unidos");
            break;

        case 16:
            strcpy(seleccion,"Francia");
            break;

        case 17:
            strcpy(seleccion,"Gales");
            break;

        case 18:
            strcpy(seleccion,"Ghana");
            break;

        case 19:
            strcpy(seleccion,"Holanda");
            break;

        case 20:
            strcpy(seleccion,"Inglaterra");
            break;
        case 21:
            strcpy(seleccion,"Iran");
            break;

        case 22:
            strcpy(seleccion,"Japon");
            break;

        case 23:
            strcpy(seleccion,"Marruecos");
            break;

        case 24:
            strcpy(seleccion,"Mexico");
            break;

        case 25:
            strcpy(seleccion,"Polonia");
            break;

        case 26:
            strcpy(seleccion,"Portugal");
            break;

        case 27:
            strcpy(seleccion,"Qatar");
            break;

        case 28:
            strcpy(seleccion,"Senegal");
            break;

        case 29:
            strcpy(seleccion,"Serbia");
            break;

        case 30:
            strcpy(seleccion,"Suiza");
            break;

        case 31:
            strcpy(seleccion,"Tunez");
            break;

        case 32:
            strcpy(seleccion,"Uruguay");
            break;
        }
        retorno=1;
    }
	return retorno;
}

void menuSelecciones()
{
	printf( "==============================\n"
			"|     LISTA DE SELECCIONES   |\n"
			"==============================\n");
	printf( "|   ID   |      SELECCION    |\n"
			"------------------------------\n"
			"|   1    |      Alemania     |\n"
			"------------------------------\n"
			"|   2    |   Arabia Saudita  |\n"
			"------------------------------\n"
			"|   3    |      Argentina    |\n"
			"------------------------------\n"
			"|   4    |      Australia    |\n"
			"------------------------------\n"
			"|   5    |      Belgica      |\n"
			"------------------------------\n"
			"|   6    |      Brasil       |\n"
			"------------------------------\n"
			"|   7    |      Camerun      |\n"
			"------------------------------\n"
			"|   8    |      Canada       |\n"
			"------------------------------\n"
			"|   9    |   Corea del Sur   |\n"
			"------------------------------\n"
			"|   10   |    Costa Rica     |\n"
			"------------------------------\n"
			"|   11   |      Croacia      |\n"
			"------------------------------\n"
			"|   12   |     Dinamarca     |\n"
			"------------------------------\n"
			"|   13   |      Ecuador      |\n"
			"------------------------------\n"
			"|   14   |      Espana       |\n"
			"------------------------------\n"
			"|   15   |   Estados Unidos  |\n"
			"------------------------------\n"
			"|   16   |      Francia      |\n"
			"------------------------------\n"
			"|   17   |      Gales        |\n"
			"------------------------------\n"
			"|   18   |      Ghana        |\n"
			"------------------------------\n"
			"|   19   |      Holanda      |\n"
			"------------------------------\n"
			"|   20   |     Inglaterra    |\n"
			"------------------------------\n"
			"|   21   |      Iran         |\n"
			"------------------------------\n"
			"|   22   |      Japon        |\n"
			"------------------------------\n"
			"|   23   |     Marruecos     |\n"
			"------------------------------\n"
			"|   24   |      Mexico       |\n"
			"------------------------------\n"
			"|   25   |      Polonia      |\n"
			"------------------------------\n"
			"|   26   |      Portugal     |\n"
			"------------------------------\n"
			"|   27   |      Qatar        |\n"
			"------------------------------\n"
			"|   28   |      Senegal      |\n"
			"------------------------------\n"
			"|   29   |      Serbia       |\n"
			"------------------------------\n"
			"|   30   |      Suiza        |\n"
			"------------------------------\n"
			"|   31   |      Tunez        |\n"
			"------------------------------\n"
			"|   32   |      Uruguay      |\n"
			"------------------------------\n");
}

int cargarNacionalidades(int id, char* nacionalidad)
{
	int retorno = 0;

	if(nacionalidad!= NULL && id>0)
    {
        switch(id)
        {
        case 1:
            strcpy(nacionalidad,"Alemana");
            break;

        case 2:
            strcpy(nacionalidad,"Saudi");
            break;

        case 3:
            strcpy(nacionalidad,"Argentino")    ;
            break;

        case 4:
            strcpy(nacionalidad,"Australiano")    ;
            break;

        case 5:
            strcpy(nacionalidad,"Belga");
            break;

        case 6:
            strcpy(nacionalidad,"Brasilero");
            break;

        case 7:
            strcpy(nacionalidad,"Camerunes");
            break;

        case 8:
            strcpy(nacionalidad,"Canadiense");
            break;

        case 9:
            strcpy(nacionalidad,"Coreano");
            break;

        case 10:
            strcpy(nacionalidad,"Costarricense");
            break;

        case 11:
            strcpy(nacionalidad,"Croata");
            break;

        case 12:
            strcpy(nacionalidad,"Danes");
            break;

        case 13:
            strcpy(nacionalidad,"Ecuatoriano");
            break;

        case 14:
            strcpy(nacionalidad,"Espanol");
            break;

        case 15:
            strcpy(nacionalidad,"Estadounidense");
            break;

        case 16:
            strcpy(nacionalidad,"Frances");
            break;

        case 17:
            strcpy(nacionalidad,"Gales");
            break;

        case 18:
            strcpy(nacionalidad,"Ghanes");
            break;

        case 19:
            strcpy(nacionalidad,"Holandes");
            break;

        case 20:
            strcpy(nacionalidad,"Ingles");
            break;
        case 21:
            strcpy(nacionalidad,"Irani");
            break;

        case 22:
            strcpy(nacionalidad,"Japones");
            break;

        case 23:
            strcpy(nacionalidad,"Marroqui");
            break;

        case 24:
            strcpy(nacionalidad,"Mexicano");
            break;

        case 25:
            strcpy(nacionalidad,"Polaco");
            break;

        case 26:
            strcpy(nacionalidad,"Portugues");
            break;

        case 27:
            strcpy(nacionalidad,"Qatari");
            break;

        case 28:
            strcpy(nacionalidad,"Senegales");
            break;

        case 29:
            strcpy(nacionalidad,"Serbio");
            break;

        case 30:
            strcpy(nacionalidad,"Suizo");
            break;

        case 31:
            strcpy(nacionalidad,"Tunecino");
            break;

        case 32:
            strcpy(nacionalidad,"Uruguayo");
            break;
        }
        retorno=1;
    }
	return retorno;
}

void menuNacionalidades()
{
	printf( "==============================\n"
			"|   LISTA DE NACIONALIDADES  |\n"
			"==============================\n");
	printf( "|   ID   |   NACIONALIDADES  |\n"
			"------------------------------\n"
			"|   1    |      Aleman       |\n"
			"------------------------------\n"
			"|   2    |      Saudi        |\n"
			"------------------------------\n"
			"|   3    |     Argentino     |\n"
			"------------------------------\n"
			"|   4    |    Australiano    |\n"
			"------------------------------\n"
			"|   5    |       Belga       |\n"
			"------------------------------\n"
			"|   6    |     Brasilero     |\n"
			"------------------------------\n"
			"|   7    |     Camerunes     |\n"
			"------------------------------\n"
			"|   8    |    Canadiense     |\n"
			"------------------------------\n"
			"|   9    |      Coreano      |\n"
			"------------------------------\n"
			"|   10   |  Costarriquiense  |\n"
			"------------------------------\n"
			"|   11   |      Croata       |\n"
			"------------------------------\n"
			"|   12   |       Danes       |\n"
			"------------------------------\n"
			"|   13   |    Ecuatoriano    |\n"
			"------------------------------\n"
			"|   14   |      Espanol      |\n"
			"------------------------------\n"
			"|   15   |   Estadounidense  |\n"
			"------------------------------\n"
			"|   16   |      Frances      |\n"
			"------------------------------\n"
			"|   17   |      Gales        |\n"
			"------------------------------\n"
			"|   18   |      Ghanes       |\n"
			"------------------------------\n"
			"|   19   |     Holandes      |\n"
			"------------------------------\n"
			"|   20   |      Ingles       |\n"
			"------------------------------\n"
			"|   21   |      Irani        |\n"
			"------------------------------\n"
			"|   22   |      Japones      |\n"
			"------------------------------\n"
			"|   23   |      Marroqui     |\n"
			"------------------------------\n"
			"|   24   |      Mexicano     |\n"
			"------------------------------\n"
			"|   25   |      Polaco       |\n"
			"------------------------------\n"
			"|   26   |      Portugues    |\n"
			"------------------------------\n"
			"|   27   |      Qatari       |\n"
			"------------------------------\n"
			"|   28   |     Senegales     |\n"
			"------------------------------\n"
			"|   29   |      Serbio       |\n"
			"------------------------------\n"
			"|   30   |      Suizo        |\n"
			"------------------------------\n"
			"|   31   |     Tunecino      |\n"
			"------------------------------\n"
			"|   32   |     Uruguayo      |\n"
			"------------------------------\n");
}


int menuModificacion(int* pOpcion)
{
	if(pOpcion!=NULL)
	{
		printf("            ***MENU MODIFICACION JUGADOR***\n\n"
			   "1.Cambiar nombre del jugador.\n"
			   "2.Cambiar edad del jugador.\n"
			   "3.Cambiar posicion del jugador.\n"
			   "4.Cambiar nacionalidad del jugador.\n");
		scanf("%d", pOpcion);
	}

	return *pOpcion;
}

int menuOrdenamiento(int* pOpcion)
{
	int retorno = 0;
	if(pOpcion!=NULL)
	{
		printf("                  ***ORDENAR Y LISTAR***\n\n\n");
		printf("1.Ordenar jugadores por nacionalidad.\n"
			   "2.Oredenar selecciones por confederacion.\n"
			   "3.Ordenar jugadores por edad.\n"
			   "4.Ordenar jugadores por nombre.\n"
			   "5.Salir.\n");
		utn_getNumeroInt(pOpcion, "Ingrese opcion: ", "Opcion invalida, vuelva a intentarlo: ", 1, 5, 50);
		retorno = 1;
	}

	return retorno;
}
