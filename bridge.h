#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Bridge
{
    int width, height, box, topLeftCoordinate,
        topRightCoordinate, botRightCoordinate;
public:
    Bridge(int w, int h, int b, int tl, int tr, int br )
    {
        width = w;
        height = h;
        box = b;
        topLeftCoordinate = tl;
        topRightCoordinate = tr;
        botRightCoordinate = br;
    }

    vector<int> bridgeYValues;

    vector<int> bridge_inquiry()
    {
        vector<int> bridgeYValues;
        int n, yinput;

        do {
            cout << "How many bridges (3-5): ";
            cin >> n;
        } while (n < 3 || n > 5);

        for (int i = 0; i < n; i++)
        {
            do {
                cout << "Enter y from [1 to " << height - 2 //exclude top and bot
                    << "]: ";
                cin >> yinput;
            } while (yinput < 1 || yinput > height - 2);

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
        int racerY, int coordinateY)
    {
        int coordinate = 0;
        while (coordinate < box) {

            if (racerX == coordinateX && racerY == coordinateY) {
                break;
            }

            if ((coordinate >= topLeftCoordinate && coordinate < topRightCoordinate) || coordinate >= (topLeftCoordinate + box)) {
                coordinateX += 4;
            }
            else if (coordinate >= topRightCoordinate && coordinate < botRightCoordinate) {
                coordinateY += 1;
            }
            else if (coordinate >= botRightCoordinate && coordinate < box) {
                coordinateX -= 4;
            }
            else if (coordinate < topLeftCoordinate || (coordinate < (topLeftCoordinate + box) && coordinate >= box)) {
                coordinateY -= 1;
            }

            coordinate++;

        }
        return coordinate;
    }

    //oriX is the initial x value eg:1,2,3
    void checkIfAtBridgeNMove(int oriX, int& x, int y, int& location)
    {
        vector<int>::iterator r =
            find(bridgeYValues.begin(), bridgeYValues.end(), y);
        if (r != bridgeYValues.end())
        {
            switch (x)
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
            location = returnLocation(oriX, x, y, height-1);
        }
    }

};