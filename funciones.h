#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "list.h"
#include "hashmap.h"
#include <stdio.h>

typedef struct Zona Zona;

typedef struct Animal Animal;

typedef struct Jugador Jugador;

void iniciarJuego(List*, Jugador*);
  // Función para iniciar el juego
  // Añadir los parametros de la función y modificar su tipo si es necesario

void cargarPartida(List*, Jugador*);
  // Función para cargar partida
  // Añadir parametros de la función y modificar su tipo si es necesario

void mostrarCreditos();

  // Agregar los creditos. Por ahora no sé que quieren poner acá

void funcionJuego(List*, Jugador*);

  //Funcion principal donde se produce el juego

void importar(List*, FILE*);

  //Importacion de los ficheros que se entregan y se guardan en el mapa

void guardarPartida(Zona*, Jugador*);

  //Se guarda la partida actual, la zona y la moralidad, en un fichero

void interaccionAnimal(char*, Zona*,Jugador*);

  //Toda la interaccion que hay con los animales

char* obtenerDialogo(char*, HashMap*);

  //Se obtiene la cadena de dialogo del mapa del animal

void inicializarZonas(List*, int);

  //Se inicializan las zonas a utilizar

void inicializarJugador(Jugador*,int);

  //Se inicializan el jugador

void importarArchivo(List*);

  //Funcion para la importacion

void procesoMenuPrincipal(int,List*,Jugador*);

  //Menu de zonas 

void menuPrincipal();

  //Menu al inicio del juego

void imprimirMarco(const char *);

  //Se imprimen marcos para nombres

void pasarZona(Jugador*, List*);

  //Funcion para pasar de zona, final del juego

void liberarMemoria(Zona*);

  //Se liberar la memoria de las zonas y animales

void mostrarIntroduccion();

  //Se muestra la introduccion del juego

void mostrarFinal(int);

  //Se muestra los finales del juego

#endif