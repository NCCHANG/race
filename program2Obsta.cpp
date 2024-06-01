#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>
#include <vector>

using namespace std;
using namespace std::chrono;

//configuration
int height = 11;
int width = 49;

int box = 10;
int topRightCoordinate = 21;
int botRightCoordinate = 31;
int topLeftCoordinate = 10;

bool gameRunning = true;

//flash
char flash = 'f';
int flashXPosition = 1;
int flashYPosition = height - 1;
int flashLapLeft = 2;
bool flashEnded = false;

char superman = 's';
int supermanXPosition = 3;
int supermanYPosition = height - 1;
int supermanLapLeft = 2;
bool supermanEnded = false;

char batman = 'b'; //3-6
int batmanXPosition = 2;
int batmanYPosition = height - 1;
int batmanLapLeft = 2;
bool batmanEnded = false;

char obstacles = 'O';
int obstacleXPosition = 2;
int obstacleYPosition = height - 1;

//for counting
int step;
int flashLocation = 0;
int supermanLocation = 0;
int batmanLocation = 0;

struct Obstacle {

    int obstacleNum, temp, coordinate = 0;
    vector<int> myXObstacle;

    void obstacleDisplay(vector<int> myYobstacle, int xCoordinate, int yCoordinate, int i) {
        while (coordinate < box) {

            if (myYobstacle[i] == coordinate) {
                obstacleXPosition = xCoordinate;
                obstacleYPosition = yCoordinate;
                break;
            }

            if ((coordinate >= topLeftCoordinate && coordinate < topRightCoordinate) || coordinate >= (topLeftCoordinate + box)){
                xCoordinate += 4;
            } else if (coordinate >= topRightCoordinate && coordinate < botRightCoordinate) {
                yCoordinate += 1;
            }  else if (coordinate >= botRightCoordinate && coordinate < box)  {
                xCoordinate -= 4;
            } else if (coordinate < topLeftCoordinate ||(coordinate < (topLeftCoordinate + box) && coordinate >= box)){
                yCoordinate -= 1;
            }
            
            coordinate ++;

        }  
    }

    vector<int>  obstacle_inquiry() {
    
        cout << "How many Obstacle Do You Want (5-10): ";
        cin >> obstacleNum;
        if (obstacleNum < 5 || obstacleNum > 10){
            cout << "Please enter a valid Obstacle amount!" << endl;
            obstacle_inquiry();
        }
        else {
            cout <<"Enter Obstacle location: ";
        for (int i=0; i < obstacleNum; i++) { // Form vector
            cin >> temp;
            myXObstacle.push_back(temp);
        }

        for (int i=0; i < obstacleNum; i++) {  // For printing vector
            cout << myXObstacle[i] << ' ';
            }
        cout << endl;
    }
    return myXObstacle;
    }
} obstacle ; 

class layout {

    int box = height - 1;

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

    void straightLineBorder (int x, int y, vector<int> myYobstacle) { //|   |   |   |   |   |   |   | (depends on the x)
        int i = 0;
        obstacle.obstacleDisplay(myYobstacle, x, y, i);
        if (x%4 == 0) {
                cout << '|';
            } else if (x == flashXPosition && y == flashYPosition) {
            cout << flash;  
            } else if (x == supermanXPosition && y == supermanYPosition) {
            cout << superman;
            } else if (x == batmanXPosition && y == batmanYPosition) {
            cout << batman;
            } else if (x == obstacleXPosition && y == obstacleYPosition) {
            cout << obstacles;
            }
            else {
                cout << ' ';
            }
    }

    void straightLineNotBorder (int x, int y, vector<int> myYobstacle) { //|   |                |   | (depends on x)
        int i = 0;
        obstacle.obstacleDisplay(myYobstacle, x, y, i);
        if ( x==0 || x==4 || x==width - 5 || x==width - 1) {
            cout << '|';
        } else if (x == flashXPosition && y == flashYPosition) {
            cout << flash;    
        } else if (x == supermanXPosition && y == supermanYPosition) {
            cout << superman;
        } else if (x == batmanXPosition && y == batmanYPosition) {
            cout << batman;
        } else if (x == obstacleXPosition && y == obstacleYPosition) {
            cout << obstacles;
            }
        else {
            cout << ' ';
        }
        i++;
    }
    
    public:

    void printLayout(vector<int> myXObstacle = {}) {
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
                    straightLineBorder(x, y, myXObstacle);
                }
                else {
                    straightLineNotBorder(x, y, myXObstacle);
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

void checkWinner()
{
    if (flashLocation > supermanLocation && flashLocation > batmanLocation && flashEnded == true) {
        cout << endl << "Flash Won!" << endl;
        gameRunning = false;
    } else if (supermanLocation > flashLocation && supermanLocation > batmanLocation && supermanEnded == true) {
        cout << endl << "Superman Won!" << endl;
        gameRunning = false;
    } else if (batmanLocation > supermanLocation && batmanLocation > flashLocation && batmanEnded == true) {
        cout << endl << "Batman Won!" << endl;
        gameRunning = false;
    } else if ((batmanLocation == flashLocation == supermanLocation) && 
                (batmanEnded == true && flashEnded == true && supermanEnded == true))
    {
        cout << "Draw!";
    } else if (supermanLocation == flashLocation && flashEnded == true && supermanEnded == true)
    {
        cout << "Draw!";
    } else if (supermanLocation == batmanLocation && batmanEnded == true && supermanEnded == true)
    {
        cout << "Draw!";
    } else if (batmanLocation == flashLocation && flashEnded == true && batmanEnded == true)
    {
        cout << "Draw!";
    }
}

void logic(int coordinateX, int &racerlocation, int &racerX, int &racerY,
            int &roundLeft, bool &playerEnd, int coordinateY = height - 1) {
    int coordinate = 0;
    int ox = coordinateX;
    int oy = coordinateY;

    //check if round end
    if (racerlocation >= box && roundLeft != 1) {
        racerlocation -= box;
        roundLeft -= 1;
    } else if (racerlocation >= box && roundLeft == 1) {
        playerEnd = true;
    }
    //getting x and y for the coordination
    while (coordinate < (box + 10)) {

        if (racerlocation == coordinate) {
            racerX = coordinateX;
            racerY = coordinateY;
            break;
        }

        if ((coordinate >= topLeftCoordinate && coordinate < topRightCoordinate) || coordinate >= (topLeftCoordinate + box)){
            coordinateX += 4;
        } else if (coordinate >= topRightCoordinate && coordinate < botRightCoordinate) {
            coordinateY += 1;
        }  else if (coordinate >= botRightCoordinate && coordinate < box)  {
            coordinateX -= 4;
        } else if (coordinate < topLeftCoordinate ||(coordinate < (topLeftCoordinate + box) && coordinate >= box)){
            coordinateY -= 1;
        }
        
        coordinate ++;

    }  
}

void box_inquiry() {
    int boxExtraNeeded;
    cout << "How many block do you need? (minimum 42 box and must be even number):" ;
    cin >> box;
    if (box % 2 != 0 || box < 42){
        cout << "Please enter a valid block amount!" << endl;
        box_inquiry();
    }
    boxExtraNeeded = box - 42;
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
    batmanYPosition = height - 1;
}

void lap_inquiry() {
    int num_of_lap;
    do {
        cout << "Number of Lap: ";
        cin >> num_of_lap;
    } while (num_of_lap < 1);
    flashLapLeft = num_of_lap;
    supermanLapLeft = num_of_lap;
    batmanLapLeft = num_of_lap;
}

void flashMove()
{
    srand(time(0));
    step = 2 + (rand() % 5); // 2 - 6
    flashLocation += step;
    cout << endl << "Flash move " << step << " steps." << endl;
    
    logic(1,flashLocation,flashXPosition,flashYPosition,flashLapLeft,flashEnded);
}

void supermanMove()
{
    srand(time(0));
    step = 3 + (rand() % 3); //3 - 5
    supermanLocation += step;
    cout << "Superman move " << step << " steps." << endl;
    
    logic(3,supermanLocation,supermanXPosition,supermanYPosition,supermanLapLeft,supermanEnded);
}

void batmanMove()
{
    srand(time(0));
    step = 3 + (rand() % 4); //3 - 6
    batmanLocation += step;
    cout << "Batman move " << step << " steps." << endl;
    
    logic(2,batmanLocation,batmanXPosition,batmanYPosition,batmanLapLeft,batmanEnded);
}

int main()
{
    string confirmation;
    layout l;
    box_inquiry();
    lap_inquiry();
    obstacle.myXObstacle = obstacle.obstacle_inquiry();
    l.printLayout(obstacle.myXObstacle);
    while (gameRunning) {
        this_thread::sleep_for(milliseconds(1300)); //pause for 1.3sec
        flashMove();
        supermanMove();
        batmanMove();
        l.printLayout();
        checkWinner();
    }
    cout << endl;
    system("pause");
}