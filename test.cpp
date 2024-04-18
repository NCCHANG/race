#include <iostream>
#include <time.h>

using namespace std;

int height = 8;
int width = 33;
char flash = 'f';
int flashXPosition = 1;
int flashYPosition = height - 1;
char superman = 'S';
int superManXPosition = 3;
int superManYPosition = height - 1;

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
            } else if (x== superManXPosition && y == superManYPosition)  {
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
        } else if (x== superManXPosition && y == superManYPosition)  {
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
    int random = 2 + (rand() % 4);
    static int totalBoxMoved = 0;
    totalBoxMoved = totalBoxMoved + random;
    cout << totalBoxMoved;
    cout << random << '\n';

    // This is for flash run for the left top
    if (flashYPosition != 0 && flashXPosition == 1) {
        if (totalBoxMoved >= 7 && flashYPosition != 0) {
            flashYPosition = flashYPosition - (random - (totalBoxMoved - 7));  
            flashXPosition = flashXPosition + (4 * (totalBoxMoved - 7));
        }
        else {
            flashYPosition = flashYPosition - random;
        }        
    }
    // If flash is at top
    else if (flashYPosition == 0 && flashXPosition == 1) {
        flashXPosition = flashXPosition + (4 * (totalBoxMoved - 7));
    }
    // If flash is at top right
    else if (flashXPosition != 29 && flashYPosition == 0) {
        if (totalBoxMoved >= 14) {
            flashXPosition = 29;
            // flashXPosition = flashXPosition + (4 * (totalBoxMoved - 14));
            flashYPosition = flashYPosition + ((totalBoxMoved - 14));
        }
        else {
            flashXPosition = flashXPosition + (4 * (14 - totalBoxMoved));
        }
    }
    // If flash is at rights
    else if (flashXPosition == 29 && flashYPosition != 0){
        flashYPosition = flashYPosition + ((totalBoxMoved - 14));
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
    while (i < 7) {
        startGameInput();
        i = i + 1;
    }

    return 0;
}