Proyecto 5 - Satisfaccion de restricciones - Cripto Aritmetica y N-Reinas

Juan Garcia - 05-38207
Tamara Mendt - 05-38546

README

N-REINAS:

Para correr el n-reinas debera correr en una consola: 'python nreinas.py <num_reinas>' indicando el numero de reinas a colocar, es decir
el tamano del tablero.

Detalles de implementacion:

- Para representar el tablero se utilizo una matriz n x n, donde 'n' es el numero de reinas a colocar. Cada variable, o posicion
de la matriz puede tomar tres valores, '-1' si no ha sido asignado, '0' si no puede ser asignado y '1' si esta asignado a una reina.

- Para tomar la desicion se trabaja por filas, se ingresa a el estado inicial del tablero vacio, y a partir de la primera fila,
se van asignando las variables, generando todos las posibles soluciones parciales. Y luego de asignar una variable en una fila,
se actualiza el domino de las siguientes variables en la demas filas. Esto permite ir asignando las variables, y actualizando
el domino de las siguientes, de esta manera resolver el problema por medio de forward checking.

- Al final se genera un arbol de soluciones, en donde las hojas del arbol seran las soluciones encontradas. Mientras se va generando
el arbol, se van tomando las soluciones. El recorrido se hace, haciendo DFS.

Observaciones:

- El algoritmo siempre encuentra todas las soluciones existentes para un numero de reinas, y el tiempo es bastante rapido, para
valores menores a 12 reinas. A partir de las 12 reinas el algoritmo tarda un tiempo considerable en conseguir las soluciones.
Python es un lenguaje que permite programar muy rapidamente, pero no es tan rapido como puede serlo C o C++, lenguajes mas
cercanos al bajo nivel.

- Mientras mas grande sea el numero de reinas, mayor es la cantidad de soluciones, el crecimiento es bastante rapido, por
lo tanto el arbol que se genera es muy grande y mas lento el procesamiento del msimo.  
