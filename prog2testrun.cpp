#include <iostream>
#include <time.h>

using namespace std;

enum Position {UP, DOWN, LEFT, RIGHT};

//configuration
int height = 3;
int width = 17;
bool gameRunning = true;
int box = 10;
int topRightCoordinate = 5;
int botRightCoordinate = 7;
int topLeftCoordinate = 2;

//flash
char flash = 'f';
int flashXPosition = 1;
int flashYPosition = height - 1;
Position flashSide = LEFT;

char superman = 's';
int supermanXPosition = 3;
int supermanYPosition = height - 1;
Position supermanSide = LEFT;

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
    if (flashLocation > topLeftCoordinate) { // if it will turn
        while (flashYPosition != 0) { // while it still not at top left yet
            flashYPosition -= 1;  //move up
            step -= 1;
        }
        flashXPosition += 4 * step; // move right
        flashSide = UP;
    } else { // if it stays at left
        flashYPosition -= step; //moveup only
    }
}

void topRight() {
    if (flashLocation > topRightCoordinate) { // if it will turn
        while (flashXPosition < (width - 5)) { // // while it still not at top right yet
            flashXPosition += 4; // move right 1 block
            step -= 1;
        }
        flashYPosition += step; //move down
        flashSide = RIGHT;
    } else { // if it stays at left
        flashXPosition += 4 * step; //moveup only
    }
}

void rightBottom() {
    if (flashLocation > botRightCoordinate) { // if it will turn
        while (flashYPosition != height - 1) { // while it still not at bottom right yet
            flashYPosition += 1;  //move down
            step -= 1;
        }
        flashXPosition -= 4 * step; // move left
        flashSide = DOWN;
    } else { // if it stays at right
        flashYPosition += step; //movedown only
    }
}

void bottomLeft() {
    if (flashLocation > box) { // if it will turn
        while (flashXPosition  > 4) { // while it still not at bottom left yet
            flashXPosition -= 4;  //move left
            step -= 1;
        }
        flashYPosition -= step; // move up
        gameRunning = false;
    } else if (flashLocation == box) { //if flash stop at excatly start point
        flashXPosition -= 4 * step;
        gameRunning = false;
    } else { // if it stays at bottom
        flashXPosition -= 4 * step; //moveleft only
    }
}

///

void sleftTop() {
    if (supermanLocation > topLeftCoordinate) { // if it will turn
        while (supermanYPosition != 0) { // while it still not at top left yet
            supermanYPosition -= 1;  //move up
            step -= 1;
        }
        supermanXPosition += 4 * step; // move right
        supermanSide = UP;
    } else { // if it stays at left
        supermanYPosition -= step; //moveup only
    }
}

void stopRight() {
    if (supermanLocation > topRightCoordinate) { // if it will turn
        while (supermanXPosition < (width - 5)) { // // while it still not at top right yet
            supermanXPosition += 4; // move right 1 block
            step -= 1;
        }
        supermanYPosition += step; //move down
        supermanSide = RIGHT;
    } else { // if it stays at left
        supermanXPosition += 4 * step; //moveup only
    }
}

void srightBottom() {
    if (supermanLocation > botRightCoordinate) { // if it will turn
        while (supermanYPosition != (height - 1)) { // while it still not at bottom right yet
            supermanYPosition += 1;  //move down
            step -= 1;
        }
        supermanXPosition -= 4 * step; // move left
        supermanSide = DOWN;
    } else { // if it stays at right
        supermanYPosition += step; //movedown only
    }
}

void sbottomLeft() {
    if (supermanLocation > box) { // if it will turn
        while (supermanXPosition  > 4) { // while it still not at bottom left yet
            supermanXPosition -= 4;  //move left
            step -= 1;
        }
        supermanYPosition -= step; // move up
        gameRunning = false;
    } else if (supermanLocation == box) { //if superman stop at excatly start point
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
    if (flashSide == LEFT) {
        leftTop();
    } else if (flashSide == UP) {
        topRight();
    } else if (flashSide == RIGHT) {
        rightBottom();
    } else if (flashSide == DOWN) {
        bottomLeft();
    }
    cout << flashXPosition << ' ' << flashYPosition << ' ' <<flashLocation << endl;
}

void supermanMove()
{
    srand(time(0));
    step = 3 + (rand() % 3); //3 - 5
    supermanLocation += step;
    if (supermanSide == LEFT) {
        sleftTop();
    } else if (supermanSide == UP) {
        stopRight();
    } else if (supermanSide == RIGHT) {
        srightBottom();
    } else if (supermanSide == DOWN) {
        sbottomLeft();
    }
    cout << supermanXPosition << ' ' << supermanYPosition << ' '<<' ' <<supermanLocation << endl;
}

void tobename() {
    int boxExtraNeeded;
    cin >> box;
    boxExtraNeeded = box - 10;
    while (boxExtraNeeded > 0) {
        height += 1;   // expand verticcal
        boxExtraNeeded -= 2;

        topLeftCoordinate ++;
        topRightCoordinate ++;
        botRightCoordinate += 2;

        if (boxExtraNeeded > 0) { 
            width += 4;  //(1 box = 4width (up and down)) expand horizontal
            boxExtraNeeded -= 2;

            topRightCoordinate ++;
            botRightCoordinate ++;
        }
    }
    flashYPosition = height - 1;
    supermanYPosition = height - 1;

    cout << topLeftCoordinate << topRightCoordinate << botRightCoordinate << endl;
}

int main()
{
    layout l;
    tobename();
    l.printLayout();
    while (gameRunning){
        getchar();
        flashMove();
        supermanMove();
        l.printLayout();
    }
}