#include "File_service.h"

using namespace std;

void readItems(const char * FileName, Item * itms)
{	
	cout << "Error0\n";
	ifstream ItemsFile;
	ItemsFile.open(FileName);
	
	cout << "Error1\n";
	int i=0;
	do
	{
		cout << "Error2\n";
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