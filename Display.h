#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <windows.h>
#include <iostream>
#include "Packing.h"

using namespace std;

void showBox(int ***Boxes, int numOfBoxes);
void showResult(struct Item *items);
void showItems(struct Item *items);
void bag(int ***Boxes, struct Item *items, int amountOfItems);
void changeColor(int numberOfItems);

#endif