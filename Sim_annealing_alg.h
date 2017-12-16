#ifndef SIM_ANNEALING_ALG_H
#define SIM_ANNEALING_ALG_H

#include "Packing.h"
#include <fstream>

#define TSTART 50000
#define TMIN 10

int *** simAnnealingAlgorithm(Item * itms, int * numOfBoxs, int * ord);
int objectiveFunction(int numOfBoxs, int EmptySp);	//cost ==> minimum
double probabilityFunction(int value1, int value2, int temp);
int lowerTemperature(int temp);

#endif