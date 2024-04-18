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

int random = 2 + (rand() % 4);

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

void flashStepLayout() {
    layout l;

    srand(time(0));
    int steps = 2 + (rand() % 4);
    static int totalBoxMoved = 0;
    totalBoxMoved = totalBoxMoved + steps;
    cout << totalBoxMoved;
    cout << steps << '\n';

    // while (flashYPosition != 0 && flashXPosition == 0) {
    //     if (totalBoxMoved < 7) {
    //         flashYPosition = flashYPosition - totalBoxMoved;
    //     }
    //     else {
    //         while (flashYPosition == 0)
    //         if (flashYPosition == 0) {
    //             flashXPosition = flashXPosition + (4 * (totalBoxMoved - 7));
    //         }
    //     }
    // }


    // This is for flash run from left column to top
    if (flashYPosition != 0 && flashXPosition == 1) {
        if (totalBoxMoved >= boxNumEachRow && flashYPosition != 0) {
            flashYPosition = flashYPosition - (steps - (totalBoxMoved - boxNumEachRow));  
            flashXPosition = flashXPosition + (4 * (totalBoxMoved - boxNumEachRow));
        }
    // If flash is at left column
        else {
            flashYPosition = flashYPosition - steps;
        }        
    }
    // If flash is at top row (only enter this else if if flash is at top left box)
    else if (flashYPosition == 0 && flashXPosition == 1) {
        flashXPosition = flashXPosition + (4 * (totalBoxMoved - boxNumEachRow));
    }
    // If flash go from top row to right column
    else if (flashXPosition != 33 && flashYPosition == 0) {
        if (totalBoxMoved >= boxNumEachRow * 2) {
            flashXPosition = 33;
            flashYPosition = flashYPosition + (totalBoxMoved - ((boxNumEachRow * 2)));
        }
    // If flash is at top row
        else {
            flashXPosition = flashXPosition + (4 * steps);  // ((boxNumEachRow * 2)  - totalBoxMoved)
        }
    }
    // If flash is from rights column to bottom row
    else if (flashXPosition == 33 && flashYPosition != boxNumEachRow){
        if (totalBoxMoved >=  boxNumEachRow * 3) {
            flashYPosition = flashYPosition + (steps - (totalBoxMoved - (boxNumEachRow * 3)));
            flashXPosition = flashXPosition - (4 * (totalBoxMoved - (boxNumEachRow * 3)));
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
    // l.printLayout();
}

void supermanStepLayout() {
    layout l;

    srand(time(0));
    int steps = 3 + (rand() % 3);
    static int totalBoxMoved = 0;
    totalBoxMoved = totalBoxMoved + steps;
    cout << totalBoxMoved;
    cout << steps << '\n';

    // This is for superman run from left column to top
    if (supermanYPosition != 0 && supermanXPosition == 3) {
        if (totalBoxMoved >= boxNumEachRow && supermanYPosition != 0) {
            supermanYPosition = supermanYPosition - (steps - (totalBoxMoved - boxNumEachRow));  
            supermanXPosition = supermanXPosition + (4 * (totalBoxMoved - boxNumEachRow));
        }
    // If superman is at left column
        else {
            supermanYPosition = supermanYPosition - steps;
        }        
    }
    // If superman is at top row (only enter this else if if superman is at top left box)
    else if (supermanYPosition == 0 && supermanXPosition == 3) {
        supermanXPosition = supermanXPosition + (4 * (totalBoxMoved - boxNumEachRow));
    }
    // If superman go from top row to right column
    else if (supermanXPosition != 35 && supermanYPosition == 0) {
        if (totalBoxMoved >= boxNumEachRow * 2) {
            supermanXPosition = 35;
            supermanYPosition = supermanYPosition + (totalBoxMoved - ((boxNumEachRow * 2)));
        }
    // If superman is at top row
        else {
            supermanXPosition = supermanXPosition + (4 * steps);  // ((boxNumEachRow * 2)  - totalBoxMoved)
        }
    }
    // If superman is from rights column to bottom row
    else if (supermanXPosition == 35 && supermanYPosition != boxNumEachRow){
        if (totalBoxMoved >=  boxNumEachRow * 3) {
            supermanYPosition = supermanYPosition + (steps - (totalBoxMoved - (boxNumEachRow * 3)));
            supermanXPosition = supermanXPosition - (4 * (totalBoxMoved - (boxNumEachRow * 3)));
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
    l.printLayout();
}

void startGameInput() {
        char start;
        cout << '\n' << "Press Y to start:";
        cin >> start;
    if (start == 'Y') {
        cout << '\n' << '\n';
        flashStepLayout();
        supermanStepLayout();
        cout << '\n' << '\n';
    }
    else {
        cout << "Please enter Y";
    }
}

int main()
{
    int i = 0;
    layout l;
    l.printLayout();
    while (i < 10) {
        startGameInput();
        i = i + 1;
    }

    return 0;
}