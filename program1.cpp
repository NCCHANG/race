#include <iostream>
#include <time.h>

using namespace std;

int height = 9;
int width = 37;
int boxNumEachRow = height - 1;
char flash = 'f';
int flashXPosition = 1;
int flashYPosition = height - 1;
char superman = 'S';
int supermanXPosition = 3;
int supermanYPosition = height - 1;

static int totalBoxMovedF = 0;
static int totalBoxMovedS = 0;

bool gameRunning = true;

class layout {
    void plusMinus(int x) { //+---+---+ (depends on the x)
        if (x%4 == 0) {
            cout << '+';
        } else {
            cout << '-';
        }
    }

    void plusMinusNotBorder(int x) { //+---+                +---+ (depends on the x)
        if ( x <= 4 || x >= width - 5) {
            plusMinus(x);
        } else {
            cout << ' ';
        }
    }

    void straightLineBorder (int x, int y) { //|   |   |   |   |   |   |   | (depends on the x)
        if (x%4 == 0) {
                cout << '|';
            } else if (x == flashXPosition && y == flashYPosition) {
            cout << flash;  
            } else if (x== supermanXPosition && y == supermanYPosition)  {
            cout << superman;
            } else {
                cout << ' ';
            }
    }

    void straightLineNotBorder (int x, int y) { //|   |                |   | (depends on x)
        if ( x==0 || x==4 || x==width - 5 || x==width - 1) {
            cout << '|';
        } else if (x == flashXPosition && y == flashYPosition) {
            cout << flash;    
        } else if (x== supermanXPosition && y == supermanYPosition)  {
            cout << superman;
        } else {
            cout << ' ';
        }
    }
    
    public:

    void printLayout() {
        for (int x = 0; x < width; x++) // +---+---+---
        {
            plusMinus(x);
        }


        for (int y = 0; y < height; y++)
        {
            cout << '\n';
            //|   |    | section
            for (int x = 0; x < width; x++) //|   |   |   |   | 
            {
                if (y == 0 || y == height-1) {
                    straightLineBorder(x, y);
                }
                else {
                    straightLineNotBorder(x, y);
                }
            }

            cout << '\n';
            //plusminus section
            for (int x = 0; x < width; x++) // +---+---+---
            {
                if (y==0 || y==height-2 || y==height-1)
                {
                    plusMinus(x);
                } else {
                    plusMinusNotBorder(x);
                }
            }
        }
    }
};

layout l;

void endGameCondition()
{
    if (totalBoxMovedF == totalBoxMovedS && totalBoxMovedF >= 32 && totalBoxMovedS >= 32) {
        flashYPosition = 8;
        flashXPosition = 1;
        supermanYPosition = 8;
        supermanXPosition = 3;
        cout << '\n' << "Game End" << endl;
        cout << "DRAW" << endl;
        cout << '\n' << "Flash Last Location At    " << totalBoxMovedF << endl;
        cout << "Superman Last Location At " << totalBoxMovedS << endl;
        gameRunning = false;
    }
    else if (totalBoxMovedF >= 32 && totalBoxMovedS < totalBoxMovedF) {
        flashYPosition = 8;
        flashXPosition = 1;
        supermanYPosition = 8;
        supermanXPosition = 3;
        cout << '\n' << "Game End" << endl;
        cout << "Flash Won!" << endl;
        cout << '\n' << "Flash Last Location At    " << totalBoxMovedF << endl;
        cout << "Superman Last Location At " << totalBoxMovedS << endl;
        gameRunning = false;
    }
    else if (totalBoxMovedS >= 32 && totalBoxMovedF < totalBoxMovedS){
        supermanYPosition = 8;
        supermanXPosition = 3;
        flashYPosition = 8;
        flashXPosition = 1;
        cout << '\n' << "Game End" << endl;
        cout << "Superman Won!" << endl;
        cout << '\n' << "Flash Last Location At    " << totalBoxMovedF << endl;
        cout << "Superman Last Location At " << totalBoxMovedS << endl;
        gameRunning = false;
    }
}

int flashStepLayout() {
    layout l;

    srand(time(0));
    int steps = 2 + (rand() % 5);
    totalBoxMovedF = totalBoxMovedF + steps;

    // This is for flash run from left column to top
    if (flashYPosition != 0 && flashXPosition == 1) {
        if (totalBoxMovedF >= boxNumEachRow && flashYPosition != 0) {
            flashYPosition = flashYPosition - (steps - (totalBoxMovedF - boxNumEachRow));  
            flashXPosition = flashXPosition + (4 * (totalBoxMovedF - boxNumEachRow));
        }
    // If flash is at left column
        else {
            flashYPosition = flashYPosition - steps;
        }        
    }
    // If flash is at top row (only enter this else if if flash is at top left box)
    else if (flashYPosition == 0 && flashXPosition == 1) {
        flashXPosition = flashXPosition + (4 * (totalBoxMovedF - boxNumEachRow));
    }
    // If flash go from top row to right column
    else if (flashXPosition != 33 && flashYPosition == 0) {
        if (totalBoxMovedF >= boxNumEachRow * 2) {
            flashXPosition = width - 4;
            flashYPosition = flashYPosition + (totalBoxMovedF - ((boxNumEachRow * 2)));
        }
    // If flash is at top row
        else {
            flashXPosition = flashXPosition + (4 * steps);  // ((boxNumEachRow * 2)  - totalBoxMoved)
        }
    }
    // If flash is from rights column to bottom row
    else if (flashXPosition == 33 && flashYPosition != boxNumEachRow){
        if (totalBoxMovedF >=  boxNumEachRow * 3) {
            flashYPosition = flashYPosition + (steps - (totalBoxMovedF - (boxNumEachRow * 3)));
            flashXPosition = flashXPosition - (4 * (totalBoxMovedF - (boxNumEachRow * 3)));
        }
    // If flash is at right column
        else {
            flashYPosition = flashYPosition + steps;  // (boxNumEachRow * 3 ) - totalBoxMoved
        }
    }
    // If flash at bottom row
    else if (flashYPosition == boxNumEachRow) {
        flashXPosition = flashXPosition - (4 * steps);
    }
    return 0;
}

void supermanStepLayout() {
    layout l;

    srand(time(0));
    int steps = 3 + (rand() % 3);
    totalBoxMovedS = totalBoxMovedS + steps;

    // This is for superman run from left column to top
    if (supermanYPosition != 0 && supermanXPosition == 3) {
        if (totalBoxMovedS >= boxNumEachRow && supermanYPosition != 0) {
            supermanYPosition = supermanYPosition - (steps - (totalBoxMovedS - boxNumEachRow));  
            supermanXPosition = supermanXPosition + (4 * (totalBoxMovedS - boxNumEachRow));
        }
    // If superman is at left column
        else {
            supermanYPosition = supermanYPosition - steps;
        }        
    }
    // If superman is at top row (only enter this else if if superman is at top left box)
    else if (supermanYPosition == 0 && supermanXPosition == 3) {
        supermanXPosition = supermanXPosition + (4 * (totalBoxMovedS - boxNumEachRow));
    }
    // If superman go from top row to right column
    else if (supermanXPosition != 35 && supermanYPosition == 0) {
        if (totalBoxMovedS >= boxNumEachRow * 2) {
            supermanXPosition = width - 2;
            supermanYPosition = supermanYPosition + (totalBoxMovedS - ((boxNumEachRow * 2)));
        }
    // If superman is at top row
        else {
            supermanXPosition = supermanXPosition + (4 * steps);  // ((boxNumEachRow * 2)  - totalBoxMoved)
        }
    }
    // If superman is from rights column to bottom row
    else if (supermanXPosition == 35 && supermanYPosition != boxNumEachRow){
        if (totalBoxMovedS >=  boxNumEachRow * 3) {
            supermanYPosition = supermanYPosition + (steps - (totalBoxMovedS - (boxNumEachRow * 3)));
            supermanXPosition = supermanXPosition - (4 * (totalBoxMovedS - (boxNumEachRow * 3)));
        }
    // If superman is at right column
        else {
            supermanYPosition = supermanYPosition + steps;  // (boxNumEachRow * 3 ) - totalBoxMoved
        }
    }
    // If superman at bottom row
    else if (supermanYPosition == boxNumEachRow) {
        supermanXPosition = supermanXPosition - (4 * steps);
    }
}

void startGameInput() {
        char start;
        cout << '\n' << "Flash Current Location At    " << totalBoxMovedF << endl;
        cout << "Superman Current Location At " << totalBoxMovedS << endl;
        cout << endl << "Enter y to start:";
        cin >> start;
    if (start == 'y') {
        cout << '\n' << '\n';
        flashStepLayout();
        supermanStepLayout();
        cout << endl;
    }
    else {
        cout << "Please enter y";
        return startGameInput();
    }
}

int main()
{
    layout l;
    l.printLayout();
    while (gameRunning == true) {
        startGameInput();
        endGameCondition();
        l.printLayout();
    }
    return 0;
}