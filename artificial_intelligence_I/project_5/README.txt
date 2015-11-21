Proyecto 7 - STRIPS - Random Blocks

Juan Garcia - 05-38207
Tamara Mendt - 05-38546

README

Ejecucion del programa: python random_blocks.py <num_bloques> <num_acciones> (Se realizo en Python)

Este proyecto que implementamos genera un estado inicial aleatorio del problema de los random blocks. Usando STRIPS, se modelan
los diferentes predicados:

- on(X,Y) = el objeto X esta sobre el objeto Y
- clear(X) = el objeto X esta libre
- on_table(X) = el objeto X esta en la mesa

Y ademas se definen las siguientes acciones, con sus precondiciones y efectos:

- move_from_table(X,Y) = mover X, que esta sobre la mesa, sobre Y que esta libre.

  Pre: clear(X) , clear(Y) , X!=Y , on_table(X)
  Effect: !clear(Y) , on(X,Y) , !on_table(X)

- move_to_table(X,Y) = mover el bloque X, que esta sobre Y, a la mesa

  Pre: clear(X) , on(X,Y)
  Effect: clear(Y) , on_table(X) , !on(X,Y)

- move(X,Y,Z) = mover el bloque X, que esta sobre el bloque Y, a encima del bloque Z

  Pre: on(X,Y) , clear(X) , clear(Z) , X!=Y , X!=Z , Z!=Y , Z!=Mesa
  Effect: clear(Y) , !clear(Z) , on(X,Z) , !on(X,Y)

Luego de generar el estado aleatorio, se le aplican a los <bloques> un numero pre-establecido de acciones, en la llamada del programa, y
estas son aplicadas aleatoriamente, hasta conseguir un estado final, que sera nuestro estado objetivo para el planner FF.

Detalles de implementacion:

- Se evitaron los ciclos de un paso, es decir que al hacer una accion hacia adelante, inmediatamente despues se realice la
accion contraria que llevara al estado anterior. Para ello, en cada iteracion se guarda la accion inversa a la que se aplico
actualmente, para que en la proxima iteracion se compare y no se realice la misma. Por ejemplo, si se realiza la accion
move_to_table(3,5), se guarda la accion move_from_table(3,5), para que en la siguiente iteracion no se regrese al mismo estado.

- Al principio se disponen todos los bloques en la mesa, y se realizan 10 acciones aleatorias, para generar un estado inicial,
para nuestro problema, y para comenzar a generar el numero de acciones pre-establecidas.

    En general la gama de acciones que se pueden realizarse en un estado del problema de bloques, depende proporcionalmente del numero
de bloques del que dispongamos, no tanto de la cantidad de acciones aleatorias que podamos realiarle al estado inicial, para
llegar al estado objetivo, ya que de seguro existiran mejores soluciones, y en numero considerablemente menor de pasos en que
se podra llegar al estado objetivo.

Experimentos Realizados:

####### 1 ########

Numero de Bloques: 5
[ Numero de Acciones aleatorias ==> Numero de acciones generadas por el Planner FF ] :
[ 5 ==> 3 ] , [ 10 ==> 2 ] , [ 20 ==> 5 ] , [ 50 ==> 5 ] , [ 100 ==> 2 ]

####### 2 ########

Numero de Bloques: 10
[ Numero de Acciones aleatorias ==> Numero de acciones generadas por el Planner FF ] :
[ 5 ==> 4 ] , [ 10 ==> 5 ] , [ 20 ==> 6 ] , [ 50 ==> 9 ] , [ 100 ==> 14]

####### 3 ########

Numero de Bloques: 20
[ Numero de Acciones aleatorias ==> Numero de acciones generadas por el Planner FF ] :
[ 5 ==> 5 ] , [ 10 ==> 8 ] , [ 20 ==> 8 ] , [ 50 ==> 15 ] , [ 100 ==> 16]

####### 4 ########

Numero de Bloques: 50
[ Numero de Acciones aleatorias ==> Numero de acciones generadas por el Planner FF ] :
[ 5 ==> 5 ] , [ 10 ==> 10 ] , [ 20 ==> 19 ] , [ 50 ==> 30 ] , [ 100 ==> 34 ]

####### 5 ########

Numero de Bloques: 100
[ Numero de Acciones aleatorias ==> Numero de acciones generadas por el Planner FF ] :
[ 5 ==> 5 ] , [ 10 ==> 10 ] , [ 20 ==> 20 ] , [ 50 ==> 48 ] , [ 100 ==> 64 ]

En general, los resultados que arrojo el planner FF fueron los esperados. Basicamente si colocamos un numero pequeno de bloques,
por mas acciones aleatorias que apliquemos, siempre el planner lo resolvera en pocos pasos, debido a que la gama de estados disponibles
con pocos bloques es reducida. Entonces asi se hagan miles de acciones random, en el proceso, muchas veces se repetira el estado objetivo, y esto lo encuentra mucho mas rapido el planner.

Ya para un numero mas grande de bloques, los resultados del planner se vuelven mas consistentes con el numero de acciones aleatorias
que generamos. Debido a que como son mas bloques, poseemos mas estados y acciones que visitar y realizar, por lo tanto no es tan rapido
que el planner encuentre una solucion, acercandose considerablemente al resultado mas cercano al numero de acciones random que generamos.
