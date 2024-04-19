//FAILED LOLLLLLLLLLLLLL IGNORE DIS

#include <iostream>
#include <time.h>

using namespace std;

enum Position {UP, DOWN, LEFT, RIGHT};

//configuration
int height = 8;
int width = 33;
bool gameRunning = true;

//racer
racerClass flash('f',1);
racerClass superman('s',3);

//for counting
int step;

class racerClass {
    public:
    char object;
    int xPosition;
    int yPosition;
    int location;
    Position side;

    racerClass(char obj, int x, int y = height-1, int location = 0, Position side = LEFT) {
        object = obj;
        xPosition = x;
        yPosition = y;
        location = location;
        side = side;
    }
};

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
            } else if (x == superman.x && y == superman.y) {
            cout << superman.obj;  
            } else {
                cout << ' ';
            }
    }

    void straightLineNotBorder (int x, int y) { //|   |                |   | (depends on x)
        if ( x==0 || x==4 || x==width - 5 || x==width - 1) {
            cout << '|';
        } else if (x == superman.x && y == superman.y) {
            cout << superman.obj;    
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

void leftTop(racerClass racer) {
    if (racer.location > 7) {
        //7 is coordinate of top left
        while (racer.yPosition != 0) { // while it still not at top left yet
            racer.yPosition -= 1;  //move up
            step -= 1;  //moved 1 step
        }
        racer.xPosition += 4 * step; // move right
        racer.side = UP;
    } else { // if it stays at left
        racer.yPosition -= step; //moveup only
    }
}

void topRight(racerClass racer) {
    if (racer.location > 14) {
        //14 is coordinate of top right
        while (racer.xPosition < 28) {
            racer.xPosition += 4; // move right 1 block
            step -= 1;  //moved 1 step
        }
        racer.yPosition += step; //move down
        racer.side = RIGHT;
    } else { // if it stays at left
        racer.xPosition += 4 * step; //moveup only
    }
}

void rightBottom(racerClass racer) {
    if (racer.location > 21) {
        //21 is coordinate of bottom right
        while (racer.yPosition != 7) { // while it still not at bottom right yet
            racer.yPosition += 1;  //move down
            step -= 1;  //moved 1 step
        }
        racer.xPosition -= 4 * step; // move left
        racer.side = DOWN;
    } else { // if it stays at right
        racer.yPosition += step; //movedown only
    }
}

void bottomLeft(racerClass racer) {
    if (racer.location > 28) {
        //28 is coordinate of bottom left
        while (racer.xPosition > 4) { // while it still not at bottom left yet
            racer.xPosition -= 4;  //move left
            step -= 1;  //moved 1 step
        }
        racer.yPosition -= step; // move up
        gameRunning = false;
    } else if (racer.location == 28) { //if flash stop at excatly start point
        racer.xPosition -= 4 * step;
        gameRunning = false;
    } else { // if it stays at bottom
        racer.xPosition -= 4 * step; //moveleft only
    }
}

//

void flashMove()
{
    srand(time(0));
    step = 2 + (rand() % 5); // 2 - 6
    flash.location += step;
    if (flash.side == LEFT) {
        leftTop(flash);
    } else if (flash.side == UP) {
        topRight(flash);
    } else if (flash.side == RIGHT) {
        rightBottom(flash);
    } else if (flash.side == DOWN) {
        bottomLeft(flash);
    }
    cout << flash.xPosition << ' ' << flash.yPosition << ' ' << 
    flash.side <<' ' <<flash.location << endl;
}

void supermanMove()
{
    srand(time(0));
    step = 2 + (rand() % 5); // 2 - 6
    superman.location += step;
    if (superman.side == LEFT) {
        leftTop(superman);
    } else if (superman.side == UP) {
        topRight(superman);
    } else if (superman.side == RIGHT) {
        rightBottom(superman);
    } else if (superman.side == DOWN) {
        bottomLeft(superman);
    }
    cout << superman.xPosition << ' ' << superman.yPosition << ' ' << 
    superman.side <<' ' <<superman.location << endl;
}

int main()
{
    layout l;
    l.printLayout();
    while (gameRunning){
        getchar();
        system("CLS");
        supermanMove();
        l.printLayout();
    }
}