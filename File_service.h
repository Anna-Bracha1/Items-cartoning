#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <fstream>
#include "Packing.h"

void readItems(const char * FileName, Item * itms);
void writeItems(const char * FileName, Item * itms, int numOfBox);
void writeBoxes(const char * FileName, int *** boxes, int numOfBox);

#endif