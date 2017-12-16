#include "Packing.h"

using namespace std;

int *** placeItems(int *** boxes, Item * itms, int * numOfBoxs)
{
	int numOfBoxes = 1;
	int X = 0;
	int Y = 0;
	int nextX = 0;
	for(int i = 0; i<QUANTITY; i++)
	{
		if(itms[i].cor.rotation == 1)		//if rotation == 1, length swaps places with width
		{
			int temp2;
			temp2 = itms[i].length;
			itms[i].length = itms[i].width;
			itms[i].width = temp2;
		}

		if((itms[i].length <= (BOXlength-Y)) && (itms[i].width <= (BOXwidth-X)))
		{
			itms[i].cor.x = X;
			itms[i].cor.y = Y;
			Y+=itms[i].length;
			nextX = max((X+itms[i].width), nextX);
		}
		else if(itms[i].length > (BOXlength-Y))
		{
			X = nextX;
			if(itms[i].width > (BOXwidth-X))
			{
				boxes = addBox(boxes, numOfBoxes);
				numOfBoxes+=1;
				itms[i].cor.x = 0;
				itms[i].cor.y = 0;
				X = 0;
				Y = itms[i].length;
				nextX = itms[i].width;
			}
			else
			{
				itms[i].cor.x = X;
				itms[i].cor.y = 0;
				Y = itms[i].length;
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
			Y = itms[i].length;
			nextX = itms[i].width;
		}
		itms[i].cor.boxNum = numOfBoxes;

		for(int k = itms[i].cor.y; k!=(itms[i].cor.y+itms[i].length); k++)	//fill up pixels in the box table with number assigned to the recently placed item
		{
			for(int m = itms[i].cor.x; m<(itms[i].cor.x+itms[i].width); m++)
			{
				boxes[numOfBoxes-1][k][m]=itms[i].number;
			}
		}

		if(itms[i].cor.rotation == 1)	//restore length and width to their right places in the structure
		{
			int temp2;
			temp2 = itms[i].length;
			itms[i].length = itms[i].width;
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
		Boxes[i] = new int *[BOXlength];
	for(int i = 0; i<numOfBoxs; i++)
	{
		for(int j = 0; j<BOXlength; j++)
		{
			Boxes[i][j] = new int [BOXwidth];
		}
	}

	for(int i = 0; i<(numOfBoxs-1); i++)	//assign old boxes to the new table of boxes
		for(int j = 0; j<BOXlength; j++)
			for(int k = 0; k<BOXwidth; k++)
				Boxes[i][j][k]=Boxs[i][j][k];

	for(int j = 0; j<BOXlength; j++)	//empty spaces fill up with zeros
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
		for(int i = 0; i<BOXlength; i++)
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
		Boxes[i] = new int *[BOXlength];
	for(int i = 0; i<numOfBoxs; i++)
	{
		for(int j = 0; j<BOXlength; j++)
		{
			Boxes[i][j] = new int [BOXwidth];
		}
	}

	for(int i = 0; i<numOfBoxs; i++)
		for(int j = 0; j<BOXlength; j++)
			for(int k = 0; k<BOXwidth; k++)
				Boxes[i][j][k]=0;

	return Boxes;
}

void deleteTableOfBoxes(int *** boxes, int numOfBoxs)
{
	for(int i = 0; i<numOfBoxs; i++)
	{
		for(int j = 0; j<BOXlength; j++)
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