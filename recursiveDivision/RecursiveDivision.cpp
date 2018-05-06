//
// Created by chris on 27.04.18.
//

#include "RecursiveDivision.h"
#include <ctime>
#include <random>

using namespace ::std;

RecursiveDivision::Orientation RecursiveDivision::chooseOrientation(int width, int height) {
    if (width < height) {
        return RecursiveDivision::HORIZONTAL;
    } else if (height < width) {
        return RecursiveDivision::VERTICAL;
    } else {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        double random = dist(mt);
        return random < 0.6 ? RecursiveDivision::HORIZONTAL : RecursiveDivision::VERTICAL;
    }
}

void helloFromRecDiv(){
    cout << "Hello, from Recursive Backtracking" << endl;
};

int RecursiveDivision::testMethod() {
    return 3;
}
