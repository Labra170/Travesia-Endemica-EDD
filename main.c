// Inclusión de librerias y  archivos adicionales para las funciones.
#include "funciones.h"
#include "hashmap.h"
#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// Definición de algunas variables globales.
#define DEFAULTMAP 300
#define DEFAULTTEXT 300

// Struct de tipo Zona
struct Zona {
  int ID;            // ID de la zona
  HashMap *animales; // Mapa para los animales
};

// Struct de tipo Animal
struct Animal {
  int ID; // ID del animal.
  char *nombre; // Nombre del animal.
  HashMap *dialogos; // Mapa para los dialogos del animal.
  bool entregoItem; // Booleano para el estado de si ha entregado el item o no.
  bool estado; // Booleano para el estado del animal (Vivo = true; Muerto = false).
  bool segundaInteraccion; // Booleano para utilizar el segundo saludo.
};

// Struct de tipo jugador
struct Jugador {
  int moralidad; // Contador para determinar el final
  bool item1; // Booleano del primer item (Se establece en falso al pasar de zona)
  bool item2; // Booleano del segundo item (Se establece en falso al pasar de zona)
  bool item3; // Booleano del tercer item (Se establece en falso al pasar de zona)
};

// Función main...
int main() {
  menuPrincipal();
  return 0;
}

// Función del menú principal
void menuPrincipal() {

  int opcion; // Variable para la opción elegida
  List *listaZonas = createList(); // Se crea la lista para las zonas
  Jugador jugador; // La variable jugador de tipo jugador...

  do { // Imprimir el menú y hacer la selección de opción
    printf("\n");
    printf("████████╗██████╗░░█████╗░██╗░░░██╗███████╗░██████╗██╗░█████╗░\n");
    printf("╚══██╔══╝██╔══██╗██╔══██╗██║░░░██║██╔════╝██╔════╝██║██╔══██╗\n");
    printf("░░░██║░░░██████╔╝███████║╚██╗░██╔╝█████╗░░╚█████╗░██║███████║\n");
    printf("░░░██║░░░██╔══██╗██╔══██║░╚████╔╝░██╔══╝░░░╚═══██╗██║██╔══██║\n");
    printf("░░░██║░░░██║░░██║██║░░██║░░╚██╔╝░░███████╗██████╔╝██║██║░░██║\n");
    printf("░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚══════╝╚═════╝░╚═╝╚═╝░░╚═╝\n\n");

    printf("███████╗███╗░░██╗██████╗░███████╗███╗░░░███╗██╗░█████╗░░█████╗░\n");
    printf("██╔════╝████╗░██║██╔══██╗██╔════╝████╗░████║██║██╔══██╗██╔══██╗\n");
    printf("█████╗░░██╔██╗██║██║░░██║█████╗░░██╔████╔██║██║██║░░╚═╝███████║\n");
    printf("██╔══╝░░██║╚████║██║░░██║██╔══╝░░██║╚██╔╝██║██║██║░░██╗██╔══██║\n");
    printf("███████╗██║░╚███║██████╔╝███████╗██║░╚═╝░██║██║╚█████╔╝██║░░██║\n");
    printf("╚══════╝╚═╝░░╚══╝╚═════╝░╚══════╝╚═╝░░░░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝\n");
    printf("---------------------------------------------------------------\n");
    printf("\n1.- Iniciar juego"); 
    printf("\n2.- Cargar partida");
    printf("\n3.- Créditos");
    printf("\n4.- Salir\n\n");
    printf("--------------------------------------------------------------\n");
    printf("\nElije una opción: ");
    scanf(" %d", &opcion); // El usuario ingresa un número.
    printf("\n");
    printf("\n--------------------------------------------------------------\n");
    printf("\e[1;1H\e[2J");
    procesoMenuPrincipal(opcion, listaZonas, &jugador);
  } while (opcion != 4); // Mientras que no se seleccione salir.
}

// Función para el proceso del menú principal.
void procesoMenuPrincipal(int opcion, List *listaZonas, Jugador *jugador) {
  switch (opcion) { // Switch para la opcion seleccionada
  case 1:
    iniciarJuego(listaZonas, jugador); // Llamado a función "iniciarJuego"
    funcionJuego(listaZonas, jugador); // Llamado a función "funcionJuego"
    break;
  case 2:
    cargarPartida(listaZonas, jugador); // Llamado a función "cargarPartida"
    break;
  case 3:
    mostrarCreditos(); // Llamado a función "mostrarCreditos"
    break;
  case 4:
    printf("\nHasta la próxima!\n"); // En caso de seleccionar salir.
    break;
  default:
    printf("\nOpción no válida"); // Cuando se ingresa un número que no es opción
    break;
  }
}

void iniciarJuego(List *listaZonas, Jugador *jugador) {

  // Se revisa si se cargo una partida
  void *primeraZona = firstList(listaZonas);

  if (primeraZona != NULL) {
    return; // Ya se cargo una partida anteriormente
  }

  // Se inicializan las zonas
  inicializarZonas(listaZonas, 1);

  // Se inicializa el jugador;
  inicializarJugador(jugador,0);

  // Se importan los archivos del juego
  importarArchivo(listaZonas);
}

void inicializarZonas(List *listaZonas,int zona) {

  int id, cantZona; // Variables locales... 
  // ID: Identificador de la zona.
  // cantZona: Zonas por realizar aún.
  
  switch(zona){
    case 1: // Para la zona 1
      cantZona = 3;
      id = 1;
      break;
    case 2: // Para la zona 2
      cantZona = 2;
      id = 2;
      break;
    case 3: // Para la zona 3
      cantZona = 1;
      id = 3;
      break;
  }
  
  for (int i = 1; i <= cantZona; i++) {

    Zona *zona = (Zona *)malloc(sizeof(Zona)); // Asignación de memoria para la zona

    zona->ID = id; // Asignación de id para la zona

    zona->animales = createMap(DEFAULTMAP); // Se crea el mapa de animales para la zona

    id++; // Se aumenta el contador de ID
    pushBack(listaZonas, zona); // Se envia la zona la final de la lista.
  }
}

void inicializarJugador(Jugador* jugador,int mor) {

  jugador = (Jugador *)malloc(sizeof(Jugador)); // Asignación de memoria para la variable Jugador

  jugador->item1 = false; // Se establecen los items del jugador en falso.

  jugador->item2 = false; // ...

  jugador->item3 = false; // ...

  jugador->moralidad = mor; // Se asigna el valor de la moralidad.
}

void cargarPartida(List *listaZonas, Jugador *jugador) { // Función para cargar la partida

  // Obtén el directorio actual
  char directorio_actual[256];

  // Se obtiene la direccion donde se encuentra el programa
  if (getcwd(directorio_actual, sizeof(directorio_actual)) == NULL) { // 
    perror("Error al obtener el directorio actual");
    return;
  }

  char ruta_completa[256]; // Variable para el nombre del archivo (Ubicación)
  snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s/%s", directorio_actual,
           "data", "save.txt"); // 

  FILE *archivo = fopen(ruta_completa, "r"); // Se abre el archivo en modo lectura
  if (archivo == NULL) { // Si no se pudo abrir el archivo
    perror("Error al abrir el archivo");
    return;
  }

  char linea[256]; // Para cada linea del texto
  fgets(linea, sizeof(linea), archivo);

  char *token;
  token = strtok(linea, ","); // Separador de valores en el archivo
  int cantToken = 0;
  int zona; // El número de la zona
  int mor; // La moralidad

  while (token != NULL) { // Mientras hayan valores por recorrer

    switch (cantToken) { // Dependiendo del valor del token
    case 0: // Si es el primero, el valor es el de la zona
      zona = atoi(token);
      break;
    case 1: // Si es el segundo, es el valor de la moralidad
      mor = atoi(token);
      break;
    default:
      printf("\nNO AÑADIR DATOS AL SAVE\n");
      abort();
    }
    token = strtok(NULL, ","); // Se avanza al siguiente token
    cantToken++; // Se aumenta el contador del token
  }

  fclose(archivo); // Se cierra el archivo

  inicializarZonas(listaZonas, zona); // Llamado a función inicializarZonas
  inicializarJugador(jugador,mor); // Llamado a función inicializarJugador

  strcpy(ruta_completa, directorio_actual); // Se traspasa la ruta del archivo.

  //Dependiendo de la zona que el archivo save tenga se importara un archivo diferente
  switch (zona) {
  case 1:
    snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s/%s",
             directorio_actual, "data", "zonaA.txt");
    break;
  case 2:
    snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s/%s",
             directorio_actual, "data", "zonaB.txt");
    break;
  case 3:
    snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s/%s",
             directorio_actual, "data", "zonaC.txt");
    break;
  default:
    printf("\nNO EXISTE LA ZONA\n");
    printf("CERRANDO JUEGO");
    abort();
  }

  archivo = fopen(ruta_completa, "r"); // Se abre el archivo en modo lectura

  importar(listaZonas, archivo);

  fclose(archivo); // Se cierra el archivo

  if(firstList(listaZonas) == NULL){
    printf("\nError al cargar partida\n");
    return;
  }

  printf("\nSe cargo con exito la partida\n");
}

void mostrarCreditos() { // Función para mostrar los créditos
  printf("\e[1;1H\e[2J");
  printf("\nCréditos\n");
  printf("\nDesarrolladores\n");
  printf("\nAlonso B\n");
  printf("Bryan P\n");
  printf("Cristel S\n");
  printf("Ignacio V\n");

  printf("\nNarrativa\n");
  printf("\nAlonso B\n");
  printf("Bryan P\n");
  printf("Cristel S\n");
  printf("Ignacio V\n");
  
  printf("\nMúsica\n");
  printf("\nZona 1: Evanescence");
  printf("\nZona 2: Blondon Boys");
  printf("\nZona 3: Caramelldansen");
  printf("\n");
  return;
}

void mostrarIntroduccion() { //  Función para mostrar la introducción al inicio del juego.
  
  char variableParaPausa[1000]; // Variable para poder usar scanf sin problemas...
  printf("\nEres un aventurero de un país lejano, cierto día con tus camaradas emprenden un viaje en barco hacia nuevas tierras, al \n");
  printf("tercer día de viaje ocurre un accidente por el cual te caes del barco en el que iban navegando. Despiertas en medio de la \n");
  printf("nada y comienzas a recorrer el lugar ¿hacia donde te diriges?\n");

  printf("\n\nENCUENTRA LAS PARTES DE UN MAPA PARA PASAR A LA SIGUIENTE ZONA\n\n");
  
  printf("Presiona Enter para continuar...");
  while (getchar() != '\n'); // Consumir cualquier entrada adicional
  getchar();
  printf("\n");
  printf("\e[1;1H\e[2J"); // Se borra el texto en consola
}

void mostrarFinal(int moralidad) { // Función para mostrar el final del juego

  printf("\e[1;1H\e[2J"); // Se borra el texto
  printf("\nA lo lejos se divisa la sociedad, finalmente llegaste a tu destino... \n");
  if(moralidad <= 0){ // Si la moralidad es 0 o menos, se consigue el final "bueno"
    printf("\nEn tu viaje aprendiste sobre la vida nativa de este nuevo mundo y los ayudaste a prevalecer como especie.\n");
  }
  else if (moralidad < 9) { // Si es menor a 9 pero mayor a 0, se consigue el final "neutral"
    printf("\nAprendiste sobre la vida de los animales, aunque tuviste algunos conflictos que generaron la perdida de algunas especies pero no has generado ningun desorden medioambiental.\n");
  }
  else{ // Si la moralidad es 9 o más, se consigue el final "malo"
    printf("\nEl egoísmo te devolvió a casa, ignoraste a las criaturas a tu paso generando su extinción, tus acciones han generado una catástrofe medioambiental\n");
  }
}

void funcionJuego(List *listaZonas, Jugador *jugador) { // Función principal para el funcionamiento del juego
  Zona *zonaActual = (Zona*)firstList(listaZonas); // Se va a la primera zona.
  if (zonaActual == NULL) return; // Si no hay una lista, se regresa.
  int opcion = 0;

  mostrarIntroduccion();

  do {
    printf("\e[1;1H\e[2J");
    
    imprimirMarco("¿Que quieres hacer?");
    printf("\n");
    printf("1.- Ir al norte.\n");
    printf("2.- Ir al este\n");
    printf("3.- Ir al oeste\n");
    printf("4.- Pasar de zona\n");
    printf("5.- Guardar Partida\n");
    printf("6.- Salir del juego\n");
    printf("-----------------------------------------------------\n");
    printf("Haz elegido la opción: ");
    scanf("%d", &opcion);
    printf("-----------------------------------------------------\n");
    printf("\n");
    char opcionSTR[5];
    sprintf(opcionSTR, "%d", opcion);

    switch (opcion) {
    case 1:
    case 2:
    case 3:
      interaccionAnimal(opcionSTR, zonaActual,jugador);
      break;
    case 4:
      if(jugador->item1 != true || jugador->item2 != true || jugador->item3 != true){
        printf("\nNo tienes todos los items para pasar de zona\n");
        printf("Presiona Enter para continuar...");
        while (getchar() != '\n'); // Consumir cualquier entrada adicional
        getchar();
        break;
      }
      printf("\nPasando de zona\n");
      printf("Presiona Enter para continuar...");
      while (getchar() != '\n'); // Consumir cualquier entrada adicional
      getchar();
      pasarZona(jugador,listaZonas);
      zonaActual = firstList(listaZonas);
      break;
    case 5:
      guardarPartida(zonaActual, jugador);
      break;
    case 6:
      printf("\nHasta la próxima!\n");
      return;
    default:
      printf("Opción no válida");
      break;
    }
  } while (1);
}

void pasarZona(Jugador* jugador, List* listaZonas){

  jugador->item1 = false;
  jugador->item2 = false;
  jugador->item3 = false;


  Zona* zonaBorrar = (Zona*)popFront(listaZonas);
  liberarMemoria(zonaBorrar);

  Zona* zona = (Zona*)firstList(listaZonas);

  if(zona == NULL){
    mostrarFinal(jugador->moralidad);
    printf("\e[1;1H\e[2J");
    printf("\n\nMUCHAS GRACIAS POR JUGAR NUESTRO JUEGO\n\n");
    printf("Presiona Enter para salir del juego...");
    while (getchar() != '\n'); // Consumir cualquier entrada adicional
    getchar();
    abort();
  }

  
  char directorio_actual[256];

  // Se obtiene la direccion donde se encuentra el programa
  if (getcwd(directorio_actual, sizeof(directorio_actual)) == NULL) {
    perror("Error al obtener el directorio actual");
    return;
  }

  char ruta_completa[256];

  switch(zona->ID){
    case 2:
    snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s/%s", directorio_actual,
       "data", "zonaB.txt");
    break;
    case 3:
    snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s/%s", directorio_actual,
       "data", "zonaC.txt");
    break;
  }

  FILE *archivo = fopen(ruta_completa, "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return;
  }

  importar(listaZonas, archivo);

  fclose(archivo);
}

void interaccionAnimal(char* opcionSTR, Zona *zonaActual, Jugador* jugador) {
  
  int opcion;
  Pair *pairAnimal = searchMap(zonaActual->animales, opcionSTR); //opcionSTR;
  if (pairAnimal == NULL)
    return;
  Animal *animal = (Animal *)pairAnimal->value;

  if(animal->estado == true){
  
  char *dialogo = NULL;

  int longitud = strlen(animal->nombre);
    int espacios = (43 - longitud) / 2;

    do{

    imprimirMarco(animal->nombre);
    
  if (animal->segundaInteraccion == false) {
    dialogo = obtenerDialogo("saludo1", animal->dialogos);
    if (dialogo == NULL) return;
    printf("\n%s\n", dialogo);
    animal->segundaInteraccion = true;
  }
  else {
    dialogo = obtenerDialogo("saludo2", animal->dialogos);
    if (dialogo == NULL) return;
    printf("\n%s\n", dialogo);
  }

    printf("\n\n");
    printf("1.- Preguntar sobre el animal\n");
    printf("2.- Preguntar  sobre la zona\n");
    printf("3.- Pregunta por #Parte de mapa de zona %d#\n", zonaActual->ID);
    printf("4.- Robar objeto\n");
    printf("5.- Salir al mapa\n");
    printf("Opcion: ");
    scanf(" %d", &opcion);

    switch(opcion){

      case 1:
        dialogo = obtenerDialogo("datoAnimal", animal->dialogos);
        printf("\n%s\n",dialogo);
        break;
      case 2:
        dialogo = obtenerDialogo("datoZona", animal->dialogos);
        printf("\n%s\n",dialogo);
        break;
      case 3:
        if(animal->entregoItem == false){
        dialogo = obtenerDialogo("respuestaP", animal->dialogos);
        printf("\n%s\n",dialogo);
        dialogo = obtenerDialogo("preguntaT", animal->dialogos);
        printf("\n%s\n",dialogo);

        char respuesta[254];
        printf("\nRespuesta: ");
        scanf(" %253[^\n]", respuesta);
        
        for (int i = 0; respuesta[i]; i++) {
          respuesta[i] = tolower(respuesta[i]);
        }

          if(strcmp(respuesta, obtenerDialogo("respuesta", animal->dialogos)) == 0){
            dialogo = obtenerDialogo("Acierto", animal->dialogos);
            printf("\n%s\n",dialogo);
  
  
            switch(animal->ID){
              case 1:
              jugador->item1 = true;
              break;
              case 2:
              jugador->item2 = true;
              break;
              case 3:
              jugador->item3 = true;
              break;
            }
              
            animal->entregoItem = true;
            printf("\nAqui lo tienes\n");
              
          }
          else{
            dialogo = obtenerDialogo("Equivocado", animal->dialogos);
            printf("\n%s\n", dialogo);
          }
          
        }
        else{
          printf("\nYa te entre el item\n");
        }
        break;
      case 4:
        dialogo = obtenerDialogo("robo", animal->dialogos);
        printf("\n%s\n",dialogo);
        
        switch(animal->ID){
          case 1:
          jugador->item1 = true;
          break;
          case 2:
          jugador->item2 = true;
          break;
          case 3:
          jugador->item3 = true;
          break;
        }

        animal->entregoItem = true;

        dialogo = obtenerDialogo("muerte", animal->dialogos);
        printf("\n%s\n",dialogo);

        jugador->moralidad++;
        animal->estado = false;
        return;

      case 5:
        dialogo = obtenerDialogo("despedida", animal->dialogos);
        printf("\n%s\n",dialogo);
        printf("\n");
        return;

      default:
        printf("\nNo existe esa opcion\n");
        break;
    }
      printf("\n");
    }while(1);
  }
  
  printf("\n");
  printf("\n...........\n");
  printf("Presiona Enter para continuar...");
  while (getchar() != '\n'); // Consumir cualquier entrada adicional
  getchar();
  return;
}

void imprimirMarco(const char *contenido) {
    int longitud = strlen(contenido);
    int longitudTotal = longitud + 42;
    int espaciosIzquierda = (longitudTotal - longitud) / 2;
    int espaciosDerecha = longitudTotal - longitud - espaciosIzquierda;

    // Asegurar que haya un número par de espacios a ambos lados
    if (espaciosIzquierda % 2 != 0) {
        espaciosIzquierda--;
        espaciosDerecha++;
    }

    // Imprimir borde superior
    printf("╔");
    for (int i = 0; i < longitudTotal; i++) {
        printf("═");
    }
    printf("╗\n");

    // Imprimir contenido centrado
    printf(" %*s%s%*s\n", espaciosIzquierda, "", contenido, espaciosDerecha, "");

    // Imprimir borde inferior
    printf("╚");
    for (int i = 0; i < longitudTotal; i++) {
        printf("═");
    }
    printf("╝\n");
}

char *obtenerDialogo(char *codigoDialogo, HashMap *mapaDialogos) {

  if (firstMap(mapaDialogos) == NULL) {
    printf("\nNo se encontraron dialogos\n");
    return NULL;
  }

  Pair *pairDialogo = searchMap(mapaDialogos, codigoDialogo);

  if (pairDialogo == NULL)
    return NULL;

  return (char *)pairDialogo->value;
}

void importarArchivo(List *listaZonas) {

  // Obtén el directorio actual
  char directorio_actual[256];

  // Se obtiene la direccion donde se encuentra el programa
  if (getcwd(directorio_actual, sizeof(directorio_actual)) == NULL) {
    perror("Error al obtener el directorio actual");
    return;
  }

  char ruta_completa[256];
  snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s/%s", directorio_actual,
           "data", "zonaA.txt");

  FILE *archivo = fopen(ruta_completa, "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return;
  }

  importar(listaZonas, archivo);

  fclose(archivo);
}

void guardarPartida(Zona *zonaActual, Jugador *jugador) {

  char directorio_actual[256];

  // Se obtiene la direccion donde se encuentra el programa
  if (getcwd(directorio_actual, sizeof(directorio_actual)) == NULL) {
    perror("Error al obtener el directorio actual");
    return;
  }

  char ruta_completa[256];
  snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s/%s", directorio_actual,
           "data", "save.txt");

  FILE *archivo = fopen(ruta_completa, "w");
  if (archivo == NULL) {
    perror("Error al crear el archivo");
    return;
  }

  fprintf(archivo, "%d,%d", zonaActual->ID, jugador->moralidad);

  printf("\nGuardado exitoso\n");
  printf("Presiona Enter para continuar...");
  while (getchar() != '\n'); // Consumir cualquier entrada adicional
  getchar();
  fclose(archivo);
}

void importar(List *listaZonas, FILE *archivo) {

  void *zonaNode = firstList(listaZonas);
  if (zonaNode == NULL) {
    printf("\nError a cargar\n");
    return;
  }

  Zona *zonaActual = (Zona *)zonaNode;

  char linea[256];

  int i = 1;
  printf("\n");
  while (fgets(linea, sizeof(linea), archivo) != NULL) {

    // Eliminar cualquier caracter de nueva línea de la cadena
    char *newline = strchr(linea, '\n');
    if (newline != NULL) {
      *newline = '\0';
    }

    if (strlen(linea) == 0) {
      continue; // Ignorar líneas vacías
    }

    // Hacer funcion para crear animal
    Animal *animal = (Animal *)malloc(sizeof(Animal));
    HashMap *mapaDialogos = createMap(DEFAULTTEXT);
    animal->segundaInteraccion = false;

    char *token;
    int tokenCount = 0;

    token = strtok(linea, ",");

    while (token != NULL) {
      switch (tokenCount) {
      case 0:
        animal->nombre = strdup(token);
        break;
      case 1:
        if (strcmp(token, "1") == 0) {
          animal->entregoItem = false;
        } else {
          animal->entregoItem = true;
        }
        break;
      case 2:
        if (strcmp(token, "0") == 0) {
          animal->estado = false;
        } else {
          animal->estado = true;
        }
        break;
      case 3:
        if (strcmp(token, "1") == 0) {
          animal->ID = 1;
        } else if(strcmp(token, "2") == 0) {
          animal->ID = 2;
        }
        else{
          animal->ID = 3;
        }
        break;
      }
      token = strtok(NULL, ",");
      tokenCount++;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL && linea[0] != '\n') {

      tokenCount = 0;

      token = strtok(linea, ";");

      char *clave;
      char *dialogo;

      while (token != NULL) {

        switch (tokenCount) {
        case 0:
          dialogo = strdup(token);
          break;
        case 1:
          clave = strdup(token);
          break;
        }

        token = strtok(NULL, ";");
        tokenCount++;
      }


      insertMap(mapaDialogos, strdup(clave), strdup(dialogo));
    }

    char cadena[5];
    sprintf(cadena, "%d", i++);
    char *claveAnimal = strdup(cadena);
    animal->dialogos = mapaDialogos;
    insertMap(zonaActual->animales, claveAnimal, animal);    
  }
}

void liberarMemoria(Zona* zona){
  
    Pair* pairAnimal = firstMap(zona->animales);
    if(pairAnimal == NULL){
      perror("\nError al liberar memoria\n");
      return;
    }

    while(pairAnimal != NULL){
        Animal* animal = (Animal*)pairAnimal->value;

        deleteMap(animal->dialogos);
        free(animal->nombre);

        pairAnimal = nextMap(zona->animales);
    }
  deleteMap(zona->animales);
  free(zona);
}
