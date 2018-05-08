//
// Created by chris on 27.04.18.
//

#include "RecursiveDivision.h"
#include <time.h>

using namespace ::std;

int fieldWidth, fieldHeight;

void helloFromRecDiv() {
    cout << "Hello, from Recursive Division" << endl;
};

int RecursiveDivision::testMethod() {
    return 3;
}

int generateRandom(int lower, int upper) {
    return (rand() % ((upper + 1) - lower)) + lower;
}

void drawMaze(bool **field) {
    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            cout << (field[i][j] ? "#" : ".");
        }
        cout << endl;
    }
    cout << endl;
}

RecursiveDivision::Orientation RecursiveDivision::chooseOrientation(int width, int height) {
    if (width < height) {
        return RecursiveDivision::HORIZONTAL;
    } else if (height < width) {
        return RecursiveDivision::VERTICAL;
    } else {
        int random = rand() % 2;
        return random == 1 ? RecursiveDivision::HORIZONTAL : RecursiveDivision::VERTICAL;
    }
}

bool **RecursiveDivision::initMaze(int width, int height) {
    fieldHeight = height;
    fieldWidth = width;

    auto **mazeField = new bool *[fieldHeight];
    for (int i = 0; i < fieldHeight; i++) {
        mazeField[i] = new bool[fieldWidth];
    }

    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            mazeField[i][j] = false;
        }
    }

    return mazeField;
}

void RecursiveDivision::divideField(bool **field, int x, int y, int width, int height) {
    if (width < 3 || height < 3) {
        return;
    }
    drawMaze(field);

    int wallX, wallY;
    int passageX, passageY;
    int directionX, directionY;
    int length;

    // horizontal = true; vertical = false;
    int horizontal = chooseOrientation(width, height) - 1;

    // calculate coordinates where wall will be placed.
    wallX = x + (horizontal ? 0 : generateRandom(0, width - 2));
    wallY = y + (horizontal ? generateRandom(0, height - 2) : 0);

    // calculate coordinates of passage through the wall.
    passageX = wallX + (horizontal ? generateRandom(0, width) : 0);
    passageY = wallY + (horizontal ? 0 : generateRandom(0, height));

    directionX = horizontal;
    directionY = horizontal == 0;

    length = horizontal ? width : height;

    for (int index = 0; index < length; index++) {
        if ((wallX != passageX) || (wallY != passageY)) {
            field[wallY][wallX] = true;
        }
        wallX += directionX;
        wallY += directionY;
    }

    int nextX, nextY, nextWidth, nextHeight;

    nextX = x;
    nextY = y;
    nextWidth = (horizontal ? width : wallX - x + 1);
    nextHeight = (horizontal ? wallY - y + 1 : height);

    divideField(field, nextX, nextY, nextWidth, nextHeight);

    nextX = (horizontal ? x : wallX + 1);
    nextY = (horizontal ? wallY + 1 : y);
    nextWidth = (horizontal ? width : x + width - wallX - 1);
    nextHeight = (horizontal ? y + height - wallY - 1 : height);

    divideField(field, nextX, nextY, nextWidth, nextHeight);
}

int RecursiveDivision::generateMaze() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int width, height;
    string input;
    cout << "What's the maze width? ";
    getline(cin, input);
    width = stoi(input);
    cout << "What's the maze height ";
    getline(cin, input);
    height = stoi(input);

    if ((height < 1) || (width < 1)) {
        cerr << "Maze dimensions must be positive!" << endl;
        exit(1);
    }

    auto *mazeField = initMaze(width, height);

    divideField(mazeField, 0, 0, width, height);

    return 0;
}
