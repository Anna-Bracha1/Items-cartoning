#include "Packing.h"

using namespace std;

int *** placeItems(int *** boxes, Item * itms, int * numOfBoxs)
{
	int numOfBoxes = 1;
	int X = 0;
	int Y = 0;
	int X2 = 0;
	int Y2 = 0;
	int nextX = 0;
	int check = 0;
	int currentBox = 1;
	
	for(int i = 0; i<QUANTITY; i++)
	{
		if(itms[i].cor.rotation == 1)		//if rotation == 1, length swaps places with width
		{
			int temp2;
			temp2 = itms[i].length;
			itms[i].length = itms[i].width;
			itms[i].width = temp2;
		}
		
		/*for(currentBox=1; currentBox <= numOfBoxes; currentBox++)
		{
			X2 = 0;
			Y2 = 0;
			check = 0;
			
			for(int m = 0; m < BOXwidth; m++)
			{
				for(int k = 0; k < BOXlength; k++)
				{
					if(boxes[currentBox-1][k][m] == 0)
					{	
						check = 1;
						if((itms[i].length <= (BOXlength-Y2)) && (itms[i].width <= (BOXwidth-X2)))
						{
							for(int k2 = Y2; k2 < (Y2+itms[i].length); k2++)
							{
								for(int m2 = X2; m2 < (X2+itms[i].width); m2++)
								{
									if(boxes[currentBox-1][k2][m2] != 0)
									{
										check = 2;
										break;
									}
								}
								if(check == 2)
									break;
							}
							
							if(check == 1)
							{
								itms[i].cor.x = X2;
								itms[i].cor.y = Y2;
								break;
							}
							else
								check = 0;
						}
						else
							check = 0;
					}
					else
						Y2++;
				}
				
				if(check == 1)
					break;
				else
				{
					Y2 = 0;
					X2++;
				}
			}
			
			if(check == 1)
				break;
		}
		
		if(check != 1)
		{
			boxes = addBox(boxes, numOfBoxes);
			numOfBoxes+=1;
			itms[i].cor.x = 0;
			itms[i].cor.y = 0;
		}
		itms[i].cor.boxNum = currentBox;*/
		
					
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
		currentBox = numOfBoxes;

		for(int k = itms[i].cor.y; k!=(itms[i].cor.y+itms[i].length); k++)	//fill up pixels in the box table with number assigned to the recently placed item
		{
			for(int m = itms[i].cor.x; m<(itms[i].cor.x+itms[i].width); m++)
			{
				boxes[currentBox-1][k][m]=itms[i].number;
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