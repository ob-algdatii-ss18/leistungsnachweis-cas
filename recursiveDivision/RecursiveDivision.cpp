#include "RecursiveDivision.h"

using namespace ::std;

int fieldWidth, fieldHeight;

int RecursiveDivision::generateRandomInt(int lower, int upper) {
    int diff = upper - lower;

    if (diff < 1) {
        diff = 1;
    }
    int random = (rand() % diff) + lower;
    return random;
}

bool RecursiveDivision::generateRandomBoolean() {
    return rand() % 2 == 0;
}

void RecursiveDivision::drawMaze(bool **field, std::ostream &output) {
    if (debugMode) {
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                output << (field[i][j] ? "#" : " ");
            }
            output << endl;
        }
        output << endl;
    } else {
        labPrinter->setLab(field);
        labPrinter->graphToPic("jpe");
    }
}

void RecursiveDivision::makeMazeOpening(bool **field, int rows, int cols) {
    int start = generateRandomInt(0, (rows - 1)) * 2 + 1;
    int end = generateRandomInt(0, (rows - 1)) * 2 + 1;

    field[start][0] = false;
    field[end][cols - 1] = false;
}

void RecursiveDivision::divideVertical(bool **field, int left, int right, int top, int bottom) {
    int divide = left + generateRandomInt(0, ((right - left - 2) / 2)) * 2;
    if (divide % 2 == 1)
        divide++;

    for (int i = top; i <= bottom; i++) {
        field[i][divide] = true;
    }

    int clearSpace = top + generateRandomInt(0, ((bottom - top) / 2)) * 2;
    if (clearSpace % 2 == 0)
        clearSpace++;

    field[clearSpace][divide] = false;

    divideField(field, left, divide - 1, top, bottom);
    divideField(field, divide + 1, right, top, bottom);
}

void RecursiveDivision::divideHorizontal(bool **field, int left, int right, int top, int bottom) {
    int divide = top + generateRandomInt(0, ((bottom - top - 2) / 2)) * 2;

    if (divide % 2 == 1)
        divide++;

    for (int i = left; i <= right; i++) {
        field[divide][i] = true;
    }

    int clearSpace = left + generateRandomInt(0, ((right - left) / 2)) * 2;
    if (clearSpace % 2 == 0)
        clearSpace++;

    field[divide][clearSpace] = false;

    divideField(field, left, right, top, divide - 1);
    divideField(field, left, right, divide + 1, bottom);
}

void RecursiveDivision::divideField(bool **field, int left, int right, int top, int bottom) {
    int width, height;

    width = right - left;
    height = bottom - top;

    drawMaze(field, std::cout);

    if (width > 2 && height > 2) {
        if (width > height) {
            divideVertical(field, left, right, top, bottom);
        } else if (height > width) {
            divideHorizontal(field, left, right, top, bottom);
        } else if (height == width) {
            bool verticalDivision = generateRandomBoolean();

            if (verticalDivision) {
                divideVertical(field, left, right, top, bottom);
            } else {
                divideHorizontal(field, left, right, top, bottom);
            }
        }
    } else if (width > 2 && height <= 2) {
        divideVertical(field, left, right, top, bottom);
    } else if (width <= 2 && height > 2) {
        divideHorizontal(field, left, right, top, bottom);
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

    for (int i = 0; i < fieldHeight; i++) {
        mazeField[i][0] = true;
        mazeField[i][fieldWidth - 1] = true;
    }
    for (int j = 0; j < fieldWidth; j++) {
        mazeField[0][j] = true;
        mazeField[fieldHeight - 1][j] = true;

    }

    return mazeField;
}

int RecursiveDivision::generateMaze() {

    /**
     * Enable Debug mode for maze printing:
     */
    //debugMode = true;
    labPrinter = new LabGraph();
    srand(static_cast<unsigned int>(time(nullptr)));

    int width, cols, height, rows;
    string input;

    cout << "How many cols? ";
    getline(cin, input);
    cols = stoi(input);

    cout << "How many rows? ";
    getline(cin, input);
    rows = stoi(input);

    if ((cols < 1) || (rows < 1)) {
        cerr << "Maze dimensions must be positive!" << endl;
        exit(1);
    }

    width = cols * 2 + 2;
    height = rows * 2 + 2;
    labPrinter->setDimensions(width, height);
    auto *mazeField = initMaze(width, height);

    divideField(mazeField, 1, width - 1, 1, height - 1);

    makeMazeOpening(mazeField, rows, width);

    // Enabled for printing result
    debugMode = true;
    drawMaze(mazeField, std::cout);
    labPrinter->setLab(mazeField);
    labPrinter->graphToPic("jpe");
    labPrinter->graphToPic("bnp");
    labPrinter->makeVideo();
    return 0;
}
