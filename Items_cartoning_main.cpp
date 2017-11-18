#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

#define BOXwidth 10
#define BOXheight 10
#define QUANTITY 9
#define TSTART 100
#define TMIN 10

struct Coordinates{
	int x;
	int y;
	int rotation;
	int boxNum;
};

struct Item{
	int number;
	int height;
	int width;
	Coordinates cor;
};

int *** simAnnealingAlgorithm(Item * itms, int * numOfBoxs, int * ord);
int objectiveFunction(int numOfBoxs, int EmptySp);	//cost ==> minimum
double probabilityFunction(int value1, int value2, int temp);
int lowerTemperature(int temp);
int *** placeItems(int *** boxes, Item * itms, int * numOfBoxs);
int *** addBox(int *** Boxs, int numOfBoxs);
int findEmptySpace(int ** box);
int *** createTableOfBoxes(int numOfBoxs);
void deleteTableOfBoxes(int *** boxes, int numOfBoxs);
int max(int a, int b);

int main()
{
	Item items[QUANTITY] = {{1, 4, 2, {0, 0, 0, 0}}, {2, 3, 3, {0, 0, 0, 0}}, {3, 5, 3, {0, 0, 0, 0}}, {4, 9, 1, {0, 0, 0, 0}}, {5, 5, 2, {0, 0, 0, 0}}, {6, 8, 2, {0, 0, 0, 0}},
					 {7, 4, 1, {0, 0, 0, 0}}, {8, 5, 3, {0, 0, 0, 0}}, {9, 7, 2, {0, 0, 0, 0}}};
	int Order[QUANTITY] = {0};
	
	int *** Boxes;
	int EmptySpace;
	int numOfBoxes;
	
	Boxes = simAnnealingAlgorithm(items, &numOfBoxes, Order);
	EmptySpace = findEmptySpace(Boxes[numOfBoxes-1]);
	cout << endl << "EmptySpace: " << EmptySpace << endl << endl;
	for(int i = 0; i < QUANTITY; i++)
	{
		cout << "Item " << items[i].number << endl;
		cout << "height: " << items[i].height << ", width: " << items[i].width << endl;
		cout << "x: " << items[i].cor.x << ", y: " << items[i].cor.y << endl;
		cout << "rotation: " << items[i].cor.rotation << endl;
		cout << "boxNum: " << items[i].cor.boxNum << endl << endl;
	}
}

int *** simAnnealingAlgorithm(Item * itms, int * numOfBoxs, int * order)
{
	for(int i=0; i < QUANTITY; i++)
		order[i] = i+1;
	
	srand(time(0));	//initialisation of the pseudorandom number generator
	
	int valueOfObjFun1, valueOfObjFun2;
	int *** Boxes1;
	int *** Boxes2;
	int EmptySpace1, EmptySpace2;
	int numOfBoxs2;
	int number1, number2;
	Item tempItem;
	int tempNum;
	
	Boxes1 = createTableOfBoxes(1);
	*numOfBoxs = 1;
	Boxes1 = placeItems(Boxes1, itms, numOfBoxs);
	EmptySpace1 = findEmptySpace(Boxes1[(*numOfBoxs)-1]);
	valueOfObjFun1 = objectiveFunction((*numOfBoxs), EmptySpace1);
	
	for(int temperature = TSTART; temperature > TMIN; temperature = lowerTemperature(temperature))
	{
		number1 = rand() % QUANTITY;
		number2 = rand() % QUANTITY;
		
		tempItem = itms[number1];
		itms[number1] = itms[number2];
		itms[number2] = tempItem;
		
		tempNum = order[number1];
		order[number1] = order[number2];
		order[number2] = tempNum;
		
		Boxes2 = createTableOfBoxes(1);
		numOfBoxs2 = 1;
		Boxes2 = placeItems(Boxes2, itms, &numOfBoxs2);
		EmptySpace2 = findEmptySpace(Boxes2[numOfBoxs2-1]);
		valueOfObjFun2 = objectiveFunction(numOfBoxs2, EmptySpace2);
		if(valueOfObjFun2 <= valueOfObjFun1)
		{
			deleteTableOfBoxes(Boxes1, *numOfBoxs);
			Boxes1 = Boxes2;
			valueOfObjFun1 = valueOfObjFun2;
			EmptySpace1 = EmptySpace2;
			*numOfBoxs = numOfBoxs2;
			cout << "Better" << endl;
		}
		else
		{
			double P = probabilityFunction(valueOfObjFun1, valueOfObjFun2, temperature);
			double R = ((rand() % 10000)/10000.0);
			cout << "P: " << P << ", R: " << R << endl;
			if(P > R)
			{
				deleteTableOfBoxes(Boxes1, *numOfBoxs);
				Boxes1 = Boxes2;
				valueOfObjFun1 = valueOfObjFun2;
				EmptySpace1 = EmptySpace2;
				*numOfBoxs = numOfBoxs2;
				cout << "Worse" << endl;
			}
			else
			{
				deleteTableOfBoxes(Boxes2, numOfBoxs2);
				
				tempItem = itms[number1];
				itms[number1] = itms[number2];
				itms[number2] = tempItem;
		
				tempNum = order[number1];
				order[number1] = order[number2];
				order[number2] = tempNum;
				cout << "The same" << endl;
			}
		}
	}
	
	return Boxes1;
}

int objectiveFunction(int numOfBoxs, int EmptySp)
{
	return (BOXwidth*numOfBoxs - EmptySp);
}

double probabilityFunction(int value1, int value2, int temp)
{
	return exp((value1 - value2) / (temp*(1.0/10.0)));
}

int lowerTemperature(int temp)
{
	return (0.9*temp);
}

int *** placeItems(int *** boxes, Item * itms, int * numOfBoxs)
{
	int numOfBoxes = 1;
	int X = 0;
	int Y = 0;
	int nextX = 0;
	for(int i = 0; i<QUANTITY; i++)
	{	
		if(itms[i].cor.rotation == 1)		//if rotation == 1, height swaps places with width
		{
			int temp2;
			temp2 = itms[i].height;
			itms[i].height = itms[i].width;
			itms[i].width = temp2;
		}
		
		if((itms[i].height <= (BOXheight-Y)) && (itms[i].width <= (BOXwidth-X)))
		{
			itms[i].cor.x = X;
			itms[i].cor.y = Y;
			Y+=itms[i].height;
			nextX = max((X+itms[i].width), nextX);
		}
		else if(itms[i].height > (BOXheight-Y))
		{
			X = nextX;
			if(itms[i].width > (BOXwidth-X))
			{
				boxes = addBox(boxes, numOfBoxes);
				numOfBoxes+=1;
				itms[i].cor.x = 0;
				itms[i].cor.y = 0;
				X = 0;
				Y = itms[i].height;
				nextX = itms[i].width;
			}
			else
			{
				itms[i].cor.x = X;
				itms[i].cor.y = 0;
				Y = itms[i].height;
				nextX+=itms[i].width;
			}
		}
		else
		{
			boxes = addBox(boxes, numOfBoxes);
			numOfBoxes+=1;
			itms[i].cor.x = 0;
			itms[i].cor.y = 0;
			X = 0;
			Y = itms[i].height;
			nextX = itms[i].width;
		}
		itms[i].cor.boxNum = numOfBoxes;
		
		for(int k = itms[i].cor.y; k!=(itms[i].cor.y+itms[i].height); k++)	//fill up pixels in the box table with number assigned to the recently placed item
		{
			for(int m = itms[i].cor.x; m<(itms[i].cor.x+itms[i].width); m++)
			{
				boxes[numOfBoxes-1][k][m]=itms[i].number;
			}
		}
		
		if(itms[i].cor.rotation == 1)	//restore height and width to their right places in the structure
		{
			int temp2;
			temp2 = itms[i].height;
			itms[i].height = itms[i].width;
			itms[i].width = temp2;
		}
	}
	*numOfBoxs = numOfBoxes;
	return boxes;
}

int *** addBox(int *** Boxs, int numOfBoxs)
{
	numOfBoxs++;
	int *** Boxes = new int **[numOfBoxs];	//create new table of boxes extended by one box
	for(int i = 0; i<numOfBoxs; i++)
		Boxes[i] = new int *[BOXheight];
	for(int i = 0; i<numOfBoxs; i++)
	{
		for(int j = 0; j<BOXheight; j++)
		{
			Boxes[i][j] = new int [BOXwidth];
		}
	}
	
	for(int i = 0; i<(numOfBoxs-1); i++)	//assign old boxes to the new table of boxes
		for(int j = 0; j<BOXheight; j++)
			for(int k = 0; k<BOXwidth; k++)
				Boxes[i][j][k]=Boxs[i][j][k];
	
	for(int j = 0; j<BOXheight; j++)	//empty spaces fill up with zeros
		for(int k = 0; k<BOXwidth; k++)
			Boxes[numOfBoxs-1][j][k]=0;
	
	deleteTableOfBoxes(Boxs, (numOfBoxs-1));	//delete old table of boxes

	return Boxes;
}

int findEmptySpace(int ** box)
{
	int temp;
	int EmptySpace = 0;
	for(int j = BOXwidth; j!=0; j--)
	{
		temp = 0;
		for(int i = 0; i<BOXheight; i++)
		{
			if(box[i][j-1] != 0)
			{
				temp = 1;
				break;
			}
		}
		if(temp == 0)
			EmptySpace+=1;	
	}
	return EmptySpace;
}

int *** createTableOfBoxes(int numOfBoxs)
{
	int *** Boxes = new int **[numOfBoxs];
	for(int i = 0; i<numOfBoxs; i++)
		Boxes[i] = new int *[BOXheight];
	for(int i = 0; i<numOfBoxs; i++)
	{
		for(int j = 0; j<BOXheight; j++)
		{
			Boxes[i][j] = new int [BOXwidth];
		}
	}
	
	for(int i = 0; i<numOfBoxs; i++)
		for(int j = 0; j<BOXheight; j++)
			for(int k = 0; k<BOXwidth; k++)
				Boxes[i][j][k]=0;
	
	return Boxes;
}

void deleteTableOfBoxes(int *** boxes, int numOfBoxs)
{
	for(int i = 0; i<numOfBoxs; i++)
	{
		for(int j = 0; j<BOXheight; j++)
		{
			delete [] boxes[i][j];
		}
		delete [] boxes[i];
	}
	delete [] boxes;
}

int max(int a, int b)
{
	if(a >= b)
		return a;
	else
		return b;
}