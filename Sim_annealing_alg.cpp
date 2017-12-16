#include "Sim_annealing_alg.h"

using namespace std;

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
	Item oldItems[QUANTITY];
	
	ofstream Process;
	Process.open("Process.txt"); // the file where the process of the algorithm will be recorded
	Process << "B" << " " << "W" << " " << "T" << " " << "E" << " " << "N" << endl;

	Boxes1 = createTableOfBoxes(1);
	*numOfBoxs = 1;
	Boxes1 = placeItems(Boxes1, itms, numOfBoxs);
	EmptySpace1 = findEmptySpace(Boxes1[(*numOfBoxs)-1]);
	valueOfObjFun1 = objectiveFunction((*numOfBoxs), EmptySpace1);

	for(int temperature = TSTART; temperature > TMIN; temperature = lowerTemperature(temperature))
	{
		number1 = rand() % QUANTITY;
		number2 = rand() % QUANTITY;
		
		cout << "number1: " << number1 << endl;
		cout << "number2: " << number2 << endl;
		
		for(int i=0; i<QUANTITY; i++)
		{
			oldItems[i] = itms[i];
		}
		
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
			Process << "1 0 0 " << EmptySpace1 << "\t" << *numOfBoxs << endl;
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
				Process << "0 1 0 " << EmptySpace1 << "\t" << *numOfBoxs << endl;
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
				
				for(int i=0; i<QUANTITY; i++)
				{
					itms[i] = oldItems[i];
				}
				
				cout << "The same" << endl;
				Process << "0 0 1 " << EmptySpace1 << "\t" << *numOfBoxs << endl;
			}
		}
	}
	
	Process.close();
	return Boxes1;
}

int objectiveFunction(int numOfBoxs, int EmptySp)
{
	return (BOXwidth*numOfBoxs - EmptySp);
}

double probabilityFunction(int value1, int value2, int temp)
{
	return exp((value1 - value2) / (temp*(1.0/15.0)));
}

int lowerTemperature(int temp)
{
	return (0.99*temp);
}