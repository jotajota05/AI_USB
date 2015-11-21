Proyecto 1 - Busqueda Ciega - BFS, DFS, UCS, IDS.

Tamara Mendt - 05-38546
Juan Garcia - 05-38207

README

- Compilacion: ejecutar 'make'

- Corrida: ./8puzzle <Algoritmo> <Instancia> donde algorimo es {BFS,DFS,UCS,IDS} y una instancia es una secuencia de 9 numeros del 0 al 8


Detalles de implementacion:

- Nosotros usamos una tabla de Hash para revisar los estados que ya han sido expandidos, para asi no tener que expandirlos de nuevo, al
visitarlos nuevamente en el arbol.

- Realizamos el proyecto en C++, para poder aprovechar la rapidez y lo bajo nivel de C, pero usando las clases de C++.

- Tenemos un programa Principal que se llama 8puzzle.cpp, donde tememos las funciones principales para cada algoritmo, y el main.
Admas tenemos dos clases, Estado.cpp que es la representacion de un nodo o estado en el arbol del juego. LArepresentacion del Estado
se hace llevando una matriz de char 3 x 3 que representa el tablero, un char que lleva la posicion del cero actual, o donde esta
el espacio en balnco y un valor llamado suma, que nos permite realizar el calculo de la funcion Hash. En cambio la clase Camino.cpp 
lleva el camino que hemos recorrido y el ultimo Estado visitado en ese camino. Tiene un campo del tipo Estado, que es el ultimo visitado,
un char* que lleva las acciones llevadas, un entero que representa el costo, y la profucndidad del mismo.

- En el desarrollo del proyecto nos dimos cuenta, que para que el algoritmo de IDS fuera optimo, sacrificabamos mucho tiempo
de corrida, es decir, IDS optimo podia tardar muchisimo tiempo, en comparacion de la version rapida que no obtiene la solucion 
optima.
