class Bonus {
    int width, height, box, topLeftCoordinate,
        topRightCoordinate, botRightCoordinate;

    public:

    Bonus(int w, int h, int b, int tl, int tr, int br )
    {
        width = w;
        height = h;
        box = b;
        topLeftCoordinate = tl;
        topRightCoordinate = tr;
        botRightCoordinate = br;
    }

    int bonusNum, temp = 0;
    char JKLFunc;
    int i = 0;
    int bonusXPosition = 0, bonusYPosition = 0;
    vector<int> bonusLocation;
    vector<int> bonusXLocation;
    vector<int> bonusYLocation;
    vector<int> bonusFunc;

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

    void moveForth(int xCoordinate, int yCoordinate, int &racerLocation, int &racerxCoordinate, int &raceryCoordinate) {
        
        racerLocation += 3;
        calculateXY(xCoordinate, yCoordinate, racerLocation, racerxCoordinate, raceryCoordinate);
    }

    void doubleSteps(int xCoordinate, int yCoordinate, int &racerLocation, int &racerxCoordinate, int &raceryCoordinate) {

        racerLocation *= 2;
        calculateXY(xCoordinate, yCoordinate, racerLocation, racerxCoordinate, raceryCoordinate);
    }

    void extraTurn(int step, int xCoordinate, int yCoordinate, int &racerLocation, int &racerxCoordinate, int &raceryCoordinate) {
        
        racerLocation += step;
        calculateXY(xCoordinate, yCoordinate, racerLocation, racerxCoordinate, raceryCoordinate);
    }

    void checkBonus(int step, int xInitial, int &racerXPosition, int &racerYPosition, int &racerLocation, string racername) {
        bool bonusHit = false;
        auto oX = find(bonusXLocation.begin(), bonusXLocation.end(), racerXPosition);
        auto oY = find(bonusYLocation.begin(), bonusYLocation.end(), racerYPosition);

        if (oX != bonusXLocation.end() && oY != bonusYLocation.end()) {
            for (int i = 0; i < bonusNum; i++) {
                if ((racerXPosition == bonusXLocation[i]) && racerYPosition == bonusYLocation[i]) {
                    bonusHit = true;
                    char choice;
                    cout << "Do you want to use the bonus item immediately? (y/n): ";
                    cin >> choice;
                    if (tolower(choice) == 'y') {
                        switch(bonusFunc[i]) {
                            case 'J':
                            case 'j':
                                moveForth(xInitial, height-1, racerLocation, racerXPosition, racerYPosition);
                                cout << racername << " used bonus item & moved forward 3 steps." << endl << endl;
                                break;
                            case 'K':
                            case 'k':
                                doubleSteps(xInitial, height-1, racerLocation, racerXPosition, racerYPosition);
                                cout << racername << " used bonus item & doubled their steps." << endl << endl;
                                break;
                            case 'L':
                            case 'l':
                                extraTurn(step, xInitial, height-1, racerLocation, racerXPosition, racerYPosition);
                                cout << racername << " used bonus item & got an extra turn." << endl << endl;
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }
        if (bonusHit == false && racername == "Flash") {
            racerXPosition -= 1;
        } else if (bonusHit == false && racername == "Superman") {
            racerXPosition += 1;
        }
    }


    void bonusXYPosition(vector<int> myXbonus) {
        int xCoordinate = 2;
        int yCoordinate = height - 1;
        int coordinate = 0;
        while (coordinate < box) {

            if (myXbonus[i] == coordinate) {
                bonusXPosition = xCoordinate;
                bonusYPosition = yCoordinate;
                bonusXLocation.push_back(xCoordinate);
                bonusYLocation.push_back(yCoordinate);
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

    void bonusFunc_inquiry() {
        cout << "Enter value for Bonus Item (j = Move forward 3 steps, k = Get double the move, l = Get an extra turn): ";
        for (int i=0; i < bonusNum; i++) { 
            cin >> JKLFunc;
            tolower(JKLFunc);
            bonusFunc.push_back(JKLFunc);
        }
    }

    bool ObstacleConflictFunc(const int temp, const Obstacle obstacle) {
        for (int Obsi = 0; Obsi < obstacle.obstacleLocation.size(); Obsi++) {
            if (temp == obstacle.obstacleLocation[Obsi]) {
                return true;
            }
        }
        return false;
    }

    vector<int>  bonus_inquiry(Obstacle obstacle) {
        bool obstacleConflict;
        cout << "Enter the desired total of Bonus Item for this game (2 to 6): ";
        cin >> bonusNum;
        if (bonusNum < 2 || bonusNum > 6){
            cout << "Please enter a Bonus Item amount that is within the range !" << endl;
            bonus_inquiry(obstacle);
        }
        else {
            cout <<"Enter Bonus Item location In Ascending Order (1 to " << box-1 << "): ";
        for (int i=0; i < bonusNum; i++) { 
            cin >> temp;
            obstacleConflict = ObstacleConflictFunc(temp, obstacle);
            if (obstacleConflict) {
                cout << "Obstacle is already using the location" << temp << '.' << endl;
                i--;
                continue;
            }
            bonusLocation.push_back(temp);
            
        }
        bonusFunc_inquiry();
        }
        return bonusLocation;
    }

    void printBonusInfo() { 
        int counter = 1;
        cout << endl;
        for (int i = 0; i<bonusNum; i++) {
            switch(bonusFunc[i]) {
                case 'J':
                case 'j':
                cout << "Bonus Item: " << counter << "  Function : Move forward 3 steps " << setw(2) << "  Location: " << bonusLocation[i] << endl;
                break;

                case 'K':
                case 'k':
                cout << "Bonus Item: " << counter << "  Function : Movement got doubled" << setw(2) << "  Location: " << bonusLocation[i] << endl;
                break;

                case 'L':
                case 'l':
                cout << "Bonus Item: " << counter << "  Function : Extra turn given " << setw(2) << "  Location: " << bonusLocation[i] << endl;
                break;

                default:
                cout << "Bonus Item: " << counter << "  No Bonus Item due to inserting invalid value " << setw(2) << "  Location: " << bonusLocation[i] << endl;
                break;
            }
            counter++;
        }
    }

};