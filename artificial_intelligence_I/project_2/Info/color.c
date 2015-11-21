#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <math.h> 
#include <string.h> 
#include <sys/time.h> 
#include <time.h>
#include "coloracion.c"
#include "pila.c"
#define E 2.7182818284590

/*
  Funcion que halla una solucion del algoritmo greedy. 
*/
COLORACION* solucionInicial(int n, int Ady[n][n]) {
	COLORACION* colores = new_coloracion(n);
	int max_color = 0, color, i, j;
	int solucion[n];
	for (i = 0; i < n; i++) {
		color = 0;
		for (j = 0; j < i; j++) {
			if ( Ady[i][j] == 1 && color == solucion[j] ) {
				color++;
				j=0;
			}
		}
		if (max_color < color) max_color = color;
		solucion[i] = color;
		colores->nodos[color*n+colores->num_nodos[color]]=i;
		colores->num_nodos[color]++;
	}
	colores->num_colores=max_color+1;
	return colores;
}


/*Función que logra una perturbacion de cadena de Kempe. Se utiliza para ILS.
COLORACION* kempe_chain(COLORACION* estado, int Ady[sol_ini->n][sol_ini->n],int color1,int vertice,int color2){

	PILA* pilaDFS = new_pila(estado.num_nodos[color1]+estado.num_nodos[color2]);
	PILA* color1_cerrado = new_pila(estado.num_nodos[color1]);
	PILA* color2_cerrado = new_pila(estado.num_nodos[color2]);
	int i,aux;
	if (!pila_pertenece(color1_cerrado,vertice)){
		pila_push(pilaDFS,estado.nodos[color1*(estado.n)+i]);
		while(!pila_empty(colaDFS)){
			aux = pila_pop(pilaDFS);
			for(j=0;j<estado.num_nodos[color2];)
		}
	}
	else continue;
}*/

COLORACION* mejor(COLORACION* sol_ini, int Ady[sol_ini->n][sol_ini->n]) {
	int n = sol_ini->n;
	int id[3];
	COLORACION* sol_act = clon(sol_ini);
	COLORACION* sol_mejor = clon(sol_act);
	COLORACION* sol_prima = new_coloracion(n);
	while (1) {
		id[0] = 0; id[1] = 0; id[2] = -1;
		while (genera_vecino(sol_act,Ady,id,sol_prima)) {
			if (eval(sol_prima) < eval(sol_mejor)) {
				copia(sol_prima,sol_mejor);
			}
		}
		if (eval(sol_mejor) < eval(sol_act)) {
			copia(sol_mejor,sol_act);
		} else {
			break;
		}
	}
	return(sol_mejor);
}
	

COLORACION* primer_mejor(COLORACION* sol_ini, int Ady[sol_ini->n][sol_ini->n]) {
	int n = sol_ini->n;
	int cand = 0;
	COLORACION* sol_act = clon(sol_ini);
	COLORACION* sol_prima = new_coloracion(n);
	while (cand < 100000) {
		genera_vecino_al(sol_act,Ady,sol_prima);
		if (eval(sol_prima) < eval(sol_act)) {
			copia(sol_prima,sol_act);
			cand = -1;
		}
		cand++;
	}
	return(sol_act);
}


COLORACION* simul_anneal(COLORACION* sol_ini, int Ady[sol_ini->n][sol_ini->n], int k0, int A, double t0, double seed) {
	COLORACION* sol_act = clon(sol_ini);
	COLORACION* sol_prima = new_coloracion(sol_ini->n);
	int k, a, cond_parada = 0, K = k0;
	double randv, proba, temp = t0, alpha = 0.95, ro = 1.1;
	srand(seed);

	while ( cond_parada < 250 && temp > 0.0000001 ) {
		while (k < K && a < A) {
			genera_vecino_al(sol_act,Ady,sol_prima);
			int eval_prima = eval(sol_prima);
			int eval_act = eval(sol_act);
			if (eval_prima < eval_act) {
				copia(sol_prima,sol_act);
				a++; 
			} else if (eval_prima > eval_act) {
				randv = (double)rand()/((double)(RAND_MAX)+(double)(1));
				proba = pow(E,(eval_act - eval_prima)/temp);
				if (randv < proba) {
					copia(sol_prima,sol_act);
					a++;
				}
			}
			k++;
		}
		temp = alpha * temp;
		K = ro * K;
		k = 0; a = 0;
		cond_parada++;
		printf("#"); fflush(0);
	}
	printf("\n");
	return sol_act;
}

int main ( int argc, char *argv[] ) {

	int n, ne, i = 1, j, k, x;
	struct timeval t, ti, tf;
	double tiaux,tfaux;
	FILE* Ar;
	char buf[1000], *y;
	COLORACION *col, *res;

	if (argc!=3) {
		printf("Uso: ./color <algorithm> <file_name>\n");
		exit(0);
	}
	Ar = fopen(argv[2],"r");
	if (!Ar) {
		printf("El archivo no existe.\n");
		exit(0);
	}

	while(i) {
		y = fgets(buf, sizeof(buf) -1, Ar);
		if (buf[0] != 'c') i = 0;
	}

	/* Leemos la cantidad de nodos */
	x = sscanf(buf,"p edge %d %d\n",&n, &ne);

	/* Se construye la matriz de adyacencias */
	int Ady[n][n];
	for (i=0; i<n; i++) {	
		for (j=0; j<n; j++) {
			Ady[i][j] = 0;
		}
	}
	for (i=0; i<ne; i++) {
		x = fscanf(Ar,"e %d %d\n",&j, &k);
		Ady[k-1][j-1] = 1;
		Ady[j-1][k-1] = 1;
	}

/*****************************************************************************/
	col = solucionInicial(n,Ady);
	print(col);
	printf("\n*********Fin de coloracion 1*********\n");
	perturbar(col,Ady,3);
	print(col);
/*
 if (strcmp(argv[1],"LSPM")==0){
	printf("\nLocal Search Primer Mejor:\n");
	gettimeofday (&ti, NULL);
	tiaux = (double)ti.tv_sec + (ti.tv_usec/1000000.0);
	res = primer_mejor(col,Ady);
	gettimeofday (&tf, NULL);
	tfaux = (double)tf.tv_sec + (tf.tv_usec/1000000.0);
	printf("[num_colores] -> %d\n",res->num_colores);
	printf("[evaluacion] -> %d\n",eval(res));
	printf("[inconsistencias] -> %d\n",inco(res));
	printf("[tiempo] -> %f\n",tfaux-tiaux);
}
else if (strcmp(argv[1],"LSM")==0){

	printf("Solucion inicial:\n");
	gettimeofday (&ti, NULL);
	tiaux = (double)ti.tv_sec + (ti.tv_usec/1000000.0);
	gettimeofday (&tf, NULL);
	tfaux = (double)tf.tv_sec + (tf.tv_usec/1000000.0);
	imprimir(col);
	printf("[num_colores] -> %d\n",col->num_colores);
	printf("[evaluacion] -> %d\n",eval(col));
	printf("[inconsistencias] -> %d\n",inco(col));
	printf("[tiempo] -> %f\n",tfaux-tiaux);

	printf("\nLocal Search Mejor:\n");
	gettimeofday (&ti, NULL);
	tiaux = (double)ti.tv_sec + (ti.tv_usec/1000000.0);
	res = mejor(col,Ady);
	gettimeofday (&tf, NULL);
	tfaux = (double)tf.tv_sec + (tf.tv_usec/1000000.0);
	printf("[num_colores] -> %d\n",res->num_colores);
	printf("[evaluacion] -> %d\n",eval(res));
	printf("[inconsistencias] -> %d\n",inco(res));
	printf("[tiempo] -> %f\n",tfaux-tiaux);
}
else if (strcmp(argv[1],"SA")==0){
	gettimeofday (&t, NULL);
	printf("\nSimulated Annealing (seed: %d):\n",(int)t.tv_usec);
	gettimeofday (&ti, NULL);
	tiaux = (double)ti.tv_sec + (ti.tv_usec/1000000.0);
	res = simul_anneal(col,Ady,70,40,10000,(int)t.tv_usec);
	gettimeofday (&tf, NULL);
	tfaux = (double)tf.tv_sec + (tf.tv_usec/1000000.0);
	printf("[num_colores] -> %d\n",res->num_colores);
	printf("[evaluacion] -> %d\n",eval(res));
	printf("[inconsistencias] -> %d\n",inco(res));
	printf("[tiempo] -> %f\n",tfaux-tiaux);
}
else{
	printf("\nIntroduzca un algoritmo valido\n");
	printf("Uso: ./color <algorithm> <file_name>\n");
	exit(0);
}
*/

/*****************************************************************************/
	return(0);
}
