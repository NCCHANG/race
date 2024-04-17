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


    void flashStepLayout() {
        srand(time(0));
        int random = 2 + (rand() % 4);
        static int totalRandomNum = 0;
        totalRandomNum = totalRandomNum + random;
        cout << totalRandomNum;
        cout << random << '\n';

        if (flashYPosition != 0 && flashXPosition == 1) {
            if (totalRandomNum >= 7 && flashYPosition != 0) {
                flashYPosition = flashYPosition - (random - (totalRandomNum - 7));
                flashXPosition = flashXPosition + (4 * (totalRandomNum - 7));
            }
            else {
                flashYPosition = flashYPosition - random;
            }        
            printLayout();
        }
        else if (flashYPosition == 0 && flashXPosition == 1) {
            flashXPosition = flashXPosition + (4 * (totalRandomNum - 7));
            printLayout();
        }
        else if (flashXPosition != 29 && flashYPosition == 0) {
            if (totalRandomNum >= 14) {
                flashXPosition = 29;
                // flashXPosition = flashXPosition + (4 * (totalRandomNum - 14));
                flashYPosition = flashYPosition + ((totalRandomNum - 14));
            }
            else {
                flashXPosition = flashXPosition + (4 * (14 - totalRandomNum));
            }
            printLayout();
        }
        else if (flashXPosition == 29 && flashYPosition != 0){
            flashYPosition = flashYPosition + ((totalRandomNum - 14));
            printLayout();
        }
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

};
int main()
{
    int i = 0;
    layout l;
    l.printLayout();
    while (i < 7) {
        l.startGameInput();
        i = i + 1;
    }

    return 0;
}