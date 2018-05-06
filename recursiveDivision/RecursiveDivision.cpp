//
// Created by chris on 27.04.18.
//

#include "RecursiveDivision.h"

using namespace ::std;

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

void helloFromRecDiv() {
    cout << "Hello, from Recursive Division" << endl;
};

int RecursiveDivision::testMethod() {
    return 3;
}
