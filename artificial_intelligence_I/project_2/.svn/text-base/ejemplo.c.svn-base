#include <stdio.h>
#include <stdlib.h>
#include "ia1.h"

/*
  Inteligencia Artificial I
  Abril-Julio 2009

  Ejemplo de como utilizar libfia1.so. Hecho por Carlos Castillo.

  Para compilar:

  1. Colocar ia1.h, libfia1.so y ejemplo.c

  2. Compilar de la siguiente forma:
      gcc -lm -L. -lfia1 ejemplo.c -o ejemplo

  3. Para ejecutar:
      LD_LIBRARY_PATH=. ./ejemplo

  Recuerde colocar su numero de carnet en la llamada ia1.
 */

inline double evaluar(double x[10]){
  int r;
  double z;
  if ( (r = ia1("0234745", x, &z)) ){
    fprintf(stderr, "hubo un error: %d\n", r);
    exit(EXIT_FAILURE);
  }
  return z;
}

int main(){
    double x[10] = {0.159663231186, 0.548155460762, 0.778154879239, -0.969215895035, -0.555190502459, 0.945998729181, 0.440256990697, -0.947726668766, -0.518855950571, 0.854212932221};
  if (abs(evaluar(x)-10)>0.001){
    printf("Si imprime este mensaje contactame\n");
  }
    printf("%lf\n", evaluar(x));

  return EXIT_SUCCESS;
}
