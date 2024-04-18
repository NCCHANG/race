#include <iostream>

using namespace std;

enum Position {UP, DOWN, LEFT, RIGHT};

//configuration
int height = 8;
int width = 33;

//flash
char flash = 'f';
int flashXPosition = 1;
int flashYPosition = height - 1;
Position flashPosition = LEFT;

//for counting
int step;
int flashLocation = 0;

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
            } else {
                cout << ' ';
            }
    }

    void straightLineNotBorder (int x, int y) { //|   |                |   | (depends on x)
        if ( x==0 || x==4 || x==width - 5 || x==width - 1) {
            cout << '|';
        } else if (x == flashXPosition && y == flashYPosition) {
            cout << flash;    
        }else {
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

// move logic section

void leftTop() {
    if (flashLocation > 7) {
        //if it moving from left to top
        //7 is coordinate of top left
        while (flashYPosition != 0) { // while it still not at top left yet
            flashYPosition -= 1;  //move up
            step -= 1;  //moved 1 step
        }
        flashXPosition += 4 * step; // move right
        flashPosition = UP;
    } else { // if it stays at left
        flashYPosition -= step; //moveup only
    }
}

void topRight() {
    if (flashLocation > 14) {
        //if it moving from top to right
        //14 is coordinate of top right
        while (flashXPosition != 29) {
            flashXPosition += 4; // move right 1 block
            step -= 1;  //moved 1 step
        }
        flashYPosition += step; //move down
        flashPosition = RIGHT;
    } else { // if it stays at left
        flashXPosition += 4 * step; //moveup only
    }
}

//

void flashMove()
{
    srand(time(0));
    step = 2 + (rand() % 5); // 2 - 6
    flashLocation += step;
    if (flashPosition == LEFT) {
        leftTop();
    } else if (flashPosition == UP) {
        topRight();
    }
    cout << flashXPosition << ' ' << flashYPosition << ' ' << flashLocation << endl;
}

int main()
{
    layout l;
    l.printLayout();
    while (true){
        getchar();
        flashMove();
        l.printLayout();
    }
}