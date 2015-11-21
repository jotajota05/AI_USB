/*
  Proyecto 3 - Busqueda Local

  Juan Garcia 05-38207
  Tamara Mendt 05-38546

  Compilar con: gcc -lm -L. -lfia1 localSearch.c -o localSearch
  Correr con: LD_LIBRARY_PATH=. ./localSearch
*/

#include <stdio.h>
#include <stdlib.h>
#include "ia1.h"

int llamadas;

/////////////////////////////////////////////////////////////////
//////////////////// FUNCIONES UTILES ///////////////////////////
/////////////////////////////////////////////////////////////////

inline double evaluar(double x[10]){
  int r;
  double z;
  llamadas++;
  if ( (r = ia1("0538207", x, &z)) ){
    fprintf(stderr, "hubo un error: %d\n", r);
    exit(EXIT_FAILURE);
  }
  return z;
}

int compare (const void * a, const void * b) {
  return (int)( *(double*)b - *(double*)a );
}

void copiar_vector(int leng, double a[leng], double b[leng]) {
  int i;
  for ( i = 0 ; i < leng ; i++ ) a[i] = b[i];
}

void copiar_matriz(double a[20][10], double b[20][10]) {
  int i, j;
  for ( i = 0 ; i < 20 ; i++ )
    for ( j = 0 ; j < 10 ; j++ ) 
      a[i][j] = b[i][j];

}

double *vector_aleatorio() {
  int j;
  double *aux, num;
  aux = (double *)malloc(sizeof(double)*10);
  while (evaluar(aux) < 1) {
    for ( j = 0 ; j < 10 ; j++ ) {
      num = (double)(random())/RAND_MAX;
      num = num*2 -1;
      aux[j] = num;
    }
  }
  return aux;
}

double expo(double exponente) {
  double i = 0.0;
  double result = 1.0;
  double result_aux = 1.0;
  int flag = 0;
  if (exponente < 0.0) {
    flag = 1;
    exponente *= -1.0;
  } 
  while (i < exponente) {
    result_aux = result_aux*2.71828183;
    i += 1.0;
  }
  if (flag) result = 1.0 / result_aux;
  else return result_aux;
  return result;
}

/////////////////////////////////////////////////////////////////
///////////////////////// HILL - CLIMBING ///////////////////////
/////////////////////////////////////////////////////////////////

double **sucesores_hill(double x[10],double alfa) {
  double **sucesores = (double* *)malloc(sizeof(double *)*20);
  double aux[10];
  double **aux_suc = (double* *)malloc(sizeof(double *)*20);
  int i, j, k;
  aux_suc = sucesores;
  for ( i = 0 ; i < 20 ; i++ ) {
    copiar_vector(10,aux,x);
    j = i / 2;
    *sucesores = (double *)malloc(sizeof(double)*10);
    if (i % 2) {
      aux[j] = x[j] - alfa;
      if (aux[j] < -1) {
	*sucesores = NULL;
	continue;
      }
      else copiar_vector(10,*sucesores,aux);
    } else {
      aux[j] = x[j] + alfa;
      if (aux[j] > 1) {
	*sucesores = NULL;
	continue;
      }
      else copiar_vector(10,*sucesores,aux);
    }
    sucesores++;  
  }
  sucesores = aux_suc;
  return sucesores;
}

double hill_climbing(double nodo_inicial[10]) {
  int i, j;
  int  k = 0;
  double **vecinos;
  double  alfa = ((double)(rand() % 1000)) / 1000;
  double nodo_actual[10], nodo_prox[10];
  double prox_eval = -100000;
  
  copiar_vector(10,nodo_actual,nodo_inicial);

  srand(time(0));

  while ( k < 100) {
    
    vecinos = sucesores_hill(nodo_actual,alfa);
    i = 0;

    for ( i = 0 ; i < 20 ; i++ ) {
      if (vecinos[i] == NULL) continue;
      if ( evaluar(vecinos[i]) > prox_eval ) {
	copiar_vector(10,nodo_prox,vecinos[i]);
	prox_eval = evaluar(vecinos[i]);
      }
    }

    if (prox_eval <= evaluar(nodo_actual)) {
      alfa = ((double)(rand() % 1000)) / 1000;
    } else copiar_vector(10,nodo_actual,nodo_prox);
    k++;
  }
  for ( j = 0 ; j < 10 ; j++ ) printf("%.10lf ",nodo_actual[j]);
  return evaluar(nodo_actual);
}

/////////////////////////////////////////////////////////////////
/////////////////// SIMULATED - ANNELING ////////////////////////
/////////////////////////////////////////////////////////////////

double *sucesor_simul(double nodo[10]) {
  int i;
  double *sucesor = (double *)malloc(sizeof(double)*10);
  double *sucesor_aux = (double *)malloc(sizeof(double)*10);
  double num;
  double alfa = ((double)(rand() % 1000)) / 1000.0;
  
  sucesor_aux = sucesor;
  
  int pos = random() % 10;
  int sum_res = random() % 2;

  copiar_vector(10,sucesor,nodo);
  if (sum_res == 0 ) sucesor[pos] += alfa;
  else sucesor[pos] -= alfa;

  sucesor = sucesor_aux;
  return sucesor;
}

double simulated_anneling(double nodo_inicial[10], double Temp, double MaxIter, double MaxAccept) {
  
  int i = 0;
  int a = 0;
  double *vecino, nodo_actual[10], delta, suerte;
  double eval_actual = evaluar(nodo_inicial);
  double alfa = 0.9;
  double ro = 1.003;
  double k = 0.0;

  copiar_vector(10,nodo_actual,nodo_inicial);
  srand(time(0));

  while (i < 200) {
    
    while (k < MaxIter && a < MaxAccept) {
      vecino = sucesor_simul(nodo_actual);
      delta = evaluar(vecino) - eval_actual;
      if ( delta > 0 ) {
	copiar_vector(10,nodo_actual,vecino);
	eval_actual = evaluar(vecino);
	a++;
      } else {
	suerte = (double)rand()/((double)(RAND_MAX)+(double)(1));
	if (expo(delta/Temp) > suerte ) { 
	  copiar_vector(10,nodo_actual,vecino);
	  eval_actual = evaluar(vecino);
	  a++;
	}
      }
      k += 1;
    }
    Temp *= alfa;
    MaxIter *= ro;
    k = 0.0;
    a = 0;
    i++;
  }

  int j;
  for ( j = 0 ; j < 10 ; j++ ) printf("%.10lf ",nodo_actual[j]);
  return evaluar(nodo_actual);

}

/////////////////////////////////////////////////////////////////
////////////////////// ALGORITMO GENETICO ///////////////////////
/////////////////////////////////////////////////////////////////

double valor_normal(double norm[20],int pos) {
  return norm[pos];
}

double *cruzar(double padre[10], double madre[10]) {
  int i;
  double *hijo = (double *)malloc(sizeof(double)*10);
  for ( i = 0 ; i < 10 ; i++ ) 
    hijo[i] = (padre[i] + madre[i]) / 2;
  return hijo;
}

void mutacion(double **hijos) {
  double alfa = 0.995;
  double prob = 0.2;
  double num;
  int i, j;
  for (i = 0 ; i < 10 ; i++)
    for (j = 0 ; j < 10 ; j++) {
      num = (double)(random())/RAND_MAX;
      if (num <= prob)
	hijos[i][j] *= alfa;
    }
}

double **gen_familia() {
  double **familia = (double* *)malloc(sizeof(double *)*20);
  double **aux_fam = (double* *)malloc(sizeof(double *)*20);
  double aux[10], num;
  int i, j, k;
  struct timeval t;

  gettimeofday(&t,NULL);
  srand(t.tv_sec);
  aux_fam = familia;
  for ( i = 0 ; i < 20 ; i++ ) {
    *familia = (double *)malloc(sizeof(double)*10);
    copiar_vector(10,*familia,vector_aleatorio());
    familia++;
  }
  familia = aux_fam;
  return familia;
}

double **gen_familia_nueva(double **poblacion) {
  int i, j;
  double num;
  double **familia = (double* *)malloc(sizeof(double *)*10);
  j =24;
  for ( i = 0 ; i < 10 ; i++) {
    num = (double)(random())/RAND_MAX;
    if (i > 5) {
      familia[i] = cruzar(poblacion[i],poblacion[j-i]);
      j--;
    }
    else 
      familia[i] = cruzar(poblacion[i],poblacion[5+i]);
  }
  return familia;

}

double genetic_alg() {
  int i, j, k, count, pos_max;
  double max, sum, alfa;
  double **poblacion = (double* *)malloc(sizeof(double *)*20);
  double **pob_div = (double* *)malloc(sizeof(double *)*20);
  double **hijos = (double* *)malloc(sizeof(double *)*10);
  double norm[20], norm_aux[20], num, valor_medio;

  sum = 0;
  poblacion = gen_familia();
  count = 0;
  
  while (count < 200) {
    

    //////SELECCION///////    
    for (i = 0 ; i < 20 ; i++ ) { norm[i] = evaluar(poblacion[i]); }
    copiar_vector(20,norm_aux,norm);

    //////DIVISON ENTRE MEJORES Y PEORES//////
    for (i = 0 ; i < 20 ; i++ ) { norm_aux[i] *= 1000.0; }
    qsort(norm_aux,20,sizeof(double),compare);
    for (i = 0 ; i < 20 ; i++ ) { norm_aux[i] /= 1000.0; }
    valor_medio = norm_aux[10];
    j = 0;
    k = 19;
    for ( i = 0 ; i < 20 ; i++ ) {
      if (valor_normal(norm,i) > valor_medio) { 
	pob_div[j] = poblacion[i];
	j++;
      }
      else { 
	pob_div[k] = poblacion[i];
	k--;
      }
    }

    ///////REPRODUCCION//////
    hijos = gen_familia_nueva(pob_div);

    //////MUTACION///////
    mutacion(hijos);
    
    //////REPOBLACION//////
    for ( i = 0 ; i < 10 ; i++ ) pob_div[10+i] = hijos[i];
    poblacion = pob_div;
    count++;

  }

  /////////SELECCION DEL MAXIMO/////////
  max = 0;
  for ( i = 0 ; i < 20 ; i++ ) 
    if (max < evaluar(poblacion[i])) {
      max = evaluar(poblacion[i]);
      pos_max = i;
    }

  for ( j = 0 ; j < 10 ; j++ ) printf("%.10lf ",poblacion[pos_max][j]);

  return max;
}

//////////////////////////////////////////////////////////////////
/////////////////////PROGRAMA PRINCIPAL///////////////////////////
//////////////////////////////////////////////////////////////////

int main() {
 
  int i;
  double x[10];
  double num, max;
  double *sucesor = (double *)malloc(sizeof(double)*10);
  struct timeval t;
  double t_ini,t_fin,tiempo,seg;
  int min;

  /**************************** Generacion y evaluacion del punto inicial para Hill y SImulated**************************/

  gettimeofday (&t, NULL);
  srand(t.tv_sec + t.tv_usec);
  for ( i = 0 ; i < 10 ; i++ ) { x[i] = 0; }
  for ( i = 0 ; i < 10 ; i++ ) {
    num = (double)rand()/((double)(RAND_MAX)+(double)(1));
    num = num*2 -1;
    x[i] = num;
  }


  printf("\nUbicacion del Inicial para Hill-Climbing y Simulated-Anneling: ");
  for ( i = 0 ; i < 10 ; i++ ) printf("%.10f ",x[i]);
  printf("\nEvaluacion Nodo Inicial: %.10lf\n\n",evaluar(x));


  /***************************************** Corre Hill-Climbing  *******************************************/

  gettimeofday (&t, NULL);
  t_ini = (double)t.tv_sec + (t.tv_usec/1000000.0);

  llamadas = 0;
  printf("\nUbicacion del Maximo:  ");
  max = hill_climbing(x);
  printf("\nMaximo - Hill Climbing = %.10lf\n",max);
  printf("Numero de llamadas a la funcion objetivo = %d\n",llamadas);

  gettimeofday (&t, NULL);
  t_fin = (double)t.tv_sec + (t.tv_usec/1000000.0);
  tiempo = t_fin - t_ini;
  printf("Tiempo de ejecucion Hill-Clibing: %f segundo(s)\n", tiempo);
  printf("\n");


  /***************************************** Corre Simulated-Anneling  *******************************************/

  gettimeofday (&t, NULL);
  t_ini = (double)t.tv_sec + (t.tv_usec/1000000.0);

  llamadas = 0;
  printf("Ubicacion del Maximo:  ");
  max = simulated_anneling(x,8000,40,25);
  printf("\nMaximo - Simulated Anneling = %.10lf\n",max);
  printf("Numero de llamadas a la funcion objetivo = %d\n",llamadas);

  gettimeofday (&t, NULL);
  t_fin = (double)t.tv_sec + (t.tv_usec/1000000.0);
  tiempo = t_fin - t_ini;
  printf("Tiempo de ejecucion Simulated-Anneling: %f segundo(s)\n", tiempo);
  printf("\n");


  /***************************************** Corre Algoritmo-Genetico  *******************************************/

  gettimeofday (&t, NULL);
  t_ini = (double)t.tv_sec + (t.tv_usec/1000000.0);

  llamadas = 0;
  printf("\nUbicacion del Maximo:  ");
  max = genetic_alg();
  printf("\nMaximo - Algoritmo Genetico = %.10lf\n",max);
  printf("Numero de llamadas a la funcion objetivo = %d\n",llamadas);

  gettimeofday (&t, NULL);
  t_fin = (double)t.tv_sec + (t.tv_usec/1000000.0);
  tiempo = t_fin - t_ini;
  printf("Tiempo de ejecucion Alg-Genetico: %f segundo(s)\n", tiempo);
  printf("\n");

  exit(0);

}
