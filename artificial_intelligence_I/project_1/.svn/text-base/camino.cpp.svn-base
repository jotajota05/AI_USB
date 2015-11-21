#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "estado.cpp"
#include <string>

using namespace std;

class Camino {
public:
  Estado ult_nodo;
  char acciones[50];
  int costo;
  int profundidad;
  Camino(Estado ult_nodo, char acciones[50], int costo,int profundidad);
  int operator<(const Camino&) const;
  void print();
  list<Camino> sucesores();
  void calc_sucesores(char accion_ejecutada[50],list<Camino> *sucesores);
  void insert_ordenado(list<Camino> lista);
  void copiar(char a[50],char b[50]);
};

void Camino::print(){
  int i;
  for(i=0;i<50;i++){
    if (acciones[i]=='u') cout<<" UP ";
    else if (acciones[i]=='d') cout<<" DOWN ";
    else if (acciones[i]=='l') cout<<" LEFT ";
    else if (acciones[i]=='r') cout<<" RIGHT ";
    else break;
  }
  cout<<'\n';
}

void Camino::copiar(char a[50],char b[50]) {
  int i;
  for (i = 0;i < 50;i++) {
    if (a[i]=='u'||a[i]=='d'||a[i]=='l'||a[i]=='r'||b[i]=='u'||b[i]=='d'||b[i]=='l'||b[i]=='r')
      a[i] = b[i];
    else break;
  }
}

Camino::Camino(Estado info_nodo, char info_acciones[50], int info_costo, int info_profundidad){
  int i;
  copiar(acciones,info_acciones);
  ult_nodo = info_nodo;
  costo=info_costo;
  profundidad=info_profundidad;
}

int Camino::operator< (const Camino& c) const
{
      return costo > c.costo;
}

list<Camino> Camino::sucesores(){

  list<Camino> sucesores;

  if (ult_nodo.pos_cero >= '0' && ult_nodo.pos_cero <= '5'){
    calc_sucesores((char *)"d",&sucesores);
  }
  if (ult_nodo.pos_cero >= '3' && ult_nodo.pos_cero <= '8') {    
    calc_sucesores((char *)"u",&sucesores);
  }
  if (ult_nodo.pos_cero != '2' && ult_nodo.pos_cero != '5' && ult_nodo.pos_cero != '8'){
    calc_sucesores((char *)"r",&sucesores);
  } 
  if (ult_nodo.pos_cero != '0' && ult_nodo.pos_cero != '3' && ult_nodo.pos_cero != '6'){
    calc_sucesores((char *)"l",&sucesores);
  }

  return sucesores;

}

void Camino::calc_sucesores(char accion_ejecutada[50],list<Camino> *sucesores) {
  //Se crea un nuevo estado igual al estado actual
  Estado estado_suc = ult_nodo.clon();
  short int num1,num2;
  num1=(int)ult_nodo.pos_cero-48;

  if (strcmp(accion_ejecutada,"u") == 0) {
    num2 = num1 - 3;
  } else if (strcmp(accion_ejecutada,"d") == 0) {
    num2 = num1 + 3;
  } else if (strcmp(accion_ejecutada,"r") == 0) {
    num2 = num1 + 1;
  } else if (strcmp(accion_ejecutada,"l") == 0) {
    num2 = num1 -1;
  }
  
  //Se intercambian las posiciones de 2 numeros en el nuevo estado
  estado_suc.swap(num1,num2);
  
  //Si no, hacer nuevo camino con movimiento UP,DOWN,LEFT o RIGTH.
  char aux[50] = "";
  copiar(aux,acciones);
  strcat(aux,accion_ejecutada);
  Camino camino_nuevo(estado_suc,aux,costo+1,profundidad+1);
  (*sucesores).push_back(camino_nuevo);

}
