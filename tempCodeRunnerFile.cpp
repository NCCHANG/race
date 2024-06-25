batmanMove();
        bonus.checkBonus(step, 2, batmanXPosition, batmanYPosition, batmanLocation, "Batman");
        supermanMove();
        supermanXPosition -= 1;
        bonus.checkBonus(step, 3, supermanXPosition, supermanYPosition, supermanLocation, "Superman");
        flashMove();
        flashXPosition += 1;
        bonus.checkBonus(step, 1, flashXPosition, flashYPosition, flashLocation, "Flash");