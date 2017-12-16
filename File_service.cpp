#include "File_service.h"

using namespace std;

void readItems(const char * FileName, Item * itms)
{	
	ifstream ItemsFile;
	ItemsFile.open(FileName);
	
	int i=0;
	do
	{
		ItemsFile >> itms[i].number;
		ItemsFile >> itms[i].length;
		ItemsFile >> itms[i].width;
		itms[i].cor.x = 0;
		itms[i].cor.y = 0;
		itms[i].cor.rotation = 0;
		itms[i].cor.boxNum = 0;
		cout << "Item " << itms[i].number << endl;
		cout << "height: " << itms[i].length << ", width: " << itms[i].width << endl;
		cout << "x: " << itms[i].cor.x << ", y: " << itms[i].cor.y << endl;
		cout << "rotation: " << itms[i].cor.rotation << endl;
		cout << "boxNum: " << itms[i].cor.boxNum << endl << endl;
		
		i++;
	} while(ItemsFile.good());
	
	ItemsFile.close();
}

void writeBoxes(const char * FileName, int *** boxes, int numOfBox)
{
	ofstream BoxesFile;
	BoxesFile.open(FileName);
	
	for(int i=0; i<numOfBox; i++)
	{
		for(int k=0; k<BOXlength; k++)
		{
			for(int m=0; m<BOXwidth; m++)
			{
				BoxesFile << boxes[i][k][m] << ' ';
			}
			BoxesFile << endl;
		}
		BoxesFile << endl;
	}
	
	BoxesFile.close();
}