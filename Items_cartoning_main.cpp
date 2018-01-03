#include "Packing.h"
//#include "Display.h"
#include "Sim_annealing_alg.h"
#include "File_service.h"

using namespace std;

int main()
{
	/*Item items[QUANTITY] = {{1, 4, 2, {0, 0, 0, 0}}, {2, 3, 3, {0, 0, 0, 0}}, {3, 5, 3, {0, 0, 0, 0}}, {4, 9, 1, {0, 0, 0, 0}}, {5, 5, 2, {0, 0, 0, 0}}, {6, 8, 2, {0, 0, 0, 0}},
					 {7, 4, 1, {0, 0, 0, 0}}, {8, 5, 3, {0, 0, 0, 0}}, {9, 7, 2, {0, 0, 0, 0}}};*/
	
	Item items[QUANTITY];
	
	readItems("Items2.txt", items);
	
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
		cout << "height: " << items[i].length << ", width: " << items[i].width << endl;
		cout << "x: " << items[i].cor.x << ", y: " << items[i].cor.y << endl;
		cout << "rotation: " << items[i].cor.rotation << endl;
		cout << "boxNum: " << items[i].cor.boxNum << endl << endl;
	}
	
	writeBoxes("Boxes.txt", Boxes, numOfBoxes);
	
	Item items2[QUANTITY];
	int *** Boxes2 = createTableOfBoxes(1);
	int EmptySpace2;
	int numOfBoxes2;
	
	readItems("Items2_original.txt", items2);
	Boxes2 = placeItems(Boxes2, items2, &numOfBoxes2);
	writeBoxes("Boxes2.txt", Boxes2, numOfBoxes2);	
	
    //bag(Boxes, items, amountOfItems);
    //showBox(Boxes, numOfBoxes);
    //showResult(items);
    //showItems(items);
    return 0;
}