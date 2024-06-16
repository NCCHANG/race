class Obstacle {

    public:

    int obstacleNum, temp = 0;
    char abcFunc;
    int i = 0;
    int obstacleXPosition = 0, obstacleYPosition = 0;
    vector<int> obstacleLocation;
    vector<int> obstacleXLocation;
    vector<int> obstacleYLocation;
    vector<char> obstacleFunc;

    void calculateXY(int xCoordinate, int yCoordinate, int &racerLocation, int &racerxCoordinate, int &raceryCoordinate) {
        int coordinate = 0;
        while (coordinate < (box + 10)) {

            if (coordinate == racerLocation) {
                racerxCoordinate = xCoordinate; 
                raceryCoordinate = yCoordinate;
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
            
            coordinate++;
        } 
    }

    void moveBack3Step(int xCoordinate, int yCoordinate, int &racerLocation, int &racerxCoordinate, int &raceryCoordinate) {
        
        racerLocation = racerLocation - 3;
        calculateXY(xCoordinate, yCoordinate, racerLocation, racerxCoordinate, raceryCoordinate);
    }

    void backToInitial(int xCoordinate, int yCoordinate, int &racerLocation, int &racerxCoordinate, int &raceryCoordinate) {

        racerLocation = racerLocation - racerLocation;
        calculateXY(xCoordinate, yCoordinate, racerLocation, racerxCoordinate, raceryCoordinate);
    }

    void missTurn(int step, int xCoordinate, int yCoordinate, int &racerLocation, int &racerxCoordinate, int &raceryCoordinate) {
        
        racerLocation = racerLocation - step;
        calculateXY(xCoordinate, yCoordinate, racerLocation, racerxCoordinate, raceryCoordinate);
    }

    void checkObstacle(int step, int xInitial, int &racerXPosition, int &racerYPosition, int &racerLocation, string racername) {
        bool obstacleOccur = false;
        auto oX = find(obstacleXLocation.begin(), obstacleXLocation.end(), racerXPosition);
        auto oY = find(obstacleYLocation.begin(), obstacleYLocation.end(), racerYPosition);
        
        if (oX != obstacleXLocation.end() && oY != obstacleYLocation.end()) {
            for (int i = 0; i<obstacleNum; i++) {
                if ((racerXPosition == obstacleXLocation[i]) && racerYPosition == obstacleYLocation[i]) {
                    obstacleOccur = true;
                    switch(obstacleFunc[i]) {
                        case 'A':
                        case 'a':
                        moveBack3Step(xInitial, height-1, racerLocation, racerXPosition, racerYPosition);
                        cout << racername << " HIT OBSTACLE! " << racername << " move back 3 step" << endl << endl;
                        break;

                        case 'B':
                        case 'b':
                        backToInitial(xInitial, height-1, racerLocation, racerXPosition, racerYPosition);
                        cout << racername << " HIT OBSTACLE! " << racername << " move back to initial start point" << endl << endl;
                        break;

                        case 'C':
                        case 'c':
                        missTurn(step, xInitial, height-1, racerLocation, racerXPosition, racerYPosition);
                        cout << racername << " HIT OBSTACLE! " << racername << " miss his current turn" << endl << endl;
                        break;

                        default:
                        break;
                    }
                }
            }
        }
        if (obstacleOccur == false && racername == "Flash") {
            racerXPosition -= 1;
        } else if (obstacleOccur == false && racername == "Superman") {
            racerXPosition += 1;
        }
    }

    void obstacleXYPosition(vector<int> myXobstacle) {
        int xCoordinate = 2;
        int yCoordinate = height - 1;
        int coordinate = 0;
        while (coordinate < box) {

            if (myXobstacle[i] == coordinate) {
                obstacleXPosition = xCoordinate;
                obstacleYPosition = yCoordinate;
                obstacleXLocation.push_back(xCoordinate);
                obstacleYLocation.push_back(yCoordinate);
                i++;
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

    void obstacleFunc_inquiry() {
        cout << "Enter function for this obstacle (a = step back 3 step, b = back to start point, c = miss one trun): ";
        for (int i=0; i < obstacleNum; i++) { 
            cin >> abcFunc;
            tolower(abcFunc);
            if (abcFunc != 'a' || abcFunc != 'b' || abcFunc != 'c') {
                cout << "Please Enter A Correct Alphabet For This Obstacle! (a/b/c): ";
                cin >> abcFunc;
            }
            obstacleFunc.push_back(abcFunc);
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
            cout <<"Enter Obstacle location (1- " << box-1 << "): ";
        for (int i=0; i < obstacleNum; i++) { 
            cin >> temp;
            if (temp > box || temp <= 0) {
                cout << "Please Enter A Obstacle location ! (1- " << box-1 << "): ";
                cin >> temp;
            }
            obstacleLocation.push_back(temp);
        }
        obstacleFunc_inquiry();
        }
        return obstacleLocation;
    }

    void printObstacleInfo() { 
        int counter = 1;
        cout << endl;
        for (int i = 0; i<obstacleNum; i++) {
            switch(obstacleFunc[i]) {
                case 'A':
                case 'a':
                cout << "Obstacle " << counter << ":" << setw(2) << "  Location: " << obstacleLocation[i] << setw(3) << "  Function: Move Back 3 step" << endl;
                break;

                case 'B':
                case 'b':
                cout << "Obstacle " << counter << ":" << setw(2) << "  Location: " << obstacleLocation[i] << setw(3) << "  Function: Back To Initial Position" << endl;
                break;

                case 'C':
                case 'c':
                cout << "Obstacle " << counter << ":" << setw(2) << "  Location: " << obstacleLocation[i] << setw(3) << "  Function: Miss One Turn" << endl;
                break;

                default:
                cout << "Obstacle " << counter << ":" << setw(2) << "  Location: " << obstacleLocation[i] << setw(3) << "  Function: No Function since enter wrong value" << endl;
                break;
            }
            counter++;
        }
    }

} obstacle ; 