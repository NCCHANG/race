#include <iostream>
#include <iomanip> // for setw
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <time.h>

using namespace std;
using namespace std::chrono;

//configuration
int height = 11;
int width = 49;
int widthhh = 35;

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

class RLayout {
public:
    void HorizontalEqual() {
        cout << setw(widthhh) << setfill('=') << "=" << endl;
    }

    void WelcomeMessage() {
        cout << setw(widthhh) << setfill(' ') << " Welcome To Player Registration!  " << endl;
    }

    void RegistrationLayout() {
        HorizontalEqual();

        WelcomeMessage();

        HorizontalEqual();
    }
}; 

class QLayout{
public:
    void HorizontalEqual() {
        cout << setw(widthhh) << setfill('=') << "=" << endl;
    }

    void WelcomeMessage() {
        cout << setw(widthhh) << setfill(' ') << " Game Start!            " << endl;
    }

    void StartLayout() {
        HorizontalEqual();

        WelcomeMessage();

        HorizontalEqual();
    }
    
};

struct Player {
    string name;
    string email;
    string racer;
};

void Users(vector<Player>& userslist) {
    string batman = "batman";
    string flash = "flash";
    string superman = "superman";
    
    for (int i = 0; i < 3; i++) {
        string name, email, racer;
        
        cout << "\n" ;
        cout << "User " << i+1 << "\n" ;
        
        cout << "Enter Name: ";
        getline(cin, name);
        
        cout << "Enter Email : ";
        getline(cin, email);
        
        do{
            cout << "Select your racer (Batman, Flash, Superman): ";
            getline(cin, racer);
            
        if(racer != batman && racer != flash && racer != superman ){
            cout << "The racer u hv chosen is not available. Please ur racer again!" << "\n" ;
            }
        }while (racer != batman && racer != flash && racer != superman );
        
        
        userslist.push_back({name, email, racer});
    }
}

void PrintRegisteredUser(const vector<Player>& userslist){
    for(const Player& user : userslist){
        cout << "Great! User " << user.name << ", you have chosen " << user.racer << " as your racer!" << "\n" ;
    }
}

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

    void straightLineNotBorder (int x, int y) { //|   |                |   | (depends on x)
        if ( x==0 || x==4 || x==width - 5 || x==width - 1) {
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

void checkWinner(const std::vector<Player>& userslist) //rmb to accept userlists as parameterrrrrr!!!
{
    if (flashLocation > supermanLocation && flashLocation > batmanLocation && flashEnded == true) {
        cout << endl << "Flash Won!" << endl;
        gameRunning = false;
        for(const Player&user : userslist){
            if(user.racer == "flash"){
                cout << "Congrats player "<< user.name << "!" << "Your racer Flash has won the race !" << "\n" ;
                return;
            }
        }
    } else if (supermanLocation > flashLocation && supermanLocation > batmanLocation && supermanEnded == true) {
        cout << endl << "Superman Won!" << endl;
        gameRunning = false;
        for(const Player&user : userslist){
            if(user.racer == "superman"){
                cout << "Congrats player "<< user.name << "!" << "Your racer Superman has won the race!" << "\n";
                return;
            }
        }
    } else if (batmanLocation > supermanLocation && batmanLocation > flashLocation && batmanEnded == true) {
        cout << endl << "Batman Won!" << endl;
        gameRunning = false;
        for(const Player&user : userslist){
            if (user.racer == "batman"){
                cout << "Congrats player "<< user.name << "!" << "Your racer Batman has won the race!" << "\n";
                return;
            }
        }
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

void GameStart(){
        QLayout q;
        q.StartLayout();
}

int main()
{
    RLayout s;
    s.RegistrationLayout();
    cout << "Please complete the following steps to register." << "\n";
    
    vector<Player> users;
    Users(users);
    cout << "\n" ;
    PrintRegisteredUser(users);
    cout << "\n" ;
    GameStart();
    
    string confirmation;
    layout l;
    box_inquiry();
    lap_inquiry();
    l.printLayout();
    while (gameRunning) {
        this_thread::sleep_for(milliseconds(1300)); //pause for 1.3sec
        flashMove();
        supermanMove();
        batmanMove();
        checkWinner(users);
        l.printLayout();
    }
    cout << endl;
    system("pause");
}
