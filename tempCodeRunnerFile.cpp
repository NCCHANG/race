

        obstacle.checkObstacle(batmanStep, 2, batmanXPosition, batmanYPosition, batmanLocation, "Batman");
        obstacle.checkObstacle(supermanStep, 3, supermanXPosition, supermanYPosition, supermanLocation, "Superman");
        obstacle.checkObstacle(flashStep, 1, flashXPosition, flashYPosition, flashLocation, "Flash");
        
        bridge.checkIfAtBridgeNMove(1, flashXPosition,
            flashYPosition, flashLocation);
        bridge.checkIfAtBridgeNMove(3, supermanXPosition,
            supermanYPosition, supermanLocation);
        bridge.checkIfAtBridgeNMove(2, batmanXPosition,
            batmanYPosition, batmanLocation);

        l.printLayout({},bridge.bridgeYValues);
        checkWinner();
        cout << endl;
    }
    cout << endl;
    system("pause");