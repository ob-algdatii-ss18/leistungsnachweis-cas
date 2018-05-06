//
// Created by chris on 27.04.18.
//

#include "RecursiveDivision.h"

using namespace ::std;

void helloFromRecDiv() {
    cout << "Hello, from Recursive Division" << endl;
};

int RecursiveDivision::testMethod() {
    return 3;
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
    if (width < 1 || height < 1) {
        throw std::invalid_argument("Maze width and height must be greater than 0");
    }

    auto** mazeField = new bool*[height];
    for (int i = 0; i < height; i++) {
        mazeField[i] = new bool[width];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            mazeField[i][j] = false;
        }
    }
    for (int i = 0; i < width; i++) {
        mazeField[0][i] = true;
    }
    for (int i = 0; i < width; i++) {
        mazeField[height - 1][i] = true;
    }
    for (int i = 0; i < height; i++) {
        mazeField[i][0] = true;
    }
    for (int i = 0; i < height; i++) {
        mazeField[i][width - 1] = true;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << (mazeField[i][j] ? "#" : ".");
        }
        cout << endl;
    }

    return mazeField;
}
