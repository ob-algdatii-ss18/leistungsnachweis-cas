#ifndef LEISTUNGSNACHWEIS_CAS_RECURSIVEDIVISION_H
#define LEISTUNGSNACHWEIS_CAS_RECURSIVEDIVISION_H

#include <iostream>

void helloFromRecDiv();

class RecursiveDivision {
public:
    enum Orientation {
        VERTICAL = 1, HORIZONTAL = 2
    };

    int testMethod();

    /**
     * Choose the orientation of a new wall in a field.
     *
     * If height and width are equal the function choose the orientation via random number.
     * @param width width of the field
     * @param height height of the field
     * @return Orientation to use
     */
    RecursiveDivision::Orientation chooseOrientation(int width, int height);

    bool **initMaze(int width, int height);

    int generateMaze();

    void divideField(bool **field, int x, int y, int width, int height);

    void divideVertical(bool **field, int left, int right, int top, int bottom);

    void divideHorizontal(bool **field, int left, int right, int top, int bottom);

    void makeMazeOpening(bool **field, int rows, int cols);
};


#endif //LEISTUNGSNACHWEIS_CAS_RECURSIVEDIVISION_H
