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

  mostrarIntroduccion(); // Llamado a función mostrarIntroduccion

  do {
    printf("\e[1;1H\e[2J"); // Se borra la consola.

    // Impresión del menú dentro del juego
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

    switch (opcion) { // Dependiendo de la opción elegida
    case 1:
    case 2:
    case 3:
      interaccionAnimal(opcionSTR, zonaActual,jugador); // Se interactua con el animal, usando el número de la opción como identificador del animal a utilizar.
      break;
    case 4: // Cuando se intente pasar a la siguiente zona
      if(jugador->item1 != true || jugador->item2 != true || jugador->item3 != true){ // Si el jugador no ha conseguido todos los items (1, 2, 3), se muestra que no podrá avanzar de zona.
        printf("\nNo tienes todos los items para pasar de zona\n");
        printf("Presiona Enter para continuar...");
        while (getchar() != '\n'); // Consumir cualquier entrada adicional
        getchar();
        break;
      }
      printf("\nPasando de zona\n"); // En caso contrario, se avanza a la siguiente zona
      printf("Presiona Enter para continuar...");
      while (getchar() != '\n'); // Consumir cualquier entrada adicional
      getchar();
      pasarZona(jugador,listaZonas); // Llamado a función pasarZona
      zonaActual = firstList(listaZonas); // Se actualiza la zona
      break;
    case 5:
      guardarPartida(zonaActual, jugador); // Llamado a función guardarPartida
      break;
    case 6:
      printf("\nHasta la próxima!\n"); // En caso de salir del juego
      return;
    default: // Cuando no se ingrese una opción dentro de las disponiblas
      printf("Opción no válida");
      break;
    }
  } while (1);
}

void pasarZona(Jugador* jugador, List* listaZonas){ // Función para pasar a la siguiente zona

  jugador->item1 = false; // Se reestablece el estado de los items del jugador
  jugador->item2 = false; // ...
  jugador->item3 = false; // ...


  Zona* zonaBorrar = (Zona*)popFront(listaZonas); // Se borra la primera zona de la lista
  liberarMemoria(zonaBorrar); // Se libera la memoria de la zona

  Zona* zona = (Zona*)firstList(listaZonas); // Se actualiza a la siguiente zona en la lista

  if(zona == NULL){ // Si no hay siguiente zona
    mostrarFinal(jugador->moralidad); // Se muestra el final dependiendo de la moralidad (Ver función mostrarFinal)
    printf("\e[1;1H\e[2J"); // Se borra la consola
    printf("\n\nMUCHAS GRACIAS POR JUGAR NUESTRO JUEGO\n\n");
    printf("Presiona Enter para salir del juego...");
    while (getchar() != '\n'); // Consumir cualquier entrada adicional
    getchar();
    abort(); // Finaliza el programa
  }

  
  char directorio_actual[256];

  // Se obtiene la direccion donde se encuentra el programa
  if (getcwd(directorio_actual, sizeof(directorio_actual)) == NULL) {
    perror("Error al obtener el directorio actual");
    return;
  }

  char ruta_completa[256];

  switch(zona->ID){ // En caso de la zona a la que se avance
    case 2: // Se usa la zona 2,
    snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s/%s", directorio_actual,
       "data", "zonaB.txt");
    break;
    case 3: // O zona 3
    snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s/%s", directorio_actual,
       "data", "zonaC.txt");
    break;
  }

  FILE *archivo = fopen(ruta_completa, "r"); // Se abre el archivo en modo lectura
  if (archivo == NULL) { // Si no se pudo abrir el archivo
    perror("Error al abrir el archivo");
    return;
  }

  importar(listaZonas, archivo); // Se importan la zona nuevamente

  fclose(archivo); // Se cierra el archivo
}

void interaccionAnimal(char* opcionSTR, Zona *zonaActual, Jugador* jugador) { // Función para interactuar con los animales dentro del juego
  
  int opcion;
  Pair *pairAnimal = searchMap(zonaActual->animales, opcionSTR); //opcionSTR;
  if (pairAnimal == NULL)
    return;
  Animal *animal = (Animal *)pairAnimal->value;

  if(animal->estado == true){ // Si el estado de animal es true (vivo)
  
  char *dialogo = NULL;

  int longitud = strlen(animal->nombre);
    int espacios = (43 - longitud) / 2;

    do{

    imprimirMarco(animal->nombre); // Se imprime el animal con su marco correspondiente al largo del nombre
    
  if (animal->segundaInteraccion == false) { // Si es la primera vez que hablas con el animal
    dialogo = obtenerDialogo("saludo1", animal->dialogos); // Se extrae la primera opción de saludo
    if (dialogo == NULL) return;
    printf("\n%s\n", dialogo); // Se imprime el texto
    animal->segundaInteraccion = true; // Se establece que cualquier otra interacción será la segunda.
  }
  else { // Si no es la primera vez que hablas con el animal
    dialogo = obtenerDialogo("saludo2", animal->dialogos); // Se utiliza el segundo saludo
    if (dialogo == NULL) return;
    printf("\n%s\n", dialogo); // Se imprime el texto
  }

    printf("\n\n"); // Se usa el menú para las interacciones con los animales
    printf("1.- Preguntar sobre el animal\n");
    printf("2.- Preguntar  sobre la zona\n");
    printf("3.- Pregunta por #Parte de mapa de zona %d#\n", zonaActual->ID);
    printf("4.- Robar objeto\n");
    printf("5.- Salir al mapa\n");
    printf("Opcion: ");
    scanf(" %d", &opcion); // Se lee la opción a utilizar

    switch(opcion){ // Dependiendo de la opción elegida

      case 1:
        dialogo = obtenerDialogo("datoAnimal", animal->dialogos); // Se usa el dialogo correspondiente.
        printf("\n%s\n",dialogo);
        break;
      case 2:
        dialogo = obtenerDialogo("datoZona", animal->dialogos); // Se usa el dialogo correspondiente.
        printf("\n%s\n",dialogo);
        break;
      case 3:
        if(animal->entregoItem == false){ // Si el animal no ha dado el ítem al jugador
        dialogo = obtenerDialogo("respuestaP", animal->dialogos); // Se usa el dialogo correspondiente.
        printf("\n%s\n",dialogo);
        dialogo = obtenerDialogo("preguntaT", animal->dialogos); // Se usa el dialogo correspondiente.
        printf("\n%s\n",dialogo);

        char respuesta[254];
        printf("\nRespuesta: "); // La respuesta del jugador
        scanf(" %253[^\n]", respuesta); // Se lee la respuesta del jugador
        
        for (int i = 0; respuesta[i]; i++) { // Se convierte la respuesta del jugador a minúsculas
          respuesta[i] = tolower(respuesta[i]);
        }

          if(strcmp(respuesta, obtenerDialogo("respuesta", animal->dialogos)) == 0){ // Se compara la respuesta dada con la correcta, si son iguales:
            dialogo = obtenerDialogo("Acierto", animal->dialogos); // Se utiliza el dialogo correspondiente
            printf("\n%s\n",dialogo);
  
  
            switch(animal->ID){ // Dependiendo de la ID del animal
              case 1:
              jugador->item1 = true; // Se actualiza el item asociado al ID
              break;
              case 2:
              jugador->item2 = true; // ...
              break;
              case 3:
              jugador->item3 = true; // ...
              break;
            }
              
            animal->entregoItem = true; // Se actualiza el estado del animal en la cat. de estado del ítem
            printf("\nAqui lo tienes\n");
              
          }
          else{ // Si la respuesta es incorrecta:
            dialogo = obtenerDialogo("Equivocado", animal->dialogos); // Se utiliza el diálogo correspondiente
            printf("\n%s\n", dialogo);
          }
          
        }
        else{ // Si el estado del ítem, es ya entregado...
          printf("\nYa te entregué el ítem\n");
        }
        break;
      case 4: // En el caso de querer robar el ítem
        dialogo = obtenerDialogo("robo", animal->dialogos); // Se utiliza el diálogo correspondiente
        printf("\n%s\n",dialogo);
        
        switch(animal->ID){ // Se utiliza el ID del animal para asociar al ítem dentro del inventario del jugador
          case 1:
          jugador->item1 = true; // Se establece en verdadero
          break;
          case 2:
          jugador->item2 = true; // ...
          break;
          case 3:
          jugador->item3 = true; // ...
          break;
        }

        animal->entregoItem = true; // Se establece que entregó el ítem

        dialogo = obtenerDialogo("muerte", animal->dialogos); // Se utiliza el diálogo por haber matado al animal
        printf("\n%s\n",dialogo);

        jugador->moralidad++; // Se sube la moralidad del jugador
        animal->estado = false; // Se establece el estado del animal en false (muerto)
        return;

      case 5: // Te despides del animal
        dialogo = obtenerDialogo("despedida", animal->dialogos);
        printf("\n%s\n",dialogo);
        printf("\n");
        return;

      default: // Cuando no se ingrese una opción disponible
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

void imprimirMarco(const char *contenido) { // Función para imprimir el marco
    int longitud = strlen(contenido); // La longitud del marco, en base al largo del texto a utilizar dentro.
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

char *obtenerDialogo(char *codigoDialogo, HashMap *mapaDialogos) { // Función para extraer los diálogos del mapa

  if (firstMap(mapaDialogos) == NULL) { // Si el mapa no se creó correctamente
    printf("\nNo se encontraron dialogos\n");
    return NULL;
  }

  Pair *pairDialogo = searchMap(mapaDialogos, codigoDialogo); // Se busca en el mapa con la clave a utilizar

  if (pairDialogo == NULL) // Si no se encontró con la clave.
    return NULL;

  return (char *)pairDialogo->value; // Se regresa el texto a utilizar
}

void importarArchivo(List *listaZonas) { // Función para importar un archivo

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

  FILE *archivo = fopen(ruta_completa, "r"); // Se abre el archivo en modo lectura
  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return;
  }

  importar(listaZonas, archivo); // Se importan las zonas

  fclose(archivo); // Se cierra el archivo
}

void guardarPartida(Zona *zonaActual, Jugador *jugador) { // Función para guardar partida

  char directorio_actual[256];

  // Se obtiene la direccion donde se encuentra el programa
  if (getcwd(directorio_actual, sizeof(directorio_actual)) == NULL) {
    perror("Error al obtener el directorio actual");
    return;
  }

  char ruta_completa[256];
  snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s/%s", directorio_actual,
           "data", "save.txt");

  FILE *archivo = fopen(ruta_completa, "w"); // Se abre el archivo en modo escritura
  if (archivo == NULL) {
    perror("Error al crear el archivo");
    return;
  }

  fprintf(archivo, "%d,%d", zonaActual->ID, jugador->moralidad); // Dentro del archivo se guarda, la zona en la que está el jugador y su moralidad

  printf("\nGuardado exitoso\n");
  printf("Presiona Enter para continuar...");
  while (getchar() != '\n'); // Consumir cualquier entrada adicional
  getchar();
  fclose(archivo); // Se cierra el archivo
}

void importar(List *listaZonas, FILE *archivo) { // Función de importación

  void *zonaNode = firstList(listaZonas); // Nodo auxiliar al primer nodo de la lista
  if (zonaNode == NULL) {
    printf("\nError a cargar\n");
    return;
  }

  Zona *zonaActual = (Zona *)zonaNode; // Se establece el nodo auxiliar a un nodo actual (temporal)

  char linea[256];

  int i = 1;
  printf("\n");
  while (fgets(linea, sizeof(linea), archivo) != NULL) { // Se avanza linea por linea en el archivo

    // Eliminar cualquier caracter de nueva línea de la cadena
    char *newline = strchr(linea, '\n');
    if (newline != NULL) {
      *newline = '\0';
    }

    if (strlen(linea) == 0) {
      continue; // Ignorar líneas vacías
    }

    // Hacer funcion para crear animal
    Animal *animal = (Animal *)malloc(sizeof(Animal)); // Se asigna memoria al animal
    HashMap *mapaDialogos = createMap(DEFAULTTEXT); // Se crea el mapa para los diálogos
    animal->segundaInteraccion = false; // Se establece que el animal no ha hecho la segunda interacción

    char *token;
    int tokenCount = 0;

    token = strtok(linea, ","); // Se establece un token usando la coma como separador

    while (token != NULL) { // Mientras todavía haya texto para avanzar.
      switch (tokenCount) { // Dependiendo del contador del token
      case 0: // En 0, es el nombre del animal
        animal->nombre = strdup(token);
        break;
      case 1: // 1: Estado de la entrega del ítem en el animal
        if (strcmp(token, "1") == 0) {
          animal->entregoItem = false;
        } else {
          animal->entregoItem = true;
        }
        break;
      case 2: // 2: Estado del animal
        if (strcmp(token, "0") == 0) {
          animal->estado = false;
        } else {
          animal->estado = true;
        }
        break;
      case 3: // 3: ID del animal
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
      token = strtok(NULL, ","); // Se avanza al siguiente token
      tokenCount++; // Se aumenta el contador del token
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL && linea[0] != '\n') { // Mientras haya texto

      tokenCount = 0; // Contador del token

      token = strtok(linea, ";"); // Se utiliza el ';' como separador

      char *clave; // key
      char *dialogo; // value

      while (token != NULL) { // Mientras haya token's para avanzar

        switch (tokenCount) { // Dependiendo del contador
        case 0: // 0: El dialogo
          dialogo = strdup(token);
          break;
        case 1: // 1: La clave a utilizar en el mapa
          clave = strdup(token);
          break;
        }

        token = strtok(NULL, ";"); // Se avanza al siguiente token
        tokenCount++; // Se aumenta el contador
      }


      insertMap(mapaDialogos, strdup(clave), strdup(dialogo)); // Se inserta al mapa.
    }

    char cadena[5];
    sprintf(cadena, "%d", i++);
    char *claveAnimal = strdup(cadena);
    animal->dialogos = mapaDialogos; // Al animal se le asigna el mapa correspondiente
    insertMap(zonaActual->animales, claveAnimal, animal); // Se inserta el animal al mapa de animales de la zona.
  }
}

void liberarMemoria(Zona* zona){ // Función para liberar memoria
  
    Pair* pairAnimal = firstMap(zona->animales); // Pair temporal a la primera casilla (ocupada) del mapa de animales
    if(pairAnimal == NULL){ // Si no se pudo ir a la primera casilla (ocupada)
      perror("\nError al liberar memoria\n");
      return;
    }

    while(pairAnimal != NULL){ // Mientras el pair temporal sea distinto a NULL
        Animal* animal = (Animal*)pairAnimal->value; // Se crea otra auxiliar para el "value" del animal

        deleteMap(animal->dialogos); // Se borra el dialogo del animal
        free(animal->nombre); // Se libera el nombre del animal

        pairAnimal = nextMap(zona->animales); // Se avanza a la siguiente casilla ocupada
    }
  deleteMap(zona->animales); // Se borra el mapa de animales dentro de la zona
  free(zona); // Se libera la zona.
}
