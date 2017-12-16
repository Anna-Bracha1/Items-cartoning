#include "Display.h"

void showBox(int ***Boxes, int numOfBoxes){
    for(int k=0; k<numOfBoxes; k++){
        for(int i=0; i<BOXwidth; i++){
            for(int j=0; j<BOXlength; j++){
                changeColor(Boxes[k][i][j]);
                cout.width(2);
                cout<<Boxes[k][i][j];
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
}

void changeColor(int numberOfItems){
    HANDLE hOut;
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (numberOfItems == 0)
        SetConsoleTextAttribute( hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    else
    switch (numberOfItems%6)
    {
        case 0: SetConsoleTextAttribute( hOut, FOREGROUND_RED );
                break;
        case 1: SetConsoleTextAttribute( hOut, FOREGROUND_BLUE );
                break;
        case 2: SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
                break;
        case 3: SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_RED);
                break;
        case 4: SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;
        case 5: SetConsoleTextAttribute( hOut, FOREGROUND_BLUE | FOREGROUND_RED);
                break;
        default: SetConsoleTextAttribute( hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                break;
    }
}

void showResult(struct Item *items){
    cout<<"Number  ";
    cout<<"Coordinate x  ";
    cout<<"Coordinate y  ";
    cout<<"Rotation  ";
    cout<<"Number of Box";
    for(int i=0; i<QUANTITY; i++){
        cout<<endl;
        changeColor(items[i].number);
        cout.width(2); cout<<items[i].number;
        cout.width(10); cout<<items[i].cor.x;
        cout.width(14); cout<<items[i].cor.y;
        cout.width(14); cout<<items[i].cor.rotation;
        cout.width(12); cout<<items[i].cor.boxNum;
    }
    cout<<endl<<endl;
    changeColor(0);
}

void showItems(struct Item *items){
    cout<<"Number  ";
    cout<<"Length ";
    cout<<"Width \n";
    for(int i=1; i<=QUANTITY; i++){
        changeColor(i);
        cout.width(2); cout<<i;
        for(int j=0; j<QUANTITY; j++){
            if(items[j].number == i){
                cout.width(10); cout<<items[j].length;
                cout.width(6); cout<<items[j].width;
            }
        }
        cout<<endl;
    }
    changeColor(0);
}