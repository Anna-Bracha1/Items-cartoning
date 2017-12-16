#include "Packing.h"
#include "Display.h"
#include "Sim_annealing_alg.h"

int main()
{
	Item items[QUANTITY] = {{1, 4, 2, {0, 0, 0, 0}}, {2, 3, 3, {0, 0, 0, 0}}, {3, 5, 3, {0, 0, 0, 0}}, {4, 9, 1, {0, 0, 0, 0}}, {5, 5, 2, {0, 0, 0, 0}}, {6, 8, 2, {0, 0, 0, 0}},
					 {7, 4, 1, {0, 0, 0, 0}}, {8, 5, 3, {0, 0, 0, 0}}, {9, 7, 2, {0, 0, 0, 0}}};
	int Order[QUANTITY] = {0};

    int amountOfItems = sizeof(items)/sizeof(items[0]);
	int *** Boxes;
	int EmptySpace;
	int numOfBoxes;

	Boxes = simAnnealingAlgorithm(items, &numOfBoxes, Order);
	EmptySpace = findEmptySpace(Boxes[numOfBoxes-1]);
	cout<<endl<<"EmptySpace: "<<EmptySpace<<endl<<endl;
    //bag(Boxes, items, amountOfItems);
    showBox(Boxes, numOfBoxes);
    showResult(items);
    showItems(items);
    return 0;
}