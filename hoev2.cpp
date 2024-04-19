#include <iostream>
#include <time.h>

using namespace std;

enum Position {UP, DOWN, LEFT, RIGHT};

//configuration
int height = 8;
int width = 33;
bool gameRunning = true;

//flash
char flash = 'f';
int flashXPosition = 1;
int flashYPosition = height - 1;
Position flashPosition = LEFT;

char superman = 's';
int supermanXPosition = 3;
int supermanYPosition = height - 1;
Position supermanPosition = LEFT;

//for counting
int step;
int flashLocation = 0;
int supermanLocation = 0;

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
            } else if (x == supermanXPosition && y == supermanYPosition) {
            cout << superman; }
            else {
                cout << ' ';
            }
    }

    void straightLineNotBorder (int x, int y) { //|   |                |   | (depends on x)
        if ( x==0 || x==4 || x==width - 5 || x==width - 1) {
            cout << '|';
        } else if (x == flashXPosition && y == flashYPosition) {
            cout << flash;    
        } else if (x == supermanXPosition && y == supermanYPosition) {
            cout << superman; }
        else {
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
        //14 is coordinate of top right
        while (flashXPosition < 28) {
            flashXPosition += 4; // move right 1 block
            step -= 1;  //moved 1 step
        }
        flashYPosition += step; //move down
        flashPosition = RIGHT;
    } else { // if it stays at left
        flashXPosition += 4 * step; //moveup only
    }
}

void rightBottom() {
    if (flashLocation > 21) {
        //21 is coordinate of bottom right
        while (flashYPosition != 7) { // while it still not at bottom right yet
            flashYPosition += 1;  //move down
            step -= 1;  //moved 1 step
        }
        flashXPosition -= 4 * step; // move left
        flashPosition = DOWN;
    } else { // if it stays at right
        flashYPosition += step; //movedown only
    }
}

void bottomLeft() {
    if (flashLocation > 28) {
        //28 is coordinate of bottom left
        while (flashXPosition  > 4) { // while it still not at bottom left yet
            flashXPosition -= 4;  //move left
            step -= 1;  //moved 1 step
        }
        flashYPosition -= step; // move up
        gameRunning = false;
    } else if (flashLocation == 28) { //if flash stop at excatly start point
        flashXPosition -= 4 * step;
        gameRunning = false;
    } else { // if it stays at bottom
        flashXPosition -= 4 * step; //moveleft only
    }
}

///

void sleftTop() {
    if (supermanLocation > 7) {
        //7 is coordinate of top left
        while (supermanYPosition != 0) { // while it still not at top left yet
            supermanYPosition -= 1;  //move up
            step -= 1;  //moved 1 step
        }
        supermanXPosition += 4 * step; // move right
        supermanPosition = UP;
    } else { // if it stays at left
        supermanYPosition -= step; //moveup only
    }
}

void stopRight() {
    if (supermanLocation > 14) {
        //14 is coordinate of top right
        while (supermanXPosition < 28) {
            supermanXPosition += 4; // move right 1 block
            step -= 1;  //moved 1 step
        }
        supermanYPosition += step; //move down
        supermanPosition = RIGHT;
    } else { // if it stays at left
        supermanXPosition += 4 * step; //moveup only
    }
}

void srightBottom() {
    if (supermanLocation > 21) {
        //21 is coordinate of bottom right
        while (supermanYPosition != 7) { // while it still not at bottom right yet
            supermanYPosition += 1;  //move down
            step -= 1;  //moved 1 step
        }
        supermanXPosition -= 4 * step; // move left
        supermanPosition = DOWN;
    } else { // if it stays at right
        supermanYPosition += step; //movedown only
    }
}

void sbottomLeft() {
    if (supermanLocation > 28) {
        //28 is coordinate of bottom left
        while (supermanXPosition  > 4) { // while it still not at bottom left yet
            supermanXPosition -= 4;  //move left
            step -= 1;  //moved 1 step
        }
        supermanYPosition -= step; // move up
        gameRunning = false;
    } else if (supermanLocation == 28) { //if superman stop at excatly start point
        supermanXPosition -= 4 * step;
        gameRunning = false;
    } else { // if it stays at bottom
        supermanXPosition -= 4 * step; //moveleft only
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
    } else if (flashPosition == RIGHT) {
        rightBottom();
    } else if (flashPosition == DOWN) {
        bottomLeft();
    }
    cout << flashXPosition << ' ' << flashYPosition << ' ' << 
    flashPosition <<' ' <<flashLocation << endl;
}

void supermanMove()
{
    srand(time(0));
    step = 3 + (rand() % 3); //3 - 5
    supermanLocation += step;
    if (supermanPosition == LEFT) {
        sleftTop();
    } else if (supermanPosition == UP) {
        stopRight();
    } else if (supermanPosition == RIGHT) {
        srightBottom();
    } else if (supermanPosition == DOWN) {
        sbottomLeft();
    }
    cout << supermanXPosition << ' ' << supermanYPosition << ' ' << 
    supermanPosition <<' ' <<supermanLocation << endl;
}

int main()
{
    layout l;
    l.printLayout();
    while (gameRunning){
        getchar();
        flashMove();
        supermanMove();
        l.printLayout();
    }
}