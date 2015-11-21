#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class Estado{
public:
  char matriz[9];
  char pos_cero;
  short int suma;
  Estado();
  Estado(char *info_mat);
  short int calc_suma(char *info_mat,char pos_cero);
  void calc_total();
  void print();
  int es_objetivo();
  int es_igual(Estado otro);
  Estado clon();
  void swap(short int num1, short int num2);
};


//Constructor de la clase Estado
Estado::Estado(){
  int i;
  for(i=0;i<9;i++) matriz[i]='0';
  pos_cero='0';
  suma = 0;
}

//Constructor de la clase Estado con argumentos.
Estado::Estado(char *info_mat) {
  short int i,j;
  for(i=0;i<9;i++){
      if(*info_mat=='0') pos_cero = (char)(i+48);
      matriz[i]=*info_mat;
      info_mat++;
    }
  suma = calc_suma(matriz,pos_cero);
}

Estado Estado::clon(){
  int i;
  Estado clon;
  for (i=0;i<9;i++)
      clon.matriz[i] = matriz[i];	
  clon.pos_cero = pos_cero;
  clon.suma = suma;
  //clon.calc_total();
  return clon;
}

short int Estado::calc_suma(char info_mat[9],char pos_cero) {
  short int suma_aux, primero, segundo;

if (pos_cero == '0' || pos_cero == '3' || pos_cero == '6') {
    primero = (int)info_mat[(int)pos_cero-48+1] - 48;
    segundo = (int)info_mat[(int)pos_cero-48+2]- 48;
  } else if (pos_cero == '2' || pos_cero == '5' || pos_cero == '8') {
    primero = (int)info_mat[(int)pos_cero-48-1]- 48;
    segundo = (int)info_mat[(int)pos_cero-48-2]- 48;
  } else  {
    primero = (int)info_mat[(int)pos_cero-48-1]- 48;
    segundo = (int)info_mat[(int)pos_cero-48+1]- 48;
  }
 if (segundo <= 2) 
   suma_aux = primero - 1;
 else if (segundo <= 4) 
   suma_aux = primero + 7;
 else if (segundo <= 6) 
   suma_aux = primero + 15;
 else if (segundo <= 8) 
   suma_aux = primero + 23;  
 return suma_aux;
}

//Procedimiento que imprime la matriz de un estado
void Estado::print(){
  int i;
  for (i=0;i<9;i++){
    if ((i % 3) == 0) cout<<"\n";  
    cout<<matriz[i]<<' ';
  }
  cout<<"\n";
}

//Funcion booleana que verifica si la matriz de un estado representa la solucion del problema.
int Estado::es_objetivo() {
  int i;
  for(i=0;i<9;i++) if (matriz[i] != (char)(i+48)) return 0;
  return 1;
}

int Estado::es_igual(Estado otro){
  int i;
  for (i=0;i<9;i++){
      if (matriz[i] != otro.matriz[i]) return 0;
  }
  return 1;
}

void Estado::swap(short int num1,short int num2) {
  char aux1 = matriz[num1];
  char aux2 = matriz[num2];
  matriz[num1] = aux2;
  matriz[num2] = aux1;
  if (matriz[num1] == '0'){
    pos_cero = (char)(num1+48);
  }
  else if (matriz[num2] == '0'){
    pos_cero = (char)(num2+48);
  }
  suma = calc_suma(matriz,pos_cero);
}

