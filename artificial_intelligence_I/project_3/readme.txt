Proyecto 4 - Inteligencia Artificial

Juan Garcia	05-38207
Tamara Mendt	05-38546

Para cada parte del proyecto hay un programa escrito en python que resuelve el problema especificado. El nombre de los programas son sudoku.py, cardpuzzle.py y solitario.py. Para correr los programas es necesario especificar el nombre del archivo que contiene la instancia del problema. La extension de este archivo debe ser '.inst'. Los tres archivos son script's que llaman a los programas sudoku-cnf.py, cardpuzzle-cnf.py y solitario-cnf.py respectivamente. Estos programas, tambien escritos en python, traducen las instancias de cada problema a un problema de Satisfactibilidad, en formato cnf. En el directorio donde se decidan ejecutar los script debe existir un subdirectorio /cnf. En este subdirectorio se podran encontrar los archivos en formato cnf de cada instancia traducida. Luego de hacer la traduccion respectiva, cada script, ejecuta el sat solver zchaff al problema de satisfactibilidad e imprime la solucion al problema en pantalla. Para correr los script, es necesario que el ejecutable de zchaff se encuentre en el mismo directorio que los programas principales.

SUDOKU:

El programa sudoku.py recibe un archivo con la instancia sudoku que desea resolver. La salida de este programa es una secuencia de 81 caracteres donde el caracter i corresponde a la posicion (i/9, i mod 9) del tablero de sudoku.
La traduccion de sudoku a un problema de satisfactibilidad se realiza de la siguiente manera:

- 729 variables Xijk donde i representa una fila en el tablero sudoku, j representa una columna y k es el numero entre 1 y 9 que se encuentra en la casilla [i,j].

- 1ra restriccion: En cada casilla debe haber un numero del 1 al 9. Para cada casilla [i,j] se debe cumplir ( Xij1 \/ ... \/ Xij9 ). Estas restricciones generan 9*9 = 81 clausulas.

- 2da restriccion: En cada casilla puede haber solamente un numero. Para cada casilla [i,j] y para cada par de numeros [k,k'] entre 1 y 9 con k!=k' se debe cumplir:
( !Xijk \/ !Xijk' ). Estas restricciones generan 9*9*36 = 2916 clausulas.

- 3ra restriccion: Dos casillas distintas en una misma fila, columna o cuadrado, no pueden contener el mismo numero. Suponiendo que X1,X2,X3,X4,X5,X6,X7,X8,X9 representan las casillas de una fila, columna o cuadrado dado, se debe cumplir que
 ( !Xi \/ !Xj ) si i!=j. Para cada fila, columna y cuadrado se generan 2916 clausulas, en total se generan 8748 clausulas.

CARD PUZZLE:

El programa cardpuzzle.py recibe un archivo con la instancia inicial del problema. Si el problema no se puede resolver, la salida sera 0, mientras que si tiene solucion, la salida sera una secuencia de las tarjetas a utilizar. Si la tarjeta i se utiliza con la orientacion que se da en la entrada al programa, se imprime i. Si se usa al reves, se imprime -i. La traduccion utilizada fue la siguiente:

- k variables, donde k es el numero de tarjetas especificado en la entrada. Una instancia positiva de una variable representa la tarjeta con la orientacion especificada en la entrada. En cambio, una instancia negativa de una variable representa a la tarjeta con la orientacion contraria a aquella especificada en la entrada.

- Cada clausula corresponde a un hueco de la tarjeta, de modo que si hay i huecos en cada columna, el numero de clausulas es 2*i. 

- Para cada carta, si el hueco r de la columna s esta 'tapado', es decir, no hay hueco, entonces la clausula que corresponde a ese hueco tendra una instancia de esa variable. De igual manera, la claúsula que corresponde al hueco r en la columna contraria, tendra una instancia de la variable negada (esto es porque al voltear la tarjeta, las columnas se intercambian). Se quiere lograr que todos los huecos queden tapados al final.

SOLITARIO:

El programa solitario.py recibe un archivo con la instancia inicial del problema. La salida del programa es 1 si tiene solucion y 0 en el caso contrario. La traduccion utilizada fue la siguiente:
- m^3 variables Xijk, siendo m la dimension del tablero. i representa una fila en el tablero de metras, j representa una columna y k representa el contenido de la casilla. Si k es igual a 1, la casilla no contiene nada, si es igual a 2, la casilla tiene una metra azul y finalmente, si es igual a 3, la casilla contiene una metra roja.

-1ra restriccion: En cada casilla debe haber ninguna metra, una metra azul o una metra roja. Para cada casilla [i,j] se debe cumplir 
(Xij1 \/ Xij2 \/ Xij3). Estas restricciones generan m*m = m^2 clausulas.

-2da restriccion: En cada casilla solamente puede haber una metra de un color o ninguna metra. Para cada casilla [i,j] y para cada par de numeros [k,k'] entre 1 y 3 con k!=k' se debe cumplir:
( !Xijk \/ !Xijk' ). Estas restricciones generan m*m*3 = m^2*3 clausulas.

-3ra restriccion: No pueden haber filas vacias. Para cada fila se cumple que alguna de las casillas debe ser no vacia. Para cada fila se cumple:
( !X1j1 \/ !X2j1 \/ ... \/ !Xmj1)

-Restricciones que dependen de la instancia de entrada: 
	- Para cada fila se debe cumplir que al menor una de las metras que estan en la instancia original de esa fila debe permanecer ahi. Para cada fila se crea una clausula tal que cada metra en la instancia inicial de la fila debe estar representada en la fila.
	- Para cada columna se debe cumplir que no pueden haber metras de colores diferentes. Para cada columna se crean a*r clausulas donde a es el numero de metras azules en la instancia original de la columna y r es el numero de metras azules en la instancia original de la columna. Cada clausula se forma de la siguiente manera : (!Xij2 \/ !Xi'j3).
	- Para cada casilla vacia en la instancia original del problema se instancia la variable correspondiente a esa casilla con contenido metra vacia, es decir, se crea una claúsula unitaria. Esto es porque si una casilla es vacia al principio del problema, no puede cambiar esa condicion y se hace para detectar cuando existan filas completamente vacias, en cuyo caso el problema no tiene solucion.


