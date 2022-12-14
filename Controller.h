#include "Jugador.h"
#include "Seleccion.h"

char *itoa(int value, char *result, int base);

int controller_cargarJugadoresDesdeTexto(char* path , LinkedList* pArrayListJugador);

int controller_cargarJugadoresDesdeBinario(char* path , LinkedList* pArrayListJugador);

int controller_nextId(char* id);

int controller_agregarJugador(LinkedList* pArrayListJugador);

int controller_buscarIdJugador(LinkedList* pArrayListJugador, int id, int* pIndice);

int controller_editarJugador(LinkedList* pArrayListJugador, LinkedList* listaSeleccion);

int controller_removerJugador(LinkedList* pArrayListJugador, LinkedList* listaSeleccion);

int controller_listarJugador(Jugador* unJugador, LinkedList* listaSeleccion);

int controller_listarJugadores(LinkedList* pArrayListJugador, LinkedList* listaSeleccion);

int cargarNombreSeleccion(LinkedList* pArrayListSeleccion, int idSeleccion, char* pNacionalidad);

int controller_ordenarJugadores(LinkedList* pArrayListJugador, LinkedList* pArrayListSeleccion);

int controller_guardarJugadoresModoTexto(char* path , LinkedList* pArrayListJugador, LinkedList* pArrayListSelecciones);

int controller_guardarJugadoresModoBinario(char* path , LinkedList* pArrayListJugador);

int controller_cargarSeleccionesDesdeTexto(char* path , LinkedList* pArrayListSeleccion);

int controller_convocarJugador(LinkedList* pArrayListJugador,LinkedList* pArrayListSeleccion);

int controller_quitarJugaSeleccion(LinkedList* pArrayListJugador,LinkedList* pArrayListSeleccion);

int controller_listarJugadoresConvocados(LinkedList* pArrayListJugador, LinkedList* pArrayListSeleccion);

int controller_buscarIdSeleccion(int id, LinkedList* pArrayListSeleccion, int* pIndice);

int nuevaListaBinarioPorConfederacion(LinkedList* pArrayListJugador, LinkedList* pArrayListSeleccion,LinkedList* pArrayListaNuevaJugadores);

int controller_editarSeleccion(LinkedList* pArrayListSeleccion);

int listarSeleccion(Seleccion* unaSeleccion);

int controller_listarSelecciones(LinkedList* pArrayListSeleccion);

int controller_ordenarSelecciones(LinkedList* pArrayListSeleccion);

int controller_guardarSeleccionesModoTexto(char* path , LinkedList* pArrayListSeleccion);

