#include <iostream>
#include <time.h>

using namespace std;

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

char superman = 's';
int supermanXPosition = 3;
int supermanYPosition = height - 1;

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

void logic(int coordinateX, int location, int &racerX, int &racerY, int coordinateY = height - 1) {
    int coordinate = 0;
    while (coordinate < box) {
    if (coordinate >= topLeftCoordinate && coordinate < topRightCoordinate){
        coordinateX += 4;
    } else if (coordinate >= topRightCoordinate && coordinate < botRightCoordinate) {
        coordinateY += 1;
    }  else if (coordinate >= botRightCoordinate && coordinate < box)  {
        coordinateX -= 4;
    } else if (coordinate < topLeftCoordinate){
        coordinateY -= 1;
    }
    
    coordinate ++;

    if (location == coordinate) {
        racerX = coordinateX;
        racerY = coordinateY;
        break;
    }
    }
}

void box_inquiry() {
    int boxExtraNeeded;
    cout << "How many block do you need? (minimum 10 box and must be even number):" ;
    cin >> box;
    if (box % 2 != 0 || box < 10){
        cout << "Please enter a valid block amount!" << endl;
        box_inquiry();
    }
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
}

void checkGameCondition()
{
    if (flashLocation > box) {
        cout << endl << "Flash Won!";
        gameRunning = false;
    } else if (supermanLocation > box) {
        cout << endl << "Superman Won!";
        gameRunning = false;
    }
}

void flashMove()
{
    srand(time(0));
    step = 2 + (rand() % 5); // 2 - 6
    flashLocation += step;
    
    logic(1,flashLocation,flashXPosition,flashYPosition);
}

void supermanMove()
{
    srand(time(0));
    step = 3 + (rand() % 3); //3 - 5
    supermanLocation += step;
    
    logic(3,supermanLocation,supermanXPosition,supermanYPosition);
}

int main()
{
    string confirmation;
    layout l;
    box_inquiry();
    l.printLayout();
    while (gameRunning) {
        do {
            cout << endl <<"press y to run: ";
            cin >> confirmation;
        } while (confirmation != "y");

        flashMove();
        supermanMove();
        l.printLayout();
        checkGameCondition();
    }
    cout << endl;
    system("pause");
}