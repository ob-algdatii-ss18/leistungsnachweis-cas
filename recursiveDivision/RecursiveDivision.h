//
// Created by chris on 27.04.18.
//

#ifndef LEISTUNGSNACHWEIS_CAS_RECURSIVEDIVISION_H
#define LEISTUNGSNACHWEIS_CAS_RECURSIVEDIVISION_H

#include <iostream>

void helloFromRecDiv();

class RecursiveDivision {
public:
    enum Orientation {
        HORIZONTAL, VERTICAL
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
};


#endif //LEISTUNGSNACHWEIS_CAS_RECURSIVEDIVISION_H
