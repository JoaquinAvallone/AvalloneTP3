#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Jugador.h"
#include "validaciones.h"
#include "menus.h"


int main()
{
	setbuf(stdout,NULL);
	char respuesta = 'n';
    int flagPuntoOcho = 0;
    int flagSalida = 0;
    LinkedList* listaJugadores = ll_newLinkedList();
    LinkedList* listaSelecciones = ll_newLinkedList();
    LinkedList* listaJugaPorConf = ll_newLinkedList();

    do{
        switch(menuPrincipal())
        {
            case 1:
            	if(controller_cargarJugadoresDesdeTexto("jugadores.csv",listaJugadores) && controller_cargarSeleccionesDesdeTexto("selecciones.csv", listaSelecciones))
            	{
            		printf("Los archivos fueron cargados exitosamente.\n");
            	}
            	else
            	{
            		printf("Hubo un error al cargar los archivos.\n");
            	}
            	pausa();
                break;
            case 2:
            	if(ll_isEmpty(listaJugadores))
            	{
            		printf("Primero se debe ingresar al punto 1.\n");
            	}
            	else
            	{
            		if(controller_agregarJugador(listaJugadores))
            		{
            			flagSalida=1;
            			printf("La carga del jugador fue exitosa.\n");
            		}
            		else
            		{
            			printf("Hubo un problema al cargar el jugador.\n");
            		}
            	}
            	pausa();
            	break;
            case 3:
            	if(ll_isEmpty(listaJugadores))
            	{
            		printf("Primero se debe ingresar al punto 1.\n");
            	}
            	else
            	{
            		if(controller_editarJugador(listaJugadores, listaSelecciones))
            		{
            			flagSalida=1;
            			printf("La modificacion del jugador fue exitosa.\n");
            		}
            		else
            		{
            			printf("Modificacion del jugador cancelada.n");
            		}
            	}
            	pausa();
            	break;
            case 4:
            	if(ll_isEmpty(listaJugadores))
				{
					printf("Primero se debe ingresar al punto 1.\n");
				}
				else
				{
					if(controller_removerJugador(listaJugadores, listaSelecciones))
					{
						flagSalida=1;
						printf("La baja del jugador fue exitosa.\n");
					}
					else
					{
						printf("Baja del jugador cancelada.n");
					}
				}
				pausa();
            	break;
            case 5:
            	if(ll_isEmpty(listaJugadores))
            	{
            		printf("Primero se debe ingresar al punto 1.\n");
            	}
            	else
            	{
            		switch(opcionListar())
            		{
            		case 1:
            			controller_listarJugadores(listaJugadores, listaSelecciones);
            			break;
            		case 2:
            			controller_listarSelecciones(listaSelecciones);
            			break;
            		case 3:
            			controller_listarJugadoresConvocados(listaJugadores, listaSelecciones);
            			break;
            		case 4:
            			break;
            		}
            	}
            	pausa();
            	break;
            case 6:
            	if(ll_isEmpty(listaJugadores))
            	{
            		printf("Primero se debe ingresar al punto 1.\n");
            	}
            	else
            	{
            		switch(menuConvocacion())
					{
					case 1:
						flagSalida=1;
						controller_convocarJugador(listaJugadores, listaSelecciones);
						break;
					case 2:
						if(controller_quitarJugaSeleccion(listaJugadores, listaSelecciones))
						{
							flagSalida=1;
							printf("Jugador quitado con exito.\n");
						}
						else
						{
							printf("Baja cancelada.\n");
						}
						break;
					}
            	}
            	pausa();
            	break;
            case 7:
            	if(ll_isEmpty(listaJugadores))
				{
					printf("Primero se debe ingresar al punto 1.\n");
				}
				else
				{
					controller_ordenarJugadores(listaJugadores, listaSelecciones);
				}
            	pausa();
            	break;
            case 8:
            	if(ll_isEmpty(listaJugadores))
				{
					printf("Primero se debe ingresar al punto 1.\n");
				}
            	else
            	{
            		flagSalida=1;
            		flagPuntoOcho = 1;
            		nuevaListaBinarioPorConfederacion(listaJugadores, listaSelecciones, listaJugaPorConf);
            		controller_guardarJugadoresModoBinario("JugadoresPorConf.csv", listaJugaPorConf);
            	}
            	pausa();
            	break;
            case 9:
            	if(ll_isEmpty(listaJugadores))
				{
					printf("Primero se debe ingresar al punto 1.\n");
				}
				else
				{
					if(flagPuntoOcho)
					{
						controller_cargarJugadoresDesdeBinario("JugadoresPorConf.bin", listaJugaPorConf);
						controller_listarJugadores(listaJugaPorConf, listaSelecciones);
					}
					else
					{
						printf("Primero se debe ingresar al punto 8.\n");
					}
				}
            	pausa();
            	break;
            case 10:
            	if(ll_isEmpty(listaJugadores))
				{
					printf("Primero se debe ingresar al punto 1.\n");
				}
				else
				{
					if(controller_guardarJugadoresModoTexto("jugadores.csv", listaJugadores, listaSelecciones) &&
					controller_guardarSeleccionesModoTexto("selecciones.csv", listaSelecciones))
					{
						printf("Cambios guardados con exito.\n");
						flagSalida=-1;
					}
					else
					{
						printf("Hubo un problema al guardar.\n");
					}
				}
				pausa();
            	break;
            case 11:
            	if(flagSalida==-1)
            	{
            		confirmaSalida(&respuesta, 's', 'n', "Los cambios realizados fueron guardados.\n¿Desea continuar? s(si) n(no)\n");
            	}
            	else
            	{
            		if(flagSalida)
            		{
            			confirmaSalida(&respuesta, 's', 'n', "No guardo los cambios realizados en el punto 10.\n¿Desea continuar? s(si) n(no)\n");
            		}
            		else
            		{
            			confirmaSalida(&respuesta, 's', 'n', "No se realizaron cambios.\n¿Desea continuar? s(si) n(no)\n");
            		}
            	}
            	pausa();
            	break;
            default:
			printf("La opcion no existe.\n");
			pausa();
        }
        limpiarConsola();
    }while(respuesta == 'n');

    return 0;
}

