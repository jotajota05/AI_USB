README 

Proyecto 3 - Busqueda Local - Hill Climbing / Simulated Anneling / Algoritmo Genetico
Inteligencia Artificial - Abril Julio 2009

Juan Garcia	05-38207
Tamara Mendt	05-38546

NOTA IMPORTANTE!! El proyecto fue desarrollado bajo una Arquitectura 64 bits (Arch Linux X86_64)

En este proyecto se implementaron tres algoritmos de busqueda local. El objetivo era encontrar el maximo valor de una funcion
de R^10 a R, y con un valor maximo de 10. Los Algoritmos implementados fueron Hill-Climbing, Simulated-Anneling y un Algoritmo 
gentico. Para compilar el programa solo debera ejecutar en el terminal 'make', parado en el directorio donde se encuentren los
archivos. Y para correr, se ejecuta el comando 'sh run.sh'. Estos dos comandos son facilidades agregadas, ya que los verdaderos
comandos de compilacion son un poco complicados.
(COMPILACION: gcc -lm -L. -lfia1 localsearch.c -o localsearch EJECUCION: LD_LIBRARY_PATH=. ./localSearch )

Los Algoritmos de Hill-Climbing y Simulated-Anneling tienen similitudes entre ellos. Los dos necesitan de un punto inicial
donde evaluar la funcion, y desde alli comenzar la corrida. Al comienzo se genera un vector aleatorio y se le pasa a los dos 
algoritmos para que ejecuten. En general el vector aleatorio evalua la funcion en valores negativos, aunque podria ajustarse
la solucion inicial a que diera una evaluacion mayor que cero, aunque esto podria hacer que el algoritmo no pueda hallar un
camino mas facil hacia la solucion maxima.

En cuanto a la generacion de vecindades, para Hill-CLimbing simplemente se generan los vecinos sumandole o restandole a una componente
del vector actual un alfa generado aleatoriamente, y de los maximo 20 vecinos que se generan me movere para el mejor, en caso de que
exista. Para Simulated-Anneling se genera un sucesor a partir de una posicion randon en el vector, al cual aleatoriamente se le sumara
o restara un alfa elegido aletoriamente tambien. Y si el mismo es mejor que donde estoy, me muevo hacia el, si no lo es, me movere
dependiendo de una probabilidad establecida.

El algoritmo genetico se basa en 6 etapas, primero se genera la poblacion aleatoriamente, luego se seleccionaran aquellos que 
poseen mejor funcion de evaluacion, y se dividira el grupo en dos, los buenos y los malos. A partir de aqui viene la reproduccion, en donde basado
en una probabilidad, los buenos se cruzaran con buenos, medios o malos, y asi general una nueva poblacion hija. Despues estos nuevos
hijos pasaran por un proceso de mutacion que deberia hacerlos mejores, para finalmente repoblar la poblacion inicial, sustituyendo a
los menos aptos. Luego de esto se procede a obtener nuevas poblaciones mas evolucionadas que la anterior, hasta encontrar un individuo maximo.

Realizamos una gran cantidad de corridas a los algorimos y estos fueron los mejores resultados obtenidos.

MEJORES RESULTADOS OBTENIDOS DE TODAS LAS CORRIDAS REALIZADAS:

///////////////////////////////
///////HILL CLIMBING//////////
//////////////////////////////


Ubicacion del Inicial para Hill-Climbing y Simulated-Anneling: 0.9667721037 0.4867202761 0.6081240857 -0.6851219926 0.5724543808 0.2038417272 0.3015555711 0.6976890797 -0.5646829437 0.4447965436 
Evaluacion Nodo Inicial: -65.1047338846

Ubicacion del Maximo:  -0.6022278963 0.8867202761 -0.3638759143 -0.6851219926 -0.6815456192 -0.6301582728 0.3015555711 -0.1663109203 -0.5646829437 -0.1622034564 
Maximo - Hill Climbing = 9.4264250359
Numero de llamadas a la funcion objetivo = 1839
Tiempo de ejecucion Hill-Clibing: 0.003338 segundo(s)

///////////////////////////////////////////////////////////////

Ubicacion del Inicial para Hill-Climbing y Simulated-Anneling: -0.3310768045 0.9373320416 -0.2712673172 -0.9059037250 -0.7330895346 -0.9996446036 0.4740730748 0.3053272367 -0.8543009348 -0.2123636976 
Evaluacion Nodo Inicial: 2.5210525396

Ubicacion del Maximo:  -0.5550768045 0.9373320416 -0.2712673172 -0.6099037250 -0.6280895346 -0.6846446036 0.2340730748 -0.2866727633 -0.6133009348 -0.2433636976 
Maximo - Hill Climbing = 9.3562332301
Numero de llamadas a la funcion objetivo = 1621
Tiempo de ejecucion Hill-Clibing: 0.003005 segundo(s)


//////////////////////////////////
///////SIMULATED ANNELING////////
////////////////////////////////


Ubicacion del Inicial para Hill-Climbing y Simulated-Anneling: 0.6321212575 -0.7899725335 0.7116370583 0.3710595220 -0.9791388186 0.2653450761 0.5882552648 0.8668508194 -0.3594887648 0.8799223946 
Evaluacion Nodo Inicial: -100.5518570971

Ubicacion del Maximo:  -0.6198787425 0.9590274665 -0.2943629417 -0.5649404780 -0.7301388186 -0.7666549239 0.4522552648 -0.1821491806 -0.5084887648 -0.2240776054 
Maximo - Simulated Anneling = 9.6827388047
Numero de llamadas a la funcion objetivo = 12620
Tiempo de ejecucion Simulated-Anneling: 7.137009 segundo(s)

////////////////////////////////////////////////////////////////

Ubicacion del Inicial para Hill-Climbing y Simulated-Anneling: -0.8607100146 -0.2019776441 -0.0084754266 -0.8489892837 0.9353346843 -0.7195390305 -0.8301766310 -0.4112172592 0.8352179704 -0.5292513557 
Evaluacion Nodo Inicial: -70.4677788173

Ubicacion del Maximo:  -0.4697100146 0.8640223559 -0.2784754266 -0.6449892837 -0.6886653157 -0.7775390305 0.3068233690 -0.1582172592 -0.5197820296 -0.2652513557 
Maximo - Simulated Anneling = 9.7009260096
Numero de llamadas a la funcion objetivo = 12605
Tiempo de ejecucion Simulated-Anneling: 7.097930 segundo(s)


/////////////////////////////////////
///////ALGORITMO GENETICO///////////
////////////////////////////////////


Ubicacion del Maximo:  -0.5838381496 0.8722465210 -0.2276109785 -0.6743057522 -0.6454981788 -0.7453817527 0.4216641773 -0.1478054684 -0.4871869261 -0.1949351719 
Maximo - Algoritmo Genetico = 9.8181460836
Numero de llamadas a la funcion objetivo = 590770
Tiempo de ejecucion Alg-Genetico: 1.053758 segundo(s)

/////////////////////////////////////////////////////////

Ubicacion del Maximo:  -0.5833089439 0.8892182812 -0.3008583974 -0.6950472405 -0.6782639309 -0.7617488314 0.3157956706 -0.1610840820 -0.5130579302 -0.1231111626 
Maximo - Algoritmo Genetico = 9.7407736967
Numero de llamadas a la funcion objetivo = 501196
Tiempo de ejecucion Alg-Genetico: 0.935178 segundo(s)
