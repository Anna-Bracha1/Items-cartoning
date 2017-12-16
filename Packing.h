#ifndef PACKING_H_
#define PACKING_H_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

#define BOXwidth 10
#define BOXlength 10
#define QUANTITY 9
#define TSTART 100
#define TMIN 10

struct Coordinates{
	int x;
	int y;
	bool rotation;
	int boxNum;
};

struct Item{
	int number;
	int length;
	int width;
	Coordinates cor;
};

int *** placeItems(int *** boxes, Item * itms, int * numOfBoxs);
int *** addBox(int *** Boxs, int numOfBoxs);
int findEmptySpace(int ** box);
int *** createTableOfBoxes(int numOfBoxs);
void deleteTableOfBoxes(int *** boxes, int numOfBoxs);
int max(int a, int b);

#endif