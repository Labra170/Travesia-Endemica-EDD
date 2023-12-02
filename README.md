
# Proyecto Estructura de Datos - Travesia Endemica

**Descripcion**

La aplicacion es un pequeño juego en base de texto, donde eres un navegante que se cae del barco que viajaba y llega a la zona mas austral de Chile, y tiene la mision de volver al Peru para poder volver a casa

## Compilar y ejecutar codigo
### Desde Replit
* Abra su cuenta en repl.it (si no tiene cree una a través de su cuenta en github)
* En el home de repl.it busque la tarea y clónela para comenzar a trabajar, en caso de no encontrarla inserte `https://github.com/Labra170/Travesia-Endemica-EDD.git` donde le pide la URL 
* Seleccione el lenguaje (C)
* Una vez importado, escriba `gcc *.c -o main` para configurar la complacion
* Una vez guardado, presione el boton **Run** para probar el programa
### Desde sistema
---
* Descarge e instale [git](https://git-scm.com/downloads)
* Entre a `cmd` en su sistema
* Clone el repositorio con `git clone https://github.com/Labra170/Travesia-Endemica-EDD.git`
* Navege al directorio con `cd Travesia-Endemica-EDD`
* Compile el codigo con `gcc *.c -o programa`
* Ejecute la aplicacion con `/programa.exe`

`Advertencia - El programa cuenta con caracteres que talvez su sistema no soporte asi que se veran raros, NO ES UN ERROR, en replit se ven correctamente`

---
## Funciones

### Principales

**Funcionando correctamente**

* Iniciar el juego al importar los datos de los animales de un archivo
* Carga de una partida anterior
* La interaccion con la zona
* La interaccion con todos los animales que posee una zona
* El pasar de una zona a otra, en la cual se importa otro archivo hacia datos de animales
* La liberacion de memoria de los animales y zonas

**Con Problemas**
* No es un problema de una funcion exactamente sino un problema de calculo de la variable moralidad de la estructura jugador
`Suponemos que es porque al asignarse su memoria por alguna razon la variable se vuelve a asiganar un valor aleatorio`

### Secundarias

**Funcionando correctamente**

* Muestra de un menu con opciones
* Muesta de dialogos
* Inicializacion de zonas y animales

## Contribuciones

* Alonso Bravo: Implementacion de inicio, carga, pasar de zona y escritura de dialogos
* Bryan Pizarro: Implementacion de estructuras, varias las funciones del programa y testeo de la aplicacion
* Cristel Santibañez: Implementacion de estructuras, varias las funciones del programa, testeo de la aplicacion y escritura de introduccion y finales
* Ignacio Vera: Implementacion de diseño de codigo, pasar de zona y escritura de dialogos
