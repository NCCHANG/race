#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <thread>
#include <time.h>

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

//for counting
int step;
int flashLocation = 0;
int supermanLocation = 0;
int batmanLocation = 0;

struct Bridge
{
    vector<int> bridgeYValues;

    vector<int> bridge_inquiry() 
    {
        vector<int> bridgeYValues;
        int n, yinput;
        
        do {
            cout << "How many bridges (3-5): ";
            cin >> n;
        } while(n < 3 || n > 5);

        for(int i = 0; i < n; i++)
        {
            cout << "Enter y from [1 to " << height - 2 //exclude top and bot
                << "]: "; 
            cin >> yinput;
            if (yinput < 1 || yinput > height - 2)
            {
                cout << "WARNING! MAKE SURE THE NUMBER IS IN RANGE!\n";
                i--;
                continue;
            }
            bridgeYValues.push_back(yinput);
        }
        return bridgeYValues;
    }

    int returnLocation(int coordinateX, int racerX,
             int racerY, int coordinateY = height - 1)
    {
    int coordinate = 0;
    while (coordinate < (box + 10)) {

        if (racerX == coordinateX && racerY == coordinateY) {
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
        return coordinate;
    }

    //oriX is the initial x value eg:1,2,3
    void checkIfAtBridgeNMove(int oriX,int& x, int y, int& location)
    {
        vector<int>::iterator r = 
        find(bridgeYValues.begin(),bridgeYValues.end(),y);
        if (r != bridgeYValues.end())
        {
            switch(x)
            {
                case 1:
                x = width - 4;
                break;
                case 2:
                x = width - 3;
                break;
                case 3:
                x = width - 2;
                break;
            }
            location = returnLocation(oriX,x,y);
        }
    }

} bridge;

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
            cout << superman;
            } else if (x == batmanXPosition && y == batmanYPosition) {
            cout << batman;
            } else {
                cout << ' ';
            }
    }

    void straightLineNotBorder (int x, int y, vector<int> bridgeHeights) { //|   |                |   | (depends on x)
        
        vector<int>::iterator r = find(bridgeHeights.begin(),bridgeHeights.end(),y);
        bool found = (r != bridgeHeights.end()) ? true : false;

        if ( x==0 || x==4 && !found || x==width - 5 && !found || x==width - 1) {
            cout << '|';
        } else if (x == flashXPosition && y == flashYPosition) {
            cout << flash;    
        } else if (x == supermanXPosition && y == supermanYPosition) {
            cout << superman;
        } else if (x == batmanXPosition && y == batmanYPosition) {
            cout << batman;
        }
        else {
            cout << ' ';
        }
    }
    
    public:

    void printLayout(vector<int> bridgeHeights = {}) {
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
                    straightLineNotBorder(x, y, bridgeHeights);
                }
            }

            cout << '\n';
            //plusminus section
            for (int x = 0; x < width; x++) // +---+---+---
            {
                vector<int>::iterator r = find(bridgeHeights.begin(),bridgeHeights.end(),y+1);
                bool found_bridgeYPlusOne = (r != bridgeHeights.end()) ? true : false; // bridge top

                r = find(bridgeHeights.begin(),bridgeHeights.end(),y); //bridge bot
                bool found_bridgeY = (r != bridgeHeights.end()) ? true : false;
                if (y==0 || y==height-2 || found_bridgeYPlusOne
                || found_bridgeY || y==height-1)
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
    l.printLayout();
    cout << '\n';
    lap_inquiry();
    bridge.bridgeYValues = bridge.bridge_inquiry();
    l.printLayout(bridge.bridgeYValues);
    while (gameRunning) {
        this_thread::sleep_for(milliseconds(1300)); //pause for 1.3sec
        flashMove();
        supermanMove();
        batmanMove();
        bridge.checkIfAtBridgeNMove(1,flashXPosition,
                                flashYPosition,flashLocation);
        bridge.checkIfAtBridgeNMove(3,supermanXPosition,
                                supermanYPosition,supermanLocation);
        bridge.checkIfAtBridgeNMove(2,batmanXPosition,
                                batmanYPosition,batmanLocation);
        checkWinner();
        l.printLayout(bridge.bridgeYValues);
    }
    cout << endl;
    system("pause");
}