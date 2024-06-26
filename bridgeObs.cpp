#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <time.h>
#include <vector>
#include <algorithm>
#include "bridge.h"
#include "obstacle.h"

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
int flashStep = 0;

char superman = 's';
int supermanXPosition = 3;
int supermanYPosition = height - 1;
int supermanLapLeft = 2;
bool supermanEnded = false;
int supermanStep = 0;

char batman = 'b'; //3-6
int batmanXPosition = 2;
int batmanYPosition = height - 1;
int batmanLapLeft = 2;
bool batmanEnded = false;
int batmanStep = 0;

//for counting
int step;
int flashLocation = 0;
int supermanLocation = 0;
int batmanLocation = 0;


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

    void straightLineBorder (int x, int y, vector<int> myXobstacle, Obstacle obstacle) { //|   |   |   |   |   |   |   | (depends on the x)
        bool printO = false;
        auto rx = find(obstacle.obstacleXLocation.begin(), obstacle.obstacleXLocation.end(), x);
        auto ry = find(obstacle.obstacleYLocation.begin(), obstacle.obstacleYLocation.end(), y);
        if (x%4 == 0) {
                cout << '|';
            } else if (x == flashXPosition && y == flashYPosition) {
            cout << flash;  
            } else if (x == supermanXPosition && y == supermanYPosition) {
            cout << superman;
            } else if (x == batmanXPosition && y == batmanYPosition) {
            cout << batman;
            } else if (rx != obstacle.obstacleXLocation.end() && ry != obstacle.obstacleYLocation.end()) {
                for (int i = 0; i<obstacle.obstacleNum; i++) {
                    if (x == obstacle.obstacleXLocation[i] && y == obstacle.obstacleYLocation[i]) {
                        cout << 'O';
                        printO = true;
                    }
                }
                if (printO == false) {
                    cout << ' ';
                }
            } else {
                cout << ' ';
            }
    }

    void straightLineNotBorder (int x, int y,vector<int> bridgeHeights, vector<int> myXobstacle, Obstacle obstacle) { //|   |                |   | (depends on x)
        bool printO = false;
        vector<int>::iterator rx = find(obstacle.obstacleXLocation.begin(), obstacle.obstacleXLocation.end(), x);
        vector<int>::iterator ry = find(obstacle.obstacleYLocation.begin(), obstacle.obstacleYLocation.end(), y);
        vector<int>::iterator r = find(bridgeHeights.begin(), bridgeHeights.end(), y);
        bool found = (r != bridgeHeights.end()) ? true : false;

        if ( x==0 || x == 4 && !found || x == width - 5 && !found || x==width - 1) {
            cout << '|';
        } else if (x == flashXPosition && y == flashYPosition) {
            cout << flash;    
        } else if (x == supermanXPosition && y == supermanYPosition) {
            cout << superman;
        } else if (x == batmanXPosition && y == batmanYPosition) {
            cout << batman;
        } else if (rx != obstacle.obstacleXLocation.end() && ry != obstacle.obstacleYLocation.end()) {
            for (int i = 0; i<obstacle.obstacleNum; i++) {
                if (x == obstacle.obstacleXLocation[i] && y == obstacle.obstacleYLocation[i]) {
                    cout << 'O';
                    printO = true;
                }
            }
            if (printO == false) {
                cout << ' ';
            } 
        } else {
            cout << ' ';
        }
    }
    
    public:

    void printLayout(Obstacle obstacle,vector<int> myXObstacle = {},
                vector<int> bridgeHeights = {}) {
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
                    straightLineBorder(x, y, myXObstacle,obstacle);
                }
                else {
                    straightLineNotBorder(x, y, bridgeHeights ,myXObstacle,obstacle);
                }
            }

            cout << '\n';
            //plusminus section
            for (int x = 0; x < width; x++) // +---+---+---
            {
                vector<int>::iterator r = find(bridgeHeights.begin(), bridgeHeights.end(), y + 1);
                bool found_bridgeYPlusOne = (r != bridgeHeights.end()) ? true : false; // bridge top

                r = find(bridgeHeights.begin(), bridgeHeights.end(), y); //bridge bot
                bool found_bridgeY = (r != bridgeHeights.end()) ? true : false;
                if (y == 0 || y == height - 2 || found_bridgeYPlusOne
                    || found_bridgeY || y == height - 1)
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
        cout << endl << "Draw!" << endl;
        gameRunning = false;
    } else if (supermanLocation == flashLocation && flashEnded == true && supermanEnded == true)
    {
        cout << endl << "Draw!" << endl;
        gameRunning = false;
    } else if (supermanLocation == batmanLocation && batmanEnded == true && supermanEnded == true)
    {
        cout << endl << "Draw!" << endl;
        gameRunning = false;
    } else if (batmanLocation == flashLocation && flashEnded == true && batmanEnded == true)
    {
        cout << endl << "Draw!" << endl;
        gameRunning = false;
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
        roundLeft -= 1;
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
        cout << endl << "Number of Lap: ";
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
    cout << "Flash move " << step << " steps." << endl;
    cout << "Flash lap remaining: " << flashLapLeft << endl << endl;
    
    logic(1,flashLocation,flashXPosition,flashYPosition,flashLapLeft,flashEnded);
}

void supermanMove()
{
    srand(time(0));
    step = 3 + (rand() % 3); //3 - 5
    supermanLocation += step;
    cout << "Superman move " << step << " steps." << endl;
    cout << "Superman lap remaining: " << supermanLapLeft << endl << endl;
    
    logic(3,supermanLocation,supermanXPosition,supermanYPosition,supermanLapLeft,supermanEnded);
}

void batmanMove()
{
    srand(time(0));
    step = 3 + (rand() % 4); //3 - 6
    batmanLocation += step;
    cout << endl << "Batman move " << step << " steps." << endl;
    cout << "Batman lap remaining: " << batmanLapLeft << endl << endl;
    
    logic(2,batmanLocation,batmanXPosition,batmanYPosition,batmanLapLeft,batmanEnded);
}

void checkObstacleAfterBridge(Obstacle obstacle) {
    supermanXPosition -= 1;
    flashXPosition += 1;
    obstacle.checkObstacle(batmanStep, 2, batmanXPosition,
                            batmanYPosition, batmanLocation, "Batman");
    obstacle.checkObstacle(supermanStep, 3, supermanXPosition, 
                            supermanYPosition, supermanLocation, "Superman");
    obstacle.checkObstacle(flashStep, 1, flashXPosition, 
                            flashYPosition, flashLocation, "Flash");
}

int main()
{
    string confirmation;
    layout l;
    box_inquiry();
    Bridge bridge(width, height, box, topLeftCoordinate, topRightCoordinate, botRightCoordinate);
    Obstacle obstacle(width, height, box, topLeftCoordinate, topRightCoordinate, botRightCoordinate);
    l.printLayout(obstacle);
    lap_inquiry();
    bridge.bridgeYValues = bridge.bridge_inquiry();
    obstacle.obstacleLocation = obstacle.obstacle_inquiry();
    obstacle.obstacleXYPosition(obstacle.obstacleLocation);
    obstacle.printObstacleInfo();
    l.printLayout(obstacle,obstacle.obstacleLocation,bridge.bridgeYValues);
    cout << endl;
    while (gameRunning) {
        // this_thread::sleep_for(milliseconds(1300)); //pause for 1.3sec
        cin.get();
        batmanMove();
        batmanStep = step;
        supermanMove();
        supermanStep = step;
        flashMove();
        flashStep = step;

        checkObstacleAfterBridge(obstacle);

        bridge.checkIfAtBridgeNMove(1, flashXPosition,
            flashYPosition, flashLocation);
        bridge.checkIfAtBridgeNMove(3, supermanXPosition,
            supermanYPosition, supermanLocation);
        bridge.checkIfAtBridgeNMove(2, batmanXPosition,
            batmanYPosition, batmanLocation);

        checkObstacleAfterBridge(obstacle);

        l.printLayout(obstacle,{},bridge.bridgeYValues);
        checkWinner();
        cout << endl;
    }
    cout << endl;
    system("pause");
}