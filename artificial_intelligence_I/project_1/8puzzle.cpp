#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <queue>
#include <list>
#include "camino.cpp"

using namespace std;

int nodos_expandidos;

bool operator<(const Camino &a, const Camino &b) {
  return a.costo < b.costo;
}

int almacenar(list<Camino> cam_hallados[32],Camino camino){
  list<Camino>::iterator cam;
  short int suma = camino.ult_nodo.suma;
  short int flag=0;
  for (cam=cam_hallados[suma].begin();cam!=cam_hallados[suma].end();cam++){
    if ((*cam).ult_nodo.es_igual(camino.ult_nodo)){
      return 0;
    } 
  }
  cam_hallados[suma].push_back(camino);
  return 1;
}

void insert_ucs(list<Camino> * dir_lista, Camino camino){
  list<Camino>::iterator it;
  for (it=(*dir_lista).begin();it!=(*dir_lista).end();it++){
    if ((*it).costo > camino.costo) {
      (*dir_lista).insert(it,1,camino);
      break;
    }
  }
  if (it==(*dir_lista).end()) (*dir_lista).push_back(camino);
}

void BFS_UCS_DFS(list<Camino> colaAlg,char algoritmo) {
  int p = 0;
  nodos_expandidos = 0;
  list<Camino> cam_hallados[32];
  list<Camino> sucesores;
  list<Camino>::iterator cam;
  int flag = 0;
  almacenar(cam_hallados,colaAlg.front());
  while (!colaAlg.empty()) {
    if (colaAlg.front().ult_nodo.es_objetivo()) {
      cout<<"\nSolucion hallada...\n\n";
      cout<<"Secuencia de Acciones: ";
      colaAlg.front().print();
      if (colaAlg.front().costo > 50 && algoritmo=='d')
	printf("DFS encontro solucion, pero muy larga para representar el camino.\n");
      cout<<"Numero de nodos expandidos: "<<nodos_expandidos;
      cout<<"\n"<<"Numero de pasos: "<<colaAlg.front().costo<<'\n';
      flag = 1;
      break;
    } else {
      nodos_expandidos++;
      sucesores = colaAlg.front().sucesores();
      colaAlg.pop_front();
      for (cam = sucesores.begin();cam != sucesores.end();cam++) {
	if (almacenar(cam_hallados,*cam)) {
	  //El caracter d indica que se quiere hacer dfs
	  if (algoritmo=='d') {
	    colaAlg.push_front(*cam);
	  }
	  //El caracter b indica que se quiere hacer bfs
	  if (algoritmo=='b') colaAlg.push_back(*cam);
	  //El caracter d indica que se quiere hacer ucs
	  if (algoritmo=='u') insert_ucs(&colaAlg,*cam);
	}
      }
    }
  }
  if (flag == 0) cout<<"La instancia dada no tiene solucion.\n";
}

void IDS(Camino estadoini){
  nodos_expandidos = 0;
  list<Camino> sucesores;
  list<Camino>::iterator cam;
  int flag = 0;
  int max_profundidad = 1;
  while(1){
    list<Camino> pilaIDS;
    pilaIDS.push_front(estadoini);
    list<Camino> cam_hallados[32];
    while (!pilaIDS.empty()){
      if (pilaIDS.front().ult_nodo.es_objetivo()){
	cout<<"\nSolucion hallada...\n\n";
	cout<<"Secuencia de Acciones: ";
	pilaIDS.front().print();
	cout<<"Numero de nodos expandidos: "<<nodos_expandidos;
	cout<<"\n"<<"Numero de pasos: "<<pilaIDS.front().costo<<'\n';
	flag = 1;
	break;
      }
      else if (pilaIDS.front().profundidad <= max_profundidad){
	nodos_expandidos++;
	sucesores = pilaIDS.front().sucesores();
	pilaIDS.pop_front();
	for (cam = sucesores.begin();cam != sucesores.end();cam++) {
	  if (almacenar(cam_hallados,*cam)) pilaIDS.push_front(*cam);
	}
      }
      else pilaIDS.pop_front();	
    }
    if (flag==1) break;
    max_profundidad++;
  }
}

int parseLine(char* line){
	int i = strlen(line);
	short j = 0; 
	while (j < 9) {line++; j++;}
	line[i-3] = '\0';
	i = atoi(line);
	return i;
}


int getMemoryPeak(){ 
	FILE* file = fopen("/proc/self/status", "r");
	int result = -1;
	char line[128];

	while (fgets(line, 128, file) != NULL){
		if (strncmp(line, "VmPeak:", 7) == 0) {
			result = parseLine(line);
			break;
		}
		
	}
	fclose(file);
	return result;
}


int main(int argc, char ** argv) {

  /**************** Instanciar el estado y camino inicial con argumentos*********************************/

  char *info_nodo;
  if (argc!=11) {
    cout<<"ERROR... Use: ./8puzzle <nombre_algoritmo> <numeros [0,8] separados por ' '(espacios)>\n";
    exit(0);
  }else {
    info_nodo=argv[2];
    int i;
    for(i=3;i<11;i++) {
      if (strcmp(argv[i],"1")&&strcmp(argv[i],"2")&&strcmp(argv[i],"3")&&
	  strcmp(argv[i],"4")&&strcmp(argv[i],"5")&&strcmp(argv[i],"6")&&
	  strcmp(argv[i],"7")&&strcmp(argv[i],"8")&&strcmp(argv[i],"0"))
	{
	  cout<<"ERROR... Use: ./8puzzle <nombre_algoritmo> <numeros [0,8] separados por ' '(espacios)>\n";
	  exit(0);
	}
      else strcat(info_nodo,argv[i]);
    }
  }

  Estado nodo_inicial(info_nodo);
  char acciones_hechas[] = "";
  Camino camino(nodo_inicial,acciones_hechas,0,0);
  struct timeval t;
  double t_ini,t_fin,time,seg;
  int min;

  /*************************************************************************************************************/
  /***************Aqui comienzan las corridas de los algoritmos ***********************************************/

  if (strcmp(argv[1],"BFS") == 0 || strcmp(argv[1],"bfs") == 0) {
    
    list<Camino> colaBFS;
    cout<<"Hacemos BFS\n";
    gettimeofday (&t, NULL);
    t_ini = (double)t.tv_sec + (t.tv_usec/1000000.0);
    colaBFS.push_back(camino);
    BFS_UCS_DFS(colaBFS,'b');

  } else if (strcmp(argv[1],"UCS") == 0 || strcmp(argv[1],"ucs") == 0) {
    
    cout<<"Hacemos UCS\n";
    gettimeofday (&t, NULL);
    t_ini = (double)t.tv_sec + (t.tv_usec/1000000.0);
    list<Camino> listaUCS;
    listaUCS.push_back(camino);
    BFS_UCS_DFS(listaUCS,'u');
  
  } else if (strcmp(argv[1],"DFS") == 0 || strcmp(argv[1],"dfs") == 0) {
    
    list<Camino> pilaDFS;
    cout<<"Hacemos DFS\n";
    gettimeofday (&t, NULL);
    t_ini = (double)t.tv_sec + (t.tv_usec/1000000.0); 
    pilaDFS.push_front(camino);
    BFS_UCS_DFS(pilaDFS,'d');

  } else if (strcmp(argv[1],"IDS") == 0 || strcmp(argv[1],"ids") == 0) {
  
    cout<<"Hacemos IDS\n";
    gettimeofday (&t,NULL);
    t_ini = (double)t.tv_sec + (t.tv_usec/1000000.0);
    IDS(camino);

  } else cout<<"ERROR... Inserte un Algoritmo valido\n";

  /***************Caluculo el tiempo que se ha tomado el algoritmo***************************/

  gettimeofday (&t, NULL);
  t_fin = (double)t.tv_sec + (t.tv_usec/1000000.0);
  time = t_fin - t_ini;
  min = ((int)time / 60);
  seg = time - (min*60); 
  printf("Tiempo de ejecucion: %d minuto(s), %f segundo(s)\n", min, seg);
  int max = getMemoryPeak();
  printf("Consumo Maximo de Memoria: %d\n",max);
  cout<<"\n";

  return 0;

}


