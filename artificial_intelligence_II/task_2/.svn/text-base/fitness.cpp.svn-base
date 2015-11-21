#include <math.h>
#include <stdio.h>
#include "fitness.h"

vector<int> logicAnd(vector<int> chromosome, vector<int> data, int base, int ini, int fin) {
  vector<int> result;
  int i;

  for (i = ini; i < fin; i++) {
    result.push_back(chromosome.at(base + i) & data.at(i));
  }

  return result;
}

int check_1s(vector<int> vec) {
  unsigned int i;
  
  for (i = 0; i < vec.size(); i++) {
    if (vec.at(i) == 1)
      return 1;    
  }

  return 0;
}

vector<float> computeFitness(vector< vector<int> > testData,  vector< vector<int> > pop) {

  vector<float> fitness;
  unsigned int i, j, k, num, total_classified, ch;
  
  for (i = 0; i < pop.size(); i++) {
    num = pop.at(i).size() / 118;
    total_classified = 0;

    for (j = 0; j < testData.size(); j++) {
      for (k = 0; k < num; k++) {
	ch = k * 118;
	
	if (check_1s(logicAnd(pop.at(i), testData.at(j), ch, 0, 4)) && 
	    check_1s(logicAnd(pop.at(i), testData.at(j), ch, 4, 12)) &&
	    check_1s(logicAnd(pop.at(i), testData.at(j), ch, 12, 15)) &&
	    check_1s(logicAnd(pop.at(i), testData.at(j), ch, 15, 31)) &&
	    check_1s(logicAnd(pop.at(i), testData.at(j), ch, 31, 34)) &&
	    check_1s(logicAnd(pop.at(i), testData.at(j), ch, 34, 41)) &&
	    check_1s(logicAnd(pop.at(i), testData.at(j), ch, 41, 55)) &&
	    check_1s(logicAnd(pop.at(i), testData.at(j), ch, 55, 61)) &&
	    check_1s(logicAnd(pop.at(i), testData.at(j), ch, 61, 66)) &&
	    check_1s(logicAnd(pop.at(i), testData.at(j), ch, 66, 68)) &&
	    check_1s(logicAnd(pop.at(i), testData.at(j), ch, 68, 70)) &&
	    check_1s(logicAnd(pop.at(i), testData.at(j), ch, 70, 72)) &&
	    check_1s(logicAnd(pop.at(i), testData.at(j), ch, 72, 76)) &&
	    check_1s(logicAnd(pop.at(i), testData.at(j), ch, 76, 117)) &&
	    (pop.at(i).at(ch + 117) == testData.at(j).at(117))) {

	  total_classified++;
	  break;
	}
      }
    }
    //printf("total = %d, %f, %f\n", total_classified, (float)total_classified / (float)testData.size(), pow((float)total_classified / (float)testData.size(), 2));
    fitness.push_back(pow((float)total_classified / (float)testData.size(), 2));
  }

  return fitness;
}
