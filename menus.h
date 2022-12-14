/*
 * menus.h
 *
 *  Created on: 27 nov. 2022
 *      Author: mac2020
 */

#ifndef MENUS_H_
#define MENUS_H_



#endif /* MENUS_H_ */

int menuPrincipal();

int opcionListar();

int menuConvocacion();

int menuConfederaciones(int* pOpcion);

int opcionesConfederaciones(int opcion, char* descripcion);

int cargarPosicion(int opcion,char* posicion);

void menuPosiciones();

int opcionesSeleccion(int id, char* seleccion);

void menuSelecciones();

int cargarNacionalidades(int id, char* nacionalidad);

void menuNacionalidades();

int menuModificacion(int* pOpcion);

int menuOrdenamiento(int* pOpcion);
